#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();

    QString getRole() const;

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonRegister_clicked();

private:
    Ui::Signin *ui;
    QString userRole;
};

#endif