// CvPlotQt - https://github.com/Profactor/cv-plot-qt
// Copyright (c) 2020 by PROFACTOR GmbH - https://www.profactor.at/

#pragma once

#include <CvPlotQt/libdef.h>
#include <CvPlot/core/Axes.h>
#include <QObject>

namespace CvPlotQt {

class CVPLOTQT_LIBRARY_INTERFACE DrawableQuick :public QObject {
	Q_OBJECT;
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
public:
	using QObject::QObject;
    virtual void addTo(CvPlot::Axes &axes) = 0;
    virtual void setName(QString name) = 0;
    virtual QString getName() = 0;
    Q_SIGNAL void nameChanged();
	Q_SIGNAL void contentChanged();
};

}

