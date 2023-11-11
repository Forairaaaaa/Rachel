/**
 * @file lgfx_fx.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "lgfx_fx.h"

  void LGFX_SpriteFx::drawFastHLineInDifference( int32_t x, int32_t y, int32_t w)
  {
    if (!_panel->isReadable())
      drawFastHLine(x, y, w);

    startWrite();

    // Get fill color 
    lgfx::rgb888_t fill_color;
    fill_color.set(_write_conv.revert_rgb888(_color.raw));

    lgfx::bgr888_t last_color_buffer;
    lgfx::bgr888_t color_buffer;
    uint32_t draw_line_width = 0;

    readRectRGB(x, y, 1, 1, &color_buffer);
    last_color_buffer.R8(abs((int16_t)fill_color.R8() - color_buffer.R8()));
    last_color_buffer.G8(abs((int16_t)fill_color.G8() - color_buffer.G8()));
    last_color_buffer.B8(abs((int16_t)fill_color.B8() - color_buffer.B8()));

    for (int j = 0; j < w; j++)
    {
      // Get difference 
      readRectRGB(x + j, y, 1, 1, &color_buffer);
      color_buffer.R8(abs((int16_t)fill_color.R8() - color_buffer.R8()));
      color_buffer.G8(abs((int16_t)fill_color.G8() - color_buffer.G8()));
      color_buffer.B8(abs((int16_t)fill_color.B8() - color_buffer.B8()));

      // If comes new color 
      if (color_buffer.get() != last_color_buffer.get()) {
        setColor(last_color_buffer);
        drawFastHLine(x + j - draw_line_width, y, draw_line_width);
        last_color_buffer = color_buffer;
        // If also reach the end of line 
        if (j == w - 1) {
          draw_line_width = 0;
        }
        else {
          draw_line_width = 1;
          continue;
        }
      }
      // If reach the end of line 
      if (j == w - 1) {
        setColor(last_color_buffer);
        drawFastHLine(x + j - draw_line_width, y, draw_line_width + 1);
        draw_line_width = 0;
        last_color_buffer = color_buffer;
        break;
      }
      draw_line_width++;
    }

    setColor(fill_color);
    endWrite();
  }


  void LGFX_SpriteFx::fillRectInDifference( int32_t x, int32_t y, int32_t w, int32_t h)
  {
    if (!_panel->isReadable())
      fillRect(x, y, w, h);

    _adjust_abs(x, w);
    _adjust_abs(y, h);

    startWrite();
    for (int i = 0; i < h; i++) 
    {
      drawFastHLineInDifference(x, y + i, w);
    }
    endWrite();
  }


  constexpr float LoAlphaTheshold = 1.0f / 32.0f;
  constexpr float HiAlphaTheshold = 1.0f - LoAlphaTheshold;

  void LGFX_SpriteFx::fillSmoothRoundRectInDifference(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r)
  {
    if (!_panel->isReadable())
      fillSmoothRoundRect(x, y, w, h, r);

    startWrite();
    int32_t xs = 0;
    int32_t cx = 0;
    uint32_t rgb888 = _write_conv.revert_rgb888(_color.raw);
    // Limit radius to half width or height
    if (r > w / 2) r = w / 2;
    if (r > h / 2) r = h / 2;

    y += r;
    h -= 2 * r;
    fillRectInDifference(x, y, w, h);
    h--;
    x += r;
    w -= 2 * r + 1;
    int32_t r1 = r * r;
    r++;
    int32_t r2 = r * r;

    for (int32_t cy = r - 1; cy > 0; cy--)
    {
      int32_t dy2 = (r - cy) * (r - cy);
      for (cx = xs; cx < r; cx++)
      {
        int32_t hyp2 = (r - cx) * (r - cx) + dy2;
        if (hyp2 <= r1) break;
        if (hyp2 >= r2) continue;
        float alphaf = (float)r - sqrtf(hyp2);
        if (alphaf > HiAlphaTheshold) break;
        xs = cx;
        if (alphaf < LoAlphaTheshold) continue;
        uint8_t alpha = alphaf * 255;
        fillRectAlpha(x + cx - r    , y + cy - r    , 1, 1, alpha, rgb888);
        fillRectAlpha(x - cx + r + w, y + cy - r    , 1, 1, alpha, rgb888);
        fillRectAlpha(x - cx + r + w, y - cy + r + h, 1, 1, alpha, rgb888);
        fillRectAlpha(x + cx - r    , y - cy + r + h, 1, 1, alpha, rgb888);
      }
      drawFastHLineInDifference(x + cx - r, y + cy - r, 2 * (r - cx) + 1 + w);
      drawFastHLineInDifference(x + cx - r, y - cy + r + h, 2 * (r - cx) + 1 + w);
    }
    endWrite();
  }
  