#ifndef MKCLIENTSOCKET_H
#define MKCLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "maketras.h"

class MkClientSocket :public QObject
{
    Q_OBJECT
public:
    MkClientSocket(const QString& strHost, int nPort, QWidget* pwgt = 0);

    QVector<TargetPositionNet>* getVect(){return &vnettar;}
    QMutex m_mutex;
private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize=0;
    QVector<TargetPositionNet> vnettar;
public slots:
    void SlotSendToServer(double trace_time);

private slots:
    void slotConnected();
    void slotReadyRead   (  );
    void slotError       (QAbstractSocket::SocketError);



};

#endif // MKCLIENTSOCKET_H
