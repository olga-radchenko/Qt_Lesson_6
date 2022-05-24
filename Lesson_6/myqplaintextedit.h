#ifndef MYQPLAINTEXTEDIT_H
#define MYQPLAINTEXTEDIT_H

#include <QMenu>
#include <QFont>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QTextCursor>
#include <QFontDialog>
#include <QPlainTextEdit>
#include <QTextCharFormat>

class MyQPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

    QMenu *menu;
    QAction *getFormat_act;
    QAction *setFormat_act;
    QAction *choseFormat_act;
    QTextCharFormat savedFormat;

public:

    explicit MyQPlainTextEdit(QWidget *parent = nullptr);
    explicit MyQPlainTextEdit(const QString &text, QWidget *parent = nullptr);

     ~MyQPlainTextEdit();

    void contextMenuEvent(QContextMenuEvent *event) override;

private Q_SLOTS:
    void getFormat();
    void setFormat();
    void choseFormat();
};

#endif // MYQPLAINTEXTEDIT_H
