/* ======================================================================
**  MyClient.cpp
** ======================================================================
**
** ======================================================================
**  Copyright (c) 2007 by Max Schlee
** ======================================================================
*/
#include <QtNetwork>
#include <QtGui>
#include <qtextedit.h>
#include <qlineedit.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <qlabel.h>
#include "MyClient.h"
#include "maketras.h"

// ----------------------------------------------------------------------
MyClientWidget::MyClientWidget(const QString& strHost,
                   int            nPort, 
                   QWidget*       pwgt /*=0*/
                  ) : QWidget(pwgt)
{
    m_pMkClientSock= new MkClientSocket(strHost,nPort,pwgt);


    m_ptxtInfo  = new QTextEdit;
    //m_ptxtInput = new QLineEdit;


    connect(this, SIGNAL(SignalSendSecTime(double )),
                m_pMkClientSock, SLOT(SlotSendToServer(double ))
               );

    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton("&Send time");
    connect(pcmd, SIGNAL(clicked()), SLOT(PressSend()));

    QPushButton* pcmd_show = new QPushButton("Show Data");
    connect(pcmd_show, SIGNAL(clicked()), SLOT(SlotShowTracks()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;    
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
 //   pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    pvbxLayout->addWidget(pcmd_show);

    setLayout(pvbxLayout);
}



// ------------------------------------------------------------------
void MyClientWidget::PressSend()
{
//    m_pMkClientSock->SendToServer(3);
   emit  SignalSendSecTime(3.0);
}
//-------------------------------------------------------------------------
void MyClientWidget::SlotShowTracks()
{
    QVector<TargetPositionNet>* ptp=m_pMkClientSock->getVect();
    QMutexLocker locker(&m_pMkClientSock->m_mutex);

    qsizetype trace_count=(*ptp).count();
    QString str = QString("число трасс %1").arg(trace_count);
    m_ptxtInfo->append( str);

    for (int i=0;i<trace_count;i++) {
        str =
         QString("x_km %1 y_km %2 h_m %3").arg((*ptp)[i].fx_km).arg((*ptp)[i].fy_km).arg((*ptp)[i].ih_m);
        m_ptxtInfo->append( str);

    }
}
