#include "Movement.h"
#include "global.h"

// Sup bro

void setVirtualCarSpeed(float linearSpeed, float angularSpeed)
{
	virtualCarLinearSpeed = linearSpeed;
	virtualCarAngularSpeed = angularSpeed;
}

void spotTurn(int turnDir, float angle) {

	//get currentCarAngle as a rounded int
	int anglePreset = (int)round(currentCarAngle);
	//store starting angle as rounded int
	int angleAtDetect = (int)round(angle);
	//intialise count
	int count = 0;


	switch (turnDir) {

	case 0:
		//reinitialise count
		count = 0;
		//check if turn still needs to occur
		if (((anglePreset % 90) != 0) || (angleAtDetect == round(currentCarAngle)) || (anglePreset == 360)) {

			//block and turn right 90
			while (count < 4) {
				setVirtualCarSpeed(0.0, (virtualCarAngularSpeed_seed * (-1.0)));
				count++;
			}
		}
		//stay stationary
		else {
			setVirtualCarSpeed(0.0, 0.0);
		}
		break;

	case 1:
		//reinitialise count
		count = 0;
		//check if turn still needs to occur
		if (((anglePreset % 90) != 0) || (angleAtDetect == round(currentCarAngle)) || (anglePreset == 360)) {

			//block and turn left 90
			while (count < 4) {
				setVirtualCarSpeed(0.0, virtualCarAngularSpeed_seed);
				count++;
			}

		}
		//stay stationary
		else {
			setVirtualCarSpeed(0.0, 0.0);
		}
		break;

	default:
		break;
	}
}

void singleLine() {

	//intialise straight line flag
	int straight = 0;

	//intialise halfTitlRange value
	float halfTiltRange = (num_sensors - 1.0) / 2.0;

	//intialise tilt sums for Rand L
	float tiltSumL = 0.0;
	float tiltSumR = 0.0;

	//initialise activated sensor count for Rand L
	float activatedSensorCountR = 0.0;
	float activatedSensorCountL = 0.0;

	//check for right turns from sensors 0 - 2
	for (int i = 0; i < 3; i++)
	{
		if (virtualCarSensorStates[i] == 0)
		{
			float tiltR = (float)i - halfTiltRange;
			tiltSumR += tiltR;
			activatedSensorCountR += 1.0;
		}
	}

	//check for left turns from sensors 4 - 6
	for (int j = 4; j < 7; j++)
	{
		if (virtualCarSensorStates[j] == 0)
		{
			float tiltL = (float)j - halfTiltRange;
			tiltSumL += tiltL;
			activatedSensorCountL += 1.0;
		}
	}

	//check for straight line(middle sensor activated)
	if ((virtualCarSensorStates[3] == 0) && (activatedSensorCountL == 0) && (activatedSensorCountR == 0)) {
		straight = 1;
	}
	else {
		straight = 0;
	}

	//turn left
	if (activatedSensorCountL > 0.0) {
		setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed * tiltSumL);
	}

	//turn right
	else if (activatedSensorCountR > 0.0) {
		setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed * tiltSumR);
	}

	//go straight
	else if (straight) {
		setVirtualCarSpeed(virtualCarLinearSpeed_seed, 0);
	}

	//turn around at dead end
	else {
		setVirtualCarSpeed(0.0, virtualCarAngularSpeed_seed);
	}
}