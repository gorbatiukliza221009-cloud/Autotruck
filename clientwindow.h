#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_pushButtonAccount_clicked();
private slots:
    void on_pushButtonServices_clicked();
    void on_pushButtonViewServices_clicked();
    void on_pushButtonOrders_clicked();
    void on_pushButtonContacts_clicked();
    void on_pushButtonDiagnostic_clicked();

private:
    Ui::ClientWindow *ui;
    QString currentRole;

    void setClientMode();
    void setAdminMode();
};

#endif