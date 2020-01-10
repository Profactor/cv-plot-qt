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
	title: "DemoSync"

	function sync(from, to){
		to.xLimAuto=from.xLimAuto
		if(!from.xLimAuto){
			to.xLimLow = from.xLimLow
			to.xLimHigh = from.xLimHigh			
		}
		to.yLimAuto=from.yLimAuto
		if(!from.yLimAuto){
			to.yLimLow = from.yLimLow
			to.yLimHigh = from.yLimHigh			
		}
	}
	RowLayout{
		anchors.fill: parent
		AxesView{
			id: axes1
			Layout.fillHeight: true
			Layout.fillWidth: true
			yReverse: true
			fixedAspectRatio: true
			xTight: true
			yTight: true
			tightBox: true
			onMouseHandled: sync(axes1,axes2)
			Image{
				mat: helpers.getLenna()
			}	
		}
		AxesView{
			id: axes2
			Layout.fillHeight: true
			Layout.fillWidth: true
			yReverse: true
			fixedAspectRatio: true
			xTight: true
			yTight: true
			tightBox: true
			onMouseHandled: sync(axes2,axes1)
			Image{
				mat: helpers.getLenna()
			}	
		}
	}
	Helpers {
		id: helpers
	}
}
