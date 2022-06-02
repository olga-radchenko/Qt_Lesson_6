#include "file_viewer.h"
#include "ui_file_viewer.h"
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

FileViewer::FileViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileViewer)
{
    fsModel = new QFileSystemModel (this);
    ui->setupUi(this);

    // model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    // fsModel->setNameFilters(QStringList("*.txt"));

    fsModel->setRootPath(QDir::homePath());
    ui->dirLineEdit->setText(QDir::homePath());
    ui->treeView->setModel(fsModel);
    ui->treeView->setRootIndex(fsModel->index(QDir::homePath()));
    ui->treeView->setCurrentIndex(fsModel->index(QDir::homePath()));
    ui->treeView->setObjectName(QString::fromUtf8("treeView"));
    ui->treeView->setGeometry(QRect(20, 40, 571, 251));
    ui->treeView->show();

    connect(ui->treeView,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTreeViewDoubleClicked(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)), this, SLOT(onTreeViewClicked(QModelIndex)));
}

FileViewer::~FileViewer()
{
    delete ui;
}

void FileViewer::onTreeViewClicked(const QModelIndex &index)
{
    ui->dirLineEdit->setText(fsModel->filePath(index));
}

void FileViewer::onTreeViewDoubleClicked(const QModelIndex &index)
{
    if(!fsModel->filePath(index).contains(".")) showFolder();
    else QDesktopServices::openUrl(QUrl::fromLocalFile(ui->dirLineEdit->text()));
}

void FileViewer::showFolder()
{
    fsModel->setRootPath(ui->dirLineEdit->text());
    ui->treeView->setRootIndex(fsModel->index(ui->dirLineEdit->text()));
    ui->treeView->setModel(fsModel);
}

void FileViewer::on_openBtn_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->dirLineEdit->text()));
}

void FileViewer::on_dirLineEdit_editingFinished()
{
    showFolder();
}

void FileViewer::on_upBtn_clicked()
{
    QDir currDir{ui->dirLineEdit->text()};
    currDir.cdUp();
    ui->dirLineEdit->setText(currDir.path());
    fsModel->setRootPath(ui->dirLineEdit->text());
    ui->treeView->setRootIndex(fsModel->index(ui->dirLineEdit->text()));
    ui->treeView->setModel(fsModel);
}

void FileViewer::on_backBtn_clicked()
{
    this->close();
}

void FileViewer::switchLanguage()
{
    this->ui->retranslateUi(this);
}
