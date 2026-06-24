#include "signin.h"
#include "ui_signin.h"
#include "loginwindow.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLineEdit>

Signin::Signin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Signin)
{
    ui->setupUi(this);

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

Signin::~Signin()
{
    delete ui;
}

QString Signin::getRole() const
{
    return userRole;
}

void Signin::on_pushButtonLogin_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();

    if(login.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Введіть логін і пароль");
        return;
    }

    QSqlQuery checkUser;
    checkUser.prepare("SELECT Password, Role FROM Users WHERE Login = :login");
    checkUser.bindValue(":login", login);

    if(!checkUser.exec())
    {
        QMessageBox::critical(this, "Помилка БД", checkUser.lastError().text());
        return;
    }

    if(!checkUser.next())
    {
        QMessageBox::warning(this, "Акаунт не знайдено",
                             "Такого акаунта немає. Спочатку потрібно зареєструватися.");
        return;
    }

    QString dbPassword = checkUser.value(0).toString();
    QString role = checkUser.value(1).toString();

    if(password != dbPassword)
    {
        QMessageBox::warning(this, "Помилка", "Неправильний пароль");
        return;
    }

    userRole = role;

    QMessageBox::information(this, "Успіх", "Авторизацію виконано");
    accept();
}

void Signin::on_pushButtonExit_clicked()
{
    close();
}

void Signin::on_pushButtonRegister_clicked()
{
    this->close();

    LoginWindow registerWindow;
    registerWindow.exec();
}