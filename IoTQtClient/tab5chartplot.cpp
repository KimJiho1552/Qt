#include "tab5chartplot.h"
#include "ui_tab5chartplot.h"

Tab5ChartPlot::Tab5ChartPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab5ChartPlot)
{
    ui->setupUi(this);

    //조도 그래프------------------------------------------
    pIlluLine = new QLineSeries(this);
    pIlluLine->setName("조도");

    QPen penIllu;
    penIllu.setWidth(2);
    penIllu.setBrush(Qt::red);
    penIllu.setCapStyle(Qt::FlatCap);
    penIllu.setJoinStyle(Qt::MiterJoin);
    pIlluLine->setPen(penIllu);
    //---------------------------------------------------

    //온도 그래프------------------------------------------
    pTempLine = new QLineSeries(this);
    pTempLine->setName("온도");

    QPen penTemp;
    penTemp.setWidth(2);
    penTemp.setBrush(Qt::green);
    penTemp.setCapStyle(Qt::FlatCap);
    penTemp.setJoinStyle(Qt::MiterJoin);
    pTempLine->setPen(penTemp);
    //---------------------------------------------------

    //습도 그래프------------------------------------------
    pHumiLine = new QLineSeries(this);
    pHumiLine->setName("습도");

    QPen penHumi;
    penHumi.setWidth(2);
    penHumi.setBrush(Qt::blue);
    penHumi.setCapStyle(Qt::FlatCap);
    penHumi.setJoinStyle(Qt::MiterJoin);
    pHumiLine->setPen(penHumi);
    //---------------------------------------------------

    //차트 그리기------------------------------------------
    chart = new QChart();
    chart->addSeries(pIlluLine);
    chart->addSeries(pTempLine);
    chart->addSeries(pHumiLine);
    chart->createDefaultAxes();
//    chart->axes(Qt::Horizontal).first()->setRange(0, 20); //x축
    chart->axes(Qt::Vertical).first()->setRange(0, 100);  //y축 0~100

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->pChartHLayout->layout()->addWidget(chartView);
    //----------------------------------------------------

    //시간 가져오기-----------------------------------------
    axisX = new QDateTimeAxis;
    axisX->setFormat("h:mm");

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDate.setDate(date); //날짜 초기화
    firstDate.setTime(time); //시간 초기화

    chartView->chart()->setAxisX(axisX, pIlluLine); //그래프
    chartView->chart()->setAxisX(axisX, pTempLine);
    chartView->chart()->setAxisX(axisX, pHumiLine);

    QTime tempTime = time.addSecs(600); //10분
    lastDate.setDate(date);
    lastDate.setTime(tempTime);

    axisX->setRange(firstDate, lastDate); //범위를 firstDate와 lastDate로 설정
    //----------------------------------------------------

    connect(ui->pPBClearButton, SIGNAL(clicked()), this, SLOT(charPlotClear())); //clear
    connect(ui->pPBAddButton, SIGNAL(clicked()), this, SLOT(charPlotAdd()));     //add
}

Tab5ChartPlot::~Tab5ChartPlot()
{
    delete ui;
}

void Tab5ChartPlot::charPlotClear() {
    pIlluLine->clear();
    pTempLine->clear();
    pHumiLine->clear();
}

void Tab5ChartPlot::charPlotAdd() {
    pIlluLine->append(ui->pLExPosition->text().toDouble(), ui->pLEyPosition->text().toDouble());

    ui->pLExPosition->clear();
    ui->pLEyPosition->clear();
}

void Tab5ChartPlot::slotTab5RecvData(QString recvData) {
//    qDebug() << recvData;
    QDate date = QDate::currentDate(); //날짜 가져오기
    QTime time = QTime::currentTime(); //시간 가져오기

    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    recvData.replace("[", "@"); //[ -> @
    recvData.replace("]", "@"); //] -> @
    QStringList qlist = recvData.split("@");

    if(qlist[2] == "SENSOR") {
        pIlluLine->append(xValue.toMSecsSinceEpoch(), qlist[3].toDouble()); //toMSecsSinceEpoch() : 초를 분으로 변환
        pTempLine->append(xValue.toMSecsSinceEpoch(), qlist[4].toDouble());
        pHumiLine->append(xValue.toMSecsSinceEpoch(), qlist[5].toDouble());
    }
}
