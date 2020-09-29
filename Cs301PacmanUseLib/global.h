#pragma once
#include <vector>
using namespace std;

extern float virtualCarLinearSpeed;//can get ands set
extern float virtualCarAngularSpeed;//can get and set
extern float currentCarAngle;//can get and set
extern float currentCarPosCoord_X, currentCarPosCoord_Y;//can get and set

extern int sensorPopulationAlgorithmID;//can set
extern float sensorSeparation;//can set
extern float num_sensors;//can set

extern vector<int> virtualCarSensorStates; //can get

extern float virtualCarLinearSpeed_seed;
extern float virtualCarAngularSpeed_seed;

