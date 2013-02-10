// Tabbed pane project template
#ifndef YouMailBB10_HPP_
#define YouMailBB10_HPP_

#include <QObject>

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
};

#endif /* YouMailBB10_HPP_ */