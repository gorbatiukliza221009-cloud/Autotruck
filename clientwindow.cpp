#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "signin.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "mainwindow.h"
#include "statisticswindow.h"
#include <QMessageBox>

ClientWindow::ClientWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    setClientMode();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::setClientMode()
{
    currentRole = "client";

    ui->pushButtonViewServices->setText("Переглянути послуги");
    ui->pushButtonDiagnostic->setText("Швидкий запис на діагностику");
}

void ClientWindow::setAdminMode()
{
    currentRole = "admin";

    ui->pushButtonViewServices->setText("Внести редагування");
    ui->pushButtonDiagnostic->setText("Статистика клієнтів");
}

void ClientWindow::on_pushButtonAccount_clicked()
{
    Signin signIn;

    if(signIn.exec() == QDialog::Accepted)
    {
        QString role = signIn.getRole();

        if(role == "admin")
        {
            setAdminMode();

            QMessageBox::information(this, "Адміністратор",
                                     "Ви увійшли як адміністратор");
        }
        else
        {
            setClientMode();

            QMessageBox::information(this, "Клієнт",
                                     "Ви увійшли як клієнт");
        }
    }
}

void ClientWindow::on_pushButtonViewServices_clicked()
{
    if(currentRole == "admin")
    {
        MainWindow *adminWindow = new MainWindow();
        adminWindow->show();
    }
    else
    {
        on_pushButtonServices_clicked();
    }
}

void ClientWindow::on_pushButtonDiagnostic_clicked()
{
        if(currentRole == "admin")
        {
            StatisticsWindow *stats = new StatisticsWindow();
            stats->show();
            return;
        }

        QDialog dialog(this);
        dialog.setWindowTitle("Швидкий запис на діагностику");
        dialog.resize(400, 250);

        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
        QFormLayout *formLayout = new QFormLayout();

        QLineEdit *lineEditName = new QLineEdit();
        QLineEdit *lineEditPhone = new QLineEdit();
        QDateTimeEdit *dateTimeEdit = new QDateTimeEdit();

        dateTimeEdit->setCalendarPopup(true);
        dateTimeEdit->setDateTime(QDateTime::currentDateTime());

        formLayout->addRow("Ім’я:", lineEditName);
        formLayout->addRow("Телефон:", lineEditPhone);
        formLayout->addRow("Дата і час:", dateTimeEdit);

        QPushButton *buttonSave = new QPushButton("Записатися");

        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(buttonSave);

        connect(buttonSave, &QPushButton::clicked, [&]()
                {
                    QString name = lineEditName->text();
                    QString phone = lineEditPhone->text();
                    QString dateTime = dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm");

                    if(name.isEmpty() || phone.isEmpty())
                    {
                        QMessageBox::warning(&dialog, "Помилка", "Заповніть ім’я та номер телефону");
                        return;
                    }

                    QSqlQuery query;
                    query.exec("CREATE TABLE IF NOT EXISTS DiagnosticOrders ("
                               "ID_Order INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "ClientName TEXT NOT NULL, "
                               "Phone TEXT NOT NULL, "
                               "DateTime TEXT NOT NULL)");

                    query.prepare("INSERT INTO DiagnosticOrders (ClientName, Phone, DateTime) "
                                  "VALUES (:name, :phone, :datetime)");

                    query.bindValue(":name", name);
                    query.bindValue(":phone", phone);
                    query.bindValue(":datetime", dateTime);

                    if(query.exec())
                    {
                        QMessageBox::information(&dialog, "Успіх", "Вас записано на діагностику");
                        dialog.accept();
                    }
                    else
                    {
                        QMessageBox::critical(&dialog, "Помилка БД", query.lastError().text());
                    }
                });

        dialog.exec();
    }

void ClientWindow::on_pushButtonServices_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Список послуг");
    dialog.resize(700, 400);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QTableWidget *table = new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Назва", "Категорія", "Ціна", "Тривалість", "Гарантія"});
    table->horizontalHeader()->setStretchLastSection(true);

    QSqlQuery query;
    query.prepare("SELECT ServiceName, Category, Price, Duration, Warranty FROM Services");

    if(!query.exec())
    {
        QMessageBox::critical(this, "Помилка БД", query.lastError().text());
        return;
    }

    int row = 0;

    while(query.next())
    {
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value(2).toString() + " грн"));
        table->setItem(row, 3, new QTableWidgetItem(query.value(3).toString() + " хв"));
        table->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));

        row++;
    }

    layout->addWidget(table);
    dialog.exec();
}

void ClientWindow::on_pushButtonContacts_clicked()
{
    QMessageBox::information(this,
                             "Контакти AutoTrucks",
                             "AutoTrucks\n\n"
                             "Телефон: +380 XX XXX XX XX\n"
                             "Email: autotrucks.office@gmail.com\n"
                             "Адреса: м. Чернівці\n\n"
                             "Графік роботи:\n"
                             "Пн–Пт: 09:00–18:00\n"
                             "Сб-Нд: вихідний");
}
void ClientWindow::on_pushButtonOrders_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Мої замовлення");
    dialog.resize(600, 350);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QTableWidget *table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"ID", "Ім’я", "Телефон", "Дата і час"});
    table->horizontalHeader()->setStretchLastSection(true);

    QSqlQuery query;
    query.prepare("SELECT ID_Order, ClientName, Phone, DateTime FROM DiagnosticOrders");

    if(!query.exec())
    {
        QMessageBox::warning(this, "Замовлення", "Поки що немає створених замовлень");
        return;
    }

    int row = 0;

    while(query.next())
    {
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));

        row++;
    }

    layout->addWidget(table);
    dialog.exec();
}

