// https://www.nesdev.org/wiki/Controller_reading_code
// TODO: May need to include turbo a and turbo b
typedef enum {
    RIGHT = 1 << 7,
    LEFT = 1 << 6,
    DOWN = 1 << 5,
    UP = 1 << 4,
    START = 1 << 3,
    SELECT = 1 << 2,
    BUTTON_B = 1 << 1,
    BUTTON_A = 1
} JoypadButtons;

typedef struct {
    bool strobe; // While high, shift registers in controller are reloaded from button states (Get current buttons)
    uint8_t button_index;
    JoypadButtons buttons;
}