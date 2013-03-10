# Auto-generated by IDE. All changes by user will be lost!
# Created at 3/10/13 7:02 PM

BASEDIR = $$_PRO_FILE_PWD_

INCLUDEPATH +=  \
    $$BASEDIR/src/api/util \
    $$BASEDIR/src/api/client \
    $$BASEDIR/src/api/object \
    $$BASEDIR/src/api \
    $$BASEDIR/src/api/method \
    $$BASEDIR/src

SOURCES +=  \
    $$BASEDIR/src/YouMailBB10.cpp \
    $$BASEDIR/src/api/client/apiclient.cpp \
    $$BASEDIR/src/api/object/response.cpp \
    $$BASEDIR/src/main.cpp

HEADERS +=  \
    $$BASEDIR/src/YouMailBB10.hpp \
    $$BASEDIR/src/api/client/apiclient.h \
    $$BASEDIR/src/api/constants.h \
    $$BASEDIR/src/api/method/addfolder.h \
    $$BASEDIR/src/api/method/apimethod.h \
    $$BASEDIR/src/api/method/apimethodresponsehandler.h \
    $$BASEDIR/src/api/method/apimethodvisitor.h \
    $$BASEDIR/src/api/method/authenticate.h \
    $$BASEDIR/src/api/method/deletefolder.h \
    $$BASEDIR/src/api/method/getaccesspoint.h \
    $$BASEDIR/src/api/method/getfolders.h \
    $$BASEDIR/src/api/method/getmessages.h \
    $$BASEDIR/src/api/method/getpreferences.h \
    $$BASEDIR/src/api/method/getsettings.h \
    $$BASEDIR/src/api/object/alertsettings.h \
    $$BASEDIR/src/api/object/apiobject.h \
    $$BASEDIR/src/api/object/apiobjectdeserializer.h \
    $$BASEDIR/src/api/object/apiobjectserializer.h \
    $$BASEDIR/src/api/object/apiobjectvisitor.h \
    $$BASEDIR/src/api/object/apiobjectvisitorfactory.h \
    $$BASEDIR/src/api/object/authtoken.h \
    $$BASEDIR/src/api/object/contact.h \
    $$BASEDIR/src/api/object/messageboxentry.h \
    $$BASEDIR/src/api/object/messageboxfolder.h \
    $$BASEDIR/src/api/object/preferences.h \
    $$BASEDIR/src/api/object/pushregistration.h \
    $$BASEDIR/src/api/object/response.h \
    $$BASEDIR/src/api/object/settings.h \
    $$BASEDIR/src/api/object/transcriptionsettings.h \
    $$BASEDIR/src/api/util/util.h

CONFIG += precompile_header
PRECOMPILED_HEADER = $$BASEDIR/precompiled.h

lupdate_inclusion {
    SOURCES += \
        $$BASEDIR/../assets/*.qml
}

TRANSLATIONS = \
    $${TARGET}.ts

