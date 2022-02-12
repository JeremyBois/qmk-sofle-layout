#pragma once

#include QMK_KEYBOARD_H

//
// Based on works from callum-oakley
// https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
//

// Represents the four states a oneshot trigger can be in
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;

// Represents the three states a move/hold layer trigger can be in
typedef enum {
    mh_cleared,
    mh_down_unused,
    mh_down_used,
} movehold_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(oneshot_state *state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// Custom oneshot layer implementation that doesn't rely on timers. If the key is held
// and another key is pressed then the layer is turn off else if the layer is released before any other
// trigger then the layer stay one until a next key is pressed
void update_oneshot_layer(oneshot_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// To be implemented by the consumer. Defines keys to cancel oneshot mods / layers.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored_key(uint16_t keycode);

// Custom move / hold layer implementation that doesn't rely on timers. If the key is held
// and another key is pressed then the layer is turn off when the the layer key is released.
// If the layer is released before any other trigger then the layer stay one.
void update_move_hold_layer(movehold_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record);

// Same as update_move_hold_layer but using layer_on not layer_move
void update_on_hold_layer(movehold_state *state, uint16_t layer, uint16_t trigger, uint16_t keycode, keyrecord_t *record);