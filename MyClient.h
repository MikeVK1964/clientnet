/* ======================================================================
**  MyClient.h
** ======================================================================
**
** ======================================================================
**  Copyright (c) 2007 by Max Schlee
** ======================================================================
*/
#ifndef _MyClient_h_
#define _MyClient_h_

#include <QWidget>
#include <QTcpSocket>
#include "mkclientsocket.h"

class QTextEdit;
class QLineEdit;

// ======================================================================
class MyClientWidget : public QWidget {
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    MkClientSocket* m_pMkClientSock;

    QTextEdit*  m_ptxtInfo;
//    QLineEdit*  m_ptxtInput;

public:
    MyClientWidget(const QString& strHost, int nPort, QWidget* pwgt = 0) ;

private slots:
    void PressSend();
    void SlotShowTracks();
signals:
     void SignalSendSecTime(double );
};
#endif  //_MyClient_h_
