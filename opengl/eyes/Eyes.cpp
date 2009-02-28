// Eyes.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Eyes.h"
#include "math.h"

HWND	g_hWnd	= NULL;
HDC		g_hDC	= NULL;
HGLRC	g_hRC	= NULL;
DEVMODE	g_oldDevMode;
HANDLE	hMutex	= NULL;
POINT	curPos;

#define EYES_WIDTH		300
#define EYES_HEIGHT		300

#define REDRAW_TIMER	1
#define GETCURSORPOS_TIMER	2

#define EYES_IL			1
#define PUPIL_IL		2

// Проверка - было ли запущено раньше
bool IsRunning(HANDLE &hMutex)
{
	hMutex = CreateMutex(NULL, false, "OpenGLEyesMutex");

	if( GetLastError() == ERROR_ALREADY_EXISTS )
		return true;

	return false;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if( IsRunning(hMutex) )
		return 1;

	WNDCLASSEX	winClass; 
	MSG			uMsg;

	memset(&uMsg, 0, sizeof(uMsg));

	winClass.lpszClassName = "OPENGL_EYES_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon	       = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	winClass.hIconSm	   = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx(NULL, 
							"OPENGL_EYES_WINDOWS_CLASS", 
							"OpenGL - Fine Eyes",
							WS_POPUP | WS_VISIBLE /*| WS_CAPTION*/,
							0, 0, EYES_WIDTH, EYES_HEIGHT, 
							NULL, NULL, hInstance, NULL);

	if( g_hWnd == NULL )
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	Init();
	SetCursor(LoadCursor(hInstance, IDC_HAND));

	SetTimer(g_hWnd, REDRAW_TIMER, 10, &TimerProc);
	SetTimer(g_hWnd, GETCURSORPOS_TIMER, 1, &TimerProc);

	while ( uMsg.message != WM_QUIT )
		if( PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}

	Shutdown();

	UnregisterClass("OPENGL_EYES_WINDOWS_CLASS", winClass.hInstance);

	return uMsg.wParam;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if( idEvent == REDRAW_TIMER )
	{
		SetView();
		Display();
	}
	if( idEvent = GETCURSORPOS_TIMER )
		GetCursorPos(&curPos);
}

// The window's message handler
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static isDragged = false;
	switch ( msg )
	{
	case WM_SIZE:
		HRGN hRgnLeft, hRgnRight;
		RECT rcLeft, rcRight;
		GetWindowRect(hWnd, &rcLeft);
		OffsetRect(&rcLeft, - rcLeft.left, - rcLeft.top);
		rcLeft.left += 15;
		rcLeft.top += 50;
		rcLeft.bottom -= 50;
		rcLeft.right = rcLeft.left + (rcLeft.right - rcLeft.left)/2 - 5;

		rcRight.top = rcLeft.top;
		rcRight.bottom = rcLeft.bottom;
		rcRight.left = rcLeft.right - 5;
		rcRight.right = rcLeft.right + (rcLeft.right - rcLeft.left);
		 
		DeleteObject(hRgnLeft);
		hRgnLeft = CreateEllipticRgnIndirect(&rcLeft);
		DeleteObject(hRgnRight);
		hRgnRight = CreateEllipticRgnIndirect(&rcRight);

		CombineRgn(hRgnLeft, hRgnLeft, hRgnRight, RGN_OR);
		SetWindowRgn(hWnd, hRgnLeft, TRUE);
		break;
	case WM_LBUTTONDOWN:
		{
			isDragged = true;
			break;
		}
	case WM_LBUTTONUP:
		{
			isDragged = false;
			break;
		}
	case WM_CHAR:
		if( wParam == 27 );
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}

void Init()
{
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &g_oldDevMode);

	g_hDC = GetDC(g_hWnd);

	PIXELFORMATDESCRIPTOR pfd;

	int nTotalFormats = DescribePixelFormat(g_hDC, 1, sizeof(pfd), NULL);

	int nPixelFormat;

	for ( nPixelFormat = 1; nPixelFormat <= nTotalFormats; ++nPixelFormat )
	{
		if( DescribePixelFormat(g_hDC, nPixelFormat, sizeof(pfd), &pfd) == 0 )
		{
			DWORD dwErrorCode = GetLastError();
			return;
		}

		if( !(pfd.dwFlags & PFD_SUPPORT_OPENGL) )
			continue;

		if( !(pfd.dwFlags & PFD_DOUBLEBUFFER) )
			continue;

		if( pfd.iPixelType != PFD_TYPE_RGBA )
			continue;

//		if( pfd.cColorBits != 32 )
//			continue;

		if( pfd.cDepthBits != 16 )
			continue;

		break;
	}

