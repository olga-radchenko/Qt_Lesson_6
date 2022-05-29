#include "myqplaintextedit.h"

MyQPlainTextEdit::MyQPlainTextEdit(QWidget *parent) : QTextEdit(parent) {}

MyQPlainTextEdit::MyQPlainTextEdit(const QString &text, QWidget *parent) : QTextEdit(text, parent) {}

MyQPlainTextEdit::~MyQPlainTextEdit() {delete this;}

void MyQPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);

    menu = createStandardContextMenu();
    QMenu* submenu = menu->addMenu(tr("Выровнять"));

    QList<QAction*> actions = menu->actions();

    foreach (QAction *action, actions)
    {
       QString actionText = action->text();
       if (actionText.contains("Undo"))
       {
           actionText.replace("Undo", tr("Отменить"));
           action->setText(actionText);
       }
       else if (actionText.contains("Redo"))
       {
           actionText.replace("Redo", tr("Вернуть"));
           action->setText(actionText);
       }
       else if (actionText.contains("Cu&t"))
       {
           actionText.replace("Cu&t", tr("Вырезать"));
           action->setText(actionText);
       }
       else if (actionText.contains("Copy"))
       {
           actionText.replace("Copy", tr("Копировать"));
           action->setText(actionText);
       }
       else if (actionText.contains("Paste"))
       {
           actionText.replace("Paste", tr("Вставить"));
           action->setText(actionText);
       }
       else if (actionText.contains("Delete"))
       {
           actionText.replace("Delete", tr("Удалить"));
           action->setText(actionText);
       }
       else if (actionText.contains("Select All"))
       {
           actionText.replace("Select All", tr("Выделить все"));
           action->setText(actionText);
       }
    }

    getFormat_act       = new QAction(tr("Копировать формат"));
    setFormat_act       = new QAction(tr("Применить формат"));
    choseColor_act      = new QAction(tr("Цвет..."));
    choseFormat_act     = new QAction(tr("Формат..."));
    alignCenter_act     = new QAction(tr("по центру"));
    alignRight_act      = new QAction(tr("по правому краю"));
    alignLeft_act       = new QAction(tr("по левому краю"));

    menu->addAction(getFormat_act);
    menu->addAction(setFormat_act);
    menu->addAction(choseColor_act);
    menu->addAction(choseFormat_act);

    submenu->addAction(alignCenter_act);
    submenu->addAction(alignLeft_act);
    submenu->addAction(alignRight_act);

    auto cursor = this->textCursor();

    if(cursor.selectedText().isEmpty())
    {
        getFormat_act->setEnabled(false);
        setFormat_act->setEnabled(false);
        choseFormat_act->setEnabled(false);
        choseColor_act->setEnabled(false);
                submenu->setEnabled(false);
    }

    connect(choseColor_act, SIGNAL(triggered()), this, SLOT(choseColor()));
    connect(getFormat_act,  SIGNAL(triggered()), this, SLOT(getFormat()));
    connect(setFormat_act,  SIGNAL(triggered()), this, SLOT(setFormat()));
    connect(choseFormat_act,SIGNAL(triggered()), this, SLOT(choseFormat()));

    connect(alignCenter_act,SIGNAL(triggered()), this, SLOT(setAlignCenter()));
    connect(alignLeft_act,  SIGNAL(triggered()), this, SLOT(setAlignLeft()));
    connect(alignRight_act, SIGNAL(triggered()), this, SLOT(setAlignRight()));

    menu->exec(QCursor::pos());

    disconnect(choseColor_act, SIGNAL(triggered()), this, SLOT(choseColor()));
    disconnect(getFormat_act,  SIGNAL(triggered()), this, SLOT(getFormat()));
    disconnect(setFormat_act,  SIGNAL(triggered()), this, SLOT(setFormat()));
    disconnect(choseFormat_act,SIGNAL(triggered()), this, SLOT(choseFormat()));

    disconnect(alignCenter_act,SIGNAL(triggered()), this, SLOT(setAlignCenter()));
    disconnect(alignLeft_act,  SIGNAL(triggered()), this, SLOT(setAlignLeft()));
    disconnect(alignRight_act, SIGNAL(triggered()), this, SLOT(setAlignRight()));

    delete menu;
}

void MyQPlainTextEdit::setAlignCenter()
{
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    this->setTextCursor(cursor);
}

void MyQPlainTextEdit::setAlignLeft()
{
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(textBlockFormat);
    this->setTextCursor(cursor);
}

void MyQPlainTextEdit::setAlignRight()
{
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(textBlockFormat);
    this->setTextCursor(cursor);
}

void MyQPlainTextEdit::choseColor()
{
    QColor color = QColorDialog::getColor();
    if (!color.isValid()) return;
    QFont font = this->textCursor().charFormat().font();
    QTextCharFormat charFormat = this->textCursor().charFormat();
    charFormat.setForeground(QBrush{color});
    charFormat.setFont(font);
    this->textCursor().setCharFormat(charFormat);
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

