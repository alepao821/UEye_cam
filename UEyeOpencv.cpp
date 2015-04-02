//******************************************************************************
//
//                 Low Cost Vision
//
//******************************************************************************
// Project:        ueyeOpencv
// File:           UEyeOpenCV.cpp
// Description:    Wrapper class of UEye camera to support OpenCV Mat using the UEye SDK
// Author:         Wouter Langerak
// Notes:          For more functionalities use the SDK of UEye, the purpose of this project is to make it compatible with OpenCV Mat.
//
// License: newBSD 
//  
// Copyright © 2012, HU University of Applied Sciences Utrecht. 
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//******************************************************************************

#include "UEyeOpenCV.hpp"
#include <iostream>
#include <ueye.h>

UeyeOpencvCam::UeyeOpencvCam(int wdth, int heigh) {
        width = wdth;
        height = heigh;
        using std::cout;
        using std::endl;
        mattie = cv::Mat(height, width, CV_8UC3);
        hCam = 0;
        char* ppcImgMem;
        int pid;
        INT nAOISupported = 0;
        double on = 1;
        double empty;
        int retInt = IS_SUCCESS;
        retInt = is_InitCamera(&hCam, 0);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        retInt = is_SetColorMode(hCam, IS_CM_BGR8_PACKED);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        retInt = is_ImageFormat(hCam, IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED, (void*) &nAOISupported, sizeof(nAOISupported));
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        retInt = is_AllocImageMem(hCam, width, height, 24, &ppcImgMem, &pid);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        retInt = is_SetImageMem(hCam, ppcImgMem, pid);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        //set auto settings
        retInt = is_SetAutoParameter(hCam, IS_SET_ENABLE_AUTO_WHITEBALANCE, &on, &empty);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        retInt = is_SetAutoParameter(hCam, IS_SET_ENABLE_AUTO_GAIN, &on, &empty);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        retInt = is_SetFrameRate(hCam, 15, NULL);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
        
        retInt = is_CaptureVideo(hCam, IS_DONT_WAIT);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
}

UeyeOpencvCam::~UeyeOpencvCam() {
        int retInt = is_ExitCamera(hCam);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
}

cv::Mat UeyeOpencvCam::getFrame() {
        getFrame_mem(mattie);
        return mattie;
}

void UeyeOpencvCam::getFrame_mem(cv::Mat& mat) {
        VOID* pMem;
        int retInt = is_GetImageMem(hCam, &pMem);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
//      if (mat.cols == width && mat.rows == height && mat.depth() == 3) {
                memcpy(mat.ptr(), pMem, width * height * 3);
//      } else {
//              throw UeyeOpenCVException(hCam, -1337);
//      }
}

HIDS UeyeOpencvCam::getHIDS() {
        return hCam;
}

void UeyeOpencvCam::setAutoWhiteBalance(bool set) {
        double empty;
        double on = set ? 1 : 0;
        int retInt = is_SetAutoParameter(hCam, IS_SET_ENABLE_AUTO_WHITEBALANCE, &on, &empty);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
}

void UeyeOpencvCam::setAutoGain(bool set) {
        double empty;
        double on = set ? 1 : 0;
        int retInt = is_SetAutoParameter(hCam, IS_SET_ENABLE_AUTO_GAIN, &on, &empty);
        if (retInt != IS_SUCCESS) {
                throw UeyeOpenCVException(hCam, retInt);
        }
}
