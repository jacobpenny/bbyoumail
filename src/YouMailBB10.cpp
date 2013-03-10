// Tabbed pane project template
#include "YouMailBB10.hpp"
#include "api/method/apimethod.h"
#include "api/method/apimethodresponsehandler.h"
#include "api/method/authenticate.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QtDebug>



using ymbb10::api::method::Authenticate;
//using ymbb10::api::method::ResponseMessage;
using ymbb10::api::method::ApiMethodBase;
using ymbb10::api::method::ApiMethodResponseHandler;


using namespace bb::cascades;
using namespace bb::system;



YouMailBB10::YouMailBB10(bb::cascades::Application *app) : QObject(app)
{
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	AbstractPane *root = qml->createRootObject<AbstractPane>();


	apiClient_ = new ymbb10::api::ApiClient("http://api.youmail.com/api", "youmailapp", app, this);

	ApiMethodResponseHandler* responseHandler = new ApiMethodResponseHandler; // should this be heap?

	// declare our enum so it works with slots

    qRegisterMetaType<ymbb10::api::method::ResponseMessage>("ymbb10::api::method::ResponseMessage");

	bool r1 = QObject::connect(responseHandler, SIGNAL(responseProcessed(ymbb10::api::method::ResponseMessage)),
			this, SLOT(responseMessage(ymbb10::api::method::ResponseMessage)));

	bool r2 = QObject::connect(apiClient_, SIGNAL(responseDeserialized(ymbb10::api::method::ApiMethodBase*)),
			responseHandler, SLOT(handleResponse(ymbb10::api::method::ApiMethodBase*)));


	Q_ASSERT(r1);
	Q_ASSERT(r2);

	pResponseHandlerThread_ = new QThread;
	responseHandler->moveToThread(pResponseHandlerThread_);

	pResponseHandlerThread_->start();

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
	/*
	bool authSucessful = (userPin.toString() == userPhone.toString()); // place holder
	if (authSucessful) {
		// store auth token
		loginSheet_->close();
	} else {
		//showAuthFailedToast();
		 *
	}
	*/
}

void YouMailBB10::responseMessage(ymbb10::api::method::ResponseMessage message) {
	qDebug() << message;
	if (message == ymbb10::api::method::AUTH_SUCCESS) {
		loginSheet_->close();
	}
}



void YouMailBB10::showAuthFailedToast() {
    SystemToast *toast = new SystemToast(this); // leak?
    toast->setBody("Authentication failed, please try again.");
    toast->show();
}


