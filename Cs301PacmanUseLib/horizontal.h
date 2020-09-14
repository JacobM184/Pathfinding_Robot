
//#include "mainFungGLAppEngin.h" //a must
//
//extern float virtualCarLinearSpeed_seed;
//extern float virtualCarAngularSpeed_seed;

if (currentCarPosCoord_X > 6)
	currentCarAngle = 180;


if (currentCarPosCoord_X < -6)
	currentCarAngle = 0;

setVirtualCarSpeed(virtualCarLinearSpeed_seed, 0.0);