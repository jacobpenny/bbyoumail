// Tabbed pane project template
#ifndef YouMailBB10_HPP_
#define YouMailBB10_HPP_

#include <QObject>
#include <bb/cascades/Sheet>

#include <bb/system/SystemDialog>
#include <bb/system/SystemListDialog>
#include <bb/system/SystemPrompt>
#include <bb/system/SystemCredentialsPrompt>
#include <bb/system/SystemToast>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiInputField>
#include <bb/system/SystemUiError>
#include <bb/system/SystemUiInputMode>
#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiPosition>
#include <bb/system/SystemUiResult>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "api/client/apiclient.h"

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class YouMailBB10 : public QObject
{
Q_OBJECT

public:
    YouMailBB10(bb::cascades::Application *app);
    virtual ~YouMailBB10() {}

public slots:
    void handleLoginButtonClicked();

private:
    void showAuthFailedToast();

private:
    bb::cascades::Sheet *loginSheet_;
    QNetworkAccessManager* mNetworkAccessManager;
    ymbb10::api::ApiClient* apiClient_;

};


#endif /* YouMailBB10_HPP_ */
