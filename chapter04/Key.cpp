#include<Windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Key");
void Line(const HDC& hdc, const int &left, const int& top, const int& right, const int& bottom);	//선그리기 함수 선언
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];
	int len;
	switch (iMessage)
	{
	case WM_CHAR:
		if ((TCHAR)wParam == ' ') {		//스페이스바 입력시 문자열 초기화
			str[0] = 0;
		}
		else {
			len = lstrlen(str);
			str[len] = (TCHAR)wParam;
			str[len + 1] = 0;
		}
		//BOOL InvalidateRect(HWND hWnd, CONST RECT *lpRect, BOOL bErase)
		//RECT *lpRect NULL입력시 윈도우 전체영역
		//BOLL bErase TRUE시 지우고 다시그리기, FALSE 현재상태에서 그리기
		InvalidateRect(hWnd, NULL, TRUE);		//문자가 새로 입력될 때마다 강제로 WM_PAINT 메시지를 발생시키기 위해 사용
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
void Line(const HDC& hdc, const int &left,const int& top,const int& right, const int& bottom) {	//선그리기 함수 정의
	MoveToEx(hdc, left, top,NULL);
	LineTo(hdc, right, bottom);
}