// Base class implementing the "user" of the application. This abstract class
// implements some of the basic features required for the user such as personal
// details (username, email, etc.)
//
// Author: Archit Gupta
// Date: Dec 23, 2015

#ifndef __USER_H_INCLUDED__
#define __USER_H_INCLUDED__
    
#include <string.h>
class User
{
    public:
        // Writing constructors for the class first
        User();
        User(string username);
        
        // getting the user name. Look into the requirement of other function
        // calls for this class
        string get_user_name();

    private:
        string m_user_name;
};
#endif
