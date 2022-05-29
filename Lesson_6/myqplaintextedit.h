#ifndef MYQPLAINTEXTEDIT_H
#define MYQPLAINTEXTEDIT_H

#include <QMenu>
#include <QFont>
#include <QList>
#include <QColor>
#include <QDebug>
#include <QBrush>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QTextEdit>
#include <QTextCursor>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QTextBlockFormat>

class MyQPlainTextEdit : public QTextEdit
{
    /* оказывается, QPlainTextEdit не поддерживает выравнивание текста...
                                                                            Печалька. */
    Q_OBJECT

    QMenu   *menu;
    QAction *getFormat_act;
    QAction *setFormat_act;
    QAction *choseColor_act;
    QAction *choseFormat_act;
    QAction *alignCenter_act;
    QAction *alignLeft_act;
    QAction *alignRight_act;
    QTextCharFormat savedFormat;

    void contextMenuEvent(QContextMenuEvent *event) override;

public:
    explicit MyQPlainTextEdit(QWidget *parent = nullptr);
    explicit MyQPlainTextEdit(const QString &text, QWidget *parent = nullptr);
            ~MyQPlainTextEdit();

private Q_SLOTS:
    void getFormat();
    void setFormat();
    void choseColor();
    void choseFormat();
    void setAlignLeft();
    void setAlignRight();
    void setAlignCenter();
};

#endif // MYQPLAINTEXTEDIT_H
