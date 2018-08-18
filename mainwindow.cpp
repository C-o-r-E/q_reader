#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QtDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //TODO: decouple this


    //lets find some tty devices
    QDir devices("/dev", "tty.usb*", QDir::Name,QDir::System);
    //QStringList filters;
    //filters << "tty*";
    //devices.setNameFilters(filters);

    QStringList entries = devices.entryList();
    ui->comboBox->addItems(entries);

    QString temp = "";
    temp.sprintf("found %d devs...", entries.count());
    ui->plainTextEdit->appendPlainText(temp);
    ui->plainTextEdit->appendPlainText("The following devices were found:");
    for(int i=0; i<entries.count(); i++)
    {
        ui->plainTextEdit->appendPlainText(entries.at(i));
    }


    // Initialize libnfc and set the nfc_context
    nfc_init(&context);
    if (context == NULL)
    {
        ui->statusBar->showMessage("Unable to init libnfc (malloc)");
        //return 1;
    }
    else
    {
        // Display libnfc version
        QString n_ver = "Using libnfc version: ";
        n_ver.append(nfc_version());
        ui->statusBar->showMessage(n_ver);
        ui->connectButton->setEnabled(true);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_released()
{
    QString n_dev = "";
    QString n_conf = "";

    if(ui->comboBox->currentIndex() >= 0)
    {
        n_dev = ui->comboBox->itemText(ui->comboBox->currentIndex());
        n_conf.sprintf("pn532_uart:/dev/%s", n_dev.toStdString().c_str());
        qDebug() << "The conf string: " << n_conf;


    }
    else
    {
        return;
    }


    //nfc_connstring config = n_conf.toStdString().c_str();
    //nfc_connstring config = "pn532_uart:/dev/tty.usbserial-A1012X05";

    pnd = nfc_open(context, n_conf.toStdString().c_str());

    if (pnd == NULL)
    {
        ui->plainTextEdit->appendPlainText("Unable to open NFC device.");
        return;
    }
    // Set opened NFC device to initiator mode
    if (nfc_initiator_init(pnd) < 0)
    {
        ui->plainTextEdit->appendPlainText(nfc_strerror(pnd));
        //nfc_perror(pnd, "nfc_initiator_init");
        return;
    }

    QString st_info = "";
    st_info.sprintf("NFC reader: %s opened\n", nfc_device_get_name(pnd));
    ui->plainTextEdit->appendPlainText(st_info);

    ui->readButton->setEnabled(true);
    ui->connectButton->setEnabled(false);

    return;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(pnd != NULL)
    {
        qDebug() << "cleanup: closing nfc device at exit...";
        // Close NFC device
        nfc_close(pnd);
    }

    if(context != NULL)
    {
        qDebug() << "cleanup: closing nfc context at exit...";
        // Release the context
        nfc_exit(context);
    }

    event->accept();
    return;
}

void MainWindow::on_readButton_released()
{

    const nfc_modulation nmMifare = { NMT_ISO14443A, NBR_106 };

    QString st_info = "";

    if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0)
    {
        st_info.sprintf("Got ID (%lu bytes):", nt.nti.nai.szUidLen);
        ui->plainTextEdit->appendPlainText(st_info);

        st_info.clear();
        for(size_t i=0; i<nt.nti.nai.szUidLen; i++)
        {
            QString stmp = "";
            stmp.sprintf("%02X", nt.nti.nai.abtUid[i]);
            st_info.append(stmp);
        }
        ui->plainTextEdit->appendPlainText(st_info);


        QString markup = "";
        markup.sprintf("http://morg.123core.net/members/cards/check/%s/",
                       st_info.toStdString().c_str());

        QUrl link(markup);
        QDesktopServices::openUrl(link);


    }
    else
    {
        ui->plainTextEdit->appendPlainText(nfc_strerror(pnd));
        ui->plainTextEdit->appendPlainText("Please make sure the device is connected and restart the program");
        ui->connectButton->setEnabled(false);
    }

}
