#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "isr.h"
#include "libs/io.h"
#include <stdbool.h>
#include <stdint.h>

#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64
#define PS2_SET_LEDS 0xED

#define SHIFT_MOD (1 << 0)
#define CAPS_LOCK_MOD (1 << 1)

unsigned char key_map[] = {
    0,   0,    '1',  '2', '3',  '4', '5',  '6', '7', '8', '9', '0', '-',
    '=', '\b', '\t', 'q', 'w',  'e', 'r',  't', 'y', 'u', 'i', 'o', 'p',
    '[', ']',  '\n', 3,   'a',  's', 'd',  'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`',  4,   '\\', 'z', 'x',  'c', 'v', 'b', 'n', 'm', ',',
    '.', '/',  4,    '*', 5,    ' ', '\0', 0,   0,   0,   0,   0,   0,
    0,   0,    0,    0,   0,    0,   '7',  '8', '9', '-', '4', '5', '6',
    '+', '1',  '2',  '3', '0',  '.', 0,    0};

unsigned char caps_lock_key_map[] = {
    0,   0,    '1',  '2', '3',  '4', '5',  '6', '7', '8', '9', '0', '-',
    '=', '\b', 2,    'Q', 'W',  'E', 'R',  'T', 'Y', 'U', 'I', 'O', 'P',
    '[', ']',  '\n', 3,   'A',  'S', 'D',  'F', 'G', 'H', 'J', 'K', 'L',
    ';', '\'', '`',  4,   '\\', 'Z', 'X',  'C', 'V', 'B', 'N', 'M', ',',
    '.', '/',  4,    '*', 5,    ' ', '\0', 0,   0,   0,   0,   0,   0,
    0,   0,    0,    0,   0,    0,   '7',  '8', '9', '-', '4', '5', '6',
    '+', '1',  '2',  '3', '0',  '.', 0,    0};

unsigned char shift_key_map[] = {
    0,   0,    '!',  '@', '#', '$', '%',  '^', '&', '*', '(', ')', '_',
    '+', '\b', 2,    'Q', 'W', 'E', 'R',  'T', 'Y', 'U', 'I', 'O', 'P',
    '{', '}',  '\n', 3,   'A', 'S', 'D',  'F', 'G', 'H', 'J', 'K', 'L',
    ':', '\"', '~',  4,   '|', 'Z', 'X',  'C', 'V', 'B', 'N', 'M', '<',
    '>', '?',  4,    '*', 5,   ' ', '\0', 0,   0,   0,   0,   0,   0,
    0,   0,    0,    0,   0,   0,   '7',  '8', '9', '-', '4', '5', '6',
    '+', '1',  '2',  '3', '0', '.', 0,    0};

unsigned char current_led_states = 0;
unsigned char current_mods = 0;

unsigned char *cur_key_map = key_map;

void ps2_wait_input_buffer() {
  while (inb(PS2_STATUS_PORT) & 2)
    ;
}

void ps2_turn_off_caps_lock_led(unsigned char cur_leds_state) {
  cur_leds_state &= ~(1 << 2);

  ps2_wait_input_buffer();
  outb(PS2_DATA_PORT, PS2_SET_LEDS);

  ps2_wait_input_buffer();
  outb(PS2_DATA_PORT, cur_leds_state);

  current_led_states = cur_leds_state;
}

void keyboard_callback(struct registers *regs) {
  unsigned char scancode = inb(0x60);
  if (scancode < 0x80) {
    if (scancode > 85) {
      kprint_hex(scancode);
    }

    if (scancode == 42 || scancode == 54) {
      current_mods |= SHIFT_MOD;
    }

    else if (scancode == 58) {
      current_mods ^= CAPS_LOCK_MOD;
    } else {
      if (current_mods & SHIFT_MOD)
        cur_key_map = shift_key_map;
      else if (current_mods & CAPS_LOCK_MOD)
        cur_key_map = caps_lock_key_map;
      else
        cur_key_map = key_map;

      kprint_char(cur_key_map[scancode]);
    }
  } else {
    unsigned char released_key = scancode - 0x80;

    if (released_key == 42 || released_key == 54) {
      current_mods &= ~SHIFT_MOD;
    }
  }
  outb(0x20, 0x20);
}

void keyboard_init(void) {
  ps2_turn_off_caps_lock_led(0);
  register_interrupt_handler(33, keyboard_callback);
}
