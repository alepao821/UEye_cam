//******************************************************************************
//
//                 Low Cost Vision
//
//******************************************************************************
// Project:        ueyeOpencv
// File:           UEyeOpenCV.hpp
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

#pragma once
#include <ueye.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "UEyeOpenCVException.hpp"
/**
 * Wrapper class of UEye camera to support OpenCV Mat using the UEye SDK
 */
class UeyeOpencvCam {
public:
/**
 * Constructor creates camera interface of UEye cam
 * @param wdth : width of the image taken by the camera
 * @param heigh : height of the image taken by the camera
 */
        UeyeOpencvCam(int wdth, int heigh);
        /**
         * Returns the camera id
         * @return camera id
         */
        HIDS getHIDS();
        /**
         * Deconstructor
         */
        ~UeyeOpencvCam();
        /**
         * Returns an OpenCV Mat of the current view of the camera.
         * @return OpenCV Mat
         */
        cv::Mat getFrame();
        /**
         * Paste an OpenCV Mat of the current view of the camera in the @param mat.
         */
        void getFrame_mem(cv::Mat& mat);
        /**
         * Toggle auto white balance.
         * @param set
         */
        void setAutoWhiteBalance(bool set=true);
        /**
         * Toggle auto gain.
         * @param set
         */
        void setAutoGain(bool set=true);
private:
        HIDS hCam;
        cv::Mat mattie;
        int width;
        int height;
};
