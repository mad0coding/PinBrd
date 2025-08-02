#include "widget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget mywidget;
    mywidget.setWindowTitle(mywidget.Title/* + mywidget.Version*/); // 设置窗口名称
    mywidget.show();
    mywidget.setFocusPolicy(Qt::StrongFocus);
    
    setbuf(stdout, NULL); // 设置printf缓冲为0,使立即输出
    
    a.exec();
    
    return 0;
}
