TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Downloads/libtommath-1.2.0/release/ -ltommath
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Downloads/libtommath-1.2.0/debug/ -ltommath
else:unix: LIBS += -L$$PWD/../../Downloads/libtommath-1.2.0/ -ltommath

INCLUDEPATH += $$PWD/../../Downloads/libtommath-1.2.0
DEPENDPATH += $$PWD/../../Downloads/libtommath-1.2.0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Downloads/libtommath-1.2.0/release/libtommath.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Downloads/libtommath-1.2.0/debug/libtommath.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Downloads/libtommath-1.2.0/release/tommath.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Downloads/libtommath-1.2.0/debug/tommath.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../Downloads/libtommath-1.2.0/libtommath.a
