// #include <Arduino.h>
#ifndef SDL_H
#define SDL_H

#include <stdint.h>
#define byte uint8_t

int sdl_update(void);
void sdl_init(void);
void sdl_frame(void);
void sdl_quit(void);
byte* sdl_get_framebuffer(void);
unsigned int sdl_get_buttons(void);
unsigned int sdl_get_directions(void);
#endif
