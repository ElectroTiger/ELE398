#ifndef DRIFTPREDICTOR
    #define DRIFTPREDICTOR
	/* Functions which are used to set the drift prediction variables.
	 * To obtain a drift prediction, every function here should be called
	 * in sequence. */
	    /* Set other droplet size parameters
     * Arguments:
     * diameter: Droplet diameter in mm
     * dragCoeff: The drag coefficient
     * dropletDensity: The droplet density in g/cm^3
     * */
    void setParams(double diameter, double dragCoefficient, double dropletDensity);

	/* Set the initial position of the particle in meters. */
    void setx0(double x, double y, double z);

    /* Set the initial velocity of the particle in meters. */
    void setv0(double vx, double vy, double z);

    /* Set the wind velocity condition in meters. */
    void setw(double wx, double wy, double wz);

    /* Set alpha, the constant for the drift equation.
     * Arguments:
     * pressure: Pressure in Pascals
     * temperature: Temperature in Celsius
     * humidity: Relative humidity*/
    void setAlpha(double pressure, double temperature, double humidity);

    /* Calculate the current drift. */
    void getDrift (double* fallTime, double* xPos, double* yPos);

    #endif

/* [] END OF FILE */
