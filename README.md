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

If you need to modify an object in the tree, you create a temporary object that points to the item in the `lvgl` tree.

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