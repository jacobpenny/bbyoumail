#include "YouMailBB10.hpp"
#include "api/method/apimethod.h"
#include "api/method/apimethodresponsehandler.h"
#include "api/method/authenticate.h"
#include "settings/appsettings.h"


#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QtDebug>

#include <bb/data/SqlConnection>

using ymbb10::api::method::Authenticate;
using ymbb10::api::method::ApiMethodBase;
using ymbb10::api::method::ApiMethodResponseHandler;
using ymbb10::storage::SqlStorage;

using namespace bb::cascades;
using namespace bb::system;

YouMailBB10::YouMailBB10(bb::cascades::Application *app) : QObject(app)
{
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	AbstractPane *root = qml->createRootObject<AbstractPane>();

	app->setOrganizationName("edgesoft");
	app->setApplicationName("barnowl");

	apiClient_ = new ymbb10::api::ApiClient("http://api.youmail.com/api", "youmailapp", app);
	responseHandler_ = new ApiMethodResponseHandler;

	QString databaseName = "test.db";
	copyFileToDataFolder(databaseName);
	QString databasePath = QDir::homePath() + "/" + databaseName;

	sqlStorage_ = new SqlStorage(QDir::currentPath() + "/data/test.db");

	// Register our enum so it works with slots
    qRegisterMetaType<ymbb10::api::method::ResponseMessage>("ymbb10::api::method::ResponseMessage");

	bool r1 = QObject::connect(responseHandler_, SIGNAL(responseProcessed(ymbb10::api::method::ResponseMessage)),
			this, SLOT(responseMessage(ymbb10::api::method::ResponseMessage)));

	bool r2 = QObject::connect(apiClient_, SIGNAL(responseDeserialized(ymbb10::api::method::ApiMethodBase*)),
			responseHandler_, SLOT(handleResponse(ymbb10::api::method::ApiMethodBase*)));

	Q_ASSERT(r1);
	Q_ASSERT(r2);

	pResponseHandlerThread_ = new QThread;
	responseHandler_->moveToThread(pResponseHandlerThread_);
	pResponseHandlerThread_->start();

	QSettings settings;
	qDebug() << app->applicationVersion();
	qDebug() << "APP_VERSION: " << settings.value(ymbb10::settings::APP_VERSION, QString("0.0.0.0")).toString();


	settings.setValue(ymbb10::settings::PREV_APP_VERSION, settings.value(ymbb10::settings::APP_VERSION, QString("0.0.0.0")));
	settings.setValue(ymbb10::settings::APP_VERSION, app->applicationVersion());

	onStart();
	app->setScene(root);
}

void YouMailBB10::onStart()
{
	sqlStorage_->onOpen(false);

	if (!haveCredentials()) {
		QmlDocument *sheetQml = QmlDocument::create("asset:///Loginsheet.qml").parent(this);
		loginSheet_ = sheetQml->createRootObject<Sheet>();
		loginSheet_->open();
		QObject *loginButton = loginSheet_->findChild<QObject*>("login_button");

		bool res = QObject::connect(loginButton, SIGNAL(clicked()), this,
		                            SLOT(handleLoginButtonClicked()));
		Q_ASSERT(res);
	} else {
		// have credentials, make some api calls
	}
}

bool YouMailBB10::haveCredentials() {
	QSettings loginSettings;
	qDebug() << "Stored phone number: " << loginSettings.value("userphone").toString();
	qDebug() << "Stored pin: " << loginSettings.value("userpin").toString();
	qDebug() << "Auth token: " << loginSettings.value("authtoken").toString();
	return loginSettings.contains("userphone") && loginSettings.contains("userpin");
}

void YouMailBB10::handleLoginButtonClicked()
{
	QObject *userPhoneField = loginSheet_->findChild<QObject*>("phone_number");
	QVariant userPhone = userPhoneField->property("text");

	QObject *userPinField = loginSheet_->findChild<QObject*>("user_pin");
	QVariant userPin = userPinField->property("text");

	QSharedPointer<ApiMethodBase> authCall(new Authenticate(userPhone.toString(), userPin.toString()));
	apiClient_->execute(authCall);

	// Store phone/pin
	QSettings loginSettings;
	loginSettings.setValue("userphone", userPhone.toString());
	loginSettings.setValue("userpin", userPin.toString());
	loginSettings.sync();
}

void YouMailBB10::responseMessage(ymbb10::api::method::ResponseMessage message) {
	qDebug() << "Main thread received message code: " << message;
	switch (message) {

	case ymbb10::api::method::AUTH_SUCCESS :
		if (loginSheet_->isOpened()) {
			loginSheet_->close();
			// make some requests for messages here?
		} else {

		}
		break;
	}
}

void YouMailBB10::showAuthFailedToast() {
    SystemToast *toast = new SystemToast(this); // leak?
    toast->setBody("Authentication failed, please try again.");
    toast->show();
}


void YouMailBB10::copyFileToDataFolder(const QString fileName)
{
    // Since we need read and write access to the file, it has
    // to be moved to a folder where we have access to it. First,
    // we check if the file already exists (previously copied).
    QString dataFolder = QDir::homePath();
    QString newFileName = dataFolder + "/" + fileName;
    QFile newFile(newFileName);


    if (!newFile.exists()) {
        // If the file is not already in the data folder, we copy it from the
        // assets folder (read only) to the data folder (read and write).
        QString appFolder(QDir::homePath());
        appFolder.chop(4);
        QString originalFileName = appFolder + "app/native/assets/" + fileName;
        QFile originalFile(originalFileName);

        if (originalFile.exists()) {
            // Create sub folders if any creates the SQL folder for a file path like e.g. sql/quotesdb
            QFileInfo fileInfo(newFileName);
            QDir().mkpath (fileInfo.dir().path());

            if(!originalFile.copy(newFileName)) {
                qDebug() << "Failed to copy file to path: " << newFileName;
            }
        } else {
            qDebug() << "Failed to copy file data base file does not exists.";
        }
    }
}


