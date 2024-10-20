#include "keymap_us_international.h"
#include "sendstring_us_international.h"

#define CAPS_LOCK_KEY 26

void e_accents_each(tap_dance_state_t *state, void *user_data);
void a_accents_each(tap_dance_state_t *state, void *user_data);
void o_accents_each(tap_dance_state_t *state, void *user_data);
void u_accents_each(tap_dance_state_t *state, void *user_data);
void i_accents_each(tap_dance_state_t *state, void *user_data);

enum {
  E_ACCENTS,
  A_ACCENTS,
  O_ACCENTS,
  U_ACCENTS,
  I_ACCENTS,
};

tap_dance_action_t tap_dance_actions[] = {
    [E_ACCENTS] = ACTION_TAP_DANCE_FN_ADVANCED(e_accents_each, NULL, NULL),
    [A_ACCENTS] = ACTION_TAP_DANCE_FN_ADVANCED(a_accents_each, NULL, NULL),
    [O_ACCENTS] = ACTION_TAP_DANCE_FN_ADVANCED(o_accents_each, NULL, NULL),
    [U_ACCENTS] = ACTION_TAP_DANCE_FN_ADVANCED(u_accents_each, NULL, NULL),
    [I_ACCENTS] = ACTION_TAP_DANCE_FN_ADVANCED(i_accents_each, NULL, NULL),
};

// TODO : tap dance to toggle shift lock

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x6_3(
      KC_ESC,        KC_QUOT,       KC_COMM,       KC_DOT,        KC_P,          KC_Y,                      KC_F,          KC_G,          KC_C,          KC_R,          KC_L,          KC_BSPC,
      KC_TAB,        LGUI_T(KC_A),  LALT_T(KC_O),  LCTL_T(KC_E),  LSFT_T(KC_U),  KC_I,                      KC_D,          LSFT_T(KC_H),  LCTL_T(KC_T),  LALT_T(KC_N),  LGUI_T(KC_S),  S(KC_TAB),
      KC_CAPS,       KC_SCLN,       KC_Q,          KC_J,          KC_K,          KC_X,                      KC_B,          KC_M,          KC_W,          KC_V,          KC_Z,          KC_ENT,
                                                   MO(3),         MO(2),         LT(1, KC_SPC),             LT(1, KC_SPC), MO(2),         MO(3)
    ),

    [1] = LAYOUT_split_3x6_3(
      KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,         KC_F6,                     KC_7,          KC_8,          KC_9,          KC_PLUS,       KC_ASTR,       KC_DEL,
      KC_F7,         KC_F8,         KC_F9,         KC_F10,        KC_F11,        KC_F12,                    KC_4,          KC_5,          KC_6,          KC_MINS,       KC_SLSH,       _______,
      _______,       _______,       _______,       _______,       _______,       _______,                   KC_1,          KC_2,          KC_3,          _______,       _______,       _______,
                                                   _______,       _______,       KC_SPC,                    KC_DOT,        KC_0,          KC_EQL
    ),

    [2] = LAYOUT_split_3x6_3(
      _______,       A(KC_F2),      RALT(KC_COMM), A(KC_F4),      C(KC_F2),      S(KC_F9),                  C(KC_PGUP),    KC_HOME,       KC_UP,         KC_END,        _______,       _______,
      KC_VOLD,       TD(A_ACCENTS), TD(O_ACCENTS), TD(E_ACCENTS), TD(U_ACCENTS), TD(I_ACCENTS),             C(KC_PGDN),    KC_LEFT,       KC_DOWN,       KC_RGHT,       _______,       KC_VOLU,
      _______,       _______,       _______,       _______,       _______,       _______,                   _______,       _______,       _______,       _______,       _______,       _______,
                                                   _______,       _______,       _______,                   C(A(KC_LEFT)), _______,       C(A(KC_RGHT))
    ),

    [3] = LAYOUT_split_3x6_3(
      QK_BOOT,       KC_CIRC,       KC_HASH,       KC_TILD,       S(KC_0),       S(KC_9),                   S(KC_9),       S(KC_0),       KC_TILD,     KC_HASH,       KC_CIRC,       _______,
      KC_NUBS,       KC_AMPR,       KC_DLR,        KC_EXLM,       KC_RBRC,       KC_LBRC,                   KC_LBRC,       KC_RBRC,       KC_EXLM,     KC_DLR,        KC_AMPR,       KC_NUBS,
      KC_GRV,        KC_ASTR,       KC_PERC,       KC_AT,         S(KC_RBRC),    S(KC_LBRC),                S(KC_LBRC),    S(KC_RBRC),    KC_AT,       KC_PERC,       KC_ASTR,       KC_GRV,
                                                   KC_QUES,       KC_PIPE,       KC_UNDS,                   KC_UNDS,       KC_PIPE,       KC_QUES
    )
};
