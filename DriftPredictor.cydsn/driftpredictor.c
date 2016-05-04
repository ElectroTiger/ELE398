#include "project.h"
#include "driftpredictor.h"
#include "stdlib.h"


struct structDriftEstimate {
    float xPos;
    float yPos;
};

oDriftEstimate DriftEstimate_new() {
    oDriftEstimate newObj= malloc(sizeof(oDriftEstimate));
    return newObj;
}

float DriftEstimate_GetXPos(oDriftEstimate obj) {
    return obj->xPos;
}

float DriftEstimate_GetYPos(oDriftEstimate obj) {
    return obj->yPos;
}

void DriftEstimate_Update(float humidity, float temp, float pressure, float altitude, float xVel, float yVel) {
    
}



/* [] END OF FILE */
