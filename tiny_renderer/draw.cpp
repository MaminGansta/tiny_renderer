#include <math.h>
#include <stdint.h>
#include "render_stuff.h"

void drawPixel(Render_State* surface, int x, int y, uint32_t color) {
	surface->memory[y * surface->width + x] = color;
}


void drawLine(Render_State* surface, int x, int y, int x2, int y2, uint32_t color) {
	bool yLonger = false;
	int shortLen = y2 - y;
	int longLen = x2 - x;
	if (abs(shortLen) > abs(longLen)) {
		int swap = shortLen;
		shortLen = longLen;
		longLen = swap;
		yLonger = true;
	}
	int decInc;
	if (longLen == 0) decInc = 0;
	else decInc = (shortLen << 16) / longLen;

	if (yLonger) {
		if (longLen > 0) {
			longLen += y;
			for (int j = 0x8000 + (x << 16); y <= longLen; ++y) {
				drawPixel(surface, j >> 16, y, color);
				j += decInc;
			}
			return;
		}
		longLen += y;
		for (int j = 0x8000 + (x << 16); y >= longLen; --y) {
			drawPixel(surface, j >> 16, y, color);
			j -= decInc;
		}
		return;
	}

	if (longLen > 0) {
		longLen += x;
		for (int j = 0x8000 + (y << 16); x <= longLen; ++x) {
			drawPixel(surface, x, j >> 16, color);
			j += decInc;
		}
		return;
	}
	longLen += x;
	for (int j = 0x8000 + (y << 16); x >= longLen; --x) {
		drawPixel(surface, x, j >> 16, color);
		j -= decInc;
	}

}

void drawSquare(Render_State* surface, int x, int y, int x2, int y2, uint32_t color) {
	drawLine(surface, x, y, x2, y2, color);
	drawLine(surface, x2, y2, x2 + (y - y2), y2 + (x2 - x), color);
	drawLine(surface, x, y, x + (y - y2), y + (x2 - x), color);
	drawLine(surface, x + (y - y2), y + (x2 - x), x2 + (y - y2), y2 + (x2 - x), color);
}


void drawRect(Render_State* surface, int x, int y, int x2, int y2, uint32_t color) {
	drawLine(surface, x, y, x2, y, color);
	drawLine(surface, x2, y, x2, y2, color);
	drawLine(surface, x2, y2, x, y2, color);
	drawLine(surface, x, y2, x, y, color);
}