// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#pragma once

#include <CvPlotQt/libdef.h>
#include <CvPlotQt/DrawableQuick.h>
#include <CvPlot/Internal/Pimpl.h>
#include <CvPlot/Internal/no_warning.h>
#include <QColor>
#include <QVariantList>

namespace CvPlotQt {

class CVPLOTQT_LIBRARY_INTERFACE SeriesQuick :public DrawableQuick {
	Q_OBJECT;
	Q_PROPERTY(QVariantList xData READ getXData WRITE setXData NOTIFY xDataChanged);
	Q_PROPERTY(QVariantList yData READ getYData WRITE setYData NOTIFY yDataChanged);
	Q_PROPERTY(QString lineType READ getLineType WRITE setLineType NOTIFY lineTypeChanged);
	Q_PROPERTY(QString markerType READ getMarkerType WRITE setMarkerType NOTIFY markerTypeChanged);
	Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged);
	Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged);

public:
	explicit SeriesQuick(QObject *parent=nullptr);
	~SeriesQuick();

	void setXData(QVariantList xData);
	QVariantList getXData();
	void setYData(QVariantList yData);
	QVariantList getYData();
	void setLineType(QString lineType);
	QString getLineType();
	void setMarkerType(QString markerType);
	QString getMarkerType();	
	void setLineWidth(int lineWidth);
	int getLineWidth();
	void setColor(QColor color);
	QColor getColor();
    
    Q_SIGNAL void xDataChanged();
	Q_SIGNAL void yDataChanged();
	Q_SIGNAL void lineTypeChanged();
	Q_SIGNAL void markerTypeChanged();
	Q_SIGNAL void lineWidthChanged();
	Q_SIGNAL void colorChanged();

	void addTo(CvPlot::Axes &axes)override;
    void setName(QString name)override;
    QString getName()override;
private:
	class Impl;
	CVPLOT_NO_WARNING_DLL_INTERFACE(CvPlot::Internal::Pimpl<Impl>, impl);
};

}

