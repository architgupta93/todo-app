/* CPP file for implementing the functions described in the header file for the status-bar object

Author: Archit Gupta
Date: May 26, 2016
*/

#include "status-bar.h"
#include "process.h"

StatusBar::StatusBar()
{
    win = NULL;
    currentList = NULL;
    currentListEntry = NULL;
    currentListMode = VISUAL;
}

StatusBar::StatusBar(WINDOW* _win)
{
    win = _win;
    currentListMode = VISUAL;
    initialize();
}

void StatusBar::initialize()
{
    std::string statusBarBanner = "Welcome! This is the status bar.";
    print(statusBarBanner);
    return;
}

void StatusBar::clear()
{
    wclear(win);
    refresh();
}

void StatusBar::print(std::string& print_message)
{
    mvwprintw(win, Y_OFFSET, X_OFFSET, "%s", print_message.c_str()); 
    wmove(win, Y_OFFSET, X_OFFSET);
    refresh();  // Print the message and update the window
}

void StatusBar::refresh()
{
    wrefresh(win);  // Basic function that might be required
}

void StatusBar::update_list_entry(ToDoListEntry* cListEntry)
{
    currentListEntry = cListEntry;
}

void StatusBar::update_list(ToDoList* cList)
{
    currentList = cList;
}

void StatusBar::set_mode(PreviewMode mode)
{
    currentListMode = mode;
}
