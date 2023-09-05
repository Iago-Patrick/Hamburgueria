#include "last_user.h"

last_user& last_user::get()
{
    static last_user set;

    return set;
}

void last_user::set_user(const QString &user)
{
    loged_user = user;
}

QString last_user::get_user() const
{
    return loged_user;
}
