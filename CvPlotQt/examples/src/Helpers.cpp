// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include "Helpers.h"
#include <opencv2/opencv.hpp>

cv::Mat Helpers::getLenna() {
	return cv::imread("exampledata/lenna.jpg");
}