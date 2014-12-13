#include "mainwindow.h"
#include <webbrowserapp.h>

int main(int argc, char *argv[])
{
    WebBrowserApp a(argc,argv);

    if (!a.isTheOnlyBrowser())
        return 0;

    a.newQtWebBrowseWin();


    return a.exec();
}
