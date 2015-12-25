// This is the main file that intializes the app and sets up the basic data
// structures required for tis functionality
//
// Author: Archit Gupta
// Date: December 24, 2015

#include "definitions.h"
#include "display.h"
#include "user.h"
#include "todolist.h"
#include "process.h"
#include <string>

int main(int argc, char** argv)
{
    std::string banner_text = "Welcome to the ToDo Application!\nPress any key to continue ...";
    DisplayHandler* m_display = new DisplayHandler();
    m_display->initialize();
    m_display->banner(banner_text);
    while(valid_keystroke(m_display, getch()))
    {

    }
    m_display->terminate();
    return 0;
}
