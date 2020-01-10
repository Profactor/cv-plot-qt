// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import at.profactor.cvplotqt 0.1
import at.profactor.cvplotqtdemo 0.1

ApplicationWindow {
	width: 640
	height: 480
	visible: true
	title: "DemoOneMinute"
	AxesView{
		anchors.fill: parent
		Series{
			yData:[1,2,4,3,0]
			markerType: "Circle"
		}
	}
	Helpers {
		id: helpers
	}
}
