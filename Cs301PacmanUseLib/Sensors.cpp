#include <iostream>
#include "Sensors.h"
#include "SensorState.h"

void Sensors::SetCurrentToPrev()
{
    for (int i = 0; i < currentSensorArray.size(); i++) {
        prevSensorArray[i] = currentSensorArray[i];
    }
}

int Sensors::SensorArrayToIntCentered()
{
    int currSize = currentSensorArray.size();
    int startingPoint = -1 * ((currSize - 1) / 2);
    int currentNumber = 0;

    for (int i = 0; i < currSize; i++) {
        currentNumber += currentSensorArray[i] * startingPoint;
        startingPoint++;
    }

    return currentNumber;
}

int Sensors::SensorArrayToIntOrigin()
{
    int currSize = currentSensorArray.size();
    int currentNumber = 0;

    for (int i = 0; i < currSize; i++) {
        currentNumber += currentSensorArray[i];
    }

    return currentNumber;
}

Sensors::Sensors(std::vector<int> sensorArray)
{
    this->currentSensorArray = sensorArray;

    this->state = SensorState::STRAIGHT;
    this->turnState = SensorState::NONE;
    this->turnDeteced = false;
    this->start = true;
    this->stateDetected = false;

    for (int i = 0; i < currentSensorArray.size(); i++) {
        this->prevSensorArray.push_back(currentSensorArray[i]);
    }
}

void Sensors::TestSensorArray(std::vector<int> newSensorArray)
{
    //Update the sensor array with the new one
    this->currentSensorArray = newSensorArray;

    //Check if the previous sensor data is the same as the current sensor data
    if (std::equal(currentSensorArray.begin(), currentSensorArray.end(), this->prevSensorArray.begin()) && !stateDetected) {
        //std::cout << "similar" << std::endl;
        SetCurrentToPrev();
        return;
    }

    //Retrieve the numerical number
    int sensorValCentred = SensorArrayToIntCentered();
    int sensorVal = SensorArrayToIntOrigin();
    int size = currentSensorArray.size();

    if (start && !stateDetected) {
        if (this->turnState == SensorState::NONE) {
            //Check if there is a turn has been detected
            if (sensorVal == (size - 1) / 2 && currentSensorArray[(size - 1) / 2] == 0) {
                //Check if it is a right turn
                this->turnDeteced = true;

                if (sensorValCentred > 0) {
                    this->turnState = SensorState::LEFT_TURN;
                    //std::cout << "LEFT TURN DETECTED" << std::endl;
                    SetCurrentToPrev();
                    return;
                }
                //Check f it is left turn
                else if (sensorValCentred < 0) {
                    this->turnState = SensorState::RIGHT_TURN;
                    //std::cout << "RIGHT TURN DETECTED" << std::endl;
                    SetCurrentToPrev();
                    return;
                }
            }
            //Check if the detector has detected all of it to be all 1
            else if (sensorVal <= 0) {
                this->state = SensorState::INTERSECTION;
                //std::cout << "INTERSECTION DETECTED" << std::endl;
                this->stateDetected = true;
            }
            //Check if the detector has detected all of it is 0
            else if (sensorVal >= size) {
                this->state = SensorState::DEAD_END;
                //std::cout << "DEAD END DETECTED" << std::endl;
                this->stateDetected = true;
            }
        }
        //If the turn has already been detected now determine if 
        else {
            if (sensorVal == 6) {
                this->state = SensorState::INTERSECTION;
                //std::cout << "INTERSECTION DETECTED" << std::endl;
                this->stateDetected = true;
            }
            else if (sensorVal == 7) {
                this->state = this->turnState;
                //std::cout << "TURN DETECTED" << std::endl;
                this->stateDetected = true;
            }
        }
    }

    if (stateDetected) {
        int straightConstant[] = { 1,1,1,0,1,1,1 };
        this->stateDetected = false;

        //checks if the previous and current are the same and represent a
        //the robot following a straight line
        for (int i = 0; i < size; i++) {
            //std::cout << this->prevSensorArray[i] << ":" << this->currentSensorArray[i] << ":" << straightConstant[i] << std::endl;
            if (!stateDetected && ((this->prevSensorArray[i] != straightConstant[i]) || (currentSensorArray[i] != straightConstant[i]))) {
                //std::cout << "FAULT" << std::endl;
                this->stateDetected = true;
            }
        }

        //std::cout << std::endl;


        //if it determines that it is following a straight line that means
        //we reset the detector
        if (!stateDetected) {
            this->state = SensorState::STRAIGHT;
            this->turnState = SensorState::NONE;
            std::cout << "STRAIGHT DETECTED" << std::endl;
        }
    }

    SetCurrentToPrev();
}

SensorState Sensors::GetCurrentState()
{
    return this->state;
}

void Sensors::printCurrentState()
{
    switch (this->state) {
    case SensorState::STRAIGHT:
        std::cout << "state: STRAIGHT" << std::endl;
        break;
    case SensorState::INTERSECTION:
        std::cout << "state: INTERSECTION" << std::endl;
        break;
    case SensorState::LEFT_TURN:
        std::cout << "state: LEFT_TURN" << std::endl;
        break;
    case SensorState::RIGHT_TURN:
        std::cout << "state: RIGHT_TURN" << std::endl;
        break;
    case SensorState::DEAD_END:
        std::cout << "state: DEAD_END" << std::endl;
        break;
    default:
        std::cout << "state: NONE" << std::endl;
        break;
    }
}

bool Sensors::getTurnDetection()
{
    return false;
}

void Sensors::SensorStop()
{
}

void Sensors::SensorStart()
{
}
