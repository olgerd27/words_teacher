#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("MSoft");
    a.setApplicationName(QObject::tr("Words Teacher"));
    Window w;
    w.show();
    return a.exec();
}
