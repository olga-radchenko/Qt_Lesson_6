#ifndef FINDFILETHREAD_H
#define FINDFILETHREAD_H

#include <QObject>

class FindFileThread : public QObject
{
    Q_OBJECT
public:
    explicit FindFileThread(QObject *parent = nullptr);

signals:

};

#endif // FINDFILETHREAD_H
