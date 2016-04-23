#include <windows.h>

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

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
	WORD x, y;
	WCHAR* message = (wchar_t *)calloc(16, sizeof(wchar_t));
	int result;

	switch (Message) {

	case WM_PAINT:
		//http://www.firststeps.ru/mfc/winapi/r.php?37

		hdc = BeginPaint(hwnd, &ps);
		
		OSVERSIONINFO osvi;
		ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		result = GetVersionEx((OSVERSIONINFO*)&osvi);

		if (result )

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}

	return 0;
}

int getOSVersionInfo {

}