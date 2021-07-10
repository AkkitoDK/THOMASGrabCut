#pragma once

#include <stdexcept>
#include <windows.h>
#include <iostream>

#ifdef USINGOPENCV_EXPORTS  
#define USINGOPENCV_EXPORTS_API __declspec(dllexport)   
#else  
#define USINGOPENCV_EXPORTS_API __declspec(dllimport)   
#endif  


namespace UsingOpenCV
{
	class Functions
	{
	public:
		// Initialize OpenCV.
		static USINGOPENCV_EXPORTS_API void Initialize();

		// return each frame.
		static USINGOPENCV_EXPORTS_API BYTE* ProcessFrame();

		//return middle
		static USINGOPENCV_EXPORTS_API int* Coordinates();
	};
}