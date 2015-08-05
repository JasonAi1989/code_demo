#include <QtGui>
#include "login.h"

MyLogin::MyLogin(QWidget *parent)
:QDialog(parent)
{
    QLabel* usrLabel = new QLabel(tr("用户名:"));
    QLabel* pwdLabel = new QLabel(tr("密  码:"));

    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);

    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(usrLabel, 0, 0, 1, 1); 
    gridLayout->addWidget(usrLineEdit, 0, 1, 1, 3); 
    gridLayout->addWidget(pwdLabel, 1, 0, 1, 1); 
    gridLayout->addWidget(pwdLineEdit, 1, 1, 1, 3); 

    QPushButton* okBtn = new QPushButton(tr("确定"));
    QPushButton* cancleBtn = new QPushButton(tr("取消"));
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancleBtn);

    QVBoxLayout* dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(40);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addLayout(btnLayout);
    setLayout(dlgLayout);   //it is must!!

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancleBtn, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("登录"));
    resize(300, 200);
}

void MyLogin::accept()
{
    if(usrLineEdit->text().trimmed() == tr("lcf") \
        && pwdLineEdit->text() == tr("lcf")) 
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("用户或密码错误!"), QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}
