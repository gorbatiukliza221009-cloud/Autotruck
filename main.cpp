#include "clientwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/lizag/OneDrive/Desktop/AutoTrucks.db");

    if(!db.open())
    {
        QMessageBox::critical(nullptr, "Помилка БД", db.lastError().text());
        return 1;
    }

    ClientWindow w;
    w.show();

    return a.exec();
}