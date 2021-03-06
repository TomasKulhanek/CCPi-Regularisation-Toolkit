/*
 * This work is part of the Core Imaging Library developed by
 * Visual Analytics and Imaging System Group of the Science Technology
 * Facilities Council, STFC
 *
 * Copyright 2017 Daniil Kazantsev
 * Copyright 2017 Srikanth Nagella, Edoardo Pasca
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "matrix.h"
#include "mex.h"
#include "LLT_ROF_GPU_core.h"

/* CUDA implementation of Lysaker, Lundervold and Tai (LLT) model [1] combined with Rudin-Osher-Fatemi [2] TV regularisation penalty.
* 
* This penalty can deliver visually pleasant piecewise-smooth recovery if regularisation parameters are selected well. 
* The rule of thumb for selection is to start with lambdaLLT = 0 (just the ROF-TV model) and then proceed to increase 
* lambdaLLT starting with smaller values. 
*
* Input Parameters:
* 1. U0 - original noise image/volume
* 2. lambdaROF - ROF-related regularisation parameter
* 3. lambdaLLT - LLT-related regularisation parameter
* 4. tau - time-marching step 
* 5. iter - iterations number (for both models)
*
* Output:
* Filtered/regularised image
*
* References: 
* [1] Lysaker, M., Lundervold, A. and Tai, X.C., 2003. Noise removal using fourth-order partial differential equation with applications to medical magnetic resonance images in space and time. IEEE Transactions on image processing, 12(12), pp.1579-1590.
* [2] Rudin, Osher, Fatemi, "Nonlinear Total Variation based noise removal algorithms"
*/

void mexFunction(
        int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
        
{
    int number_of_dims, iterationsNumb;
    mwSize dimX, dimY, dimZ;
    const mwSize *dim_array;
    
    float *Input, *Output=NULL, lambdaROF, lambdaLLT, tau;
    
    dim_array = mxGetDimensions(prhs[0]);
    number_of_dims = mxGetNumberOfDimensions(prhs[0]);
    
    if ((nrhs < 3) || (nrhs > 5)) mexErrMsgTxt("At least 3 parameters is required, all parameters are: Image(2D/3D), Regularisation parameter (ROF), Regularisation parameter (LTT), iterations number, time-marching parameter");
    
    /*Handling Matlab input data*/
    Input  = (float *) mxGetData(prhs[0]);
    lambdaROF =  (float) mxGetScalar(prhs[1]); /* ROF regularization parameter */
    lambdaLLT =  (float) mxGetScalar(prhs[2]); /* ROF regularization parameter */    
    iterationsNumb = 250;
    tau =  0.0025;
    
    if (mxGetClassID(prhs[0]) != mxSINGLE_CLASS) {mexErrMsgTxt("The input image must be in a single precision"); }   
    if ((nrhs == 4) || (nrhs == 5)) iterationsNumb =  (int) mxGetScalar(prhs[3]); /* iterations number */    
    if (nrhs == 5) tau =  (float) mxGetScalar(prhs[4]); /* marching step parameter */  
        
    /*Handling Matlab output data*/
    dimX = dim_array[0]; dimY = dim_array[1]; dimZ = dim_array[2];
    
    /* output arrays*/
    if (number_of_dims == 2) {
        dimZ = 1; /*2D case*/
        /* output image/volume */
        Output = (float*)mxGetPr(plhs[0] = mxCreateNumericArray(2, dim_array, mxSINGLE_CLASS, mxREAL));                        
    }    
    if (number_of_dims == 3) Output = (float*)mxGetPr(plhs[0] = mxCreateNumericArray(3, dim_array, mxSINGLE_CLASS, mxREAL));   
  
    LLT_ROF_GPU_main(Input, Output, lambdaROF, lambdaLLT, iterationsNumb, tau, dimX, dimY, dimZ);    
}