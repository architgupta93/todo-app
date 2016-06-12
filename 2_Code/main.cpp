// This is the main file that intializes the app and sets up the basic data
// structures required for tis functionality
//
// Author: Archit Gupta
// Date: December 24, 2015

#include "display.h"
#include "user.h"
#include "todolist.h"
#include "process.h"
#include <string>
#include <ncurses.h>

int main(int argc, char** argv)
{
    DisplayHandler* m_display = new DisplayHandler();
    m_display->initialize();

    // Testing display and keystrokes with the SampleToDoLIst class

    SampleToDoList test;
    ToDoList *pTest = &test;    // We are using the upcasting operation here.
                                // This seems to be an interesting operation.

    // Interestingly, the constructors, destructors and the eqwuality operator
    // are not ingerited by a subclass by default

    int MAX_X, MAX_Y;   // Getting bound values for the window
    MAX_X = m_display->get_MAX_X();
    MAX_Y = m_display->get_MAX_Y();
    m_display->setup_status_bar();
    WINDOW* boundingBox = m_display->setup_window();
    WINDOW* baseList = m_display->setup_window(MAX_Y-2, MAX_X-2, 1, 1);
    ListPreviewManager lp(baseList, pTest);
    lp.print_todo_list_in_window(pTest->get_list_top());
    while(!lp.exit_signal())
        lp.process(wgetch(baseList));
    m_display->terminate();
    return 0;
}
