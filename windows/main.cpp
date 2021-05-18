#include "webview.hpp"
#include <tchar.h>

static TCHAR *szWindowClass = _T("DesktopApp");
static TCHAR *szTitle = _T("nekow");

HINSTANCE hInst;

webview::WebView *webInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
		_In_ HINSTANCE hInstance,
		_In_ HINSTANCE hPrevInstance,
		_In_ LPSTR lpCmdLine,
		_In_ int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
		return 1;

	HWND hWnd = CreateWindow(
			szWindowClass,
			szTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			1200, 900,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
		return 1;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	webInst = new webview::WebView(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete webInst;

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		if (webInst != nullptr) 
		{
			RECT bounds;
			GetClientRect(hWnd, &bounds);
			webInst->put_Bounds(bounds);
		};
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}