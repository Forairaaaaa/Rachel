

/*
#include <SDL/SDL.h>
#include <sys/time.h>
static SDL_Surface *screen;
static unsigned int frames;
static struct timeval tv1, tv2;



static int button_start, button_select, button_a, button_b, button_down, button_up, button_left, button_right;

void sdl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

int sdl_update(void)
{
	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			return 1;

		if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_a:
					button_a = 1;
				break;
				case SDLK_s:
					button_b = 1;
				break;
				case SDLK_d:
					button_select = 1;
				break;
				case SDLK_f:
					button_start = 1;
				break;
				case SDLK_LEFT:
					button_left = 1;
				break;
				case SDLK_RIGHT:
					button_right = 1;
				break;
				case SDLK_DOWN:
					button_down = 1;
				break;
				case SDLK_UP:
					button_up = 1;
				break;
			}
		}

		if(e.type == SDL_KEYUP)
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_a:
					button_a = 0;
				break;
				case SDLK_s:
					button_b = 0;
				break;
				case SDLK_d:
					button_select = 0;
				break;
				case SDLK_f:
					button_start = 0;
				break;
				case SDLK_LEFT:
					button_left = 0;
				break;
				case SDLK_RIGHT:
					button_right = 0;
				break;
				case SDLK_DOWN:
					button_down = 0;
				break;
				case SDLK_UP:
					button_up = 0;
				break;
			}
		}

	}
	return 0;
}

unsigned int sdl_get_buttons(void)
{
	return (button_start*8) | (button_select*4) | (button_b*2) | button_a;
}

unsigned int sdl_get_directions(void)
{
	return (button_down*8) | (button_up*4) | (button_left*2) | button_right;
}

unsigned int *sdl_get_framebuffer(void)
{
	return screen->pixels;
}

void sdl_frame(void)
{
	if(frames == 0)
  		gettimeofday(&tv1, NULL);
	
	frames++;
	if(frames % 1000 == 0)
	{
		gettimeofday(&tv2, NULL);
		printf("Frames %d, seconds: %d, fps: %d\n", frames, tv2.tv_sec - tv1.tv_sec, frames/(tv2.tv_sec - tv1.tv_sec));
	}
	SDL_Flip(screen);
}

void sdl_quit()
{
	SDL_Quit();
}
*/
// #include "SPI.h"
// #include "Adafruit_GFX.h"
// #include "Adafruit_ILI9341.h"

// #define _cs   22   // 3 goes to TFT CS
// #define _dc   21   // 4 goes to TFT DC
// #define _mosi 23  // 5 goes to TFT MOSI
// #define _sclk 19  // 6 goes to TFT SCK/CLK
// #define _rst  18  // ESP RST to TFT RESET
// #define _miso 25    // Not connected
// #define _led   5
// //       3.3V     // Goes to TFT LED  
// //       5v       // Goes to TFT Vcc
// //       Gnd      // Goes to TFT Gnd        

// // Use hardware SPI (on ESP D4 and D8 as above)
// //Adafruit_ILI9341 tft = Adafruit_ILI9341(_CS, _DC);
// // If using the breakout, change pins as desired
// Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst, _miso);

// void backlighting(bool state) {
//     if (!state) {
//         digitalWrite(_led, LOW);
//     }
//     else {
//         digitalWrite(_led, HIGH);
//     }
// }

#include "../../../hal/hal.h"
#define byte uint8_t

#define GAMEBOY_HEIGHT 160
#define GAMEBOY_WIDTH 144
byte pixels[GAMEBOY_HEIGHT * GAMEBOY_WIDTH / 4];

static int button_start, button_select, button_a, button_b, button_down, button_up, button_left, button_right;

byte getColorIndexFromFrameBuffer(int x, int y) {
  int offset = x + y * 160;
  return (pixels[offset >> 2] >> ((offset & 3) << 1)) & 3;
}

