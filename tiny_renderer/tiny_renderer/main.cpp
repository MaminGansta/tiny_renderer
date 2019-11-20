#include <windows.h>
#include "Timer.h"
#include "render_stuff.h"
#include "simulate.h"
#include "geometry.h"
#include "Model.h"
#include "vector.h"

using namespace m::Timer;


Render_State surface;
bool running = true;

int start_width = 800;
int start_height = 800;
int win_width = start_width + 39;
int win_height = start_height + 16;


LRESULT CALLBACK win_callback(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam)
{
	LRESULT res = 0;

	switch (uMsg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			running = false;
		} break;

		case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			surface.width = rect.right - rect.left;
			surface.height = rect.bottom - rect.top;

			int size = surface.width * surface.height * sizeof(unsigned int);

			if (surface.memory) VirtualFree(surface.memory, 0 , MEM_RELEASE);
			surface.memory = (uint32_t*)VirtualAlloc(0, size * sizeof(uint32_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			surface.bitmap_info.bmiHeader.biSize = sizeof(surface.bitmap_info.bmiHeader);
			surface.bitmap_info.bmiHeader.biWidth = surface.width;
			surface.bitmap_info.bmiHeader.biHeight = surface.height;
			surface.bitmap_info.bmiHeader.biPlanes = 1;
			surface.bitmap_info.bmiHeader.biBitCount = 32;
			surface.bitmap_info.bmiHeader.biCompression = BI_RGB;

		} break;

		default:
		{
			res = DefWindowProc(hwnd, uMsg, wparam, lParam);
		}
	}
	return res;
}





int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPiv, LPSTR args, int someshit)
{
	// create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game";
	window_class.lpfnWndProc = win_callback;

	// reg window
	RegisterClass(&window_class);

	// create window
	HWND window = CreateWindow(window_class.lpszClassName, "Game!!!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, win_width, win_height, 0, 0, hInst, 0);
	HDC hdc = GetDC(window);

	// Model
	Model model("obj/african_head.obj");
	//Model model("obj/diablo3_pose/diablo3_pose.obj");
	float* zbuffer = new float[surface.width * surface.height];


	timer_init();
	while (running)
	{
		// Input
		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Simulate
		Vec3f light_dir(0, 0, -1);
		for (int i = surface.width * surface.height; i--;)
			zbuffer[i] = -std::numeric_limits<float>::max();


		for (int i = 0; i < model.nfaces(); i++) {
			m::vector<int> face = model.face(i);
			Vec3f screen_coords[3];
			Vec3f world_coords[3];
			for (int j = 0; j < 3; j++) {
				Vec3f v = model.vert(face[j]);
				screen_coords[j] = Vec3f((v.x + 1.0f) * surface.width / 2.0f, (v.y + 1.0f) * surface.height / 2.0f, v.z);
				world_coords[j] = v;
			}
			Vec3f n;
			cproduct((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]), &n);
			n.normalize();
			float intensity = dproduct(n, light_dir);
			if (intensity > 0)
			{
				Vec2i uv[3];
				for (int k = 0; k < 3; k++)
					uv[k] = model.uv(i, k);

				triangle(screen_coords, uv, zbuffer, &surface, &model, intensity);
			}
		}

		// Render
		StretchDIBits(hdc, 0, 0, surface.width, surface.height, 0, 0, surface.width, surface.height, surface.memory, &surface.bitmap_info, DIB_RGB_COLORS, SRCCOPY);


		// Timer
		timer_update();

		// Log
		
	}
		
	return 0;
}