#-------------------------------------------------
#
# Project created by QtCreator 2022-05-02T10:48:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    addeventdialog.cpp \
    addattributedialog.cpp \
    addobjectdialog.cpp \
    addrelationdialog.cpp \
    changerelationdialog.cpp \
    d_class_properties.cpp \
    diagram_class.cpp \
  editmessagedialog.cpp \
    editobjectdialog.cpp \
        main.cpp \
        mainwindow.cpp \
    clsdgrwidget.cpp \
    seqdiagram.cpp \
    seqdiagramwidget.cpp \
    seqevent.cpp \
    seqobject.cpp \
    basicdialog.cpp

HEADERS += \
    addeventdialog.h \
    addattributedialog.h \
    addobjectdialog.h \
    addrelationdialog.h \
    changerelationdialog.h \
    d_class_properties.h \
    diagram_class.h \
    editmessagedialog.h \
    editobjectdialog.h \
        mainwindow.h \
    clsdgrwidget.h \
    seqdiagram.h \
    seqdiagramwidget.h \
    seqevent.h \
    seqobject.h \
    basicdialog.h

FORMS += \
        addeventdialog.ui \
        addattributedialog.ui \
        addobjectdialog.ui \
        addrelationdialog.ui \
        changerelationdialog.ui \
        editmessagedialog.ui \
        editobjectdialog.ui \
        mainwindow.ui \
        basicdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
