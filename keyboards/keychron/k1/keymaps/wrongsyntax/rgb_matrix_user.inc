RGB_MATRIX_EFFECT(ws_alpha_mods)
RGB_MATRIX_EFFECT(mod_alpha_caps)
RGB_MATRIX_EFFECT(mod_alpha_regular)
// RGB_MATRIX_EFFECT(numpad)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Also defines LED_MIN and LED_MAX
#include "rgb_matrix_map.h"

#define RGB_WS_GREEN 0x00, 0x45, 0x08
// #define RGB_WS_GOLD 0x54, 0x4A, 0x00
#define RGB_WS_GOLD RGB_GOLD

static bool ws_alpha_mods(effect_params_t* params) {
    for (uint8_t i = LED_MIN; i <= LED_MAX; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, RGB_WS_GOLD);
        } else {
            rgb_matrix_set_color(i, RGB_WS_GREEN);
        }
    }

    rgb_matrix_set_color(LED_CAPS, RGB_GREEN);

    for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_EDIT); i++) {
        rgb_matrix_set_color(LED_LIST_EDIT[i], RGB_WS_GREEN);
    }

    // for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_ARROWS); i++) {
    //     rgb_matrix_set_color(LED_LIST_ARROWS[i], RGB_WS_GREEN);
    // }

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
        rgb_matrix_set_color(LED_LIST_LETTERS[i], RGB_WS_GREEN);
    }

    rgb_matrix_set_color(LED_CAPS, RGB_GREEN);

    return rgb_matrix_check_finished_leds(LED_MAX);
}

// static bool numpad(effect_params_t* params) {
//     rgb_matrix_set_color_all(0x00, 0x00, 0x00);

//     for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD_NUMS); i++) {
//         rgb_matrix_set_color(LED_LIST_NUMPAD_NUMS[i], RGB_BLUE);
//     }

//     return rgb_matrix_check_finished_leds(LED_MAX);
// }

#endif

