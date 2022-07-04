#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(1); //시작 화면, 없으면 마지막 화면 나옴

    //Tab2 화면
    pTab2SocketClient = new Tab2SocketClient(ui->pTab2);
    ui->pTab2->setLayout(pTab2SocketClient->layout()); //tab2를 누르면 tab2socketclient.ui가 실행

    //Tab3 화면
    pTab3ControlPannel = new Tab3ControlPannel(ui->pTab3);
    ui->pTab3->setLayout(pTab3ControlPannel->layout());

    //Tab4 화면
    pTab4SensorDisplay = new Tab4SensorDisplay(ui->pTab4);
    ui->pTab4->setLayout(pTab4SensorDisplay->layout());

    //Tab5 화면
    pTab5ChartPlot = new Tab5ChartPlot(ui->pTab5);
    ui->pTab5->setLayout(pTab5ChartPlot->layout());

    //Tab6 화면
    pTab6DataBase = new Tab6DataBase(ui->pTab6);
    ui->pTab6->setLayout(pTab6DataBase->layout());

    connect(pTab2SocketClient, SIGNAL(sigTab3RecvData(QString)), pTab3ControlPannel, SLOT(slotTab3RecvData(QString))); //문자열 분리
    connect(pTab2SocketClient, SIGNAL(sigTab4RecvData(QString)), pTab4SensorDisplay, SLOT(slotTab4RecvData(QString))); //sensor value
    connect(pTab2SocketClient, SIGNAL(sigTab5RecvData(QString)), pTab5ChartPlot, SLOT(slotTab5RecvData(QString)));     //chart
    connect(pTab2SocketClient, SIGNAL(sigTab6RecvData(QString)), pTab6DataBase, SLOT(slotTab6RecvData(QString)));     //DataBase
    connect(pTab3ControlPannel, SIGNAL(sigSocketSendData(QString)), pTab2SocketClient, SLOT(slotSocketSendData(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}
