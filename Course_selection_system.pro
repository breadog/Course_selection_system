QT       += core gui
QT       += sql network
QT       += xlsx

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
    showallstudent.cpp \
    teacher.cpp \
    widget.cpp \
    timetable.cpp

HEADERS += \
    changepassword.h \
    choose_course.h \
    enter_scores.h \
    showallstudent.h \
    teacher.h \
    timetable.h \
    widget.h

FORMS += \
    changepassword.ui \
    choose_course.ui \
    enter_scores.ui \
    showallstudent.ui \
    teacher.ui \
    timetable.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

