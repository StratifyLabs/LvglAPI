#include <sdk/types.h>

#include "lvgl/lvgl_api.h"

#include "lvgl.h"

const lvgl_api_t lvgl_api = {
    .sos_api =
        {
            .name = "lvgl",
            .version = LVGL_API_VERSION,
            .git_hash = SOS_GIT_HASH,
        },
};
