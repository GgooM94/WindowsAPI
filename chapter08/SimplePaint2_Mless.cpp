#include<Windows.h>
#include"resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Mless Dlg");
HWND hMDlg;

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
		if (!IsWindow(hMDlg) || !IsDialogMessage(hMDlg, &Message)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
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
		SetDlgItemInt(hSetDlg, IDC_EDRED, Red, FALSE);
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
			return  TRUE;
		case ID_RESET:
			InvalidateRect(hWndMain, NULL, TRUE);
			return TRUE;
		case IDCANCEL:
			DestroyWindow(hMDlg);
			hMDlg = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	hWndMain = hWnd;
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;
	static BOOL bNowDraw = FALSE;
	static int x, y;

	switch (iMessage)
	{
	case WM_CREATE:
		hMDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SetDlgProc);
		ShowWindow(hMDlg, SW_SHOW);
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

			return 0;
		}
	case WM_RBUTTONDOWN:
		if (!IsWindow(hMDlg)) {
			hMDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SetDlgProc);
			ShowWindow(hMDlg, SW_SHOW);
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