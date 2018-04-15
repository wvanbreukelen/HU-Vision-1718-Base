/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "PreProcessing.h"
#include "IntensityImageStudent.h"
#include "ImageFactory.h"
#include <iostream>
#include <opencv2\opencv.hpp>

const int testIterations = 50;

class StudentPreProcessing : public PreProcessing {
private:
	enum class operators {PREWITT, SOBEL};

	

	const int kernelGradientSobelX[3][3] = {
	{ -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 }
	};

	const int kernelGradientSobelY[3][3] = {
	{ -1, -2, -1 },
	{ 0, 0, 0 },
	{ 1, 2, 1}
	};
	
	const int kernelGradientPrewittX[3][3] = {
	{ -1, 0, 1 },
	{ -1, 0, 1 },
	{ -1, 0, 1 }
	};

	const int kernelGradientPrewittY[3][3] = {
	{ -1, -1, -1 },
	{ 0, 0, 0 },
	{ 1, 1, 1 }
	};

public:
	IntensityImage * stepToIntensityImage(const RGBImage &image) const;
	IntensityImage * stepScaleImage(const IntensityImage &image) const;
	IntensityImage * stepEdgeDetection(const IntensityImage &image) const;
	IntensityImage * stepThresholding(const IntensityImage &image) const;

	/*
	Calculate gradient in the X direction.
	*/
	int calcGradientX(const IntensityImage &image, const int x, const int y, operators op = operators::PREWITT) const;

	/*
	Calculate gradient in the Y direction.
	*/
	int calcGradientY(const IntensityImage &image, const int x, const int y, operators op = operators::PREWITT) const;

	/*
	Calculate the average pixel intensity for the center of the image (center = image - border).
	*/
	float calcMeanCenterPixel(const IntensityImage *image, int thresholdLevel = -1) const;

	/*
	Calculate the mean border pixel intensity for the image.
	*/
	int calcMeanBorderPixel(const IntensityImage *image, int thresholdLevel = -1) const;

};
