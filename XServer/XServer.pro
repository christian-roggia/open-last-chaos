TARGET = XServer

LIBS += /usr/local/lib/mysql/libmysqlclient.a
LIBS += -lz

HEADERS += \
    XSource/XDESC.h \
    XSource/XDES.h \
    XSource/XCommunicationProtocol.h \
    XSource/Utils.h \
    XSource/socket.h \
    XSource/ServerRun.h \
    XSource/Server.h \
    XSource/Mutex.h \
    XSource/MemPool.h \
    XSource/log.h \
    XSource/input_main.h \
    XSource/input_auth.h \
    XSource/input.h \
    XSource/DBCmd.h \
    XSource/XPack.h \
    XSource/XSettings.h \
    XSource/XConstants.h \
    XSource/XCharacter.h \
    XSource/XMap.h \
    XSource/XRegen.h \
    XSource/XPC.h \
    XSource/XNPC.h

SOURCES += \
    XSource/XDESC.cpp \
    XSource/XDES.cpp \
    XSource/XCommunicationProtocol.cpp \
    XSource/Utils.cpp \
    XSource/socket.c \
    XSource/ServerRun.cpp \
    XSource/Server.cpp \
    XSource/main.cpp \
    XSource/log.c \
    XSource/input_main.cpp \
    XSource/input_auth.cpp \
    XSource/input.cpp \
    XSource/DBCmd.cpp \
    XSource/XPack.cpp \
    XSource/XSettings.cpp \
    XSource/XConstants.cpp \
    XSource/XCharacter.cpp \
    XSource/XMap.cpp \
    XSource/XRegen.cpp \
    XSource/XPC.cpp \
    XSource/XNPC.cpp
