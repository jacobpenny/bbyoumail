// Tabbed pane project template
#include "YouMailBB10.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>


using namespace bb::cascades;
using namespace bb::system;

YouMailBB10::YouMailBB10(bb::cascades::Application *app) : QObject(app)
{
	// create scene document from main.qml asset
	// set parent to created document to ensure it exists for the whole application lifetime
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

	// create root object for the UI
	AbstractPane *root = qml->createRootObject<AbstractPane>();
	// set created root object as a scene
	app->setScene(root);

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
}


void YouMailBB10::handleLoginButtonClicked()
{
	QObject *userPhoneField = loginSheet_->findChild<QObject*>("phone_number");
	QVariant userPhone = userPhoneField->property("text");

	QObject *userPinField = loginSheet_->findChild<QObject*>("user_pin");
	QVariant userPin = userPinField->property("text");

	// Execute authenicate call here

	bool authSucessful = (userPin.toString() == userPhone.toString()); // place holder
	if (authSucessful) {
		// store auth token
		loginSheet_->close();
	} else {
		showAuthFailedToast();
	}
}

void YouMailBB10::showAuthFailedToast() {
    SystemToast *toast = new SystemToast(this); // leak?
    toast->setBody("Authenication failed, please try again.");
    toast->show();
}
