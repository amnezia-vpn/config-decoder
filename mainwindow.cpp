#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString data = ui->plainTextEdit->toPlainText();
    data.replace("vpn://", "");
    QByteArray ba = QByteArray::fromBase64(data.toUtf8(), QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);

    QByteArray ba_uncompressed = qUncompress(ba);
    if (!ba_uncompressed.isEmpty()) {
        ba = ba_uncompressed;
    }

    ui->plainTextEdit_2->blockSignals(true);
    ui->plainTextEdit_2->setPlainText(QString(ba));
    ui->plainTextEdit_2->blockSignals(false);
}


void MainWindow::on_plainTextEdit_2_textChanged()
{
    QString data = ui->plainTextEdit_2->toPlainText();

    QByteArray compressedConfig = qCompress(data.toUtf8(), 8);
    QString s = QString("vpn://%1")
                   .arg(QString(compressedConfig.toBase64(QByteArray::Base64UrlEncoding
                                                          | QByteArray::OmitTrailingEquals)));

    ui->plainTextEdit->blockSignals(true);
    ui->plainTextEdit->setPlainText(s);
    ui->plainTextEdit->blockSignals(false);
}

