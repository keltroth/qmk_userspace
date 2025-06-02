#include "default_keyboard.h"

#define CAPS_LOCK_KEY 26

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x6_3(
      KC_ESC,           KC_QUOT,          KC_COMM,          KC_DOT,           KC_P,             KC_Y,                      KC_F,             KC_G,             KC_C,             KC_R,             KC_L,             KC_BSPC,
      KC_TAB,           LGUI_T(KC_A),     LALT_T(KC_O),     LCTL_T(KC_E),     LSFT_T(KC_U),     KC_I,                      KC_D,             LSFT_T(KC_H),     LCTL_T(KC_T),     LALT_T(KC_N),     LGUI_T(KC_S),     S(KC_TAB),
      LT(5, KC_CAPS),   KC_SCLN,          KC_Q,             KC_J,             KC_K,             KC_X,                      KC_B,             KC_M,             KC_W,             KC_V,             KC_Z,             KC_ENT,
                                                            MO(4),            MO(3),            LT(2,  KC_SPC),            LT(2,  KC_SPC),   MO(3),            MO(4)
    ),

    [1] = LAYOUT_split_3x6_3(
      KC_ESC,           KC_QUOT,          KC_COMM,          KC_DOT,           KC_P,             KC_Y,                      KC_F,             KC_G,             KC_C,             KC_R,             KC_L,             KC_BSPC,
      KC_TAB,           KC_A,             KC_O,             KC_E,             KC_U,             KC_I,                      KC_D,             KC_H,             KC_T,             KC_N,             KC_S,             S(KC_TAB),
      LT(5, KC_CAPS),   KC_SCLN,          KC_Q,             KC_J,             KC_K,             KC_X,                      KC_B,             KC_M,             KC_W,             KC_V,             KC_Z,             KC_ENT,
                                                            MO(4),            MO(3),            LT(2,  KC_SPC),            LT(2,  KC_SPC),   MO(3),            MO(4)
    ),

    [2] = LAYOUT_split_3x6_3(
      KC_F1,            KC_F2,            KC_F3,            KC_F4,            KC_F5,            KC_F6,                     KC_7,             KC_8,             KC_9,             KC_PLUS,          KC_ASTR,          KC_DEL,
      KC_F7,            KC_F8,            KC_F9,            KC_F10,           KC_F11,           KC_F12,                    KC_4,             KC_5,             KC_6,             KC_MINS,          KC_SLSH,          _______,
      _______,          _______,          _______,          _______,          _______,          _______,                   KC_1,             KC_2,             KC_3,             _______,          _______,          _______,
                                                            _______,          _______,          KC_SPC,                    KC_DOT,           KC_0,             KC_EQL
    ),

    [3] = LAYOUT_split_3x6_3(
      _______,          A(KC_F2),         _______,          A(KC_F4),         C(KC_F2),         S(KC_F9),                  C(KC_PGUP),       KC_HOME,          KC_UP,            KC_END,           _______,          _______,
      KC_VOLD,          _______,          _______,          _______,          _______,          _______,                   C(KC_PGDN),       KC_LEFT,          KC_DOWN,          KC_RGHT,          _______,          KC_VOLU,
      _______,          _______,          _______,          _______,          _______,          _______,                   _______,          _______,          _______,          _______,          _______,          _______,
                                                            _______,          _______,          _______,                   C(A(KC_LEFT)),    _______,          C(A(KC_RGHT))
    ),

    [4] = LAYOUT_split_3x6_3(
      QK_BOOT,          KC_CIRC,          KC_HASH,          KC_TILD,          S(KC_0),          S(KC_9),                   S(KC_9),          S(KC_0),          KC_TILD,          KC_HASH,          KC_CIRC,          _______,
      KC_BSLS,          KC_AMPR,          KC_DLR,           KC_EXLM,          KC_RBRC,          KC_LBRC,                   KC_LBRC,          KC_RBRC,          KC_EXLM,          KC_DLR,           KC_AMPR,          KC_BSLS,
      KC_GRV,           KC_ASTR,          KC_PERC,          KC_AT,            S(KC_RBRC),       S(KC_LBRC),                S(KC_LBRC),       S(KC_RBRC),       KC_AT,            KC_PERC,          KC_ASTR,          KC_GRV,
                                                            KC_QUES,          KC_PIPE,          KC_UNDS,                   KC_UNDS,          KC_PIPE,          KC_QUES
    ),

    [5] = LAYOUT_split_3x6_3(
      _______,          _______,          _______,          _______,          _______,          _______,                   _______,          RALT(S(KC_QUOT)), RALT(KC_TILD),    RALT(KC_COMM),    _______,          _______,
      _______,          RALT(KC_A),       RALT(KC_O),       RALT(KC_E),       _______,          _______,                   _______,          RALT(KC_QUOT),    RALT(KC_CIRC),    RALT(KC_GRV),     _______,          _______,
      _______,          _______,          _______,          _______,          _______,          _______,                   _______,          _______,          _______,          _______,          _______,          TG(1),
                                                            _______,          _______,          _______,                   _______,          _______,          _______
    )
};

typedef struct __attribute__((packed)) {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t g;
    uint8_t h;
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint8_t l;
    uint8_t m;
    uint8_t n;
    uint8_t o;
    uint8_t p;
    uint8_t q;
    uint8_t r;
    uint8_t s;
    uint8_t t;
    uint8_t u;
    uint8_t v;
    uint8_t w;
    uint8_t x;
    uint8_t y;
    uint8_t z;
} alphabet_counter_t;

typedef struct __attribute__((packed)) {
    alphabet_counter_t alphabet_stats;
} master_to_slave_t;

