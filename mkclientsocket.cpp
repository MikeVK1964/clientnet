#include "mkclientsocket.h"
//#include "maketras.h"

MkClientSocket::MkClientSocket(const QString& strHost, int nPort , QWidget* pwgt )
    : QObject{}
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    //    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
    //            this,         SLOT(slotError(QAbstractSocket::SocketError))
    //           );
       // так начиная с QT5
    connect(m_pTcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
                this,         SLOT(slotError(QAbstractSocket::SocketError))
               );

}
void MkClientSocket::slotConnected()
{
    qDebug() << "Connected123";
}
// ----------------------------------------------------------------------
// вызывается при получении данных от сервера
void MkClientSocket::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_10);
    for (;;) {
        if (!m_nNextBlockSize) {   // число байт в блоке
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

       if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;   // не весь блок считан
        }
        m_mutex.lock();

         qsizetype trace_count;

         in >> trace_count;
         vnettar.clear();  //

         for (int i=0;i<trace_count;i++ )
         {
            TargetPositionNet tracePos;
            in >> tracePos;
            vnettar.push_back(tracePos);
         }
         m_nNextBlockSize = 0;
        m_mutex.unlock();
    }

}
// trace_time -
void MkClientSocket::SlotSendToServer(double trace_time)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
//    double trace_time=3; // время движения с начала имитации в секундах
//    out <<  QTime::currentTime() << m_ptxtInput->text();
    out << trace_time;
    m_pTcpSocket->write(arrBlock);

}
void MkClientSocket::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
  //  m_ptxtInfo->append(strError);
    qDebug() << strError;
}
