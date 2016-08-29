#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <nfc/nfc.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void on_connectButton_released();

   void on_readButton_released();

private:
   void closeEvent(QCloseEvent *event);

    Ui::MainWindow *ui;

    //TODO Move this
    nfc_device *pnd;
    nfc_target nt;

    // Allocate only a pointer to nfc_context
    nfc_context *context;
};

#endif // MAINWINDOW_H
