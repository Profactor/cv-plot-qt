// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#include <CvPlotQt/AxesView.h>
#include <QPainter>
#include <opencv2/opencv.hpp>
#include <CvPlot/gui/MouseAdapter.h>
#include <CvPlot/core/Axes.h>
#include <CvPlot/core/makeAxes.h>
#include <CvPlot/drawables/Series.h>
#include <CvPlot/drawables/XAxis.h>
#include <CvPlot/drawables/YAxis.h>
#include <CvPlot/drawables/Title.h>
#include <CvPlot/drawables/XLabel.h>
#include <CvPlot/drawables/YLabel.h>
#include <CvPlot/drawables/HorizontalGrid.h>
#include <CvPlot/drawables/VerticalGrid.h>
#include <CvPlot/drawables/Border.h>
#include <CvPlot/drawables/Image.h>

using namespace CvPlot;

namespace {
void paintMat(QPainter *painter, const cv::Mat3b &bgr) {
	cv::Mat3b rgb;
	cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);
	QImage qimage(rgb.data, rgb.cols, rgb.rows, rgb.cols * 3, QImage::Format_RGB888);
	painter->drawImage(0, 0, qimage);
}
cv::MouseEventTypes getType(QMouseEvent *event) {
	if (event->type() == QEvent::MouseButtonPress && event->button() == Qt::LeftButton) {
		return cv::EVENT_LBUTTONDOWN;
	}
	if (event->type() == QEvent::MouseButtonRelease && event->button() == Qt::LeftButton) {
		return cv::EVENT_LBUTTONUP;
	}
	if (event->type() == QEvent::MouseButtonDblClick && event->button() == Qt::LeftButton) {
		return cv::EVENT_LBUTTONDBLCLK;
	}

	if (event->type() == QEvent::MouseButtonPress && event->button() == Qt::RightButton) {
		return cv::EVENT_RBUTTONDOWN;
	}
	if (event->type() == QEvent::MouseButtonRelease && event->button() == Qt::RightButton) {
		return cv::EVENT_RBUTTONUP;
	}
	if (event->type() == QEvent::MouseButtonDblClick && event->button() == Qt::RightButton) {
		return cv::EVENT_RBUTTONDBLCLK;
	}

	if (event->type() == QEvent::MouseButtonPress && event->button() == Qt::MiddleButton) {
		return cv::EVENT_MBUTTONDOWN;
	}
	if (event->type() == QEvent::MouseButtonRelease && event->button() == Qt::MiddleButton) {
		return cv::EVENT_MBUTTONUP;
	}
	if (event->type() == QEvent::MouseButtonDblClick && event->button() == Qt::MiddleButton) {
		return cv::EVENT_MBUTTONDBLCLK;
	}

	if (event->type() == QEvent::MouseMove) {
		return cv::EVENT_MOUSEMOVE;
	}
	return (cv::MouseEventTypes)-1;
}
cv::MouseEventTypes getType(QHoverEvent *event) {
	return cv::EVENT_MOUSEMOVE;
}
cv::MouseEventFlags getFlags(QMouseEvent *event) {
	cv::MouseEventFlags flags = (cv::MouseEventFlags)0;
	if (event->buttons() & Qt::LeftButton) {
		flags = (cv::MouseEventFlags)(flags | cv::EVENT_FLAG_LBUTTON);
	}
	if (event->buttons() & Qt::RightButton) {
		flags = (cv::MouseEventFlags)(flags | cv::EVENT_FLAG_RBUTTON);
	}
	if (event->buttons() & Qt::MiddleButton) {
		flags = (cv::MouseEventFlags)(flags | cv::EVENT_FLAG_MBUTTON);
	}
	return flags;
}
cv::MouseEventFlags getFlags(QHoverEvent *event) {
	return (cv::MouseEventFlags)0;
}

struct PropertyValues{
	bool xLog;
	bool yLog;
	bool yReverse;
	bool fixedAspectRatio;
	QString title;
	QString xLabel;
	QString yLabel;
	bool horizontalGridEnabled;
	bool verticalGridEnabled;
	bool xTight;
	bool yTight;
	bool tightBox;
	double xLimLow;
	double xLimHigh;
	double yLimLow;
	double yLimHigh;
	bool xLimAuto;
	bool yLimAuto;
};

}

namespace CvPlotQt {

class AxesView::Impl {
public:
	AxesView &_parent;
	Axes _axes;
	MouseAdapter _mouseAdapter;
	cv::Mat3b _mat;
	PropertyValues _propertyValues;
	bool _acceptMouseEvents = true;

	Impl(AxesView &parent)
		:_parent(parent)
		,_mouseAdapter(_axes){

		_axes.create<Border>();
		_axes.create<VerticalGrid>(&_axes.create<XAxis>());
        _axes.create<HorizontalGrid>(&_axes.create<YAxis>());
        _axes.create<XLabel>();
        _axes.create<YLabel>("", _axes.find<YAxis>());

		updatePropertyValues();
	}
	void updatePropertyValues() {
		_propertyValues.xLog = _axes.getXLog();
		_propertyValues.yLog = _axes.getYLog();
		_propertyValues.yReverse = _axes.getYReverse();
		_propertyValues.fixedAspectRatio = _axes.getFixedAspectRatio();
		_propertyValues.title = QString::fromStdString(_axes.findOrCreate<Title>().getTitle());
		_propertyValues.xLabel = QString::fromStdString(_axes.findOrCreate<XLabel>().getLabel());
		_propertyValues.yLabel = QString::fromStdString(_axes.findOrCreate<YLabel>().getLabel());
		_propertyValues.horizontalGridEnabled = _axes.findOrCreate<HorizontalGrid>().getEnabled();
		_propertyValues.verticalGridEnabled = _axes.findOrCreate<VerticalGrid>().getEnabled();
		_propertyValues.xTight = _axes.getXTight();
		_propertyValues.yTight = _axes.getYTight();
		_propertyValues.tightBox = _axes.getTightBox();
		_propertyValues.xLimLow = _axes.getXLim().first;
		_propertyValues.xLimHigh = _axes.getXLim().second;
		_propertyValues.yLimLow = _axes.getYLim().first;
		_propertyValues.yLimHigh = _axes.getYLim().second;
		_propertyValues.xLimAuto = _axes.getXLimAuto();
		_propertyValues.yLimAuto = _axes.getYLimAuto();
	}
	void addDrawable(DrawableQuick *drawable) {
		drawable->addTo(_axes);
		QObject::connect(drawable, &DrawableQuick::contentChanged, &_parent, &AxesView::contentChanged);
	}
	template<typename T>
	T* createDrawable() {
		T *t = new T; //dont set parent in constructor, cast in AxesView::childEvent() fails otherwise
		t->setParent(&_parent);
		return t;
	}
	template<typename Event>
	void qMouseEvent(Event *event) {
		if (!_acceptMouseEvents) {
			return;
		}
		MouseEvent mouseEvent(_axes, _mat.size(), getType(event), event->pos().x(), event->pos().y(), getFlags(event));
		//call virtual method
		if (_parent.mouseEvent(mouseEvent)) {
			_parent.updateProperties();
			_parent.mouseHandled();
			_parent.update();
		}
	}
	/*virtual*/ bool mouseEvent(const MouseEvent &mouseEvent) {
		return _mouseAdapter.mouseEvent(mouseEvent);
	}
	void wheelEvent(QWheelEvent*event) {
		if (!_acceptMouseEvents) {
			return;
		}
		//from #define CV_GET_WHEEL_DELTA(flags) ((short)((flags >> 16) & 0xffff)) // upper 16 bits
		int steps = event->angleDelta().y();
		int flags = (steps & 0xffff) << 16;
		MouseEvent mouseEvent(_axes, _mat.size(), cv::MouseEventTypes::EVENT_MOUSEWHEEL, event->pos().x(), event->pos().y(), flags);
		if (_mouseAdapter.mouseEvent(mouseEvent)) {
			_parent.updateProperties();
			_parent.mouseHandled();
			_parent.update();
		}
	}
};


AxesView::AxesView(QQuickItem * parent)
	:QQuickPaintedItem(parent)
	,impl(*this){
	setAcceptedMouseButtons(Qt::AllButtons);
	QObject::connect(this, &AxesView::contentChanged, this, [this]() {
		update();
	});
}

AxesView::~AxesView(){
}

void AxesView::paint(QPainter * painter){
	//called from render thread, but main thread is blocked
	const int rows = painter->device()->height();
	const int cols = painter->device()->width();
	impl->_axes.render(impl->_mat, cv::Size(cols, rows));
	paintMat(painter, impl->_mat);
}

void AxesView::componentComplete() {
	//add static items to axes
	for(QObject *child: children()) {
		if (qobject_cast<DrawableQuick *>(child)) {
			DrawableQuick *drawable = qobject_cast<DrawableQuick *>(child);
			impl->addDrawable(drawable);
		}
	}
	QQuickPaintedItem::componentComplete();
}

void AxesView::childEvent(QChildEvent *event){
	//add dynamic item to axes
	if (event->type() == QEvent::ChildAdded
		&& qobject_cast<DrawableQuick *>(event->child())
		) {
		DrawableQuick *drawable = qobject_cast<DrawableQuick *>(event->child());
		impl->addDrawable(drawable);
	}
	QQuickPaintedItem::childEvent(event);
}

QPointF AxesView::unproject(QPointF point){
	CvPlot::Axes &axes = getAxes();
	auto projection = axes.getProjection(cv::Size(width(), height()));
	auto inner = projection.outerToInner(cv::Point(point.x(), point.y()));
	auto pos = projection.unproject(inner);
	return QPointF((qreal)pos.x, (qreal)pos.y);
}

void AxesView::mousePressEvent(QMouseEvent *event) {
	impl->qMouseEvent(event);
}

void AxesView::mouseReleaseEvent(QMouseEvent *event) {
	impl->qMouseEvent(event);
}

void AxesView::mouseMoveEvent(QMouseEvent *event) {
	impl->qMouseEvent(event);
}

void AxesView::wheelEvent(QWheelEvent *event) {
	impl->wheelEvent(event);
}

void AxesView::mouseDoubleClickEvent(QMouseEvent *event) {
	impl->qMouseEvent(event);
}

void AxesView::hoverMoveEvent(QHoverEvent *event) {
	impl->qMouseEvent(event);
}

bool AxesView::mouseEvent(const CvPlot::MouseEvent &mouseEvent) {
	return impl->mouseEvent(mouseEvent);
}

CvPlot::Axes & AxesView::getAxes() {
	return impl->_axes;
}

void AxesView::updateProperties(){
	auto old = impl->_propertyValues;
	impl->updatePropertyValues();
	auto change = false;
	if (impl->_propertyValues.xLog != old.xLog) {
		xLogChanged();
		change = true;
	}
	if (impl->_propertyValues.yLog != old.yLog) {
		yLogChanged();
		change = true;
	}
	if (impl->_propertyValues.yReverse != old.yReverse) {
		yReverseChanged();
		change = true;
	}
	if (impl->_propertyValues.fixedAspectRatio != old.fixedAspectRatio) {
		fixedAspectRatioChanged();
		change = true;
	}
	if (impl->_propertyValues.title != old.title) {
		titleChanged();
		change = true;
	}
	if (impl->_propertyValues.xLabel != old.xLabel) {
		xLabelChanged();
		change = true;
	}
	if (impl->_propertyValues.yLabel != old.yLabel) {
		yLabelChanged();
		change = true;
	}
	if (impl->_propertyValues.horizontalGridEnabled != old.horizontalGridEnabled) {
		horizontalGridEnabledChanged();
		change = true;
	}
	if (impl->_propertyValues.verticalGridEnabled != old.verticalGridEnabled) {
		verticalGridEnabledChanged();
		change = true;
	}
	if (impl->_propertyValues.xTight != old.xTight) {
		xTightChanged();
		change = true;
	}
	if (impl->_propertyValues.yTight != old.yTight) {
		yTightChanged();
		change = true;
	}
	if (impl->_propertyValues.tightBox != old.tightBox) {
		tightBoxChanged();
		change = true;
	}
	if (impl->_propertyValues.xLimLow != old.xLimLow) {
		xLimLowChanged();
		change = true;
	}
	if (impl->_propertyValues.xLimHigh != old.xLimHigh) {
		xLimHighChanged();
		change = true;
	}
	if (impl->_propertyValues.yLimLow != old.yLimLow) {
		yLimLowChanged();
		change = true;
	}
	if (impl->_propertyValues.yLimHigh != old.yLimHigh) {
		yLimHighChanged();
		change = true;
	}
	if (impl->_propertyValues.xLimAuto != old.xLimAuto) {
		xLimAutoChanged();
		change = true;
	}
	if (impl->_propertyValues.yLimAuto != old.yLimAuto) {
		yLimAutoChanged();
		change = true;
	}
	if (change) {
		contentChanged();
	}
}

Q_INVOKABLE SeriesQuick* AxesView::createSeries() {
	return impl->createDrawable<SeriesQuick>();
}

Q_INVOKABLE CvPlotQt::ImageQuick * AxesView::createImage() {
	return impl->createDrawable<ImageQuick>();
}

void AxesView::setXLog(bool log) {
	impl->_axes.setXLog(log);
	updateProperties();
}

bool AxesView::getXLog() {
	return impl->_propertyValues.xLog;
}

void AxesView::setYLog(bool log) {
	impl->_axes.setYLog(log);
	updateProperties();
}

bool AxesView::getYLog() {
	return impl->_propertyValues.yLog;
}

void AxesView::setYReverse(bool reverse) {
	impl->_axes.setYReverse(reverse);
	updateProperties();
}

bool AxesView::getYReverse() {
	return impl->_propertyValues.yReverse;
}

void AxesView::setFixedAspectRatio(bool fixed) {
	impl->_axes.setFixedAspectRatio(fixed);
	updateProperties();
}

bool AxesView::getFixedAspectRatio() {
	return impl->_propertyValues.fixedAspectRatio;
}

void AxesView::setTitle(QString title) {
	impl->_axes.title(title.toStdString());
	updateProperties();
}

QString AxesView::getTitle() {
	return impl->_propertyValues.title;
}

void AxesView::setXLabel(QString xLabel) {
	impl->_axes.xLabel(xLabel.toStdString());
	updateProperties();
}

QString AxesView::getXLabel() {
	return impl->_propertyValues.xLabel;
}

void AxesView::setYLabel(QString yLabel) {
	impl->_axes.yLabel(yLabel.toStdString());
	updateProperties();
}

QString AxesView::getYLabel() {
	return impl->_propertyValues.yLabel;
}

bool AxesView::getHorizontalGridEnabled() {
	return impl->_propertyValues.horizontalGridEnabled;
}

void AxesView::setHorizontalGridEnabled(bool enabled) {
	impl->_axes.findOrCreate<HorizontalGrid>().setEnabled(enabled);
	updateProperties();
}

bool AxesView::getVerticalGridEnabled() {
	return impl->_propertyValues.verticalGridEnabled;
}

void AxesView::setVerticalGridEnabled(bool enabled) {
	impl->_axes.findOrCreate<VerticalGrid>().setEnabled(enabled);
	updateProperties();
}

void AxesView::setXTight(bool tight) {
	impl->_axes.setXTight(tight);
	updateProperties();
}

bool AxesView::getXTight() {
	return impl->_propertyValues.xTight;
}

void AxesView::setYTight(bool tight) {
	impl->_axes.setYTight(tight);
	updateProperties();
}

bool AxesView::getYTight() {
	return impl->_propertyValues.yTight;
}

void AxesView::setTightBox(bool tight) {
	impl->_axes.setTightBox(tight);
	updateProperties();
}

bool AxesView::getTightBox() {
	return impl->_propertyValues.tightBox;
}

void AxesView::setXLimLow(double xLimLow){
	if (xLimLow == getXLimLow()) {
		return;
	}
	impl->_axes.setXLim({ xLimLow, getXLimHigh() });
	updateProperties();
}

double AxesView::getXLimLow(){
	return impl->_propertyValues.xLimLow;
}

void AxesView::setXLimHigh(double xLimHigh){
	if (xLimHigh == getXLimHigh()) {
		return;
	}
	impl->_axes.setXLim({ getXLimLow(), xLimHigh });
	updateProperties();
}

double AxesView::getXLimHigh(){
	return impl->_propertyValues.xLimHigh;
}

void AxesView::setYLimLow(double yLimLow) {
	if (yLimLow == getYLimLow()) {
		return;
	}
	impl->_axes.setYLim({ yLimLow, getYLimHigh() });
	updateProperties();
}

double AxesView::getYLimLow() {
	return impl->_propertyValues.yLimLow;
}

void AxesView::setYLimHigh(double yLimHigh) {
	if (yLimHigh == getYLimHigh()) {
		return;
	}
	impl->_axes.setYLim({ getYLimLow(), yLimHigh });
	updateProperties();
}

double AxesView::getYLimHigh() {
	return impl->_propertyValues.yLimHigh;
}
void AxesView::setXLimAuto(bool xLimAuto){
	impl->_axes.setXLimAuto(xLimAuto);
	updateProperties();
}
bool AxesView::getXLimAuto(){
	return impl->_propertyValues.xLimAuto;
}
void AxesView::setYLimAuto(bool yLimAuto){
	impl->_axes.setYLimAuto(yLimAuto);
}
bool AxesView::getYLimAuto(){
	return impl->_propertyValues.yLimAuto;
}
void AxesView::setAcceptMouseEvents(bool acceptMouseEvents) {
	impl->_acceptMouseEvents = acceptMouseEvents;
	acceptMouseEventsChanged();
}
bool AxesView::getAcceptMouseEvents() {
	return impl->_acceptMouseEvents;
}

}

