// Header file for the functionality related to display. This implements
// abstract classes and functions which will later be used by ncurses and GTK
// respectively for a console base implementation/GUI respectively
//
// Author: Archit Gupta
// Date: December 24, 2015

#include <string>

class DisplayHandler
{
    public:
        DisplayHandler();
        void initialize();
        void terminate();
        void banner(std::string message);
        void print_line_in_middle(std::string line, int y_level);

    private:
        static int MAX_X, MAX_Y;    // Boundary values
        static int d_x, d_y;        // Current values
};
