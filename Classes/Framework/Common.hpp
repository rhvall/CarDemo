//
//  Common.hpp
//  OpenGL iOS Framework
//
//  Modified by RHVT on 24/01/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//
//
//	           (\___/)
//             (o\ /o)
//            /|:.V.:|\
//		      \\::::://
//        -----`"" ""`-----

#pragma once

static const float PI = 3.14159265358979323846f;	
static const float PI_OVER_360 = PI / 360.0f;

typedef enum TouchTypes
{
    singleInitial = 0,
    singleMiddle,
    singleFinal,
    doubleInitial,
    doubleMiddle,
    doubleFinal,
    tripleInitial,
    tripleMiddle,
    tripleFinal
} TouchTypes;


enum TextureFormat
{
    TextureFormatGray,
    TextureFormatGrayAlpha,
    TextureFormatRgb,
    TextureFormatRgba,
    TextureFormatPvrtcRgb2,
    TextureFormatPvrtcRgba2,
    TextureFormatPvrtcRgb4,
    TextureFormatPvrtcRgba4,
    TextureFormat565,
    TextureFormat5551,
};

//Radians to degrees
static inline double radToDeg(const double deg)
{
	return deg * 180.0 / PI;
};

//Degrees to radians
static inline double degToRad(const double rad)
{
	return rad * PI / 180.0;
};
