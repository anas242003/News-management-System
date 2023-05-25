#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "loadandstore.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class LoginPage : public QWidget

{
    Q_OBJECT

public:
    LoginPage(loadAndStoreFiles* tool, bool fromMain = false,QWidget* parent = nullptr);

    ~LoginPage();

    void login();
    void registerUser();

    void savaAndClose();

private:

    Ui::Widget *ui;

    QLineEdit* username;
    QLineEdit* password;
    loadAndStoreFiles* tool;
  
};

#endif // LOGINPAGE_H
