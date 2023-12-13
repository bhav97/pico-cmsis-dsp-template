#include <stdio.h>
#include "pico/stdlib.h"

#include "arm_math.h"
#include "arm_const_structs.h"


#define TEST_LENGTH_SAMPLES 2048

/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES/2];

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
arm_cfft_instance_f32 varInstCfftF32;

/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;

/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */

int main(void)
{
    arm_status status;
    float32_t maxValue;
    status = ARM_MATH_SUCCESS;

    stdio_init_all();
    status = arm_cfft_init_1024_f32(&varInstCfftF32);

    /* Process the data through the CFFT/CIFFT module */
    arm_cfft_f32(&varInstCfftF32, testInput_f32_10khz, ifftFlag, doBitReverse);

    /* Process the data through the Complex Magnitude Module for
    calculating the magnitude at each bin */
    arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);

    /* Calculates maxValue and returns corresponding BIN value */
    arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);

    status = (testIndex != refIndex) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;

    if (status != ARM_MATH_SUCCESS) {
        printf("FAILURE\n");
    }
    else{
        printf("SUCCESS\n");
    }
    while(true) {}
}

