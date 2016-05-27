// Header file for the functionality related to display. This implements
// abstract classes and functions which will later be used by ncurses and GTK
// respectively for a console base implementation/GUI respectively
//
// Author: Archit Gupta
// Date: December 24, 2015

#ifndef __DISPLAY_H_INCLUDED__
#define __DISPLAY_H_INCLUDED__

#include <string>
#include <ncurses.h>

class DisplayHandler
{
    public:
        DisplayHandler();
        void initialize();
        void terminate();
        void banner(std::string message);
        void print_line_in_middle(std::string line, int y_level);
        int get_MAX_X() {return MAX_X;}
        int get_MAX_Y() {return MAX_Y;}
        WINDOW* setup_main_window();
        WINDOW* setup_window(int height, int width, int starty, int startx);

    private:
        static std::string banner_text;
        static int MAX_X, MAX_Y;    // Boundary values
        static int d_x, d_y;        // Current values
        WINDOW* main_window;        // This is the main window that will
                                    // display all the todo information
};

#endif
