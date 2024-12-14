RGB_MATRIX_EFFECT(ws_alpha_mods)
RGB_MATRIX_EFFECT(mod_alpha_caps)
RGB_MATRIX_EFFECT(mod_alpha_regular)
RGB_MATRIX_EFFECT(numpad)
RGB_MATRIX_EFFECT(fn)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Also defines LED_MIN and LED_MAX
#include "rgb_matrix_map.h"

// Define base colors in HSV format (Hue: 0-255)
#define HSV_WS_GREEN 85, 255, 69
#define HSV_WS_PURPLE 191, 68, 93

#define HSV_WS_PRIMARY HSV_WS_GREEN
#define HSV_WS_SECONDARY HSV_WS_PURPLE

static void set_hsv_color(uint8_t led_idx, uint8_t hue, uint8_t sat, uint8_t val) {
    HSV hsv = {
        .h = hue,
        .s = sat,
        .v = val
    };
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_idx, rgb.r, rgb.g, rgb.b);
}

// Base lighting function that sets up the initial state
static void set_base_lighting(uint8_t hue, uint8_t sat, uint8_t val) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            set_hsv_color(i, (hue + 128) % 256, sat, val);
        } else {
            set_hsv_color(i, hue, sat, val);
        }
    }
}

static bool ws_alpha_mods(effect_params_t* params) {
    uint8_t hue = rgb_matrix_config.hsv.h;
    uint8_t sat = rgb_matrix_config.hsv.s;
    uint8_t val = rgb_matrix_config.hsv.v;

    set_base_lighting(hue, sat, val);
//    set_hsv_color(LED_CAPS, 85, sat, val);

    return rgb_matrix_check_finished_leds(DRIVER_LED_TOTAL);
}

static bool mod_alpha_caps(effect_params_t* params) {
//    uint8_t hue = rgb_matrix_config.hsv.h;
    uint8_t sat = rgb_matrix_config.hsv.s;
    uint8_t val = rgb_matrix_config.hsv.v;

//    set_base_lighting(hue, sat, val);

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_LETTERS); i++) {
        set_hsv_color(LED_LIST_LETTERS[i], 0, sat, val);
    }

    set_hsv_color(LED_CAPS, 0, sat, val);

    return rgb_matrix_check_finished_leds(DRIVER_LED_TOTAL);
}

static bool mod_alpha_regular(effect_params_t* params) {   
    uint8_t hue = rgb_matrix_config.hsv.h;
    uint8_t sat = rgb_matrix_config.hsv.s;
    uint8_t val = rgb_matrix_config.hsv.v;

//    set_base_lighting(hue, sat, val);

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_LETTERS); i++) {
        set_hsv_color(LED_LIST_LETTERS[i], hue, sat, val);
    }

    set_hsv_color(LED_CAPS, 85, sat, val);

    return rgb_matrix_check_finished_leds(DRIVER_LED_TOTAL);
}

static bool numpad(effect_params_t* params) {   
    uint8_t hue = rgb_matrix_config.hsv.h;
    uint8_t sat = rgb_matrix_config.hsv.s;
    uint8_t val = rgb_matrix_config.hsv.v;

//    set_base_lighting(hue, sat, val);

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD_NUMS); i++) {
        set_hsv_color(LED_LIST_NUMPAD_NUMS[i], hue, sat, val);
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD_OPS); i++) {
        set_hsv_color(LED_LIST_NUMPAD_OPS[i], (hue + 128) % 256, sat, val);
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_WASD); i++) {
        set_hsv_color(LED_LIST_WASD[i], 191, sat, val);
    }

    set_hsv_color(LED_N, 0, sat, val);
    set_hsv_color(LED_FN, 0, sat, val);

    return rgb_matrix_check_finished_leds(DRIVER_LED_TOTAL);
}

static bool fn(effect_params_t* params) {
    uint8_t hue = rgb_matrix_config.hsv.h;
    uint8_t sat = rgb_matrix_config.hsv.s;
    uint8_t val = rgb_matrix_config.hsv.v;

//    set_base_lighting(hue, sat, val);

    set_hsv_color(LED_CAPS, 0, sat, val);
    set_hsv_color(LED_N, hue, sat, val);
    set_hsv_color(LED_RGB, 85, sat, val);

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_FN); i++) {
        set_hsv_color(LED_LIST_FN[i], 39, sat, val);
    }

    return rgb_matrix_check_finished_leds(DRIVER_LED_TOTAL);
}

#endif
