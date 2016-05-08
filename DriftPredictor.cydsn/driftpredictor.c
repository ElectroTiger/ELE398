#include "project.h"
#include "driftpredictor.h"
#include "stdlib.h"
#include <math.h>
#include "MATLAB Generated Code/calculate_drift.h"

#define TEMP2CELSIUS 273.15
#define GASCONSTANT 287.05 // In J/(kg K)
#define M_PI 3.14159265358979323846

	/* Functions which are used to set the drift prediction variables.
	 * To obtain a drift prediction, every function here should be called
	 * in sequence. */
	    /* Set other droplet size parameters
     * Arguments:
     * diameter: Droplet diameter in mm
     * dragCoeff: The drag coefficient
     * */

	static double dropletDiameter; // In meters
	static double dragCoeff; // Dimensionless
	static double x0[3];
	static double v0[3];
	static double w[3];
	static double pres; // Pressure in Pascals
	static double temp; // Temperature in Kelvin
	static double rh; // Relative humidity in percentage
	static double alpha;
	static double dropDensity; // kg/m^3

    void setParams(double diameter, double dragCoefficient, double dropletDensity) {
    	dropletDiameter = diameter / 1000.;
    	dragCoeff = dragCoefficient;
    	dropDensity = dropletDensity * 1000;
    }

	/* Set the initial position of the particle in meters. */
    void setx0(double x, double y, double z) {
    	x0[0] = x;
    	x0[1] = y;
    	x0[2] = z;
    }

    /* Set the initial velocity of the particle in meters. */
    void setv0(double vx, double vy, double vz) {
    	v0[0] = vx;
    	v0[1] = vy;
    	v0[2] = vz;
    }

    /* Set the wind velocity condition in meters. */
    void setw(double wx, double wy, double wz) {
    	w[0] = wx;
    	w[1] = wy;
    	w[2] = wz;
    }
    
    /* Set alpha, the constant for the drift equation.
     * Arguments:
     * pressure: Pressure in Pascals
     * temperature: Temperature in Celsius
     * humidity: Relative humidity*/
    void setAlpha(double pressure, double temperature, double humidity) {
    	pres = pressure;
    	temp = temperature + TEMP2CELSIUS;
    	rh = humidity;

    	double airDensity;
    	{
    		/* Saturation vapor pressure of water. */
    		double Es;
    		{
    			double c0 = 6.1078;
    			double c1 = 7.5;
    			double c2 = 237.3;
    			double Tc = temp - TEMP2CELSIUS;
    			Es = 100 * c0 * pow(10,(c1*Tc/(c2*Tc)));
    		}

    		/* Partial pressure of water vapor. */
    		double Pv = rh * Es;

    		airDensity = (pressure / (GASCONSTANT * temp)) * (1 - (0.378 * Pv)/pressure);
    	}

    	double area = M_PI * dropletDiameter * dropletDiameter / 4;
    	double mass = (dropDensity * M_PI * dropletDiameter * dropletDiameter * dropletDiameter) / 6;

    	alpha = 0.5 * airDensity * dragCoeff * area / (2 * mass);
    }

    /* Calculate the current drift. */
    void getDrift (double* pFallTime, double* pxPos, double* pyPos) {
    	calculate_drift(x0, w, v0, alpha, pFallTime, pxPos, pyPos);
    }


/* [] END OF FILE */
