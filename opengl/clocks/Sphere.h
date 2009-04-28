#ifndef SPHERE_He
#define SPHERE_H

#include <GL/gl.h>

struct TTimeElementProperties		//	свойства элемента (часа, минуты, секунды)
{
	GLfloat		fColor[3];
	GLfloat		fPosition[3];
	GLfloat		fAngles[3];
};

class CSphere
{
protected:
	TTimeElementProperties mProperties;
public:
	CSphere(void);
	virtual ~CSphere(void);
};
#endif /* SPHERE_H */

