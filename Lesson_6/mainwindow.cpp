#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_dir.cdUp();
    m_dir.cd("Lesson_6");
    m_translator = new QTranslator();
    if(!m_translator->load("Lesson_6_en_US",m_dir.path()))
        qWarning()<<"Can't load translation file!";

    m_tabWidget = nullptr;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_act_triggered()
{
    QFileDialog openFileDialog(this);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList files;

    if (openFileDialog.exec())
     {
         files = openFileDialog.selectedFiles();

         if(!m_tabWidget)
         {
             m_tabWidget = new QTabWidget(ui->centralwidget);
             m_tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
             m_tabWidget->setGeometry(QRect(14, 9, 771, 531));
             m_tabWidget->setTabsClosable(true);
             connect(m_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
         }

         foreach(auto file, files)
         {
             QFile f{file};
             if (!f.open(QIODevice::ReadWrite | QIODevice::Text)) return;
             m_tabWidget->setCurrentIndex(m_tabWidget->addTab(new QPlainTextEdit(f.readAll()), QFileInfo{f}.fileName()));
         }
         m_tabWidget->show();
     }
}

void MainWindow::closeTab(int index)
{
    m_tabWidget->removeTab(index);
    //if(m_tabWidget->in) если нет открытых вкладок - удалить таб вижет через шеред поинтер
}

void MainWindow::on_save_act_triggered()
{
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить"));

    QFile file{fileName};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    auto txtWdgtCh = qobject_cast<QPlainTextEdit *>(m_tabWidget->currentWidget());

    file.write(txtWdgtCh->toPlainText().toLocal8Bit());
    file.close();
}

void MainWindow::on_print_act_triggered()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Печать"));

    if (dlg.exec() != QDialog::Accepted)
        return;

    auto txtWdgtCh = qobject_cast<QPlainTextEdit *>(m_tabWidget->currentWidget());
    txtWdgtCh->print(&printer);
}

void MainWindow::on_new_act_triggered()
{
    if(!m_tabWidget)
    {
        m_tabWidget = new QTabWidget(ui->centralwidget);
        m_tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        m_tabWidget->setGeometry(QRect(14, 9, 771, 531));
        m_tabWidget->setTabsClosable(true);
        connect(m_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    }

    m_tabWidget->setCurrentIndex(m_tabWidget->addTab(new QPlainTextEdit(), tr("Новый файл")));
    m_tabWidget->show();
}

void MainWindow::on_exit_act_triggered()
{
    delete this;
}

void MainWindow::on_light_act_triggered()
{
    QFile file{m_dir.path()+"\\light_theme.qss"};
    file.open(QIODevice::ReadOnly);
    const QString cssStyle{file.readAll()};
    qApp->setStyleSheet(cssStyle);
    ui->light_act->setChecked(true);
    ui->dark_act->setChecked(false);
}

void MainWindow::on_dark_act_triggered()
{
    QFile file{m_dir.path()+"\\dark_theme.qss"};
    file.open(QIODevice::ReadOnly);
    const QString cssStyle{file.readAll()};
    qApp->setStyleSheet(cssStyle);
    ui->light_act->setChecked(false);
    ui->dark_act->setChecked(true);
}

void MainWindow::on_en_act_triggered()
{
    qApp->installTranslator(m_translator);
    this->ui->retranslateUi(this);
    ui->en_act->setChecked(true);
    ui->ru_act->setChecked(false);
}

void MainWindow::on_ru_act_triggered()
{
    qApp->removeTranslator(m_translator);
    this->ui->retranslateUi(this);
    ui->en_act->setChecked(false);
    ui->ru_act->setChecked(true);
}

void MainWindow::on_ref_act_triggered()
{
    QFile file{m_dir.path()+"\\help.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QString txt = file.readAll();

    QMessageBox message(QMessageBox::Icon::Information, tr("Справка"), txt, QMessageBox::Ok);
    int ret = message.exec();

    if(ret == QMessageBox::Ok) file.close();
}
