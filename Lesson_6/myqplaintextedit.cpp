#include "myqplaintextedit.h"

MyQPlainTextEdit::MyQPlainTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{

}

MyQPlainTextEdit::MyQPlainTextEdit(const QString &text, QWidget *parent) : QPlainTextEdit(text, parent)
{

}

MyQPlainTextEdit::~MyQPlainTextEdit()
{
    delete this;
}

void MyQPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    menu = createStandardContextMenu();

    choseFormat_act = new QAction(tr("Формат..."));
    getFormat_act   = new QAction(tr("Копировать формат"));
    setFormat_act   = new QAction(tr("Применить формат"));

    menu->addAction(choseFormat_act);
    menu->addAction(getFormat_act);
    menu->addAction(setFormat_act);

    auto cursor = this->textCursor();

    if(cursor.selectedText().isEmpty())
    {
        getFormat_act->setEnabled(false);
        setFormat_act->setEnabled(false);
        choseFormat_act->setEnabled(false);
    }

    connect(getFormat_act, SIGNAL(triggered()), this, SLOT(getFormat()));
    connect(setFormat_act, SIGNAL(triggered()), this, SLOT(setFormat()));
    connect(choseFormat_act, SIGNAL(triggered()), this, SLOT(choseFormat()));

    menu->exec(event->globalPos());

    disconnect(getFormat_act, SIGNAL(triggered()), this, SLOT(getFormat()));
    disconnect(setFormat_act, SIGNAL(triggered()), this, SLOT(setFormat()));
    disconnect(choseFormat_act, SIGNAL(triggered()), this, SLOT(choseFormat()));

    delete menu;
}

void MyQPlainTextEdit::choseFormat()
{
    QFont font = this->textCursor().charFormat().font();
    QFontDialog fdlg(font, this);

    bool isOk(false);
    auto newFont{fdlg.getFont(&isOk)};

    if(isOk)
    {
        auto charFormat{this->textCursor().charFormat()};
        charFormat.setFont(newFont);
        this->textCursor().setCharFormat(charFormat);
    }
}

void MyQPlainTextEdit::getFormat()
{
    savedFormat = this->textCursor().charFormat();
}

void MyQPlainTextEdit::setFormat()
{
    this->textCursor().setCharFormat(savedFormat);
}
