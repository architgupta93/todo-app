// Header file for the functionality related to display. This implements
// abstract classes and functions which will later be used by ncurses and GTK
// respectively for a console base implementation/GUI respectively
//
// Author: Archit Gupta
// Date: December 24, 2015

#ifndef __DISPLAY_H_INCLUDED__
#define __DISPLAY_H_INCLUDED__

#include "status-bar.h"
#include <string>
#include <ncurses.h>
#include <vector>

/* DisplayHandler is the main class responsible for displaying ToDo lists on the
 * screen. 
 * 1. It maintains a list of windows that should be displayed and refreshs
 * the overall layout as and when required.
 * 2. It maintains a pointer to the status bar window which displays the status
 * of operations being executed
 */
class DisplayHandler
{
    public:
        DisplayHandler();
        // Public Function: Initialize()
        // Initializes the main screen to be displayed as the application is
        // launched. Also shows the banner text splash.
        void initialize();

        // Public Function: refresh()
        // Refreshed the overall window layout.
        void refresh();

        // Public Function: terminate() [TODO: Make this protected maybe!]
        // Terminates the display program.
        void terminate();

        // Public Function: banner()
        // Clears the layout screen, takes a std::string as an input, and prints
        // it in the middle of the screeb.
        void banner(std::string message);

        // Public Function: setupStatusBar()
        void setupStatusBar();

        // Public Functions: getMAXX(), getMAXY()
        // Return the values for the class members MAX_X and MAX_Y
        int getMAXX() {return MAX_X;}
        int getMAXY() {return MAX_Y;}

        // Public Function(s): setupWindow(arguments)
        // These functions setup a new window in the display and return a
        // pointer to the newly created window.
        WINDOW* setupWindow();
        WINDOW* setupWindow(int height, int width, int starty, int startx);
        WINDOW* setupWindowWithFrame(int height, int width, int starty, int startx);

    protected:
        void printLineInMiddle(std::string line, int y_level);

    private:
        StatusBar* m_status_bar;
        static std::string banner_text;
        static int MAX_X, MAX_Y;    // Boundary values for the display
        static int d_x, d_y;        // Current cursor values
        std::vector<WINDOW*> m_windows;  // A vector of all the windows that are currently being displayed
};

#endif
