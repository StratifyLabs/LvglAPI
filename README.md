# LvglAPI

The LvglAPI is a C++ wrapper library for the [lvgl embedded graphics library](https://lvgl.io/). The coding style follows the Stratify Labs [API framework](https://github.com/StratifyLabs/API) style.

## How to

The API uses the following pattern to add objects to the display:

```c++
#include <lvgl.hpp>

//The add function looks like this for adding a List to a Container
Container & add(List & list, void (*configure_callback)(List & list));

int my_draw_function(){

  static const List::Context my_list_context{"MyList"};

  //here we use a lambda function to pass the configure callback
  //The callback is called immediately after the object is created
  //the parent is always the object calling `.add()`
  Container::active_screen().add(List(my_list_context).configure([](List & list){

    //use method chaining (if you like) to set the object attributes
    list.set_width(90_percent)
      .set_height(100_percent)
      .add_button(LV_SYMBOL_OK, "", "OK")
      .add_button(LV_SYMBOL_LEFT, "", "LEFT")
      .add_button(LV_SYMBOL_RIGHT, "", "RIGHT")
      .add_button(LV_SYMBOL_UP, "", "UP")
      .add_button(LV_SYMBOL_DOWN, "", "DOWN");
  })).add(Button(LV_SYMBOL_RIGHT).configure([](Button & button){
    //add a tall skinny button on the right
    button.set_height(100_percent).set_x(90_percent).set_width(10_percent).add_label();
  }));
}
```
