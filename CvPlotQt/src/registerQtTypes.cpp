// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include <CvPlotQt/registerQtTypes.h>
#include <CvPlotQt/SeriesQuick.h>
#include <CvPlotQt/ImageQuick.h>
#include <CvPlotQt/AxesView.h>
#include <qqml.h>

Q_DECLARE_METATYPE(cv::Mat)

namespace CvPlotQt{

void registerQtTypes() {
	qmlRegisterType<AxesView>("at.profactor.cvplotqt", 0, 1, "AxesView");
	qmlRegisterType<SeriesQuick>("at.profactor.cvplotqt", 0, 1, "Series");
	qmlRegisterType<ImageQuick>("at.profactor.cvplotqt", 0, 1, "Image");
	qRegisterMetaType<cv::Mat>();
}

}