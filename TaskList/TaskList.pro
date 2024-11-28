QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appmanager.cpp \
    group.cpp \
    groupmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    searchmanager.cpp \
    task.cpp \
    taskmanager.cpp \
    trashmanager.cpp

HEADERS += \
    appmanager.h \
    group.h \
    groupmanager.h \
    mainwindow.h \
    menu.h \
    searchmanager.h \
    stable.h \
    task.h \
    taskmanager.h \
    trashmanager.h

PRECOMPILED_HEADER = stable.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc