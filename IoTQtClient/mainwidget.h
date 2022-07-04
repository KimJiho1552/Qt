#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab2socketclient.h"
#include "tab3controlpannel.h"
#include "tab4sensordisplay.h"
#include "tab5chartplot.h"
#include "tab6database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Tab2SocketClient* pTab2SocketClient;
    Tab3ControlPannel* pTab3ControlPannel;
    Tab4SensorDisplay* pTab4SensorDisplay;
    Tab5ChartPlot* pTab5ChartPlot;
    Tab6DataBase* pTab6DataBase;
};
#endif // MAINWIDGET_H
