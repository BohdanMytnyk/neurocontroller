QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

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
    controller/controller.cpp \
    controller/pid.cpp \
    controller/sample.cpp \
    controller/samplegenerator.cpp \
    main.cpp \
    neurocontroller.cpp \
    satellite/cubesat.cpp \
    satellite/satellite.cpp \
    satellite/wheel.cpp \
    satellite/complexsat.cpp \
    simulation/command.cpp \
    simulation/controlledsim.cpp \
    ui/commandwindow.cpp \
    simulation/instructedsim.cpp \
    simulation/instruction.cpp \
    simulation/simulation.cpp \
    qcustomplot.cpp


HEADERS += \
    controller/controller.h \
    controller/pid.h \
    controller/sample.h \
    controller/samplegenerator.h \
    neurocontroller.h \
    satellite/cubesat.h \
    satellite/satellite.h \
    satellite/wheel.h \
    satellite/complexsat.h \
    simulation/command.h \
    simulation/controlledsim.h \
    simulation/instructedsim.h \
    simulation/instruction.h \
    simulation/simulation.h \
    utils.h \
    ui/commandwindow.h \
    qcustomplot.h \




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
FORMS += \
    ui/mainwindow.ui \
    ui/commandwindow.ui
