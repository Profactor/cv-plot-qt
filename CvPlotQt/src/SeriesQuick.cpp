// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include <CvPlotQt/SeriesQuick.h>
#include <CvPlot/drawables/Series.h>

using namespace CvPlot;

namespace CvPlotQt {

namespace {
void convert(const QVariantList &list, std::vector<double> &vector) {
	vector.clear();
	vector.reserve(list.size());
	for (const auto &it : list) {
		vector.push_back(it.toDouble());
	}
}
void convert(const std::vector<double> &vector, QVariantList &list) {
	list.clear();
	for (const double &value : vector) {
		list.push_back(value);
	}
}
void convert(const LineType &lineType, QString &string) {
	if (lineType == LineType::None) {
		string = "None";
		return;
	}
	if (lineType == LineType::Solid) {
		string = "Solid";
		return;
	}
	string = "?";
}
void convert(const QString &string, LineType &lineType) {
	if (0 == string.compare("None", Qt::CaseInsensitive)) {
		lineType = LineType::None;
		return;
	}
	if (0 == string.compare("Solid", Qt::CaseInsensitive)) {
		lineType = LineType::Solid;
		return;
	}
	lineType = LineType::Solid;
}
void convert(const MarkerType &markerType, QString &string) {
	if (markerType == MarkerType::None) {
		string = "None";
		return;
	}
	if (markerType == MarkerType::Circle) {
		string = "Circle";
		return;
	}
	if (markerType == MarkerType::Point) {
		string = "Point";
		return;
	}
	string = "?";
}
void convert(const QString &string, MarkerType &markerType) {
	if (0 == string.compare("None", Qt::CaseInsensitive)) {
		markerType = MarkerType::None;
		return;
	}
	if (0 == string.compare("Circle", Qt::CaseInsensitive)) {
		markerType = MarkerType::Circle;
		return;
	}
	if (0 == string.compare("Point", Qt::CaseInsensitive)) {
		markerType = MarkerType::Point;
		return;
	}
	markerType = MarkerType::None;
}
void convert(const QColor &color, cv::Scalar &scalar) {
	scalar = cv::Scalar(color.blue(), color.green(), color.red());
}
void convert(const cv::Scalar &scalar, QColor &color) {
	color = QColor(scalar.val[2], scalar.val[1], scalar.val[0]);
}
}

class SeriesQuick::Impl {
public:
	std::unique_ptr<Series> _series = std::make_unique<Series>();
	Series *_seriesPtr = _series.get();
};

SeriesQuick::SeriesQuick(QObject * parent)
:DrawableQuick(parent){
}

SeriesQuick::~SeriesQuick(){
}

QVariantList SeriesQuick::getXData() {
	QVariantList list;
	convert(impl->_seriesPtr->getX(), list);
	return list;
}

void SeriesQuick::setXData(QVariantList xData) {
	std::vector<double> vector;
	convert(xData, vector);
	impl->_seriesPtr->setX(vector);
	xDataChanged();
	contentChanged();
}

QVariantList SeriesQuick::getYData() {
	QVariantList list;
	convert(impl->_seriesPtr->getY(), list);
	return list;
}

void SeriesQuick::setYData(QVariantList yData) {
	std::vector<double> vector;
	convert(yData, vector);
	impl->_seriesPtr->setY(vector);
	yDataChanged();
	contentChanged();
}

void SeriesQuick::addTo(Axes &axes) {
	axes.drawables().push_back(std::move(impl->_series));
}

QString SeriesQuick::getName() {
    return QString::fromStdString(impl->_seriesPtr->getName());
}

void SeriesQuick::setName(QString name) {
    impl->_seriesPtr->setName(name.toStdString());
}

void SeriesQuick::setLineType(QString string) {
	LineType lineType;
	convert(string, lineType);
	impl->_seriesPtr->setLineType(lineType);
	lineTypeChanged();
	contentChanged();
}

QString SeriesQuick::getLineType() {
	QString string;
	convert(impl->_seriesPtr->getLineType(), string);
	return string;
}

void SeriesQuick::setMarkerType(QString string) {
	MarkerType markerType;
	convert(string, markerType);
	impl->_seriesPtr->setMarkerType(markerType);
	markerTypeChanged();
	contentChanged();
}

QString SeriesQuick::getMarkerType() {
	QString string;
	convert(impl->_seriesPtr->getMarkerType(), string);
	return string;
}

void SeriesQuick::setLineWidth(int lineWidth){
	impl->_seriesPtr->setLineWidth(lineWidth);
	lineWidthChanged();
	contentChanged();
}

int SeriesQuick::getLineWidth(){
	return impl->_seriesPtr->getLineWidth();
}

void SeriesQuick::setColor(QColor color){
	cv::Scalar scalar;
	convert(color, scalar);
	impl->_seriesPtr->setColor(scalar);
	colorChanged();
	contentChanged();
}

QColor SeriesQuick::getColor(){
	QColor color;
	convert(impl->_seriesPtr->getColor(), color);
	return color;
}

}