#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

// sm_td: https://github.com/stasmarkin/sm_td/tree/main
#include "sm_td.h"

// Layer definitions
enum layers {
    _BASE = 0,
    _NAV,      // navigation layer following Emacs Meow modal editing
    _SYM,      // symbols/numbers
    _MACRO,    // macros
    _MATHS,    // maths/unicode
    _MOUSE,    // mouse layer
    _AUDIO,    // audio layer
    _FN,       // function/other keys
};

enum custom_keycodes {
    // Base Layer

    // Left hand HRMs
    HRM_C = SAFE_RANGE,
    HRM_R,
    HRM_S,
    HRM_T,

    // Right hand HRMs
    HRM_N,
    HRM_E,
    HRM_I,
    HRM_A,

    // Fn layer
    FN_Q,

    // Thumb keys
    TMB_SYM,
    TMB_NAV,

    // Macros
    CKC_DQUO // Double quote ("), i.e. CTRL + 2
};

// Define overrides:
const key_override_t tab = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);   // Shift + Space => Tab
const key_override_t enter = ko_make_basic(MOD_MASK_CTRL, KC_SPC, KC_ENTER); // Ctrl + Space => Enter
const key_override_t dquot = ko_make_basic(MOD_MASK_SHIFT, KC_QUOTE, CKC_DQUO); // Ctrl + ' => "

// Apply overrides
const key_override_t *key_overrides[] = {
    &tab,
    &enter,
    &dquot,
};

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        // Home Row Mods
        SMTD_MT_ON_MKEY(HRM_C, KC_C, KC_LEFT_GUI)
        SMTD_MT_ON_MKEY(HRM_R, KC_R, KC_LEFT_ALT)
        SMTD_MT_ON_MKEY(HRM_S, KC_S, KC_LEFT_CTRL)
        SMTD_MT_ON_MKEY(HRM_T, KC_T, KC_LSFT)

        SMTD_MT_ON_MKEY(HRM_N, KC_N, KC_RSFT)
        SMTD_MT_ON_MKEY(HRM_E, KC_E, KC_RIGHT_CTRL)
        SMTD_MT_ON_MKEY(HRM_I, KC_I, KC_RIGHT_ALT)
        SMTD_MT_ON_MKEY(HRM_A, KC_A, KC_RIGHT_GUI)

        // Fn layer
        SMTD_LT_ON_MKEY(FN_Q, KC_Q, _FN)

        // Thumb Actions                                  TAP:                  | HOLD:
        SMTD_LT_ON_MKEY(TMB_NAV, TG(_NAV), _MOUSE)        // Toggle Nav layer   | Mouse layer
        SMTD_LT_ON_MKEY(TMB_SYM, TG(_SYM), _MATHS)        // Toggle Maths layer | Symbols layer
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_2(
        KC_W,  KC_L,  KC_Y,  KC_P,  KC_B,                         KC_Z, KC_F,  KC_O,      KC_U,       KC_QUOTE,
        HRM_C, HRM_R, HRM_S, HRM_T, KC_G,                         KC_M, HRM_N, HRM_E,     HRM_I,      HRM_A,
        FN_Q,  KC_J,  KC_V,  KC_D,  KC_K,                         KC_X, KC_H,  KC_SLASH,  KC_COMMA,   KC_DOT,
                                    TMB_SYM, KC_SPC,     KC_BSPC, TMB_NAV
    ),

    [_FN] = LAYOUT_split_3x5_2(KC_TRNS, KC_TRNS, KC_COLN, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_PERC, KC_SLSH, KC_ENT, KC_TRNS, DF(1), KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EXLM, KC_TRNS, DF(0), KC_TRNS, RALT_T(KC_COMM), RCTL_T(KC_DOT), QK_BOOT, KC_TRNS, KC_TAB, KC_NO, KC_TRNS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        // Use smtd
        return false;
    }

    switch (keycode) {
        case CKC_DQUO:
            if (record->event.pressed) {
                // Send Ctrl + 2 (i.e. ")
                register_mods(MOD_MASK_CTRL);
                tap_code(KC_2);
                unregister_mods(MOD_MASK_CTRL);
            }
            return false;
        default:
            // Handle normally
            return true;
    }
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


