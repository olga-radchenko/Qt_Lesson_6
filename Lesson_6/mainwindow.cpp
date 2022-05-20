#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_open_act_triggered()
{
    QFileDialog openFileDialog(this);
    QStringList fileName;

    if (openFileDialog.exec())
    {
        fileName = openFileDialog.selectedFiles();

        QFile file{fileName.first()};
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;

      //  ui->tabWidget->addTab(new QTextEdit(file), "0");
       // ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), key);
    }
}
