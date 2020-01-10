// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include <CvPlotQt/ImageQuick.h>
#include <CvPlot/drawables/Image.h>
#include <CvPlotQt/internal/declareQtTypes.h>

using namespace CvPlot;

namespace CvPlotQt {

namespace {
void convert(const QRectF &rectF, cv::Rect2d &rect2d) {
	rect2d = cv::Rect2d(rectF.x(), rectF.y(), rectF.width(), rectF.height());
}
void convert(const cv::Rect2d &rect2d, QRectF &rectF) {
	rectF = QRectF(rect2d.x, rect2d.y, rect2d.width, rect2d.height);
}
}

class ImageQuick::Impl {
public:
	std::unique_ptr<Image> _image = std::make_unique<Image>();
	Image *_imagePtr = _image.get();
};

ImageQuick::ImageQuick(QObject * parent)
	:DrawableQuick(parent) {
}

ImageQuick::~ImageQuick(){
}

void ImageQuick::setMat(QVariant var){
	cv::Mat mat;
	if(var.canConvert<cv::Mat>()){
		mat = var.value<cv::Mat>();
	}
	impl->_imagePtr->setMat(mat);
	matChanged();
	contentChanged();
}

QVariant ImageQuick::getMat(){
	return QVariant::fromValue(impl->_imagePtr->getMat());
}

void ImageQuick::setPosition(QRectF position){
	cv::Rect2d rect2d;
	convert(position, rect2d);
	impl->_imagePtr->setPosition(rect2d);
	positionChanged();
	contentChanged();
}

QRectF ImageQuick::getPosition(){
	QRectF rectF;
	convert(impl->_imagePtr->getPosition(), rectF);
	return rectF;
}

void ImageQuick::addTo(Axes &axes) {
	if (!impl->_image) {
		throw std::runtime_error("already added");
	}
	axes.drawables().push_back(std::move(impl->_image));
}

QString ImageQuick::getName() {
    return QString::fromStdString(impl->_imagePtr->getName());
}

void ImageQuick::setName(QString name) {
    impl->_imagePtr->setName(name.toStdString());
}

}

