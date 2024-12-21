#ifndef WEBAPPHTPPMANAGER_H
#define WEBAPPHTPPMANAGER_H
#include "BaseHttpManager.h"
#include "Singleton2.hpp"
#include <qtmetamacros.h>

class WebAppHttpManager : public BaseHttpManager, public Singleton2<WebAppHttpManager> {
    Q_OBJECT
    friend class Singleton2<WebAppHttpManager>;
public:
    ~WebAppHttpManager();
private:
    WebAppHttpManager();
signals:

};
#endif // WEBAPPHTPPMANAGER_H

