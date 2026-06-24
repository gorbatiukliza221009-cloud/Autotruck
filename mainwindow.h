#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();      // Додати
    void on_pushButton_2_clicked();    // Редагувати
    void on_pushButton_3_clicked();    // Видалити
    void on_pushButton_4_clicked();    // Відобразити

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H