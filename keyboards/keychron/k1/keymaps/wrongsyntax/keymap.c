/* Copyright 2023 Uzair Tariq <uzair@wrongsyntax.dev> 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// #include "rgb_matrix_map.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    BASE            = 0,
    _FN             = 1,
    _NUM            = 2,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    FNNUM,
    WLSFT,
    WRSFT,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void fn_finished(qk_tap_dance_state_t *state, void *user_data);
void fn_reset(qk_tap_dance_state_t *state, void *user_data);

void wlsft_finished(qk_tap_dance_state_t *state, void *user_data);
void wlsft_reset(qk_tap_dance_state_t *state, void *user_data);

void wrsft_finished(qk_tap_dance_state_t *state, void *user_data);
void wrsft_reset(qk_tap_dance_state_t *state, void *user_data);

#define ENABLE_COMPILE_KEYCODE

#define KC_MSSN LGUI(KC_F3)         // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC))  // Finder
//! Launchpad keycode requires you to set up the keyboard shortcut in Settings > Keyboard > Shortcuts then set Launchpad to Option+Command+A
#define KC_LNCH LALT(LGUI(KC_A))    // Launchpad
#define KC_SPTL LGUI(KC_SPC)        // Spotlight
#define KC_MSNP LSFT(LGUI(KC_4))    // Mac snip tool

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Mac layout
    +-------------------------------------------------------------------------------------------+
    | ESC |  | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9| F10| F11| F12|  | |PSCR|SPTL|RGB |
    +--------------------------------------------------------------------------+ +--------------+
    |  ~  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = | BACKSP | |INS |HOME|PGUP|
    +--------------------------------------------------------------------------+ +--------------+
    |  TAB  |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] |   \  | |DEL |END |PGDN|
    +--------------------------------------------------------------------------+ +--------------+
    | CAPSLCK  |  A |  S |  D |  F |  G |  H |  J |  K |  L | ; | ' |  RETURN  |                |
    +--------------------------------------------------------------------------+      +----+    |
    | LSHIFT     |  Z |  X |  C |  V |  B |  N |  M | , | . |  / |   RSHIFT    |      | UP |    |
    +--------------------------------------------------------------------------+ +--------------+
    |LCTRL| LALT| LGUI |            SPACE            | RGUI| RALT | FN | RCTRL | |LFT |DWN |RGT |
    +-------------------------------------------------------------------------------------------+
    */

  [BASE] = LAYOUT_tkl_ansi( // Mac base layout
      KC_CAPS,          KC_BRID, KC_BRIU, KC_MSSN, KC_LNCH, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,   KC_VOLU,      KC_MSNP,  KC_SPTL, RGB_MOD,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,    KC_BSPC,       KC_INS,  KC_HOME, KC_PGUP,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,   KC_BSLS,       KC_DEL,  KC_END,  KC_PGDN,
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,
    TD(WLSFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          TD(WRSFT),                          KC_UP,
      KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, KC_RALT, TD(FNNUM), KC_RCTL,       KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN] = LAYOUT_tkl_ansi( // Mac Fn overlay
      RESET,             KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,          _______, _______, RGB_TOG,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         RGB_HUI, RGB_SAI, RGB_VAI,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         RGB_HUD, RGB_SAD, RGB_VAD,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______,TG(_NUM), _______, _______, _______, _______,          _______,                           RGB_SPI,
      _______, _______, _______,                   _______,                                     _______, _______, _______, _______,         _______, RGB_SPD, _______
    ),

    [_NUM] = LAYOUT_tkl_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_PMNS, KC_PPLS, KC_PAST, KC_PSLS,         KC_P7,   KC_P8,   KC_P9,
        _______,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,  KC_PMNS, KC_PMNS, KC_PPLS, _______,         KC_P4,   KC_P5,   KC_P6,
        _______, _______,  KC_UP,  _______, _______, _______, _______,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, _______, _______, _______,         KC_P1,   KC_P2,   KC_P3,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,  KC_P1,   KC_P2,   KC_P3,  KC_PAST, _______,          _______,
        _______, _______, _______, _______, _______, _______, TG(_NUM), KC_P0,   KC_P0,  KC_PDOT, KC_PSLS,          _______,                           KC_P0,
        _______, _______, _______,                   _______,                                     _______, _______,TG(_NUM), _______,        _______, _______, _______
    )
};

/*
Blank layout
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                          _______,
    _______, _______, _______,                   _______,                                     _______, _______, _______, _______,        _______, _______, _______

*/

bool num_lock = false;
bool fn = false;
bool allow_caps = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BASE:
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_ws_alpha_mods);
            num_lock = false;
            allow_caps = true;
            break;
        case _FN:
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_fn);
            fn = true;
            allow_caps = false;
            break;
        case _NUM:
            num_lock = true;
            allow_caps = false;
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_numpad);
            break;
        default: //  for any other layers, or the default layer
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_ws_alpha_mods);
            break;
    }
    return state;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t led_state = host_keyboard_led_state();

    if (allow_caps) {
        if (led_state.caps_lock) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_mod_alpha_caps);
        } else {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_mod_alpha_regular);
        }
    }
}

bool dip_switch_update_user(uint8_t index, bool active){
    switch(index){
        case 0:
        // if(active) { // Mac mode
        //     layer_move(MAC_BASE);
        // } else { // Windows mode
        //     layer_move(WIN_BASE);
        // }
        return false;
        case 1:
        if(active){ //Cable mode
            // do stuff
        }
        else{ //BT mode
            // do stuff
        }
        break;
    }
    return true;
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_ws_alpha_mods);
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        // state->interrupted || state->pressed is the original condition. state->interrupted is removed to allow permissive hold style functionality.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

static td_tap_t fn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t wlsft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t wrsft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void fn_finished(qk_tap_dance_state_t *state, void *user_data) {
    fn_tap_state.state = cur_dance(state);
    switch (fn_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_FN);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_NUM);
            break;
        default:
            break;
    }
}

void fn_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (fn_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_FN);
    }
    fn_tap_state.state = TD_NONE;
}

// Send a ( on single tap, [ on double tap, and { on triple tap for the WLSFT tap dance. Send Shift when held.
void wlsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    wlsft_tap_state.state = cur_dance(state);
    switch (wlsft_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LSFT);
            register_code(KC_9);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LBRC);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LSFT);
            register_code(KC_LBRC);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        default:
            break;
    }
}

void wlsft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (wlsft_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_LSFT);
            unregister_code(KC_9);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LBRC);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_LSFT);
            unregister_code(KC_LBRC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
        default:
            break;
    }
    wlsft_tap_state.state = TD_NONE;
}

// Send ) on single tap, ] on double tap, and } on triple tap for the WRSFT tap dance. Send Shift when held.
void wrsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    wrsft_tap_state.state = cur_dance(state);
    switch (wrsft_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_RSFT);
            register_code(KC_0);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_RBRC);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_RSFT);
            register_code(KC_RBRC);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_RSFT);
            break;
        default:
            break;
    }
}

void wrsft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (wrsft_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_RSFT);
            unregister_code(KC_0);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_RBRC);
            break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_RSFT);
            unregister_code(KC_RBRC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_RSFT);
            break;
        default:
            break;
    }
    wrsft_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [FNNUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_finished, fn_reset),
    [WLSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wlsft_finished, wlsft_reset),
    [WRSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, wrsft_finished, wrsft_reset),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 150;
        default:
            return TAPPING_TERM;
    }
}
