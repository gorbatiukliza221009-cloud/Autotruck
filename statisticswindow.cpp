#include "statisticswindow.h"
#include "ui_statisticswindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

StatisticsWindow::StatisticsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);

    showClientStatistics();
    showCategoryStats();
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::showClientStatistics()
{
    QString text;
    QSqlQuery query;

    query.exec("SELECT COUNT(*) FROM Clients");
    if(query.next())
        text += "Кількість клієнтів: " + query.value(0).toString() + "\n";

    query.exec("SELECT COUNT(*) FROM Orders");
    if(query.next())
        text += "Кількість замовлень: " + query.value(0).toString() + "\n";

    query.exec("SELECT COUNT(*) FROM Services");
    if(query.next())
        text += "Кількість послуг: " + query.value(0).toString() + "\n";

    ui->textEditStats->setText(text);
}

void StatisticsWindow::showCategoryStats()
{
    QSqlQuery totalQuery;
    totalQuery.exec("SELECT COUNT(*) FROM Services");

    int total = 0;
    if(totalQuery.next())
        total = totalQuery.value(0).toInt();

    ui->tableWidgetCategory->setColumnCount(4);
    ui->tableWidgetCategory->setHorizontalHeaderLabels(
        QStringList() << "Категорія" << "Кількість" << "Відсоток" << "Діаграма"
        );

    QSqlQuery query;
    query.prepare("SELECT Category, COUNT(*) FROM Services GROUP BY Category");

    if(!query.exec())
    {
        QMessageBox::critical(this, "Помилка БД", query.lastError().text());
        return;
    }

    int row = 0;

    while(query.next())
    {
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();

        double percent = 0;
        if(total > 0)
            percent = count * 100.0 / total;

        int blocks = percent / 5;
        QString bar;
        for(int i = 0; i < blocks; i++)
            bar += "█";

        ui->tableWidgetCategory->insertRow(row);
        ui->tableWidgetCategory->setItem(row, 0, new QTableWidgetItem(category));
        ui->tableWidgetCategory->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
        ui->tableWidgetCategory->setItem(row, 2, new QTableWidgetItem(QString::number(percent, 'f', 1) + "%"));
        ui->tableWidgetCategory->setItem(row, 3, new QTableWidgetItem(bar));

        row++;
    }

    ui->tableWidgetCategory->resizeColumnsToContents();
}