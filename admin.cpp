#include "admin.h"

Admin::Admin(QString l, QString p)
    : User(l, p)
{
}

QString Admin::getRole() const
{
    return "admin";
}
