#pragma once
#include <vector>
#include "SensorState.h"
class Sensors
{
private:
	bool start;
	bool turnDeteced;
	bool stateDetected;
	SensorState turnState;
	SensorState state;
	std::vector<int> currentSensorArray;
	std::vector<int> prevSensorArray;

	//Method: sets the current sensor array to the previous sensor array
	void SetCurrentToPrev();

	//Method: returns the sensor length to a symbolic number
	int SensorArrayToIntCentered();

	//Method: returns the sensor length to a symbolic number
	int SensorArrayToIntOrigin();

	//Method: check if current sensor data is the same as the last one
	//return true if they are the same and return false if they are not


public:
	Sensors(std::vector<int> sensorArray);

	void TestSensorArray(std::vector<int> currentSensorArray);
	SensorState GetCurrentState();
	void printCurrentState();
	bool getTurnDetection();
	void SensorStop();
	void SensorStart();
};

