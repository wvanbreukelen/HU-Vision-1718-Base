#include "StudentPreProcessing.h"
#include <iostream>


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

int StudentPreProcessing::calcGradientX(const IntensityImage &image, const int x, const int y, operators op) const {
	/**return (image.getPixel(x - 1, y - 1) * kernelGradientX[0][0] +
			image.getPixel(x);**/

	int sum = 0;

	if (op == operators::SOBEL) {
		//std::cout << "Using sobel X...\n";
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientSobelX[kernelX][kernelY];
			}
		}
	}
	else if (op == operators::PREWITT) {
		//std::cout << "Using prewitt X...\n";
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientPrewittX[kernelX][kernelY];
			}
		}
	}



	return sum / 9;
}

int StudentPreProcessing::calcGradientY(const IntensityImage &image, const int x, const int y, operators op) const {
	/**return (image.getPixel(x - 1, y - 1) * kernelGradientX[0][0] +
			image.getPixel(x);**/

	int sum = 0;

	if (op == operators::SOBEL) {
		//std::cout << "Using sobel Y...\n";
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientSobelY[kernelX][kernelY];
			}
		}
	}
	else if (op == operators::PREWITT) {
		//std::cout << "Using prewitt Y...\n";
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientPrewittY[kernelX][kernelY];
			}
		}
	}


	return sum / 9;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {


	//IntensityImageStudent* newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	IntensityImage* newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	// Loop through all pixels and apply kernel to calculate gradients.

	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {

			if (x > 0 && x < image.getWidth() - 1 && y > 0 && y < image.getHeight() - 1) {
				int gradientX = calcGradientX(image, x, y);
				int gradientY = calcGradientY(image, x, y);

				int sum = abs(gradientX) + abs(gradientY);
				sum = sum > 255 ? 255 : sum;
				sum = sum < 0 ? 0 : sum;
				newImage->setPixel(x, y, sum);
			}
			else {
				newImage->setPixel(x, y, 0);
			}



		}
	}

	// Using the X and Y gradients, create a new intensity image.


	//return nullptr;
	return newImage;
}

int StudentPreProcessing::calcMeanCenterPixel(const IntensityImage &image, int thresholdLevel) const {
	int centerSum = 0, centerPixelAmt = 0;

	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			if (x > 0 && x < image.getWidth() - 1 && y > 0 && y < image.getHeight() - 1) {
				// Center
				if (thresholdLevel == -1 || thresholdLevel <= image.getPixel(x, y)) {
					centerSum += image.getPixel(x, y);
					centerPixelAmt++;
				}

			}
			//else {
				// Randen
				//cornerSum += image.getPixel(x, y);
				//cornerPixelAmt++;
			//}
		}
	}

	if (centerPixelAmt > 0) {
		return (centerSum / centerPixelAmt);
	}
	else {
		return 0;
	}

}

int StudentPreProcessing::calcMeanCornerPixel(const IntensityImage &image, int thresholdLevel) const {
	int cornerSum = 0, cornerPixelAmt = 0;

	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			if (x > 0 && x < image.getWidth() - 1 && y > 0 && y < image.getHeight() - 1) {
				// Center
				//cornerSum += image.getPixel(x, y);
				//cornerPixelAmt++;
			} else {
				// Randen
				if (thresholdLevel == -1 || thresholdLevel <= image.getPixel(x, y)) {
					cornerSum += image.getPixel(x, y);
					cornerPixelAmt++;
				}
			}
		}
	}

	if (cornerPixelAmt > 0) {
		return (cornerSum / cornerPixelAmt);
	}
	else {
		return 0;
	}
	
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage* newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	int u1 = calcMeanCenterPixel(image);
	int u2 = calcMeanCornerPixel(image);
	int tOld = 0;
	int tNew = (u1 + u2) / 2;

	//std::cout << "New threshold: " << tNew << std::endl;

	while (tNew != tOld) {
		u1 = calcMeanCenterPixel(image, tNew);
		u2 = calcMeanCornerPixel(image, tNew);

		tOld = tNew;
		tNew = (u1 + u2) / 2;

		std::cout << "New threshold: " << tNew << std::endl;
	}

	for (int y = 0; y < image.getHeight(); y++) {
		for (int x = 0; x < image.getWidth(); x++) {
			if (image.getPixel(x, y) >= tNew) {
				newImage->setPixel(x, y, 255);
			}
			else {
				newImage->setPixel(x, y, 0);
			}
		}
	}

	return newImage;
}