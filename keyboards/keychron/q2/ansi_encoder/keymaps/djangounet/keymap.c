#include <stdbool.h>
#include QMK_KEYBOARD_H

#include "djangounet.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 255, 255, 255);
    } else {
        rgb_matrix_set_color(30, 0, 0, 0);
    }

    if (get_highest_layer(layer_state) > 1) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index <= led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
}
