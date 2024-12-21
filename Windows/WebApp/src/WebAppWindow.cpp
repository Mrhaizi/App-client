#include "WebAppWindow.h"
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineSettings>
#include <QVBoxLayout>
#include <QFile>
#include <QMenuBar>
#include <QAction>
#include <QWebEngineScriptCollection>

WebAppWindow::WebAppWindow(QWidget *parent)
    : QMainWindow(parent),
      web_view_(new QWebEngineView(this)),
      my_object_(new MyObject(this)),
      channel_(new QWebChannel(this))
{
    setupUi();
    setupWebChannel();
    injectJavaScript();

    // 加载初始网页
    web_view_->load(QUrl("http://localhost:8000/app1.html"));
    web_view_->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    web_view_->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
}

WebAppWindow::~WebAppWindow()
{
}

void WebAppWindow::setupUi()
{
    setCentralWidget(web_view_);
    createActions();
}

void WebAppWindow::createActions()
{
    QMenu *menu = menuBar()->addMenu(tr("切换应用"));

    QAction *app1_action = new QAction(tr("小程序 1"), this);
    connect(app1_action, &QAction::triggered, this, &WebAppWindow::switchToApp1);
    menu->addAction(app1_action);

    QAction *app2_action = new QAction(tr("小程序 2"), this);
    connect(app2_action, &QAction::triggered, this, &WebAppWindow::switchToApp2);
    menu->addAction(app2_action);
}

void WebAppWindow::switchToApp1()
{
    web_view_->load(QUrl("http://localhost:8000/app1.html"));
}

void WebAppWindow::switchToApp2()
{
    web_view_->load(QUrl("http://localhost:8000/app2.html"));
}

void WebAppWindow::setupWebChannel()
{
    // 注册对象到 WebChannel
    channel_->registerObject(QStringLiteral("qtObject"), my_object_);
    // channel_->registerObject(QStringLiteral("singleton"), &Singleton::getInstance());

    // 设置 WebChannel 到页面
    web_view_->page()->setWebChannel(channel_);

    // // 连接信号槽
    // connect(&Singleton::getInstance(), &Singleton::sendToJs, [=](const QString &message) {
    //     QString script = QString("window.receiveFromQt('%1');").arg(message);
    //     web_view_->page()->runJavaScript(script);
    // });
}

void WebAppWindow::injectJavaScript()
{
    // 读取 qwebchannel.js 文件内容
    QFile file(":/qtwebchannel/qwebchannel.js");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开 qwebchannel.js 文件";
        return;
    }
    QString qwebchannel_js = file.readAll();
    file.close();

    // 创建用于注入的 JavaScript
    QString injectedJavaScript = qwebchannel_js + R"(
        (function() {
            new QWebChannel(qt.webChannelTransport, function(channel) {
                window.qtObject = channel.objects.qtObject;
            });
        })();
    )";
    // 创建 QWebEngineScript 对象
    QWebEngineScript script;
    script.setName("QWebChannel Script");
    script.setSourceCode(injectedJavaScript);
    script.setInjectionPoint(QWebEngineScript::DocumentCreation);
    script.setWorldId(QWebEngineScript::MainWorld);
    script.setRunsOnSubFrames(true);
    // 将脚本添加到页面中
    web_view_->page()->scripts().insert(script);
}
