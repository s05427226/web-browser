#include "webbrowserapp.h"
#include "webbroswerwindow.h"
#include <QLocalSocket>
#include <QTextStream>
#include <QStringList>
#include <QLocalServer>
#include <QFile>
#include <QMessageBox>

WebBrowserApp::WebBrowserApp(int argc,char **argv) :
    QApplication(argc,argv),
    m_pLocalServer(0)
{
    QLocalSocket *socket = new QLocalSocket;
    QString strAppName = QCoreApplication::applicationName();

    socket->connectToServer(strAppName);

    if(socket->waitForConnected(500))
    {
        QTextStream s(socket);
        QStringList args = QCoreApplication::arguments();

        if(args.count() > 1) {
            s << args.last();
        }else{
            s <<QString();
        }

        s.flush();
        socket->waitForBytesWritten();
        return;
    }

    m_pLocalServer = new QLocalServer(this);
    connect(m_pLocalServer,SIGNAL(newConnection()),
            this,SLOT(newConnection()));

    if(!m_pLocalServer->listen(strAppName)) {
        if (m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError
            && QFile::exists(m_pLocalServer->serverName())) {
            QFile::remove(m_pLocalServer->serverName());
            m_pLocalServer->listen(strAppName);
        }
    }

}

void WebBrowserApp::newConnection()
{
    QLocalSocket *socket = m_pLocalServer->nextPendingConnection();
    if (!socket)
        return;
    socket->waitForReadyRead(1000);
    QTextStream stream(socket);
    QString url;
    stream >> url;

    QMessageBox::information(NULL,QString("url"),url);
    delete socket;
    mainWindow()->raise();
    mainWindow()->activateWindow();
}

QMainWindow *WebBrowserApp::newQtWebBrowseWin()
{
    WebBroswerWindow* win = new WebBroswerWindow;
    m_Windows.append(win);
    win->show();

    return win;
}

QMainWindow *WebBrowserApp::mainWindow()
{
   // clear();
    if(this->m_Windows.count() == 0)
    {
          return this->newQtWebBrowseWin();
    }else{
        return this->m_Windows[0];
    }
}

bool WebBrowserApp::isTheOnlyBrowser()
{
    return (m_pLocalServer != NULL);
}
