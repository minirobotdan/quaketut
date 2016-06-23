#include <stdio.h>
#include <Windows.h>

BOOL IsRunning = TRUE;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	LRESULT Result = 0;

	switch (uMsg) {
	case WM_KEYUP:
		IsRunning = FALSE;
		Result = 56;
		break;
	case WM_ACTIVATE:
	case WM_CREATE:
	case WM_DESTROY:
		break;
	default:
		Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return Result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = MainWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "Module 2";

	if (!RegisterClass(&wc)) {
		exit(EXIT_FAILURE);
	}

	HWND mainwindow;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r;
	r.top = r.left = 0;
	r.right = 800;
	r.bottom = 600;

	AdjustWindowRect(&r, WindowStyle, FALSE);

	mainwindow = CreateWindowEx(
		0,
		"Module 2",
		"Lesson 2.3",
		WindowStyle,
		200,
		200,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		hInstance,
		0
	);

	ShowWindow(mainwindow, SW_SHOWDEFAULT);

	HDC DeviceContext = GetDC(mainwindow);
	PatBlt(DeviceContext, 0, 0, 800, 600, BLACKNESS);
	ReleaseDC(mainwindow, DeviceContext);

	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	double SecondsPerTick = 1.0 / (double)Frequency.QuadPart;

	LARGE_INTEGER Tick, Tock;
	QueryPerformanceCounter(&Tick);

	MSG msg;
	LRESULT Result;

	while (IsRunning) {
		// Check in with OS
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			Result = DispatchMessage(&msg);
		}
		// Update game
		// Draw
		QueryPerformanceCounter(&Tock);

		__int64 Interval = Tock.QuadPart - Tick.QuadPart;
		double SecondsGoneBy = (double)Interval * SecondsPerTick;

		char buf[64];

		sprintf_s(buf, 64, "Total time: %3.7f \n", SecondsGoneBy);
		OutputDebugString(buf);

		QueryPerformanceCounter(&Tick);
	}

	return 0;
}