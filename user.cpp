#include "user.h"

User::User(QString l, QString p)
{
    login = l;
    password = p;
}

User::~User()
{
}

QString getUserLogin(const User& u)
{
    return u.login;
}

QString getUserPassword(const User& u)
{
    return u.password;
}
