//======================================================================
//Author: 
//Mr. Fung Yang
//Senior Technician Engineer Research and Design,
//Robotics and Control system signal processing Labs,
//Department of Electrical, Computer and Software Engineering,
//The University of Auckland.
//
//Written for teaching design course Compsys301 in ECSE department of UOA.
//
//This example program uses the pacman robot simulation library written by Mr. Fung Yang.
//
//Date 2012~2020
//=======================================================================

// ROBOT 
#define DEFAULT_ROBOT
//#define CUSTOM_ROBOT1

#include "mainFungGLAppEngin.h" //a must
#include "data.h" //a must
#include "global.h"
#include "highPerformanceTimer.h"//just to include if timer function is required by user.
#include <vector>
#include <iostream>
#include <windows.h>

#include "Sensors.h"
#include "Movement.h"
#include "SensorState.h"

using namespace std;

//{=================================================
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//these global variables must be defined here with no modification.
float virtualCarLinearSpeed;//can get ands set
float virtualCarAngularSpeed;//can get and set
float currentCarAngle;//can get and set
float currentCarPosCoord_X, currentCarPosCoord_Y;//can get and set

int sensorPopulationAlgorithmID;//can set
float sensorSeparation;//can set
float num_sensors;//can set

vector<int> virtualCarSensorStates; //can get

vector<ghostInfoPack> ghostInfoPackList;// can get
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//}=================================================

vector<int> initialValue = { 1,1,1,0,1,1,1 };

highPerformanceTimer myTimer;
Sensors sens = Sensors(initialValue);

//just a helper function

//The Only TWO unctions Students need to modify to add their own sensor guided
//path following control and Map path search calculations.
//{=================================================
float virtualCarLinearSpeed_seed;
float virtualCarAngularSpeed_seed;

int virtualCarInit()
{


#ifdef DEFAULT_ROBOT
	//sensorPopulationAlgorithmID = PLACE_SENSORS_AUTO_SEP;
	sensorPopulationAlgorithmID = PLACE_SENSORS_SEP_USER_DEFINED;
	num_sensors = 7;
	sensorSeparation = 0.08;// 0.095 / 2;  // separation of one line width is 0.095


	virtualCarLinearSpeed_seed = 0.6;
	virtualCarAngularSpeed_seed = 40;
#endif

#ifdef CUSTOM_ROBOT1
	//sensorPopulationAlgorithmID = PLACE_SENSORS_AUTO_SEP;
	sensorPopulationAlgorithmID = PLACE_SENSORS_SEP_USER_DEFINED;
	num_sensors = 5;
	sensorSeparation = 0.095 / 2;  // separation of one line width is 0.095
	virtualCarLinearSpeed_seed = 0.6;
	virtualCarAngularSpeed_seed = 40;
#endif

	currentCarPosCoord_X = cellToCoordX(8);
	currentCarPosCoord_Y = cellToCoordY(7);
	currentCarAngle = 0;

	return 1;
}

int virtualCarUpdate()
{
	setVirtualCarSpeed(virtualCarLinearSpeed_seed, 0.0);

	cout << "Array: ";
	for (int i = 0; i < virtualCarSensorStates.size(); i++) {
		cout << virtualCarSensorStates[i] << ", ";
	}

	cout << endl;

	sens.TestSensorArray(virtualCarSensorStates);
	sens.printCurrentState();

	cout << endl << endl;

	if (sens.GetCurrentState() == SensorState::INTERSECTION) {
		static float angle = currentCarAngle;
		spotTurn(0, angle);
	}
	else {
		singleLine();
	}

	return 1;
}
//}=============================================================

int main(int argc, char** argv)
{
	FungGlAppMainFuction(argc, argv);

	return 0;
}
