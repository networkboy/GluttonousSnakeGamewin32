#include <windows.h>
#include <iostream.h>
#include <time.h>
#include <Winuser.h>
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 
void OnInitialUpdate();
void SnakeMove();
struct Snake
{
	int x,y;
	int len;
	int direct;
}Snake[50];
struct Food
{
	int x;
	int y;
	int isfood;
}Food;

HDC hdc;
PAINTSTRUCT ps;
int i;
int t=0;
WNDCLASS wnd;
HWND hwin;
MSG msg;
int sn;
int soure;
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	
	wnd.style = CS_HREDRAW |CS_VREDRAW;  
	wnd.lpfnWndProc = WinProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hIcon = LoadIcon(NULL,IDI_APPLICATION); 
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_PEN);
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("̰����");
	wnd.hInstance = hInstance;
	if(!RegisterClass(&wnd))
	{
		MessageBox(NULL,"fail","error",0);
		return 0;
	}
	
	hwin = CreateWindow(TEXT("̰����"),TEXT("̰����"),WS_OVERLAPPEDWINDOW,20,20,1000,700,NULL,NULL,hInstance,NULL);
	
	ShowWindow(hwin,nShowCmd);
	OnInitialUpdate();

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.lParam;
}

LRESULT CALLBACK WinProc(
						 HWND hwnd, 
						 UINT uMsg, 
						 WPARAM wParam, 
						 LPARAM lParam )
{
	
	switch(uMsg)
	{
	case WM_DESTROY : PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_RETURN: 
			SetTimer(hwin,1,200,NULL);
			break;
			case VK_SPACE: 
				KillTimer(hwin,1);
				break;
			case VK_UP:
				if(Snake[0].direct!=2)Snake[0].direct=1;break;
			case VK_DOWN:
				if(Snake[0].direct!=1)Snake[0].direct=2;break;
			case VK_LEFT:
				if(Snake[0].direct!=4)Snake[0].direct=3;break;  
			case VK_RIGHT:
				if(Snake[0].direct!=3)Snake[0].direct=4;break;
			}
			break;
		}
	case WM_TIMER:
		{
			SnakeMove();
			break;
		}
		
	}
 
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
void OnInitialUpdate()
{   
	hdc=GetDC(hwin);
	Snake[0].x=10;
	Snake[0].y=10;
	Snake[1].x=10;
	Snake[1].y=11;
	Snake[2].x=10;
	Snake[2].y=12;
	Snake[0].direct=3;
	Snake[0].len=3;
	Food.isfood=1;
	ReleaseDC(hwin,hdc);
    hdc = BeginPaint(hwin,&ps);

	
}
void SnakeMove()
{   
	
	soure=(Snake[0].len-3)*10;
if(Snake[0].x*20<=0||Snake[0].y*20<=0||Snake[0].x*20>=1000||Snake[0].y*20>=700)
{    
	 KillTimer(hwin,1);
	 MessageBox(NULL,"���� ���¿�ʼ" ,"ʧ��",0);
	 SelectObject(hdc,CreateSolidBrush(RGB(255,255,255)));
     Rectangle(hdc,0,0,1000,700);
	 hdc = BeginPaint(hwin,&ps);

}

if(Snake[0].len>3)
for(int sn=Snake[0].len-1;sn>0;sn--)
{
	if(Snake[0].x*20==Snake[sn].x*20&&Snake[0].y*20==Snake[sn].y*20)
	{
		KillTimer(hwin,1);
		MessageBox(NULL,"���� ���¿�ʼ","ʧ��",0);

	}
}
SelectObject(hdc,GetStockObject(WHITE_PEN));
SelectObject(hdc,CreateSolidBrush(RGB(255,255,255)));
Rectangle(hdc,Snake[Snake[0].len-1].x*20,Snake[Snake[0].len-1].y*20,(Snake[Snake[0].len-1].x+1)*20,(Snake[Snake[0].len-1].y+1)*20);
for(int i=Snake[0].len-1;i>0;i--)
{   
	Snake[i].x=Snake[i-1].x;
	Snake[i].y=Snake[i-1].y;

}


if(Snake[0].direct==1)Snake[0].y--;
if(Snake[0].direct==2)Snake[0].y++;
if(Snake[0].direct==3)Snake[0].x--;
if(Snake[0].direct==4)Snake[0].x++;
SelectObject(hdc,CreateSolidBrush(RGB(0,0,0)));
Rectangle(hdc,Snake[0].x*20,Snake[0].y*20,(Snake[0].x+1)*20,(Snake[0].y+1)*20);
if(Snake[0].x*20==Food.x*20&&Snake[0].y*20==Food.y*20)
{
	Snake[0].len++;
	Food.isfood=1;
	
}

if(Food.isfood==1)
{   
	
	int isfo=0;
	if(Food.isfood==1)
		srand((unsigned)time(NULL));
	do
	{    
		Food.x=rand();
		Food.y=rand();
				    for(int isfo=Snake[0].len-1;isfo>=0;isfo--)	    
						if(Food.x*20==Snake[isfo].x*20&&Food.y*20==Snake[isfo].y*20)
						{
							Food.x=rand();
							Food.y=rand();
						}
	}
	while(Food.x*20<0||Food.y*20<0||Food.x*20>1000||Food.y*20>700);
	SelectObject(hdc,CreateSolidBrush(RGB(0,0,0)));
	Rectangle(hdc,Food.x*20,Food.y*20,(Food.x+1)*20,(Food.y+1)*20);
	Food.isfood=0;
		} 


}
