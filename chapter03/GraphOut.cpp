#include<Windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("GraphOut");
void Line(const HDC& hdc, const int &left, const int& top, const int& right, const int& bottom);	//���׸��� �Լ� ����
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
	HDC hdc;		//DC(Device Context) ��¿� �ʿ��� ��� ������ ������ ������ ����ü
	PAINTSTRUCT ps;	//ȭ���� ������ ������ ���ڿ��� ��� �ϱ� ����.
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetPixel(hdc, 10, 10, RGB(255, 0, 0));

		Line(hdc, 300, 300, 500, 500);	//���׸��⸦ ���� �Լ��� ����

		MoveToEx(hdc, 50, 50, NULL);	//CP�� (50,50)���� �̵�, ������
		LineTo(hdc, 300, 90);			//���� CP���� (300,30)���� ���� �׸���
		Rectangle(hdc, 50, 100, 200, 180);	//(left,top) , (right,bottom)���� �簢�� �׸���
		Ellipse(hdc, 50, 100, 200, 180);	//(left,top) , (right,bottom)���� �簢�� �׸���
		EndPaint(hWnd, &ps);
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
void Line(const HDC& hdc, const int &left,const int& top,const int& right, const int& bottom) {	//���׸��� �Լ� ����
	MoveToEx(hdc, left, top,NULL);
	LineTo(hdc, right, bottom);
}