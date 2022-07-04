#ifndef TAB6DATABASE_H
#define TAB6DATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

namespace Ui {
class Tab6DataBase;
}

class Tab6DataBase : public QWidget
{
    Q_OBJECT

public:
    explicit Tab6DataBase(QWidget *parent = nullptr);
    ~Tab6DataBase();

private:
    Ui::Tab6DataBase *ui;
    QSqlDatabase sqlDb;

private slots:
    void slotTab6RecvData(QString);
    void slotSearchDb();
    void slotDeleteDb();
};

#endif // TAB6DATABASE_H
