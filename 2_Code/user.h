// Base class implementing the "user" of the application. This abstract class
// implements some of the basic features required for the user such as personal
// details (username, email, etc.)
//
// Author: Archit Gupta
// Date: Dec 23, 2015

#ifndef __USER_H_INCLUDED__
#define __USER_H_INCLUDED__
    
#include <string>
#include <ncurses.h>

class User
{
    public:
        // Writing constructors for the class first
        User();
        User(std::string username);
        
        // getting the user name. Look into the requirement of other function
        // calls for this class
        std::string get_user_name();

    private:
        std::string m_user_name;
};
#endif
