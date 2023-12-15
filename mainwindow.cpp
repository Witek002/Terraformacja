#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationFilePath()+"mars.db");
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
    //db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName(QCoreApplication::applicationFilePath()+"mars.db");
    qInfo() <<db.open();
    if(db.open()){
        db.transaction();
        QSqlQuery select(db);
        QString name;
        //select.prepare("Select nazwa from karta where id = (:n)");
        //select.bindValue(":n",i);
        if(select.exec("Select nazwa from karta where id ="+QString::number(i)))
        {
            if(select.next())
            {
                name = select.value(0).toString();
                ui->label->setText(QString::number(i)+" "+name);
            }
        }
        else
        {
            ui->label->setText(select.lastError().text());
        }
    }
    db.commit();
    //db.close();
}