// const int color[] = {0x000000, 0x555555, 0xAAAAAA, 0xFFFFFF};
const int color[] = {TFT_BLACK, TFT_DARKGRAY, TFT_LIGHTGRAY, TFT_WHITE};

void SDL_Flip(byte *screen)
{
    //tft.fillScreen(ILI9341_BLACK);
    
    int i,j;
    int x_offset = 40;
    int y_offset = 46;
    for(i = 0;i<GAMEBOY_WIDTH;i++)
    {
        for(j = 0;j<GAMEBOY_HEIGHT;j++)
        {
            // tft.drawPixel(j, i, color[getColorIndexFromFrameBuffer(j, i)]);
            HAL::GetCanvas()->drawPixel(j + x_offset, i + y_offset, color[getColorIndexFromFrameBuffer(j, i)]);
        }
    }
    memset(pixels, 0, GAMEBOY_HEIGHT * GAMEBOY_WIDTH / 4 * sizeof(byte));

    // HAL::CanvasUpdate();
    HAL::GetCanvas()->pushRotateZoom(0, 1.5, 1.5);
}

void sdl_init(void)
{
//   tft.begin();
//   pinMode(_led, OUTPUT);
//   backlighting(true);
  
//   // read diagnostics (optional but can help debug problems)
//   uint8_t x = tft.readcommand8(ILI9341_RDMODE);
//   Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
//   x = tft.readcommand8(ILI9341_RDMADCTL);
//   Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
//   x = tft.readcommand8(ILI9341_RDPIXFMT);
//   Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
//   x = tft.readcommand8(ILI9341_RDIMGFMT);
//   Serial.print("Image Format: 0x"); Serial.println(x, HEX);
//   x = tft.readcommand8(ILI9341_RDSELFDIAG);
//   Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
//   tft.fillScreen(ILI9341_RED);

//   gpio_pad_select_gpio(GPIO_NUM_14);
//   gpio_set_direction(GPIO_NUM_14, GPIO_MODE_INPUT);

//   gpio_pad_select_gpio(GPIO_NUM_27);
//   gpio_set_direction(GPIO_NUM_27, GPIO_MODE_INPUT);

    HAL::GetCanvas()->fillScreen(TFT_BLACK);
}

int sdl_update(void)
{
	// //tft.fillScreen(ILI9341_RED);
    // button_start = !gpio_get_level(GPIO_NUM_14);
    // button_right = !gpio_get_level(GPIO_NUM_27);

    button_start = HAL::GetButton(GAMEPAD::BTN_START);
    button_select = HAL::GetButton(GAMEPAD::BTN_SELECT);
    button_a = HAL::GetButton(GAMEPAD::BTN_A);
    button_b = HAL::GetButton(GAMEPAD::BTN_B);
    button_down = HAL::GetButton(GAMEPAD::BTN_DOWN);
    button_up = HAL::GetButton(GAMEPAD::BTN_UP);
    button_left = HAL::GetButton(GAMEPAD::BTN_LEFT);
    button_right = HAL::GetButton(GAMEPAD::BTN_RIGHT);

	return 0;
}

unsigned int sdl_get_buttons(void)
{
	return (button_start*8) | (button_select*4) | (button_b*2) | button_a;
}

unsigned int sdl_get_directions(void)
{
	return (button_down*8) | (button_up*4) | (button_left*2) | button_right;
}

byte* sdl_get_framebuffer(void)
{
	return pixels;
}

void sdl_frame(void)
{
  /* 
	if(frames == 0)
		gettimeofday(&tv1, NULL);
	
	frames++;
	if(frames % 1000 == 0)
	{
		gettimeofday(&tv2, NULL);
		printf("Frames %d, seconds: %d, fps: %d\n", frames, tv2.tv_sec - tv1.tv_sec, frames/(tv2.tv_sec - tv1.tv_sec));
	}
 */
	SDL_Flip(pixels);
}


