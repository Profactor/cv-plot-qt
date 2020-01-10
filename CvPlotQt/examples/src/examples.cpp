// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include <catch.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <CvPlotQt/registerQtTypes.h>
#include "Helpers.h"
#include <qdir.h>

void run(std::string qmlFilename) {
	int argc = 0;
	QGuiApplication app(argc, nullptr);
	QDir::setCurrent(app.applicationDirPath());
	CvPlotQt::registerQtTypes();
	qmlRegisterType<Helpers>("at.profactor.cvplotqtdemo", 0, 1, "Helpers");
	QQmlApplicationEngine engine(QUrl(QString::fromStdString("qrc:/"+ qmlFilename)));
	app.exec();
}

TEST_CASE("OneMinute") {
	run("DemoOneMinute.qml");
}
TEST_CASE("TwoMinutes") {
	run("DemoTwoMinutes.qml");
}
TEST_CASE("Sync") {
	run("DemoSync.qml");
}
TEST_CASE("Properties") {
	run("DemoProperties.qml");
}
