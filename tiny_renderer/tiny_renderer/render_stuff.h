#pragma once
#include <Windows.h>
#include <stdint.h>
#include "tgaimage.h"

struct Render_State {
	int height, width;
	uint32_t* memory;

	BITMAPINFO bitmap_info;
};

inline uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255)
{
	return ((uint32_t)a << 24) + ((uint32_t)r << 16) + ((uint32_t)b << 8) + g;
}

inline uint32_t unpack_tga_color(TGAColor color)
{
	return ((uint32_t)color.r << 24 | color.g << 16 | color.b << 8 | (uint32_t)color.a);
}
