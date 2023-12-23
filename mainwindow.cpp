#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mars.db");
    qInfo() <<db.open();
    if(db.open())
    {
        ui->label->setText("conected: sukces");
    }
    else
        ui->label->setText("conected: fail");
    //db.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->i++;
    qInfo() <<db.open();
    if(db.open()){
        QString name;
        QSqlQuery query;
        query.prepare("Select nazwa from karta where id = 1");
        //query.bindValue(":n", i);
        if(query.exec()) //ciągle zwraca false
        {
            while(query.next())
            {
                name = query.value(0).toString();
                ui->label->setText(QString::number(i)+" "+name);
            }
        }
        else
        {
            ui->label->setText(query.lastError().text());
        }
    }
    //db.commit();
    //db.close();
}

