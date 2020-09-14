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
#include "highPerformanceTimer.h"//just to include if timer function is required by user.
#include <vector>
#include <iostream>

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

highPerformanceTimer myTimer;

//just a helper function
void setVirtualCarSpeed(float linearSpeed, float angularSpeed)
{
	virtualCarLinearSpeed = linearSpeed;
	virtualCarAngularSpeed = angularSpeed;
}

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
	virtualCarLinearSpeed_seed = 0.9;
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


//#include "horizontal.h"
#include "fung.h"

//	setVirtualCarSpeed(0.6, 40);
	//{----------------------------------
	//process sensor state information
	

    //}------------------------------------

	//{------------------------------------
	//updat linear and rotational speed based on sensor information
	

	//}---------------------------------------

	//below is optional. just to provid some status report and function test result .
	//You can try to use "printf()" to reimplemet this "cout" c++ section in a c style instead.
	//{--------------------------------------------------------------	
	if (myTimer.getTimer() > 0.5)
	{
		myTimer.resetTimer();

		cout << "=====================================" << endl;
		cout << "current car X, Y, theta = " << currentCarPosCoord_X << " , " << currentCarPosCoord_Y << " , " << currentCarAngle << endl;
		cout << "current Cell X, Y = " << coordToCellX(currentCarPosCoord_X) << " , " << coordToCellY(currentCarPosCoord_Y) << endl;
		cout << "-----------------------------------------" << endl;
		//cout << " ghost list info:" << endl;
		//for (int i = 0; i < ghostInfoPackList.size(); i++)
		//{
		//	cout << "g[" << i << "]: (" << ghostInfoPackList[i].coord_x << ", " << ghostInfoPackList[i].coord_y <<"); [s="<<
		//		ghostInfoPackList[i].speed<<"; [d="<< ghostInfoPackList[i].direction << "]; [T=" << ghostInfoPackList[i].ghostType<<"]" << endl;
		//}
		//cout << "-----------------------------------------" << endl;
		//int randNumber = rand_nextInt(10);
		//cout << " a rand number between 0 ~ 10 = " << randNumber << endl;
		//randNumber = rand_nextInt(10, 20);
		//cout << " a rand number between 10 ~ 20 = " << randNumber << endl;
		//cout << "-----------------------------------------" << endl;
		//cout << "map[0][9] = " << map[0][9] << endl;
		//cout << "food_list[5][0] = " << food_list[5][0] << endl;
	}	
	//}---------------------------------------------------------------
	
	return 1;
}
//}=============================================================

int main(int argc, char** argv)
{
	FungGlAppMainFuction(argc, argv);

	return 0;
}
