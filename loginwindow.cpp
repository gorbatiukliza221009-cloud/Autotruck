#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "signin.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirm->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButtonRegister_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    QString confirm = ui->lineEditConfirm->text();

    if(login.isEmpty() || password.isEmpty() || confirm.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Заповніть усі поля");
        return;
    }

    if(password != confirm)
    {
        QMessageBox::warning(this, "Помилка", "Паролі не збігаються");
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID_User FROM Users WHERE Login = :login");
    checkQuery.bindValue(":login", login);

    if(!checkQuery.exec())
    {
        QMessageBox::critical(this, "Помилка БД", checkQuery.lastError().text());
        return;
    }

    if(checkQuery.next())
    {
        QMessageBox::warning(this, "Помилка", "Користувач із таким логіном уже існує");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Users (Login, Password, Role) "
                  "VALUES (:login, :password, 'client')");

    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if(query.exec())
    {
        QMessageBox::information(this, "Успіх", "Реєстрацію виконано. Тепер увійдіть в акаунт.");
        this->close();

        Signin signin;
        signin.exec();
    }
    else
    {
        QMessageBox::critical(this, "Помилка", query.lastError().text());
    }
}

void LoginWindow::on_pushButtonSignin_clicked()
{
    this->close();

    Signin signin;
    signin.exec();
}