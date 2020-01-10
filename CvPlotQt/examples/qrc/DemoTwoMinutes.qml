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
	title: "DemoTwoMinutes"
	AxesView{
		anchors.fill: parent
		title: "Lenna"
		xLabel: "Col"
		yLabel: "Row"
		yReverse: true
		fixedAspectRatio: true
		xTight: true
		yTight: true
		tightBox: true
		Image{
			mat: helpers.getLenna()
		}	
		Series{
			xData:[100, 100, 400, 400, 100]
			yData:[100,400,400,100,100]
			color: "white"
			markerType: "Circle"
		}
	}
	Helpers {
		id: helpers
	}
}
