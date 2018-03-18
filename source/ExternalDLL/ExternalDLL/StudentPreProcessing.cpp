#include "StudentPreProcessing.h"
#include <iostream>


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	/**const int kernelGradientX[3][3] = { { -1, 1, -1 },
	{ -1, 1, -1 },
	{ -1, 1, -1 } };

	const int kernelGradientY[3][3] = { { -1, 1, -1 },
	{ -1, 1, -1 },
	{ -1, 1, -1 } };

	IntensityImageStudent newImage(image.getWidth(), image.getHeight());

	// Loop through all pixels and apply kernel to calculate gradients.

	for (int y = 1; y < image.getHeight() - 1; y++) {
		for (int x = 1; x < image.getWidth() - 1; x++) {
			int gradientX = (image.getPixel(x - 1, y - 1) * kernelGradientX[0][0]) / 9;
		}
	}

	// Using the X and Y gradients, create a new intensity image.


	//return nullptr;
	return &newImage;**/

	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}