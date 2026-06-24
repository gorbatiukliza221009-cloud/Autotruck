#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);
    ~StatisticsWindow();

private:
    Ui::StatisticsWindow *ui;

    void showClientStatistics();
    void showCategoryStats();
};

#endif