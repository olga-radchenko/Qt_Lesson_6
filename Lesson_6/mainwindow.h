#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTranslator>
#include <QFileDialog>
#include <QPainter>
#include <iostream>
#include <QTabBar>
#include <memory>
#include <QDebug>
#include <QDate>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    void makeTabWidget();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void closeTab(int index);

    void on_save_act_triggered();

    void on_print_act_triggered();

    void on_new_act_triggered();

    void on_exit_act_triggered();

    void on_light_act_triggered();

    void on_dark_act_triggered();

    void on_en_act_triggered();

    void on_ru_act_triggered();

    void on_ref_act_triggered();

    void on_open_act_triggered();

private:
    QDir m_dir;
    Ui::MainWindow *ui;
    std::shared_ptr<QTabWidget> m_tabWidget;
    QTranslator* m_translator;
};
#endif // MAINWINDOW_H
