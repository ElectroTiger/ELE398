/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* Start the MLX 90316 Module. */
void MLX90316_Start();

/* Read the current angle. Returns NaN if there is an error.*/
double MLX90316_ReadAngle();

/* Get the error string. Returns null string if there is no error. */
void MLX90316_GetError(char* errorString, int iLen);

/* [] END OF FILE */
