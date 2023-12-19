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
    add_dir.cpp \
    add_file.cpp \
    create_usr.cpp \
    directory.cpp \
    dis_dir.cpp \
    dis_disk.cpp \
    dis_mem.cpp \
    dis_openfile.cpp \
    disk.cpp \
    file.cpp \
    main.cpp \
    mainwindow.cpp \
    memory.cpp \
    page_login.cpp \
    thread.cpp \
    use_que.cpp

HEADERS += \
    add_dir.h \
    add_file.h \
    create_usr.h \
    directory.h \
    dis_dir.h \
    dis_disk.h \
    dis_mem.h \
    dis_openfile.h \
    disk.h \
    file.h \
    mainwindow.h \
    memory.h \
    page_login.h \
    thread.h \
    use_que.h

FORMS += \
    add_dir.ui \
    add_file.ui \
    create_usr.ui \
    dis_dir.ui \
    dis_disk.ui \
    dis_mem.ui \
    dis_openfile.ui \
    mainwindow.ui \
    page_login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

