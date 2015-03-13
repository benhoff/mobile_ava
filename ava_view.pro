TEMPLATE = app

QT += qml quick
QT += core
QT += network

SOURCES += main.cpp
CONFIG += c++11
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    ProjectIndexLayout.qml \
    ProjectListModel.qml \
    ProjectListView.qml \
    ava_view.pro.user \
    ../../ava/projects/views.py \
    ../../ava/projects/admin.py \
    ../../ava/projects/models.py \
    ../../ava/projects/permissions.py \
    ../../ava/projects/serializers.py \
    ../../ava/projects/tests.py \
    ../../ava/projects/urls.py
