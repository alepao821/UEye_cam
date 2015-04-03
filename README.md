# UEye Camera to OpenCV

Test application for a capture of a frame with the IDS UEye drivers and passage to OpenCV format.

To compile: g++ -std=c0xx main.cpp UEyeOpencv.cpp -o test `pkg-config --cflags --libs opencv`-lueye_api
