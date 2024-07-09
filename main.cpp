#include "widget.h"
#include "timetable.h"
#include <QApplication>
#include"schooltimetable.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Widget w;
//    w.show();
    schooltimetable *s = new schooltimetable("mgm",1,nullptr);
    s->show();
    return a.exec();
}
