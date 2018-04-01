#include<Windows.h>
#include"resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("SimplePaint2");


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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


int Red, Green, Blue;
static COLORREF Color = RGB(0, 0, 0);
static int size;
BOOL CALLBACK SetDlgProc(HWND hSetDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hSetDlg, IDC_EDRED, Red,FALSE);
		SetDlgItemInt(hSetDlg, IDC_EDGREEN, Green, FALSE);
		SetDlgItemInt(hSetDlg, IDC_EDBLUE, Blue, FALSE);
		SetDlgItemInt(hSetDlg, IDC_EDSIZE, size, FALSE);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			Red = GetDlgItemInt(hSetDlg, IDC_EDRED, NULL, FALSE);
			Green = GetDlgItemInt(hSetDlg, IDC_EDGREEN, NULL, FALSE);
			Blue = GetDlgItemInt(hSetDlg, IDC_EDBLUE, NULL, FALSE);
			size = GetDlgItemInt(hSetDlg, IDC_EDSIZE, NULL, FALSE);
			Color = RGB(Red, Green, Blue);
			if (Red < 0 || Green < 0 | Blue < 0) {
				MessageBox(hSetDlg, TEXT("색상 값을 다시 입력하십시오."), TEXT("알림"), MB_OK);
			}
			EndDialog(hSetDlg, IDOK);
			return  TRUE;
		case IDCANCEL:
			EndDialog(hSetDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;
	static BOOL bNowDraw = FALSE;
	static int x, y;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("static"), TEXT("지우기 : Space"), WS_CHILD | WS_VISIBLE, 10, 10, 100, 15,hWnd, (HMENU)-1, g_hInst, NULL);
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;
		return 0;

	case WM_MOUSEMOVE:
		if (bNowDraw) {
			hdc = GetDC(hWnd);
			MyPen = CreatePen(PS_SOLID, size, Color);
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			MoveToEx(hdc, x, y, NULL);
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);
			DeleteObject(SelectObject(hdc, OldPen));
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_SPACE:
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		}
	case WM_RBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SetDlgProc) == IDOK) {
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}