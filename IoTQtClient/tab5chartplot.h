#ifndef TAB5CHARTPLOT_H
#define TAB5CHARTPLOT_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QDebug>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Tab5ChartPlot;
}

class Tab5ChartPlot : public QWidget
{
    Q_OBJECT

public:
    explicit Tab5ChartPlot(QWidget *parent = nullptr);
    ~Tab5ChartPlot();

private:
    Ui::Tab5ChartPlot *ui;
    QLineSeries* pIlluLine;
    QLineSeries* pTempLine;
    QLineSeries* pHumiLine;
    QChart* chart;
    QChartView* chartView;
    QDateTimeAxis* axisX; //시간을 x축으로
    QDateTime firstDate;
    QDateTime lastDate;

private slots:
    void charPlotAdd();
    void charPlotClear();
    void slotTab5RecvData(QString);
};

#endif // TAB5CHARTPLOT_H
