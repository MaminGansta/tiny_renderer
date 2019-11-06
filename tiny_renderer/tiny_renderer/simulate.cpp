#include "simulate.h"

bool barycentric(Vec3f A, Vec3f B, Vec3f C, Vert3i P, Vec3f *out) {
	Vec3f s[2];
	for (int i = 0; i < 2; i++ ) {
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}
	Vec3f u = cross(s[0], s[1]);
	if (std::abs(u[2]) > 1e-2)
	{
		out->x = 1.0f - (u.x + u.y) / u.z;
		out->y = u.y / u.z;
		out->z = u.x / u.z;
		if (out->x >= 0 && out->y >= 0 && out->z >= 0)
			return true;
	}
	return false;
}

void triangle(Vec3f* pts, Vec2i* uv, float* zbuffer, Render_State* surface, Model* model,  float intensity)
{
	if (pts[0].y == pts[1].y && pts[0].y == pts[2].y) return; // i don't care about degenerate triangles
	if (pts[0].y > pts[1].y) { std::swap(pts[0], pts[1]); std::swap(uv[0], uv[1]); }
	if (pts[0].y > pts[2].y) { std::swap(pts[0], pts[2]); std::swap(uv[0], uv[2]); }
	if (pts[1].y > pts[2].y) { std::swap(pts[1], pts[2]); std::swap(uv[1], uv[2]); }

	Vert2f bot_left(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vert2f top_right(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bot_left[j] = MAX(0.0f, MIN(bot_left[j], pts[i][j]));
			top_right[j] = MIN(surface->height, MAX(top_right[j], pts[i][j]));
		}
	}
	Vert3i P;
	for (P.x = bot_left.x; P.x < top_right.x; P.x += 1.0f)
	{
		for (P.y = bot_left.y; P.y < top_right.y; P.y += 1.0f)
		{
			Vert3f bar;
			if (barycentric(pts[0], pts[1], pts[2], P, &bar))
			{
				float z = 0;
				for (int i = 0; i < 3; i++)
					z += pts[i][2] * bar[i];

				if (zbuffer[int(P.x + P.y * surface->width)] < z)
				{
					Vert2i uvP;
					uvP.x = uv[0].x * bar[0] + uv[1].x * bar[1] + uv[2].x * bar[2];
					uvP.y = uv[0].y * bar[0] + uv[1].y * bar[1] + uv[2].y * bar[2];

					TGAColor color = model->diffuse(uvP);
					zbuffer[int(P.x + P.y * surface->width)] = z;
					for (int i = 0; i < 4; i++)
						color.raw[i] *= intensity;
					surface->memory[P.y * surface->width + P.x] = *(uint32_t*)(&color);
				}
			}
		}
	}
}

void frame(Render_State* serface)
{

}