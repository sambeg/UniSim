/* Copyright (C) 2009-2010 by Niels Holst [niels.holst@agrsci.dk] and co-authors.
** Copyrights reserved.
** Released under the terms of the GNU General Public License version 3.0 or later.
** See www.gnu.org/copyleft/gpl.html.
*/
#include <qwt_plot_curve.h>
#include <usbase/file_locations.h>
#include <usbase/object_pool.h>
#include <usbase/output_variable.h>
#include <usengine/main_window_interface.h>
#include <usengine/plot_widget.h>
#include "output_plot.h"

namespace UniSim{

QList<QColor> OutputPlot::colors;

OutputPlot::OutputPlot(Identifier name, QObject *parent)
    : Output(name, parent), plotWidget(0)
{
    colors
    << QColor("#FF416E")
    << QColor("#3760D5")
    << QColor("#FFC741")
    << QColor("#34C1E8")
    << QColor("#F7FF41")
    << QColor("#A135D0")
    << QColor("#39DE52");
}

OutputPlot::~OutputPlot() {
    delete plotWidget;
}

void OutputPlot::initialize() {
    Output::initialize();
    setParameter("title", &title, QString(), "description");

    const QList<OutputVariable *> &xs(xVariables()), &ys(yVariables());
    if (ys.size() == 0) {
        QString msg = "Output plot has no y-series: " + objectName();
        throw Exception(msg);
    }
    if (xs.size() == 0) {
        QString msg = "Output plot has no x-series: " + objectName();
        throw Exception(msg);
    }
    else if (xs.size() > 1) {
        QString msg = "Output plot has more than one x-series:";
        for (int i = 0; i < xs.size(); ++ i)
            msg += "\n" + xs.at(i)->longName();
        throw Exception(msg);
    }
}

void OutputPlot::cleanup() {
    createPlotWidget();
    fillPlotWidget();
    showPlotWidget();
}

bool OutputPlot::isEmpty() const {
    return xVariables().isEmpty() || yVariables().isEmpty();
}

void OutputPlot::createPlotWidget() {
    MainWindowInterface *mainWindow =
            objectPool()->find<MainWindowInterface*>("mainWindow");
    Q_ASSERT(mainWindow);

    plotWidget = mainWindow->createPlotWidget(title);
}

void OutputPlot::fillPlotWidget() {
    Q_ASSERT(plotWidget);
    if (isEmpty()) return;

    QList<OutputVariable *> xs, ys;
    xs = xVariables();
    ys = yVariables();
    OutputVariable *x = xs[0];

    QString yAxisTitle = ys.size() == 1 ? ys[0]->label() : QString();
    plotWidget->setXYtitles(x->label(), yAxisTitle);
    plotWidget->showLegend(ys.size() > 1);

    for (int i = 0; i < ys.size(); ++i) {
        OutputVariable *y = ys[i];
        QwtPlotCurve *curve = new QwtPlotCurve(y->label());
        plotWidget->addCurve(curve);

        QColor color = colors[i % colors.size()];
        QPen pen = QPen(color);
        pen.setWidth(4);
        curve->setPen(pen);

        int numPoints = x->data()->size();
        Q_ASSERT(numPoints == y->data()->size());
        curve->setData(x->data()->data(), y->data()->data(), numPoints);
    }
}

void OutputPlot::showPlotWidget() {
    Q_ASSERT(plotWidget);
    plotWidget->show();
}

} //namespace

