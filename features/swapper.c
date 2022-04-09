#include "swapper.h"

void update_swapper(bool *active, bool *old_active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    *old_active = *active; // Keep track of old state
    if (keycode == trigger) {
        switch (keycode) {
            // Handle custom keycode detection when using mod tap
            // https://docs.qmk.fm/#/mod_tap?id=intercepting-mod-taps
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed && record->tap.count) {
                    if (!*active) {
                        *active = true;
                        register_code(cmdish);
                    }
                    register_code(tabish);
                } else {
                    unregister_code(tabish);
                    // Don't unregister cmdish until some other key is hit or released.
                }
                break;
            default:
                if (record->event.pressed) {
                    if (!*active) {
                        *active = true;
                        register_code(cmdish);
                    }
                    register_code(tabish);
                } else {
                    unregister_code(tabish);
                    // Don't unregister cmdish until some other key is hit or released.
                }
                break;
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}
