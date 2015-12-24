// Base class implementing the "user" of the application. This abstract class
// implements some of the basic features required for the user such as personal
// details (username, email, etc.)
//
// Author: Archit Gupta
// Date: Dec 23, 2015

#include "user.h"

User::User()
{
    m_user_name = "";
    comment("WARNING: No username assigned. Please ensure that we are 
            running DEBUG MODE");
}

User::User(string username):m_user_name(username)
{
    comment("User %s created", username);
}

string User::get_user_name()
{
    return m_user_name;
}
