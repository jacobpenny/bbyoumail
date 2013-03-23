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
#include <QSettings>

#include "api/client/apiclient.h"
#include "api/method/apimethod.h"
#include "api/method/apimethodresponsehandler.h"
#include "storage/sqlstorage.h"

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
using ymbb10::api::ApiClient;


class YouMailBB10 : public QObject
{
Q_OBJECT

public slots:
    void responseMessage(ymbb10::api::method::ResponseMessage message);
    void handleLoginButtonClicked();
public:
    YouMailBB10(bb::cascades::Application *app);
    virtual ~YouMailBB10() {}

private:
    void showAuthFailedToast();
    bool haveCredentials();
    void onStart();
    void copyFileToDataFolder(const QString);

private:
    bb::cascades::Sheet *loginSheet_;
    ApiClient* apiClient_;
    QThread* pResponseHandlerThread_;
    ymbb10::api::method::ApiMethodResponseHandler* responseHandler_;
    ymbb10::storage::SqlStorage* sqlStorage_;
};


#endif /* YouMailBB10_HPP_ */
