#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <satellite/wheel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Wheel* wheel = new Wheel(0,0,0,0);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_applyWheelBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
