#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chartarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_SchedulerComboBox_currentIndexChanged(int index);

    void on_InesrtButton_clicked();

    void on_SubmitButton_clicked();

    void on_RemoveButton_clicked();

    void on_LiveCheckBox_clicked(bool checked);

    void on_LiveCheckBox_clicked();

    void on_LiveCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ChartArea *Chart;
    unsigned int currentProcessID = 1;
    std::vector<process> processes;
};
#endif // MAINWINDOW_H
