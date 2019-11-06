#pragma once
#include <limits>
#include "model.h"
#include "geometry.h"
#include "render_stuff.h"

#undef max
#undef min

#define MAX(a, b) (a > b? a: b)
#define MIN(a, b) (a < b? a: b)

bool barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P);

void triangle(Vec3f* pts, Vec2i* texture, float* zbuffer, Render_State* surface, Model* model, float intensity);