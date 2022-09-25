RGB_MATRIX_EFFECT(ws_alpha_mods)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool ws_alpha_mods(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, 0x11, 0xae, 0x91);
        } else {
            rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif

