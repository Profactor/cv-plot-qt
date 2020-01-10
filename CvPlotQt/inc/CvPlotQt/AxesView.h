// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#pragma once

#include <CvPlotQt/libdef.h>
#include <CvPlotQt/DrawableQuick.h>
#include <CvPlotQt/SeriesQuick.h>
#include <CvPlotQt/ImageQuick.h>
#include <QQuickPaintedItem>
#include <CvPlot/internal/Pimpl.h>
#include <CvPlot/internal/no_warning.h>
#include <CvPlot/gui/MouseEvent.h>

namespace CvPlotQt {

class CVPLOTQT_LIBRARY_INTERFACE AxesView : public QQuickPaintedItem {
	Q_OBJECT;
	Q_PROPERTY(bool xLog READ getXLog WRITE setXLog NOTIFY xLogChanged);
	Q_PROPERTY(bool yLog READ getYLog WRITE setYLog NOTIFY yLogChanged);
	Q_PROPERTY(bool yReverse READ getYReverse WRITE setYReverse NOTIFY yReverseChanged);
	Q_PROPERTY(bool fixedAspectRatio READ getFixedAspectRatio WRITE setFixedAspectRatio NOTIFY fixedAspectRatioChanged);
	Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged);
	Q_PROPERTY(QString xLabel READ getXLabel WRITE setXLabel NOTIFY xLabelChanged);
	Q_PROPERTY(QString yLabel READ getYLabel WRITE setYLabel NOTIFY yLabelChanged);
	Q_PROPERTY(bool horizontalGridEnabled READ getHorizontalGridEnabled WRITE setHorizontalGridEnabled NOTIFY horizontalGridEnabledChanged);
	Q_PROPERTY(bool verticalGridEnabled READ getVerticalGridEnabled WRITE setVerticalGridEnabled NOTIFY verticalGridEnabledChanged);
	Q_PROPERTY(bool xTight READ getXTight WRITE setXTight NOTIFY xTightChanged);
	Q_PROPERTY(bool yTight READ getYTight WRITE setYTight NOTIFY yTightChanged);
	Q_PROPERTY(bool tightBox READ getTightBox WRITE setTightBox NOTIFY tightBoxChanged);
	Q_PROPERTY(double xLimLow READ getXLimLow WRITE setXLimLow NOTIFY xLimLowChanged);
	Q_PROPERTY(double xLimHigh READ getXLimHigh WRITE setXLimHigh NOTIFY xLimHighChanged);
	Q_PROPERTY(double yLimLow READ getYLimLow WRITE setYLimLow NOTIFY yLimLowChanged);
	Q_PROPERTY(double yLimHigh READ getYLimHigh WRITE setYLimHigh NOTIFY yLimHighChanged);
	Q_PROPERTY(bool xLimAuto READ getXLimAuto WRITE setXLimAuto NOTIFY xLimAutoChanged);
	Q_PROPERTY(bool yLimAuto READ getYLimAuto WRITE setYLimAuto NOTIFY yLimAutoChanged);
	Q_PROPERTY(bool acceptMouseEvents READ getAcceptMouseEvents WRITE setAcceptMouseEvents NOTIFY acceptMouseEventsChanged);
public:
	explicit AxesView(QQuickItem* parent = 0);
	~AxesView();

	CvPlot::Axes &getAxes();
	void updateProperties(); //call after modifying underlying Axes

	Q_INVOKABLE CvPlotQt::SeriesQuick* createSeries();
	Q_INVOKABLE CvPlotQt::ImageQuick* createImage();

	void setXLog(bool log);
	bool getXLog();
	void setYLog(bool log);
	bool getYLog();
	void setYReverse(bool reverse);
	bool getYReverse();
	void setFixedAspectRatio(bool fixed);
	bool getFixedAspectRatio();
	void setTitle(QString title);
	QString getTitle();
	void setXLabel(QString xLabel);
	QString getXLabel();
	void setYLabel(QString xLabel);
	QString getYLabel();
	bool getHorizontalGridEnabled();
	void setHorizontalGridEnabled(bool enabled);
	bool getVerticalGridEnabled();
	void setVerticalGridEnabled(bool enabled);
	void setXTight(bool tight);
	bool getXTight();
	void setYTight(bool tight);
	bool getYTight();
	void setTightBox(bool tight);
	bool getTightBox();
	void setXLimLow(double xLimLow);
	double getXLimLow();
	void setXLimHigh(double xLimHigh);
	double getXLimHigh();
	void setYLimLow(double yLimLow);
	double getYLimLow();
	void setYLimHigh(double yLimHigh);
	double getYLimHigh();
	void setXLimAuto(bool xLimAuto);
	bool getXLimAuto();
	void setYLimAuto(bool yLimAuto);
	bool getYLimAuto();
	void setAcceptMouseEvents(bool acceptMouseEvents);
	bool getAcceptMouseEvents();
	Q_SIGNAL void xLogChanged();
	Q_SIGNAL void yLogChanged();
	Q_SIGNAL void yReverseChanged();
	Q_SIGNAL void fixedAspectRatioChanged();
	Q_SIGNAL void titleChanged();
	Q_SIGNAL void xLabelChanged();
	Q_SIGNAL void yLabelChanged();
	Q_SIGNAL void horizontalGridEnabledChanged();
	Q_SIGNAL void verticalGridEnabledChanged();
	Q_SIGNAL void contentChanged();
	Q_SIGNAL void mouseHandled();
	Q_SIGNAL void xTightChanged();
	Q_SIGNAL void yTightChanged();
	Q_SIGNAL void tightBoxChanged();
	Q_SIGNAL void xLimLowChanged();
	Q_SIGNAL void xLimHighChanged();
	Q_SIGNAL void yLimLowChanged();
	Q_SIGNAL void yLimHighChanged();
	Q_SIGNAL void xLimAutoChanged();
	Q_SIGNAL void yLimAutoChanged();
	Q_SIGNAL void acceptMouseEventsChanged();

	void paint(QPainter * painter)override;
	void componentComplete() override;
	void childEvent(QChildEvent *event)override;

	Q_INVOKABLE QPointF unproject(QPointF point);

protected:
	//mouse overrides
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event)override;
	void hoverMoveEvent(QHoverEvent *event)override;

	virtual bool mouseEvent(const CvPlot::MouseEvent &mouseEvent);

private:
	class Impl;
	CVPLOT_NO_WARNING_DLL_INTERFACE(CvPlot::Internal::Pimpl<Impl>, impl);
};

}

