#include "widget.h"
#include "timetable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*Timetable *table = new Timetable();
    table->show()*/;
    Widget w;
    w.show();
    return a.exec();
}
