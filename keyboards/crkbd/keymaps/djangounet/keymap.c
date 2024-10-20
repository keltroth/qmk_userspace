#include <stdbool.h>
#include QMK_KEYBOARD_H

#include "djangounet.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (host_keyboard_led_state().caps_lock) {
    RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_KEY, 255, 255, 255);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_KEY, 0, 0, 0);
    }

    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index <= led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    if (!is_keyboard_master()) {
                        index = -index;
                    }
                    rgb_matrix_set_color(index, 50*layer, 120, 0);
                }
            }
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
}

void generic_accent_dance(uint8_t count, int8_t key) {
    switch (count) {
        case 2:
            tap_code(KC_QUOT);
            tap_code(key);
            break;
        case 3:
            tap_code(KC_BSPC);
            tap_code(KC_GRV);
            tap_code(key);
            break;
        case 4:
            tap_code(KC_BSPC);
            tap_code16(KC_CIRC);
            tap_code(key);
            break;
        case 5:
            tap_code(KC_BSPC);
            tap_code16(KC_DQUO);
            tap_code(key);
            break;
    }
}

void a_accents_each(tap_dance_state_t *state, void *user_data) {
    generic_accent_dance(state->count, KC_A);
}
void e_accents_each(tap_dance_state_t *state, void *user_data) {
    generic_accent_dance(state->count, KC_E);
}
void i_accents_each(tap_dance_state_t *state, void *user_data) {
    generic_accent_dance(state->count, KC_I);
}
void o_accents_each(tap_dance_state_t *state, void *user_data) {
    generic_accent_dance(state->count, KC_O);
}
void u_accents_each(tap_dance_state_t *state, void *user_data) {
    generic_accent_dance(state->count, KC_U);
}

static void oled_render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Specials"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

bool oled_task_user(void) {
    oled_render_layer_state();
    return false;
}
