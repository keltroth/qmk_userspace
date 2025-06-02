#include <stdint.h>
#include <transactions.h>
#include <host.h>
#include <print.h>
#include <keymap_common.h>
#include <split_util.h>

#include "djangounet.h"
#include "oled_driver.h"

#define NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE 27

/**
 * @brief Advanced user function for customizing RGB matrix LED indicators.
 *
 * This function allows the user to implement custom LED indicator behavior for the RGB matrix.
 * It is called with the range of LEDs to be processed, specified by led_min and led_max.
 *
 * @param led_min The index of the first LED to process.
 * @param led_max The index of the last LED to process.
 * @return true if the function handled the LED processing, false to allow default processing.
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
    	RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_KEY, 255, 0, 0);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_KEY, 0, 0, 0);
    }

    uint8_t layer = get_highest_layer(layer_state);

    if (layer > 1) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index <= led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, 50*layer, 120, 0);
                }
            }
        }
    }
    return true;
}

static uint32_t last_sync_housekeeping = 0;
static uint32_t last_sync_reduce_counters = 0;

static alphabet_counter_t alphabet_counter = {
    .a = 0,
    .b = 0,
    .c = 0,
    .d = 0,
    .e = 0,
    .f = 0,
    .g = 0,
    .h = 0,
    .i = 0,
    .j = 0,
    .k = 0,
    .l = 0,
    .m = 0,
    .n = 0,
    .o = 0,
    .p = 0,
    .q = 0,
    .r = 0,
    .s = 0,
    .t = 0,
    .u = 0,
    .v = 0,
    .w = 0,
    .x = 0,
    .y = 0,
    .z = 0
};

static master_to_slave_t master_to_slave = { .alphabet_stats = {
    .a = 0,
    .b = 0,
    .c = 0,
    .d = 0,
    .e = 0,
    .f = 0,
    .g = 0,
    .h = 0,
    .i = 0,
    .j = 0,
    .k = 0,
    .l = 0,
    .m = 0,
    .n = 0,
    .o = 0,
    .p = 0,
    .q = 0,
    .r = 0,
    .s = 0,
    .t = 0,
    .u = 0,
    .v = 0,
    .w = 0,
    .x = 0,
    .y = 0,
    .z = 0
} };


static master_to_slave_t *const split_shared_memory = &master_to_slave;

/**
 * @brief Initializes the OLED display rotation.
 *
 * This function is called during the OLED initialization process.
 * It allows the user to set a custom rotation for the OLED display.
 *
 * @param rotation The current OLED rotation setting.
 * @return The desired OLED rotation setting.
 */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_0;
    }
}

/**
 * Processes custom keycodes and handles user-defined key actions.
 *
 * This function is called every time a key event is registered. It allows
 * the user to implement custom behavior for specific keycodes, such as
 * macros, layer switching, or other advanced features.
 *
 * @param keycode The keycode of the key event.
 * @param record  Pointer to the keyrecord_t struct containing event information.
 * @return true if further processing should continue, false to halt processing.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint16_t base_keycode = keycode;

        if (IS_QK_MOD_TAP(keycode)) {
            base_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else if (IS_QK_LAYER_TAP(keycode)) {
            base_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
        }

		if (base_keycode >= KC_A && base_keycode <= KC_Z) {
		    int index = base_keycode - KC_A;
            *((uint8_t *)&alphabet_counter + (index * sizeof(uint8_t))) = *((uint8_t *)&alphabet_counter + (index * sizeof(uint8_t))) + 1;
		}
	}
	return true;
}

/**
 * @brief Renders the current layer state on the OLED display.
 *
 * This function is responsible for displaying the active layer(s) information
 * on the OLED screen. It can be used to provide visual feedback to the user
 * about which keyboard layer is currently active.
 *
 * @return false to indicate that no further rendering is needed.
 */
static bool oled_render_layer_state(void) {
    oled_write_P(PSTR("Basic"), get_highest_layer(layer_state) == 0);
    oled_write_P(PSTR("Typin"), get_highest_layer(layer_state) == 1);
    oled_write_P(PSTR("Func "), get_highest_layer(layer_state) == 2);
    oled_write_P(PSTR("Nav  "), get_highest_layer(layer_state) == 3);
    oled_write_P(PSTR("Specs"), get_highest_layer(layer_state) == 4);
    oled_write_P(PSTR("Accnt"), get_highest_layer(layer_state) == 5);


    oled_set_cursor(0, 15);
	oled_write_P(PSTR("ABCDE"), host_keyboard_led_state().caps_lock);
    return false;
}

/**
 * @brief Renders an animation on the OLED display.
 *
 * This function handles the drawing of animation frames on the OLED.
 * It is typically called periodically to update the display.
 *
 * @return false to indicate that no further rendering is needed.
 */
static bool oled_render_animation(void) {
    oled_clear();
    for (int i = 0; i < sizeof(alphabet_counter); i++) {
        uint8_t count = *((uint8_t *)&alphabet_counter + (i * sizeof(uint8_t)));
        for (uint8_t j = 0; j <= count; j++) {
            oled_write_pixel(j, i, true);
        }
    }
    return false;
}

/**
 * @brief   User-defined OLED task function.
 *
 * This function is called periodically to handle custom OLED display updates.
 * Implement custom rendering logic here to display information on the OLED screen.
 *
 * @return  true if the OLED display was updated, false otherwise.
 */
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        return oled_render_layer_state();
    } else {
        return oled_render_animation();
    }
}

/**
 * @brief Handles synchronization events on the slave side in a split keyboard setup.
 *
 * This function is called when the slave side receives synchronization data from the master.
 * It processes the incoming data and can optionally prepare a response to send back.
 *
 * @param in_buflen   Length of the incoming data buffer.
 * @param in_data     Pointer to the incoming data buffer.
 * @param out_buflen  Length of the outgoing data buffer.
 * @param out_data    Pointer to the outgoing data buffer to be filled with response data.
 */
void sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    alphabet_counter = m2s->alphabet_stats;
}

/**
 * @brief User-defined keyboard post-initialization function.
 *
 * This function is called after the keyboard has been initialized.
 * Use this function to perform custom setup tasks, such as enabling
 * features, setting default layers, or configuring hardware-specific
 * settings.
 *
 * This is a QMK firmware user hook.
 */
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    if (!is_keyboard_master()) {
        transaction_register_rpc(SYNC_STATS_CMD, sync_slave_handler);
    }
}

/**
 * @brief User-defined housekeeping task.
 *
 * This function is called periodically by the QMK firmware to perform
 * custom background tasks. Override this function to implement any
 * user-specific housekeeping logic that should run outside of the main
 * keyboard loop.
 *
 * Typical use cases include:
 * - Managing timers or counters
 * - Handling custom LED effects
 * - Performing background checks or updates
 *
 * Note: This function runs frequently, so keep it efficient to avoid
 * impacting keyboard performance.
 */
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        if (timer_elapsed32(last_sync_housekeeping) > 500) {
            split_shared_memory->alphabet_stats = alphabet_counter;
            if (transaction_rpc_send(SYNC_STATS_CMD, sizeof(*split_shared_memory), split_shared_memory)) {
                last_sync_housekeeping = timer_read32();
            }
        }
        if (timer_elapsed32(last_sync_reduce_counters) > 1000) {
            for (int i = 0; i < sizeof(alphabet_counter); i++) {
                if (*((uint8_t *)&alphabet_counter + i) > 0) {
                    *((uint8_t *)&alphabet_counter + i) -= 1;
                }
            }
            last_sync_reduce_counters = timer_read32();
        }
    }
}

