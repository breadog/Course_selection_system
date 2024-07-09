QT       += core gui
QT       += sql network
#QT       += xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changepassword.cpp \
    choose_course.cpp \
    enter_scores.cpp \
    main.cpp \
    schooltimetable.cpp \
    showallstudent.cpp \
    teacher.cpp \
    widget.cpp \
    timetable.cpp \
    t_mainwindow.cpp \
    teacherinfo.cpp \
    s_mainwindow.cpp \
    studentinfo.cpp

HEADERS += \
    changepassword.h \
    choose_course.h \
    enter_scores.h \
    schooltimetable.h \
    showallstudent.h \
    teacher.h \
    timetable.h \
    widget.h \
    t_mainwindow.h \
    teacherinfo.h \
    s_mainwindow.h \
    studentinfo.h

FORMS += \
    changepassword.ui \
    choose_course.ui \
    enter_scores.ui \
    schooltimetable.ui \
    showallstudent.ui \
    teacher.ui \
    timetable.ui \
    widget.ui \
    t_mainwindow.ui \
    teacherinfo.ui \
    s_mainwindow.ui \
    studentinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

