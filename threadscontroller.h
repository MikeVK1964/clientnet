#ifndef THREADSCONTROLLER_H
#define THREADSCONTROLLER_H

#include <QObject>
#include "mkclientsocket.h"


class ThreadsController : public QObject
{
    Q_OBJECT
public:
    explicit ThreadsController(QObject *parent = nullptr);
    ~ThreadsController();
    MkClientSocket* GetMkClSock(){return m_pMkClientSock; }
private:
    QThread* thread; //поток

    MkClientSocket* m_pMkClientSock=nullptr;

signals:
    void SignalSendSecTime(double );

};

#endif // THREADSCONTROLLER_H
