#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/lizag/OneDrive/Desktop/AutoTrucks.db");

    if(!db.open())
    {
        QMessageBox::critical(this, "Помилка БД", db.lastError().text());
    }

    model = new QSqlTableModel(this);
    ui->tableView->setModel(model);

    qDebug() << "DB path:" << db.databaseName();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_5->text().toInt();
    QString name = ui->lineEdit_6->text();
    double price = ui->lineEdit_7->text().toDouble();
    QString category = ui->comboBox->currentText();
    QString warranty = ui->lineEdit_8->text();
    int duration = ui->lineEdit_9->text().toInt();

    name.replace("'", "''");
    category.replace("'", "''");
    warranty.replace("'", "''");

    QSqlQuery query;

    QString sql = QString(
                      "INSERT INTO Services "
                      "(ID_Service, ServiceName, Category, Price, Duration, Warranty) "
                      "VALUES (%1, '%2', '%3', %4, %5, '%6')"
                      )
                      .arg(id)
                      .arg(name)
                      .arg(category)
                      .arg(price)
                      .arg(duration)
                      .arg(warranty);

    if(query.exec(sql))
    {
        QMessageBox::information(this, "Успіх", "Послугу додано");

        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
    }
    else
    {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    int id = ui->lineEdit_5->text().toInt();
    QString name = ui->lineEdit_6->text();
    double price = ui->lineEdit_7->text().toDouble();
    QString category = ui->comboBox->currentText();
    QString warranty = ui->lineEdit_8->text();
    int duration = ui->lineEdit_9->text().toInt();

    QSqlQuery query;

    QString sql = QString(
                      "UPDATE Services SET "
                      "ServiceName='%1', "
                      "Category='%2', "
                      "Price=%3, "
                      "Duration=%4, "
                      "Warranty='%5' "
                      "WHERE ID_Service=%6"
                      )
                      .arg(name)
                      .arg(category)
                      .arg(price)
                      .arg(duration)
                      .arg(warranty)
                      .arg(id);

    if(query.exec(sql))
    {
        QMessageBox::information(this,
                                 "Успіх",
                                 "Послугу відредаговано");
    }
    else
    {
        QMessageBox::critical(this,
                              "Помилка",
                              query.lastError().text());
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_5->text().toInt();

    QSqlQuery query;

    QString sql = QString(
                      "DELETE FROM Services WHERE ID_Service=%1"
                      ).arg(id);

    if(query.exec(sql))
    {
        QMessageBox::information(this, "Успіх", "Послугу видалено");

        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
    }
    else
    {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    model->setTable("Services");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "Код");
    model->setHeaderData(1, Qt::Horizontal, "Назва");
    model->setHeaderData(2, Qt::Horizontal, "Категорія");
    model->setHeaderData(3, Qt::Horizontal, "Ціна");
    model->setHeaderData(4, Qt::Horizontal, "Тривалість");
    model->setHeaderData(5, Qt::Horizontal, "Гарантія");

    ui->tableView->resizeColumnsToContents();
}