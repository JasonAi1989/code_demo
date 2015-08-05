#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <QDialog>

class QLineEdit;
class MyLogin : public QDialog
{
    Q_OBJECT
public:
    MyLogin(QWidget* parent=NULL);
public slots:
    virtual void accept();
private:
    QLineEdit* usrLineEdit;
    QLineEdit* pwdLineEdit;
};
#endif
