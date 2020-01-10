// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#ifndef CVPLOTQT_BUILDING
#error include this only inside this library to avoid conflicts as suggested in http://doc.qt.io/qt-5/qmetatype.html#Q_DECLARE_METATYPE
#endif 
 
#pragma once
#include <opencv2/core.hpp>

Q_DECLARE_METATYPE(cv::Mat)
