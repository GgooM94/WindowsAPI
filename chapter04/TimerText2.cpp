#include<Windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TimerText2");
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[128] = TEXT("¡á¡á¡á¡á¡á¡á¡á");
	static BOOL flag = FALSE;
	static int y = 100;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 50, NULL);

		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (y > 0)
				y -= 10;
			else {
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 2, 2000, NULL);
			}
			break;
		case 2:
			KillTimer(hWnd, 2);
			if (flag == FALSE) {
				lstrcpy(str, TEXT("¡à¡à¡à¡à¡à¡à¡à"));
				flag = TRUE;
				y = 100;
				SetTimer(hWnd, 1, 50, NULL);
			}
			else {
				lstrcpy(str, TEXT("¡á¡á¡á¡á¡á¡á¡á"));
				flag = FALSE;
				y = 100;
				SetTimer(hWnd, 1, 50, NULL);
			}
			break;	
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetTextAlign(hdc, TA_LEFT | TA_TOP);
		TextOut(hdc, 10, y, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}