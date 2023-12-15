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
      KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC,                           KC_UP,
      KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                                      KC_RGUI, KC_RALT, MO(_FN),   KC_RCTL,       KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN] = LAYOUT_tkl_ansi( // Mac Fn overlay
      RESET,             KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,          _______, _______, RGB_TOG,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         RGB_HUI, RGB_SAI, RGB_VAI,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         RGB_HUD, RGB_SAD, RGB_VAD,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______,  KC_NUM, _______, _______, _______, _______,          _______,                           RGB_SPI,
      _______, _______, _______,                   _______,                                     _______, _______, _______, _______,         _______, RGB_SPD, _______
    ),

    [_NUM] = LAYOUT_tkl_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______,
        _______,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,  KC_PMNS,  KC_PMNS, KC_PPLS, _______,        _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,  KC_P4,   KC_P5,   KC_P6,  KC_PPLS, _______, _______, _______,        _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,  KC_P1,   KC_P2,   KC_P3,  KC_PAST, _______,          _______,
        _______, _______, _______, _______, _______, _______,  KC_NUM,  KC_P0,   KC_P0,  KC_PDOT, KC_PSLS,          _______,                          _______,
        _______, _______, _______,                   _______,                                     _______, _______, _______, _______,        _______, _______, _______
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

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t led_state = host_keyboard_led_state();
    // Caps Lock setup
    if (led_state.caps_lock) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_mod_alpha_caps);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_mod_alpha_regular);
    }

    // if (led_state.num_lock) {
    //     rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_mod_alpha_caps);
    //     // switch (get_highest_layer(layer_state)) {
    //     //     case _NUM:
    //     //         rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_numpad);
    //     //         break;
    //     //     default:
    //     //         rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_ws_alpha_mods);
    //     //         break;
    //     // }
    // } else {
    //     rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_mod_alpha_regular);
    // }
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

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}
