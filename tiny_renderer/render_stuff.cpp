#include <Windows.h>

struct Render_State {
	int height, width;
	uint32_t* memory;

	BITMAPINFO bitmap_info;
};

Render_State surface;


struct Color
{
	union
	{
		 struct { uint8_t b, g, r, a; };
		uint8_t raw[4];
		uint32_t whole;
	};
};