// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#pragma once

#include <QObject>
#include <opencv2/core.hpp>

class Helpers: public QObject {
	Q_OBJECT;
public:
	using QObject::QObject;
	Q_INVOKABLE cv::Mat getLenna();
};

