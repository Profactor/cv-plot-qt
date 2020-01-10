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
	title: "DemoProperties"
	Rectangle{
		anchors.fill: parent
		color: "white"
		RowLayout{
			anchors.fill: parent
			spacing: 0
			Grid{
				Layout.fillHeight: true
				Layout.margins: 10
				columns: 2
				spacing: 10
				Text{text: "title"}
				TextField{id: titleTextField}
				Text{text: "xLabel"}
				TextField{id: xLabelTextField}
				Text{text: "yLabel"}
				TextField{id: yLabelTextField}
				Text{text: "yReverse"}
				CheckBox{id: yReverseCheckBox}
				Text{text: "fixedAspectRatio"}
				CheckBox{id: fixedAspectRatioCheckBox}
				Text{text: "xLog"}
				CheckBox{id: xLogCheckBox}
				Text{text: "yLog"}
				CheckBox{id: yLogCheckBox}
				Text{text: "horizontalGridEnabled"}
				CheckBox{
					id: horizontalGridEnabledCheckBox
					checked: true
				}
				Text{text: "verticalGridEnabled"}
				CheckBox{
					id: verticalGridEnabledCheckBox
					checked: true
				}
				Text{text: "xLimLow"}
				TextField{
					id: xLimLowTextField
					onEditingFinished: axesView.xLimLow = parseFloat(text)
				}
				Text{text: "xLimAuto"}
				CheckBox{
					id: xLimAutoCheckBox
					onCheckedChanged: axesView.xLimAuto = checked
				}
				Text{text: "lineType"}
				ComboBox {
					id: lineTypeComboBox
					currentIndex: 1
					model: ListModel {
						ListElement { text: "None"; }
						ListElement { text: "Solid"; }
					}
				}
				Text{text: "markerType"}
				ComboBox {
					id: markerTypeComboBox
					currentIndex: 0
					model: ListModel {
						ListElement { text: "None"; }
						ListElement { text: "Circle"; }
						ListElement { text: "Point"; }
					}
				}
				Text{text: "create"}
				Row{		
					spacing: 10		
					Button{
						text: "Series"
						onClicked: {
							var series = axesView.createSeries()
							series.xData=[Math.random()*100,Math.random()*100]
							series.yData=[Math.random()*100,Math.random()*100]
							series.color=Qt.rgba(Math.random(),Math.random(),Math.random(),1)
							series.lineWidth=Math.floor(1+Math.random()*6)
							series.markerType="Circle"
						}
					}
					Button{
						text: "Image"
						onClicked: {
							var image = axesView.createImage()
							image.mat = helpers.getLenna();
							image.position = Qt.rect(Math.random()*50, 50 + Math.random()*50, Math.random()*50, -Math.random()*50)
						}
					}
				}
			}
			AxesView{
				id: axesView
				Layout.fillHeight: true
				Layout.fillWidth: true
				title: titleTextField.text
				xLabel: xLabelTextField.text
				yLabel: yLabelTextField.text
				yReverse: yReverseCheckBox.checked
				fixedAspectRatio: fixedAspectRatioCheckBox.checked
				xLog: xLogCheckBox.checked
				yLog: yLogCheckBox.checked
				horizontalGridEnabled: horizontalGridEnabledCheckBox.checked
				verticalGridEnabled: verticalGridEnabledCheckBox.checked
				onXLimLowChanged: xLimLowTextField.text=xLimLow.toFixed(2)
				onXLimAutoChanged: xLimAutoCheckBox.checked = xLimAuto
				Series{
					xData:{
						var x = [];
						for (var i = 0; i <= 200; i++) {
							x.push(Math.pow(10,i/100.));
						}
						return x;
					}	
					yData: xData
					lineType: lineTypeComboBox.currentText
					markerType: markerTypeComboBox.currentText
				}
				MouseArea{
					anchors.fill: parent
					onPressed: {
						var series = axesView.createSeries()
						var point = axesView.unproject(Qt.point(mouse.x,mouse.y))
						series.xData=[point.x]
						series.yData=[point.y]
						series.markerType="Circle"
					}
				}
			}
		}
	}
	Helpers {
		id: helpers
	}
}
