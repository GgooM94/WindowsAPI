#include<Windows.h>
#include"resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Bitmap");


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

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit) {
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;
	MemDC = CreateCompatibleDC(hdc);		//메모리DC 생성 함수!!
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	//BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);						//BitBlt : DC간의 영역끼리 고속 복사 수행
	StretchBlt(hdc, x, y, 500, 500, MemDC, 0, 0, bx, by, SRCCOPY);		//StretchBlt : 원본 bit맵 크기를 확대해 복사	
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);		//메모리 사용후 삭제!!
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HBITMAP MyBitmap;
	switch (iMessage)
	{
	case WM_CREATE:
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));		//LoadBitmap 함수가 매우 느리기 때문에 Create시 미리 호출
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawBitmap(hdc, 10, 10, MyBitmap);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteObject(MyBitmap);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*★★!
메모리 DC란 화면 DC와 동일한 특성을 가지며 그 내부에 출력 표면을 가진 메모리 영역이다.
메모리에 있기는 하지만 화면 DC에서  사용할 수 있는 모든 출력을 메모리 DC에서도 할 수 있다.
선, 면, 원 등의 작도 함수는 물론 화면 DC에서는 불가능한 것까지도 가능하다.
그래서 메모리 DC에 먼저 그림을 그린 후 사용자 눈에 그려지는 과정은 보여주지 않고 
그 결과만 화면으로 고속 복사하는 방법(더블 버퍼링)을 많이 사용한다.
*/