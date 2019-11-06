#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QDialog>

namespace Ui {
class CommandWindow;
}

class CommandWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CommandWindow(QWidget *parent = 0);
    ~CommandWindow();
    bool return_ok;
    double t, x;

private slots:
    void on_cmdOk_clicked();

    void on_cmdCancel_clicked();

private:
    Ui::CommandWindow *ui;
};

#endif // COMMANDWINDOW_H
