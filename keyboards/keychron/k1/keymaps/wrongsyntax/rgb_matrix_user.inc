RGB_MATRIX_EFFECT(ws_alpha_mods)
RGB_MATRIX_EFFECT(mod_alpha_caps)
RGB_MATRIX_EFFECT(mod_alpha_regular)
RGB_MATRIX_EFFECT(numpad)
RGB_MATRIX_EFFECT(fn)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Also defines LED_MIN and LED_MAX
#include "rgb_matrix_map.h"

#define RGB_WS_GREEN 0x00, 0x45, 0x08
// #define RGB_WS_GOLD 0x54, 0x4A, 0x00
#define RGB_WS_GOLD RGB_GOLD
#define RBG_WS_PURPLE 0x45, 0x1E, 0x5D

#define RGB_WS_PRIMARY 0x00, 0x45, 0x08 // RGB_WS_GREEN
#define RGB_WS_SECONDARY 0x45, 0x1E, 0x5D // RGB_WS_PURPLE

static bool ws_alpha_mods(effect_params_t* params) {
    for (uint8_t i = LED_MIN; i <= LED_MAX; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, RGB_WS_SECONDARY);
        } else {
            rgb_matrix_set_color(i, RGB_WS_PRIMARY);
        }
    }

    rgb_matrix_set_color(LED_CAPS, RGB_GREEN);

    return rgb_matrix_check_finished_leds(LED_MAX);
}

static bool mod_alpha_caps(effect_params_t* params) {
    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_LETTERS); i++) {
        rgb_matrix_set_color(LED_LIST_LETTERS[i], RGB_RED);
    }

    rgb_matrix_set_color(LED_CAPS, RGB_RED);

    return rgb_matrix_check_finished_leds(LED_MAX);
}

static bool mod_alpha_regular(effect_params_t* params) {   
    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_LETTERS); i++) {
        rgb_matrix_set_color(LED_LIST_LETTERS[i], RGB_WS_PRIMARY);
    }

    rgb_matrix_set_color(LED_CAPS, RGB_GREEN);

    return rgb_matrix_check_finished_leds(LED_MAX);
}

static bool numpad(effect_params_t* params) {   
    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD_NUMS); i++) {
        // Uncomment and chang `i++` to `i += 2` to have per row colors
        // if (i >= 0 && i < 2) {
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i], RGB_RED);
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i + 1], RGB_RED);
        // } else if (i >= 1 && i < 8) {
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i], RGB_GREEN);
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i + 1], RGB_GREEN);
        // } else if (i >= 4 && i < 14) {
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i], RGB_BLUE);
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i + 1], RGB_BLUE);
        // } else if (i >= 14) {
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i], RGB_YELLOW);
        //     rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i + 1], RGB_YELLOW);
        // }
        rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i], RGB_WS_PRIMARY);
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD_OPS); i++) {
        rgb_matrix_set_color(LED_LIST_NUMPAD_OPS[i], RGB_WS_SECONDARY);
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_WASD); i++) {
        rgb_matrix_set_color(LED_LIST_WASD[i], RGB_PURPLE);
    }

    rgb_matrix_set_color(LED_N, RGB_RED);
    rgb_matrix_set_color(LED_FN, RGB_RED);

    return rgb_matrix_check_finished_leds(LED_MAX);
}

static bool fn(effect_params_t* params) {
    rgb_matrix_set_color(LED_CAPS, RGB_RED);
    rgb_matrix_set_color(LED_N, RGB_WS_PRIMARY);
    rgb_matrix_set_color(LED_RGB, RGB_GREEN);

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_FN); i++) {
        rgb_matrix_set_color(LED_LIST_FN[i], RGB_ORANGE);
    }

    return rgb_matrix_check_finished_leds(LED_MAX);
}

#endif
