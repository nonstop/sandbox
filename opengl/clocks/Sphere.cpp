#include "stdafx.h"
#include "Sphere.h"

CSphere::CSphere(void)
{
	mProperties.fColor[0] = 1.0;
	mProperties.fColor[1] = 1.0;
	mProperties.fColor[2] = 1.0;

	mProperties.fPosition[0] = 0.0;
	mProperties.fPosition[1] = 0.0;
	mProperties.fPosition[2] = 0.0;

	mProperties.fAngles[0] = 0.0;
	mProperties.fAngles[1] = 0.0;
	mProperties.fAngles[2] = 0.0;
}

CSphere::~CSphere(void)
{
}
