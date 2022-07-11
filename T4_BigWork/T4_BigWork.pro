QT       +=network
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    error.cpp \
    headwidget.cpp \
    judgement.cpp \
    login.cpp \
    main.cpp \
    mybutton.cpp \
    networkdata.cpp \
    networkserver.cpp \
    networksocket.cpp \
    rankinglist.cpp \
    room.cpp \
    roomview.cpp \
    servewindow.cpp \
    success.cpp \
    three_wight.cpp \
    two_wight.cpp \
    widget.cpp

HEADERS += \
    error.h \
    headwidget.h \
    judgement.h \
    login.h \
    mybutton.h \
    networkdata.h \
    networkserver.h \
    networksocket.h \
    rankinglist.h \
    room.h \
    roomview.h \
    servewindow.h \
    success.h \
    three_wight.h \
    two_wight.h \
    widget.h

FORMS += \
    error.ui \
    headwidget.ui \
    login.ui \
    room.ui \
    roomview.ui \
    servewindow.ui \
    success.ui \
    three_wight.ui \
    two_wight.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Source.qrc
