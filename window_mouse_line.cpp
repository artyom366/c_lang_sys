#include <windows.h>

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
WORD px, py;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS w;

	memset(&w, 0, sizeof(w));

	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = L"My Class";

	RegisterClass(&w);

	hwnd = CreateWindow(L"My Class", L"My title", WS_OVERLAPPEDWINDOW, 300, 200, 200, 200, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	WORD nx, ny;
	WCHAR* message = (wchar_t *)calloc(16, sizeof(wchar_t));

	switch (Message) {

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 50, 50, L"Hello World!", 13);
		EndPaint(hwnd, &ps);
		break;

	case WM_RBUTTONUP:
		hdc = GetDC(hwnd);
		nx = LOWORD(lparam);
		ny = HIWORD(lparam);
		MoveToEx(hdc, nx, ny, NULL);
		LineTo(hdc, px, py);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hwnd);
		px = LOWORD(lparam);
		py = HIWORD(lparam);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}

	return 0;
}