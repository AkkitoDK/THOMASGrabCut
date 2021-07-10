#pragma once
#include <stdexcept>
#include <windows.h>
#include <iostream>

#ifdef USINGOPENCV_EXPORTS  
#define USINGOPENCV_EXPORTS_API __declspec(dllexport)   
#else  
#define USINGOPENCV_EXPORTS_API __declspec(dllimport) 
#endif  

extern "C" {
	// Initialize OpenCV.
	 USINGOPENCV_EXPORTS_API void Initialize();

	// return each frame.
	 USINGOPENCV_EXPORTS_API BYTE* ProcessFrame();

	 USINGOPENCV_EXPORTS_API int Coordinates();
}

