#-------------------------------------------------
#
# Project created by QtCreator 2017-07-23T15:10:08
#
#-------------------------------------------------

QT       += core gui sql positioning location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mypictures
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += src

SOURCES +=\
    src/main.cpp \
    src/easyexif/exif.cpp \
    src/sqlite/sqlite3.c \
    src/database/database.cpp \
    src/picture/picture.cpp \
    src/picture/album.cpp \
    src/picture/taggroup.cpp \
    src/gui/windowmain.cpp \
    src/gui/table_view.cpp \
    src/gui/table_model.cpp \
    src/gui/widget_table_view.cpp \
    src/gui/widget_top_menu.cpp \
    src/gui/widget_big_picture_view.cpp \
    src/gui/widget_picture_info.cpp \
    src/gui/borderlayout.cpp \
    src/learning/learing_algorithm.cpp \
    src/gui/widget_settings.cpp \
    src/database/database_worker.cpp \
    src/database/settings.cpp \
    src/picture/folder.cpp \
    src/gui/widget_menu_picture.cpp \
    src/gui/dialog_list.cpp \
    src/picture/separator.cpp \
    src/geo_locating/geo_locating.cpp \
    src/gui/dialog_geo_location.cpp

HEADERS += \
    src/easyexif/exif.h \
    src/sqlite/sqlite3.h \
    src/database/database.h \
    src/picture/picture.h \
    src/picture/album.h \
    src/picture/picturelistentry.h \
    src/picture/taggroup.h \
    src/gui/windowmain.h \
    src/gui/table_view.h \
    src/gui/table_model.h \
    src/gui/widget_table_view.h \
    src/gui/widget_top_menu.h \
    src/gui/widget_big_picture_view.h \
    src/gui/widget_picture_info.h \
    src/gui/borderlayout.h \
    src/learning/learing_algorithm.h \
    src/gui/widget_settings.h \
    src/database/database_worker.h \
    src/database/settings.h \
    src/picture/folder.h \
    src/gui/widget_menu_picture.h \
    src/gui/dialog_list.h \
    src/picture/separator.h \
    src/geo_locating/geo_locating.h \
    src/gui/dialog_geo_location.h

FORMS +=

RESOURCES += \
    rsc/icons.qrc

LIBS=-ldl
