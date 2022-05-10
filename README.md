# LvglAPI

The LvglAPI is a C++ wrapper library for the [lvgl embedded graphics library](https://lvgl.io/). The coding style follows the Stratify Labs [API framework](https://github.com/StratifyLabs/API) style.

## How to

The API uses the following pattern to add objects to the display:

```c++
#include <lvgl.hpp>
int my_draw_function(){
  screen()
    .add(List("myList")
           .set_width(90_percent)
           .set_height(100_percent)
           .add_button(LV_SYMBOL_OK, "", "OK")
           .add_button(LV_SYMBOL_LEFT, "", "LEFT")
           .add_button(LV_SYMBOL_RIGHT, "", "RIGHT")
           .add_button(LV_SYMBOL_UP, "", "UP")
           .add_button(LV_SYMBOL_DOWN, "", "DOWN"))
    .add(Button("myButton")
           .set_height(100_percent)
           .set_x(90_percent)
           .set_width(10_percent)
           .add_label(LV_SYMBOL_RIGHT));
}
```

In this example, we create `List()` and a `Button()` and add them to the currently active `screen()`. The underlying `lvgl` objects will persist in memory until they are explicitly removed from the tree.

Every object that is added to the screen is given a name. The name must be either a c-style string stored as a constant or a `lvgl::UserData` object (which also must have a name).

If you need to modify an object in the tree, you create a temporary object that points to the item in the `lvgl` tree. The `find` family of functions allows you to find named children.

```c++
screen().find<List>("myList").set_width(80_percent);
// or
auto list = screen().find<List>("myList");
list.set_width(80_percent);
```

When `list` is deconstructed, it will not delete "myList". If you want to remove an item from the tree, you must do so explicitly.

```c++
screen().find<List>("myList").remove();
//or delete all children -- recursively
screen().clean();
//trying to find a deleted item will cause the program to crash
//unless you specify IsAssertOnFail::no
auto list = screen().find<List, IsAssertOnFail::no>("myList");
if( list.is_valid() ){
    //list is OK
} else {
    //list doesn't exist
}
```

### Create Custom Objects

Use the following design patter to create custom objects:


```cpp
public MyList : public lvgl::ObjectAccess<MyList> {
public:
    //this macro is a shortcut for constructing my list from a name
    //or from an existing lv_obj_t
    LVGL_OBJECT_ACCESS_DECLARE_CONSTRUCTOR(MyList);
    
    //if you need to associated data with your object
    //you need to create a struct (or class) derived from lvgl::UserDataAccess<>
    
    struct Data : public lvgl::UserDataAccess<Data> {
        explicit Data(const char * name) : lvgl::UserDataAccess<Data>(name){}

        int my_list_variable = 0;
    };
    
    //you can add public or private member functions
    //but you CANNOT add any non-static data members
    //if you need non-static data members, put them in the Data struct
    
    
    lvgl::Button get_go_button(){
        return find<lvgl::Button>(Names::go_button);
    }
    
    
private:
    //use a Names struct for names of children added to MyList
    struct Names {
        static constexpr auto go_button = "GoButton";
    };
    
    static void go_button_clicked(lv_event_t * e){
        //use this for an event handler
    }
    
};


//to use the class
//`create` will dynmically allocate a MyList::Data object
//the data will be destructed and freed when the created object is removed
//from the screen.
screen().add(MyList(MyList::Data::create("MyList").cast_as_name()));

//you can also use a static version to avoid dynamic memory allocation
//this approach does not destruct or free the MyList::Data object
static MyList::Data my_list_data("MyStaticList");
screen().add(MyList(my_list_data.cast_as_name()));

auto my_list = screen().find<MyList>("MyList");
auto * my_data = my_list.user_data<MyList::Data>();

```