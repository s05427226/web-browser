#ifndef WEBBROWSERAPP_H
#define WEBBROWSERAPP_H

#include <QApplication>

class QMainWindow;
#include <QList>

class QLocalServer;

class WebBrowserApp : public QApplication
{
    Q_OBJECT
public:
    explicit WebBrowserApp(int argc,char **argv);

signals:

public slots:
    void newConnection();
public:
    QMainWindow *newQtWebBrowseWin();
    QMainWindow *mainWindow();
    bool isTheOnlyBrowser();
private:
    QList<QMainWindow*> m_Windows;
    QLocalServer* m_pLocalServer;
};

#endif // WEBBROWSERAPP_H
