#include "StudentPreProcessing.h"
#include <opencv2/imgproc/imgproc.hpp>



IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

int StudentPreProcessing::calcGradientX(const IntensityImage &image, const int x, const int y, operators op) const {
	int sum = 0;

	if (op == operators::SOBEL) {
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientSobelX[kernelX][kernelY];
			}
		}
	}
	else if (op == operators::PREWITT) {
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientPrewittX[kernelX][kernelY];
			}
		}
	}



	return sum / 9;
}

int StudentPreProcessing::calcGradientY(const IntensityImage &image, const int x, const int y, operators op) const {
	int sum = 0;

	if (op == operators::SOBEL) {
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientSobelY[kernelX][kernelY];
			}
		}
	}
	else if (op == operators::PREWITT) {
		for (int kernelX = 0; kernelX < 3; kernelX++) {
			for (int kernelY = 0; kernelY < 3; kernelY++) {
				sum += image.getPixel(x + kernelX - 1, y + kernelY - 1) * kernelGradientPrewittY[kernelX][kernelY];
			}
		}
	}


	return sum / 9;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImage* newImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	float timings[testIterations];

	for (int i = 0; i < testIterations; i++) {
		long startTime = cv::getTickCount();

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

		long endTime = cv::getTickCount();

		timings[i] = ((endTime - startTime) / cv::getTickFrequency());
	}

	float sum = 0.0f;

	// Take a average
	for (int i = 0; i < testIterations; i++) {
		sum += timings[i];
	}

	std::cout << "Elapsed time edge detection: " << (sum / testIterations) << std::endl;

	return newImage;
}


float StudentPreProcessing::calcMeanCenterPixel(const IntensityImage *image, int thresholdLevel) const {
	float centerSum = 0, centerPixelAmt = 0;

	for (int y = 0; y < image->getHeight(); y++) {
		for (int x = 0; x < image->getWidth(); x++) {
			if (x > 0 && x < image->getWidth() - 1 && y > 0 && y < image->getHeight() - 1) {
				// Center
				if (thresholdLevel == -1 || thresholdLevel <= image->getPixel(x, y)) {
					centerSum += image->getPixel(x, y);
					centerPixelAmt++;
				}
			}
		}
	}

	if (centerPixelAmt > 0) {
		return (centerSum / centerPixelAmt);
	}
	else {
		return 0;
	}

}

int StudentPreProcessing::calcMeanBorderPixel(const IntensityImage *image, int thresholdLevel) const {
	int cornerSum = 0, cornerPixelAmt = 0;

	for (int y = 0; y < image->getHeight(); y++) {
		for (int x = 0; x < image->getWidth(); x++) {
			if (x > 0 && x < image->getWidth() - 1 && y > 0 && y < image->getHeight() - 1) {
				// Center
				//cornerSum += image.getPixel(x, y);
				//cornerPixelAmt++;
			} else {
				// Randen
				if (thresholdLevel == -1 || thresholdLevel <= image->getPixel(x, y)) {
					cornerSum += image->getPixel(x, y);
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
	IntensityImage* scaledImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	IntensityImage* thresholdImage = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());
	float timings[testIterations];

	for (int i = 0; i < testIterations; i++) {
		long startTime = cv::getTickCount();

		int u1 = calcMeanCenterPixel(&image);
		int u2 = calcMeanBorderPixel(&image);
		int tOld = -1;
		int tNew = (u1 + u2) / 2;

		while (tNew != tOld) {
			u1 = calcMeanCenterPixel(&image, tNew);
			u2 = calcMeanBorderPixel(&image, tNew);

			tOld = tNew;
			tNew = (u1 + u2) / 2;
		}

		for (int y = 0; y < image.getHeight(); y++) {
			for (int x = 0; x < image.getWidth(); x++) {
				if (image.getPixel(x, y) >= tNew) {
					thresholdImage->setPixel(x, y, 255);
				}
				else {
					thresholdImage->setPixel(x, y, 0);
				}
			}
		}

		long endTime = cv::getTickCount();

		timings[i] = (endTime - startTime) / cv::getTickFrequency();
	}

	float sum = 0.0f;

	// Take a average
	for (int i = 0; i < testIterations; i++) {
		sum += timings[i];
	}

	std::cout << "Elapsed time edge thresholding: " << (sum / testIterations) << std::endl;
	return thresholdImage;
}