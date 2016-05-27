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

StatusBar::StatusBar(WINDOW* parentWindow)
{
    win = parentWindow;
    currentListMode = VISUAL;
}

bool StatusBar::print()
{

}

bool StatusBar::refresh()
{

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
