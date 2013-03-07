######################################################################
# Automatically generated by qmake (2.01a) Thu Mar 7 00:27:39 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              src \
              translations \
              src\api \
              src\api\client \
              src\api\method \
              src\api\object \
              src\api\util
INCLUDEPATH += .

# Input
HEADERS += precompiled.h \
           src/YouMailBB10.hpp \
           src/api/constants.h \
           src/api/client/apiclient.h \
           src/api/method/AddFolder.h \
           src/api/method/apimethod.h \
           src/api/method/apimethodresponsehandler.h \
           src/api/method/apimethodvisitor.h \
           src/api/method/authenticate.h \
           src/api/method/DeleteFolder.h \
           src/api/method/GetAccessPoint.h \
           src/api/method/GetFolders.h \
           src/api/method/GetMessages.h \
           src/api/method/GetPreferences.h \
           src/api/method/GetSettings.h \
           src/api/object/alertsettings.h \
           src/api/object/apiobject.h \
           src/api/object/apiobjectdeserializer.h \
           src/api/object/apiobjectserializer.h \
           src/api/object/apiobjectvisitor.h \
           src/api/object/apiobjectvisitorfactory.h \
           src/api/object/authtoken.h \
           src/api/object/contact.h \
           src/api/object/messageboxentry.h \
           src/api/object/messageboxfolder.h \
           src/api/object/preferences.h \
           src/api/object/pushregistration.h \
           src/api/object/response.h \
           src/api/object/settings.h \
           src/api/object/transcriptionsettings.h \
           src/api/util/util.h
SOURCES += src/main.cpp \
           src/YouMailBB10.cpp \
           src/api/client/apiclient.cpp \
           src/api/method/apimethodresponsehandler.cpp \
           src/api/object/apiobjectvisitor.cpp \
           src/api/object/response.cpp
TRANSLATIONS += translations/YouMailBB10.ts
