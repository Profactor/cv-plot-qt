// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include <catch.hpp>
#include <CvPlotQt/version.h>
#include <CvPlotQt/registerQtTypes.h>
#include <CvPlotQt/AxesView.h>

using namespace CvPlotQt;

TEST_CASE("version") {
    CHECK(!version().empty());
}
TEST_CASE("registerQtTypes") {
    registerQtTypes();
}

TEST_CASE("AxesView") {
	AxesView axesView;
}
