#include "client.h"

Client::Client(QString l, QString p)
    : User(l, p)
{
}

QString Client::getRole() const
{
    return "client";
}
