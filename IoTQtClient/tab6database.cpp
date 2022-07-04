#include "tab6database.h"
#include "ui_tab6database.h"

Tab6DataBase::Tab6DataBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab6DataBase)
{
    ui->setupUi(this);
    sqlDb = QSqlDatabase::addDatabase("QSQLITE"); //사용하려는 데이터베이스
    sqlDb.setDatabaseName("temp.db"); //파일 이름

    //연결 확인
    if(sqlDb.open())
        qDebug() << "Seccess DB connection";
    else
        qDebug() << "Fail DB connection";

    QString query = "CREATE TABLE temp_db ("
                    "id integer primary key, "
                    "date DATETIME, "
                    "illu VARCHAR(10),"
                    "temp VARCHAR(10),"
                    "humi VARCHAR(10))";
    QSqlQuery qry;
    if(!qry.exec(query)) {}
    else
        qDebug() << "Create table"; //처음 만들 때 한 번만 실행됨

    connect(ui->pPBSearch, SIGNAL(clicked()), this, SLOT(slotSearchDb()));
    connect(ui->pPBDelete, SIGNAL(clicked()), this, SLOT(slotDeleteDb()));
}

Tab6DataBase::~Tab6DataBase()
{
    delete ui;
}

void Tab6DataBase::slotTab6RecvData(QString recvData) {
//    qDebug() << recvData;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString query;
    QSqlQuery qry;

    recvData.replace("[", "@");
    recvData.replace("]", "@");
    QStringList qlist = recvData.split("@");
    QString illu = qlist[3];
    QString temp = qlist[4];
    QString humi = qlist[5];

    query = "insert into temp_db(date, illu, temp, humi) values('" +
            dateTime.toString("yy/MM/dd hh:mm:ss") +
            "', '" +illu+ "', '" +temp+ "', '" +humi+ "')";
    if(qry.exec(query))
        qDebug() << "insert OK";
    else
        qDebug() << qry.lastError().text();
}

void Tab6DataBase::slotSearchDb() {
    QString query;
    QSqlQuery qry;
    QDateTime dateTimeFrom = ui->pDateTimeEditFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");
    QDateTime dateTimeTo = ui->pDateTimeEditTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    int rowCount = 0;
    ui->pTablewidget->clearContents();
    query = "select * from temp_db where date > '" +strFrom+ "' AND date < '" +strTo+ "'";
    if(qry.exec(query)) {
        while(qry.next()) {
            rowCount++;
            ui->pTablewidget->setRowCount(rowCount);
            QTableWidgetItem* id = new QTableWidgetItem();
            QTableWidgetItem* date = new QTableWidgetItem();
            QTableWidgetItem* illu = new QTableWidgetItem();
            QTableWidgetItem* temp = new QTableWidgetItem();
            QTableWidgetItem* humi = new QTableWidgetItem();
            id->setText(qry.value("id").toString());
            date->setText(qry.value("date").toString());
            illu->setText(qry.value("illu").toString());
            temp->setText(qry.value("temp").toString());
            humi->setText(qry.value("humi").toString());
            ui->pTablewidget->setItem(rowCount - 1, 0, id); //처음에 rowCount++를 했기 때문에 0부터 시작해야하므로 1을 빼줌
            ui->pTablewidget->setItem(rowCount - 1, 1, date);
            ui->pTablewidget->setItem(rowCount - 1, 2, illu);
            ui->pTablewidget->setItem(rowCount - 1, 3, temp);
            ui->pTablewidget->setItem(rowCount - 1, 4, humi);
        }
    }
}

void Tab6DataBase::slotDeleteDb() {
    QString query;
    QSqlQuery qry;
    QDateTime dateTimeFrom = ui->pDateTimeEditFrom->dateTime();
    QString strFrom = dateTimeFrom.toString("yy/MM/dd hh:mm:ss");
    QDateTime dateTimeTo = ui->pDateTimeEditTo->dateTime();
    QString strTo = dateTimeTo.toString("yy/MM/dd hh:mm:ss");

    query = "delete from temp_db where date > '" +strFrom+ "' AND date < '" +strTo+ "'";
    if(qry.exec(query)) {}
}
