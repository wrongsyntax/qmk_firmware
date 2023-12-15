/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
   Copyright 2023 Uzair Tariq <uzair@wrongsyntax.dev>
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef RGB_MATRIX_ENABLE

// Min and max in rgb/ansi.c
#define LED_MIN 0
#define LED_MAX 86

// RGB LED locations
enum led_location_map {
    LED_CAPS, // 0
    LED_F1, // 1
    LED_F2, // 2
    LED_F3, // 3
    LED_F4, // 4
    LED_F5, // 5
    LED_F6, // 6
    LED_F7, // 7
    LED_F8, // 8
    LED_F9, // 9
    LED_F10, // 10
    LED_F11, // 11
    LED_F12, // 12
    LED_SCR, // 13
    LED_SPTL, // 14
    LED_RGB, // 15
    LED_GRV, // 16
    LED_1, // 17
    LED_2, // 18
    LED_3, // 19
    LED_4, // 20
    LED_5, // 21
    LED_6, // 22
    LED_7, // 23
    LED_8, // 24
    LED_9, // 25
    LED_0, // 26
    LED_MINS, // 27
    LED_EQL, // 28
    LED_BSPC, // 29
    LED_INS, // 30
    LED_HOME, // 31
    LED_PGUP, // 32
    LED_TAB, // 33
    LED_Q, // 34
    LED_W, // 35
    LED_E, // 36
    LED_R, // 37
    LED_T, // 38
    LED_Y, // 39
    LED_U, // 40
    LED_I, // 41
    LED_O, // 42
    LED_P, // 43
    LED_LBRC, // 44
    LED_RBRC, // 45
    LED_BSLS, // 46
    LED_DEL, // 47
    LED_END, // 48
    LED_PGDN, // 49
    LED_ESC, // 50
    LED_A, // 51
    LED_S, // 52
    LED_D, // 53
    LED_F, // 54
    LED_G, // 55
    LED_H, // 56
    LED_J, // 57
    LED_K, // 58
    LED_L, // 59
    LED_SCLN, // 60
    LED_QUOT, // 61
    LED_ENT, // 62
    LED_LSHFT, // 63
    LED_Z, // 64
    LED_X, // 65
    LED_C, // 66
    LED_V, // 67
    LED_B, // 68
    LED_N, // 69
    LED_M, // 70
    LED_COMM, // 71
    LED_DOT, // 72
    LED_SLSH, // 73
    LED_RSHFT, // 74
    LED_UP, // 75
    LED_LCTL, // 76
    LED_LALT, // 77
    LED_LGUI, // 78
    LED_SPC, // 79
    LED_RGUI, // 80
    LED_RALT, // 81
    LED_FN, // 82
    LED_RCTL, // 83
    LED_LEFT, // 84
    LED_DOWN, // 85
    LED_RIGHT, // 86
};

const uint8_t LED_LIST_WASD[] = {
    LED_W,
    LED_A,
    LED_S,
    LED_D
};

const uint8_t LED_LIST_ARROWS[] = {
    LED_LEFT,
    LED_RIGHT,
    LED_UP,
    LED_DOWN
};

const uint8_t LED_LIST_FUNCROW[] = {
    LED_ESC,
    LED_F1,
    LED_F2,
    LED_F3,
    LED_F4,
    LED_F5,
    LED_F6,
    LED_F7,
    LED_F8,
    LED_F9,
    LED_F10,
    LED_F11,
    LED_F12,
    LED_SCR,
    LED_SPTL,
    LED_RGB
};

const uint8_t LED_LIST_NUMROW[] = {
    LED_GRV,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_MINS,
    LED_EQL,
    LED_BSPC,
    LED_INS,
    LED_HOME,
    LED_PGUP
};

const uint8_t LED_LIST_LETTERS[] = {
    LED_Q,
    LED_W,
    LED_E,
    LED_R,
    LED_T,
    LED_Y,
    LED_U,
    LED_I,
    LED_O,
    LED_P,
    LED_A,
    LED_S,
    LED_D,
    LED_F,
    LED_G,
    LED_H,
    LED_J,
    LED_K,
    LED_L,
    LED_Z,
    LED_X,
    LED_C,
    LED_V,
    LED_B,
    LED_N,
    LED_M
};

const uint8_t LED_LIST_NUMPAD_NUMS[] = {
    LED_M,
    LED_COMM,
    LED_DOT,
    LED_J,
    LED_K,
    LED_L,
    LED_U,
    LED_I,
    LED_O,
    LED_7,
    LED_8,
    LED_9
};

const uint8_t LED_LIST_NUMPAD_OPS[] = {
    LED_0,
    LED_P,
    LED_SCLN,
    LED_SLSH
};

const uint8_t LED_LIST_TOP_RIGHT_KB[] = {
    LED_SCR,
    LED_SPTL,
    LED_RGB,
    LED_INS,
    LED_HOME,
    LED_PGUP,
    LED_DEL,
    LED_END,
    LED_PGDN
};

const uint8_t LED_LIST_EDIT[] = {
    LED_INS,
    LED_HOME,
    LED_PGUP,
    LED_DEL,
    LED_END,
    LED_PGDN
};

#endif

/**
 * Following Macros are taken from quantum/util.h
 * Copyright 2022 Stefan Kerkmann (KarlK90)
 * Copyright 2011 Jun Wako <wakojun@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#if !defined(IS_ARRAY)
/**
 * @brief Returns true if the value is an array, false if it's a pointer.
 *
 * This macro is ill-formed for scalars, which is OK for its intended use in
 * ARRAY_SIZE.
 */
#    define IS_ARRAY(value) (!__builtin_types_compatible_p(typeof((value)), typeof(&(value)[0])))
#endif

#if !defined(ARRAY_SIZE)
/**
 * @brief Computes the number of elements of the given array at compile time.
 *
 * This Macro can only be used for statically allocated arrays that have not
 * been decayed into a pointer. This is detected at compile time, though the
 * error message for scalar values is poor.
 *
 */
#    define ARRAY_SIZE(array) (__builtin_choose_expr(IS_ARRAY((array)), sizeof((array)) / sizeof((array)[0]), (void)0))
#endif
