# LvglAPI

The LvglAPI is a C++ wrapper library for the [lvgl embedded graphics library](https://lvgl.io/). The coding style follows the Stratify Labs [API framework](https://github.com/StratifyLabs/API) style.

## How to

The API uses the following pattern to add objects to the display:

```c++
#include <lvgl.hpp>
int my_draw_function(){
  screen()
    .add(List()
           .set_width(90_percent)
           .set_height(100_percent)
           .add_button(LV_SYMBOL_OK, "", "OK")
           .add_button(LV_SYMBOL_LEFT, "", "LEFT")
           .add_button(LV_SYMBOL_RIGHT, "", "RIGHT")
           .add_button(LV_SYMBOL_UP, "", "UP")
           .add_button(LV_SYMBOL_DOWN, "", "DOWN"))
    .add(Button()
           .set_height(100_percent)
           .set_x(90_percent)
           .set_width(10_percent)
           .add_label(LV_SYMBOL_RIGHT));
}
```
