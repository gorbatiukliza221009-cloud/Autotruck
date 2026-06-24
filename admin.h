#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User
{
public:
    Admin(QString l, QString p);

    QString getRole() const override;
};

#endif
