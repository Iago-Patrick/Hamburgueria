#ifndef LAST_USER_H
#define LAST_USER_H

#include <QString>

class last_user
{
public:
    static last_user &get();
    void set_user(const QString &user);
    QString get_user() const;

private:
    last_user() = default;

    QString loged_user;
};

#endif // LAST_USER_H
