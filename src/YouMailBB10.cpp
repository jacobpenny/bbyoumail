// Tabbed pane project template
#include "YouMailBB10.hpp"


#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QtDebug>

#include "api/method/apimethodresponsehandler.h"



using ymbb10::api::method::Authenticate;
//using ymbb10::api::method::ApiMethodResponseHandler;
using ymbb10::api::object::AuthToken;

using namespace bb::cascades;
using namespace bb::system;


YouMailBB10::YouMailBB10(bb::cascades::Application *app) : QObject(app)
{
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	AbstractPane *root = qml->createRootObject<AbstractPane>();


	apiClient_ = new ymbb10::api::ApiClient("http://api.youmail.com/api", "youmailapp", app, this);
	/*
	ApiMethodResponseHandler responseHandler; // should this be heap?

	connect(&responseHandler, SIGNAL(responseProcessed(QString)),
			this, SLOT(responseMessage(QString)));
	connect(apiClient_, SIGNAL(responseDeserialized(QSharedPointer<ApiMethodBase>)),
			&responseHandler, SLOT(handleResponse(QSharedPointer<ApiMethodBase>)));

	pResponseHandlerThread_ = new QThread;
	responseHandler.moveToThread(pResponseHandlerThread_);
	*/

	bool loggedIn = false; // place holder
	if (!loggedIn) {
		QmlDocument *sheetQml = QmlDocument::create("asset:///Loginsheet.qml").parent(this);
		loginSheet_ = sheetQml->createRootObject<Sheet>();
		loginSheet_->open();
		QObject *loginButton = loginSheet_->findChild<QObject*>("login_button");

		bool res = QObject::connect(loginButton, SIGNAL(clicked()), this,
		                            SLOT(handleLoginButtonClicked()));
		Q_ASSERT(res);
	}

	app->setScene(root);
}



void YouMailBB10::handleLoginButtonClicked()
{
	QObject *userPhoneField = loginSheet_->findChild<QObject*>("phone_number");
	QVariant userPhone = userPhoneField->property("text");

	QObject *userPinField = loginSheet_->findChild<QObject*>("user_pin");
	QVariant userPin = userPinField->property("text");

	// Execute authenicate call here


	QSharedPointer<ApiMethodBase> authCall(new Authenticate(userPhone.toString(), userPin.toString()));
	apiClient_->execute(authCall);

	bool authSucessful = (userPin.toString() == userPhone.toString()); // place holder
	if (authSucessful) {
		// store auth token
		loginSheet_->close();
	} else {
		//showAuthFailedToast();
	}
}

/*
void YouMailBB10::showAuthFailedToast() {
    SystemToast *toast = new SystemToast(this); // leak?
    toast->setBody("Authentication failed, please try again.");
    toast->show();
}
*/
