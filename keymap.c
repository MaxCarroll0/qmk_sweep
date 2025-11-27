#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

// sm_td: https://github.com/stasmarkin/sm_td/tree/main
#include "sm_td.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        // Use smtd
        return false;
    }
    // Process normally
    return true;
}

// Layer definitions
enum layers {
    _BASE = 0,
    _NAV,      // navigation layer following Emacs Meow modal editing
    _SYM,      // symbols/numbers
    _MACRO,    // macros
    _MATH,     // maths/unicode
    _FN,       // function keys
    _MOUSE     // mouse layer
};

enum hrms {
    // Left hand base layer
    HRM_C = SAFE_RANAGE,
    HRM_R,
    HRM_S,
    HRM_T,

    // Right hand base layer
    HRM_N,
    HRM_E,
    HRM_I,
    HRM_A,
}

// Home Row Mods
smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT_ON_MKEY(HRM_C, KC_C, KC_LEFT_GUI)
        SMTD_MT_ON_MKEY(HRM_R, KC_R, KC_LEFT_ALT)
        SMTD_MT_ON_MKEY(HRM_S, KC_S, KC_LEFT_CTRL)
        SMTD_MT_ON_MKEY(HRM_T, KC_T, KC_LSFT)

        SMTD_MT_ON_MKEY(HRM_N, KC_N, KC_RSFT)
        SMTD_MT_ON_MKEY(HRM_E, KC_E, KC_RIGHT_CTRL)
        SMTD_MT_ON_MKEY(HRM_I, KC_I, KC_RIGHT_ALT)
        SMTD_MT_ON_MKEY(HRM_A, KC_A, KC_RIGHT_GUI)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_2(
        KC_W,  KC_L,  KC_Y,  KC_P,  KC_B,                             KC_Z, KC_F,  KC_O,      KC_U,       KC_QUOTE,
        HRM_C, HRM_R, HRM_S, HRM_T, KC_G,                             KC_M, HRM_N, HRM_E,     HRM_I,      HRM_A,
        KC_Q,  KC_J,  KC_V,  KC_D,  KC_K,                             KC_X, KC_H,  KC_SLASH,  KC_COMMA,   KC_DOT,
                                    KC_P0, KC_BSPC,     LT(7,KC_SPC), KC_P1
    ),

    [7] = LAYOUT_split_3x5_2(KC_TRNS, KC_TRNS, KC_COLN, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_PERC, KC_SLSH, KC_ENT, KC_TRNS, DF(1), KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EXLM, KC_TRNS, DF(0), KC_TRNS, RALT_T(KC_COMM), RCTL_T(KC_DOT), QK_BOOT, KC_TRNS, KC_TAB, KC_NO, KC_TRNS)
};



#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


