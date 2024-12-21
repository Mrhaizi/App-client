#ifndef WEBAPPWINDOW_H
#define WEBAPPWINDOW_H
#include <QMainWindow>
#include <QWebEngineView>
#include <QWebChannel>
#include "MyObject.h"
#include "Singleton2.hpp"

class WebAppWindow : public QMainWindow
{
    Q_OBJECT

public:
    WebAppWindow(QWidget *parent = nullptr);
    ~WebAppWindow();

private:
    QWebEngineView *web_view_;
    MyObject *my_object_;
    QWebChannel *channel_;

    void setupWebChannel();
    void injectJavaScript();
    void setupUi();
    void createActions();

private slots:
    void switchToApp1();
    void switchToApp2();
};

#endif // WEBAPPWINDOW_H