// apply pixel format
	if( SetPixelFormat(g_hDC, nPixelFormat, &pfd) == FALSE)
	{
		DWORD dwErrorCode = GetLastError();
		return;
	}

	g_hRC = wglCreateContext(g_hDC);
	wglMakeCurrent(g_hDC, g_hRC);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if( ChangeDisplaySettings(&g_oldDevMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL )
		return;
	
	glShadeModel(GL_SMOOTH);								// Enables Smooth Color Shading
	glClearDepth(1.0);										// Depth Buffer Setup

	SetView();

	glEnable(GL_DEPTH_TEST);

	GLUquadric *qObj = gluNewQuadric();
	glNewList(EYES_IL, GL_COMPILE);
    glPushMatrix();
	glTranslated(-4.5, 0.0, 0.0);
	glScaled(1.0, 1.5, 1.0);
	glColor3d(1.0, 1.0, 1.0);
	gluDisk(qObj, 0.0, 4.0, 40, 40);
	glTranslated(9.0, 0.0, 0.0);
	glColor3d(1.0, 1.0, 1.0);
	gluDisk(qObj, 0.0, 4.0, 40, 40);
	glPopMatrix();
	glEndList();

	glNewList(PUPIL_IL, GL_COMPILE);
	glPushMatrix();
	glColor3d(0.0, 0.0, 0.0);
	gluDisk(qObj, 0.0, 1.0, 20, 20);
	glPopMatrix();
	glEndList();
	gluDeleteQuadric(qObj);
}

void Shutdown()	
{
// Restore original device mode...
	ChangeDisplaySettings(&g_oldDevMode, 0);

	if( g_hRC != NULL )
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(g_hRC);
		g_hRC = NULL;
	}

	if( g_hDC != NULL )
	{
		ReleaseDC(g_hWnd, g_hDC);
		g_hDC = NULL;
	}
}

void GetLeftEyePosition(TPoint *point)
{
	POINT leftEye;
	RECT rect;
	GetWindowRect(g_hWnd, &rect);
	leftEye.x = rect.left + EYES_WIDTH/2 - EYES_WIDTH/4 + EYES_WIDTH/40;
	leftEye.y = rect.top + EYES_HEIGHT/2;

	float angle = -atan(float(curPos.y-leftEye.y)/(curPos.x-leftEye.x));
	float rad = 3.0;
	if( leftEye.x < curPos.x )
	{
		point->x = -4.5 + rad*cos(angle);
		point->y = rad*sin(angle);
	}
	if( leftEye.x > curPos.x )
	{
		point->x = -4.5 - rad*cos(angle);
		point->y = -rad*sin(angle);
	}
	if( leftEye.x == curPos.x )
	{
		point->x = -4.5;
		point->y = (curPos.y > leftEye.y) ? -rad : rad;
	}
}

void GetRightEyePosition(TPoint *point)
{
	POINT rightEye;
	RECT rect;
	GetWindowRect(g_hWnd, &rect);
	rightEye.x = rect.left + EYES_WIDTH/2 + EYES_WIDTH/4 - EYES_WIDTH/40;
	rightEye.y = rect.top + EYES_HEIGHT/2;

	float angle = -atan(float(curPos.y-rightEye.y)/(curPos.x-rightEye.x));
//	angle = atan(double(0.5));
	float rad = 3.0;
	if( rightEye.x < curPos.x )
	{
		point->x = 4.5 + rad*cos(angle);
		point->y = rad*sin(angle);
	}
	if( rightEye.x > curPos.x )
	{
		point->x = 4.5 - rad*cos(angle);
		point->y = -rad*sin(angle);
	}
	if( rightEye.x == curPos.x )
	{
		point->x = 4.5;
		point->y = (curPos.y > rightEye.y) ? -rad : rad;
	}
}

void Display()	
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCallList(EYES_IL);

	TPoint eyePos;
	GetLeftEyePosition(&eyePos);

	glPushMatrix();
	glTranslated(eyePos.x, eyePos.y, 0.01);

	if( glIsList(PUPIL_IL) == GL_TRUE )
		glCallList(PUPIL_IL);
	glPopMatrix();

	GetRightEyePosition(&eyePos);
	glPushMatrix();
	glTranslated(eyePos.x, eyePos.y, 0.01);
	if( glIsList(PUPIL_IL) == GL_TRUE )
		glCallList(PUPIL_IL);
	glPopMatrix();

	SwapBuffers(g_hDC);
}

void SetView()
{
	glViewport(0, 0, EYES_WIDTH, EYES_HEIGHT);					// Set the viewport for the OpenGL window
	glMatrixMode(GL_PROJECTION);			// Change Matrix Mode to Projection
	glLoadIdentity();						// Reset View

// Do the perspective calculations
	GLdouble scale = 10;
	glOrtho(-scale, scale, -scale, scale, -scale, scale);

	glMatrixMode(GL_MODELVIEW);				// Return to the modelview matrix
	glLoadIdentity();						// Reset View

	gluLookAt(  0.0, 0.0, 5.0, 
				0.0, 0.0, 0.0,
				0.0, 1.0, 0.0 );
}
