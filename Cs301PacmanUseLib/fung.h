//{----------------------------------
//process sensor state information
float halfTiltRange = (num_sensors - 1.0) / 2.0;
float tiltSum = 0.0;
float blackSensorCount = 0.0;
for (int i = 0; i < num_sensors; i++)
{
	if (virtualCarSensorStates[i] == 0)
	{
		float tilt = (float)i - halfTiltRange;
		tiltSum += tilt;
		blackSensorCount += 1.0;
	}
}
//}------------------------------------

//{------------------------------------
//updat linear and rotational speed based on sensor information
if (blackSensorCount > 0.0)
setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed * tiltSum);
//setVirtualCarSpeed(0.60, 40.0*tiltSum);
else
setVirtualCarSpeed(0.0, virtualCarAngularSpeed_seed);
//setVirtualCarSpeed(0.0, 40.0);
//}---------------------------------------