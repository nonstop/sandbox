// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// TODO: reference additional headers your program requires here
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"

//	списки изображений
#define IL_HOUR			1
#define IL_MINUTE		2
#define IL_SECOND		3
//	таймеры
#define REDRAW_TIMER	1		//	частота перерисовки
#define CLOCK_TIMER		2		//	обновление времени
#define SHRINK_TIMER	3		//	изменение размера
#define CURVE_TIMER		4		//	перемещение изгиба
