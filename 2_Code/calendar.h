/* Base class responsible for implementing the "calendar" in the application. Handling the backend of the calendar (managing entries, linking them with the todo-list entries etc.).

Author: Archit Gupta
Date: May 26, 2016
*/

#ifndef __CALENDAR_H_INCLUDED__
#define __CALENDAR_H_INCLUDED__

#include "definitions.h"
#include <ncurses.h>
#include <string>

// ENUM desciption for defining the day of the week

// Calendar entry class description
class CalendarEntry
{
    public:
        CalendarEntry();
    private:
        short date;
        short month;
        short year;
};

// Base class for a Calendar
class Calendar{

};

#endif
