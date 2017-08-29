# -------------------------------------------------
# Project created by QtCreator 2016-05-07T07:48:05
# -------------------------------------------------
QT += svg \
    xml
QT+=widgets
QT += testlib
    #multimedia
CONFIG += qt debug

TARGET = test3

TEMPLATE = app



#modified===============================
LIBS += -L/opt/ros/indigo/lib -lroscpp -lrospack -lpthread -lrosconsole -lrosconsole_log4cxx -lrosconsole_backend_interface \
        -lxmlrpcpp -lrostime -lroscpp_serialization -limage_transport -lcv_bridge
LIBS += -l:/opt/ros/indigo/lib/libroslib.so -l:/opt/ros/indigo/lib/libroscpp.so

LIBS += -L/usr/local/lib/ -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_imgcodecs 
LIBS += -l:/usr/local/lib/libopencv_core.so.3.3 -l:/usr/local/lib/libopencv_highgui.so.3.3 -l:/usr/local/lib/libopencv_imgcodecs.so.3.3
LIBS += -l:/usr/local/lib/libopencv_core.so
LIBS += -L/opt/ros/indigo/lib/ -lcamera_info_manager
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system

#LIBS += -L/usr/local/lib -lyaml-cpp

INCLUDEPATH += /opt/ros/indigo/include   /opt/ros/indigo/lib /usr/local/include /usr/local/include/opencv2  /usr/include/
DEPENDPATH +=   /opt/ros/indogo/include



#=======================================    
LIBS += -L \
    ../../yusb_linux_1.0.4/lib \
    -lcyusb \
    -lusb-1.0
SOURCES += main.cpp \
    mainwindow.cpp \
    cdatacapture.cpp \
    thread.cpp \
    display_thread.cpp
HEADERS += mainwindow.h \
    cdatacapture.h \
    wqueue.h \
    thread.h \
    display_thread.h \
    imgframe.h \
    ../../cyusb_linux_1.0.4/include/cyusb.h \
    /opt/ros/indigo/include/ros/ros.h
FORMS += mainwindow.ui
LIBS += -L/usr/local/lib
QMAKE_CXXFLAGS+= -std=c++11

