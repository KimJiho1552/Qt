#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    pSocketClient = new SocketClient(this);
    ui->pPBSendButton->setEnabled(false);
    connect(ui->pPBServerConnect, SIGNAL(clicked(bool)), this, SLOT(slotConnectToServer(bool))); //서버 연결
    connect(ui->pPBSendButton, SIGNAL(clicked()), this, SLOT(slotSocketSendData()));
    connect(pSocketClient, SIGNAL(sigSocketRecv(QString)), this, SLOT(slotSocketRecvUpdate(QString)));
    connect(ui->pPBRecvDataClr, SIGNAL(clicked()), ui->pTERecvData, SLOT(clear())); //수신 삭제
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}

void Tab2SocketClient::slotConnectToServer(bool check) {
    bool bOK;
    if(check) { //서버 연결 누를 때
        pSocketClient->slotConnectToServer(bOK);
        if(bOK) { //서버 연결 버튼이 토글되면
            ui->pPBServerConnect->setText("서버 해제");
            ui->pPBSendButton->setEnabled(true);
        }
    }
    else { //서버 해제 누를 때
        pSocketClient->slotClosedByServer();
        ui->pPBServerConnect->setText("서버 연결");
        ui->pPBSendButton->setEnabled(false);
    }
}

void Tab2SocketClient::slotSocketRecvUpdate(QString strRecvData) {
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
//    qDebug() << strTime;

    strRecvData.chop(1); //끝에 있는 문자 1개 제거 -> \n

    if((strRecvData.indexOf("LAMP") != -1) || (strRecvData.indexOf("GAS") != -1))
        emit sigTab3RecvData(strRecvData);
    else if(strRecvData.indexOf("SENSOR") != -1) {
        emit sigTab4RecvData(strRecvData); //Sensor Value
        emit sigTab5RecvData(strRecvData); //Chart
        emit sigTab6RecvData(strRecvData); //DataBase
    }

    strRecvData = strTime + " " + strRecvData;

    ui->pTERecvData->append(strRecvData); //전송
    ui->pTERecvData->moveCursor(QTextCursor::End); //커서 끝으로 이동
}

void Tab2SocketClient::slotSocketSendData() {
    QString strRecvId;
    QString strSendData;

    strRecvId = ui->pLERecvId->text();
    strSendData = ui->pLESendData->text();

    if(strRecvId.isEmpty())
        strSendData = "[ALLMSG]" + strSendData; //ID 없을 때 모두에게 전송
    else
        strSendData = "[" + strRecvId + "]" + strSendData; //ID 있을 때 특정 인물에게 전송

    pSocketClient->slotSocketSendData(strSendData); //Data 전송

    ui->pLESendData->clear(); //전송 후 메시지 제거
}

void Tab2SocketClient::slotSocketSendData(QString strData) {
    if(ui->pPBServerConnect->isChecked())
        pSocketClient->slotSocketSendData(strData);
    else
        QMessageBox::information(this, "socket", "서버 연결 확인");
}
