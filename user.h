#ifndef USER_H
#define USER_H

#include <QString>

class User
{
protected:
    QString login;
    QString password;

public:
    User(QString l, QString p);
    virtual ~User();

    virtual QString getRole() const = 0;

    friend QString getUserLogin(const User& u);
    friend QString getUserPassword(const User& u);
};

#endif
