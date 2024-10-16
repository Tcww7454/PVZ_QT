QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cardmanager.cpp \
    cards.cpp \
    main.cpp \
    map.cpp \
    peacard.cpp \
    peashooter.cpp \
    plant.cpp \
    plantmanager.cpp \
    pvz.cpp \
    toolbar.cpp

HEADERS += \
    cardmanager.h \
    cards.h \
    map.h \
    peacard.h \
    peashooter.h \
    plant.h \
    plantmanager.h \
    pvz.h \
    toolbar.h

FORMS += \
    pvz.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
