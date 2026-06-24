#ifndef CLIENT_H
#define CLIENT_H

#include "user.h"

class Client : public User
{
public:
    Client(QString l, QString p);

    QString getRole() const override;
};

#endif
