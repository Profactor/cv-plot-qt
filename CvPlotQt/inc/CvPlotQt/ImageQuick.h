// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#pragma once

#include <CvPlotQt/libdef.h>
#include <CvPlotQt/DrawableQuick.h>
#include <CvPlot/Internal/Pimpl.h>
#include <CvPlot/Internal/no_warning.h>
#include <QRectF>
#include <QVariant>

namespace CvPlotQt {

class CVPLOTQT_LIBRARY_INTERFACE ImageQuick :public DrawableQuick {
	Q_OBJECT;
	Q_PROPERTY(QVariant mat READ getMat WRITE setMat NOTIFY matChanged);
	Q_PROPERTY(QRectF position READ getPosition WRITE setPosition NOTIFY positionChanged);

public:
	explicit ImageQuick(QObject *parent=nullptr);
	~ImageQuick();

	void setMat(QVariant mat);
	QVariant getMat();
	void setPosition(QRectF position);
	QRectF getPosition();

	Q_SIGNAL void matChanged();
	Q_SIGNAL void positionChanged();

	void addTo(CvPlot::Axes &axes)override;
    void setName(QString name)override;
    QString getName()override;
private:
	class Impl;
	CVPLOT_NO_WARNING_DLL_INTERFACE(CvPlot::Internal::Pimpl<Impl>, impl);
};

}

