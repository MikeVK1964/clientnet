#include "threadscontroller.h"

ThreadsController::ThreadsController(QObject *parent)
    : QObject{parent}
{
    m_pMkClientSock= new MkClientSocket("localhost", 2323);
    thread = new QThread( parent );
 //   m_pMkClientSock->PrepareActions("localhost", 2323);
    connect(this, SIGNAL(SignalSendSecTime(double )),
                m_pMkClientSock, SLOT(SlotSendToServer(double ))
               );

    m_pMkClientSock->moveToThread(thread);
    thread->start();
//    const QString strHost;
//                       int            nPort,
//    m_pMkClientSock->PrepareActions("localhost", 2323);

}
ThreadsController::~ThreadsController()
{
//    if (m_pMkClientSock!=nullptr) delete m_pMkClientSock;
    // deleteLater - поток должен получить управление и все незавершенные
    //задачи(незавершенные сигналы) завершатся
    if (m_pMkClientSock!=nullptr) m_pMkClientSock->deleteLater();
    m_pMkClientSock=nullptr;
    thread->quit();
    thread->wait(); // на всякий случая в run ничего нет
    delete thread ;

}
