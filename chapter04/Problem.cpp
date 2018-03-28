#include<Windows.h>
#include<stdlib.h>
#include<time.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyTimer");
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
	SYSTEMTIME st;
	srand(time(NULL));
	static TCHAR sTime[128];
	static TCHAR problem[128];
	static RECT rt = { 100,100,400,120 };
	static int a;
	static int b;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);		//Ÿ�̸Ӹ� ������ ������ �ڵ�, Ÿ�̸� ID, �߻� �ð��ֱ�(1000 �� 1��), �ֱ�� ȣ���� �Լ�
		SendMessage(hWnd, WM_TIMER, 1, 0);	//���۽� ������ Ÿ�̸Ӹ� �ٷ� ȣ��
		return 0;
	case WM_TIMER:
		a = rand() % 30;
		b = rand() % 30;
		wsprintf(problem, TEXT("%d + %d "),a,b);
		InvalidateRect(hWnd, &rt, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, problem, lstrlen(problem));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);		//Ÿ�̸Ӹ� ������ ������ �ڵ�, �ı��� Ÿ�̸� ID
		PostQuitMessage(0);
		return 0;

	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}