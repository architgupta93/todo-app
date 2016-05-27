// Implementing various functions specified in the header file "display.h".
//
// Author: Archit Gupta
// Date: December 24, 2015

#include "display.h"
#include "assert.h"
#include <ncurses.h>
#include <sstream>

int DisplayHandler::MAX_X = 0;
int DisplayHandler::MAX_Y = 0;
int DisplayHandler::d_x = 0;
int DisplayHandler::d_y = 0;
std::string DisplayHandler::banner_text = "Welcome to the ToDo Application!\nPress any key to continue ...";

// Since these are static variables for this class, the compiler doesn't know
// where to place them (in the memory). If they were associated to any
// particular instance of this class, memory allocation would have been obvious.
// However, right now, for the compiler to be able to decide where to put these,
// it is necessary to allocate some value for them so that they can be allocated

DisplayHandler::DisplayHandler()
{

}

void DisplayHandler::initialize()
{
    initscr();
    assert(MAX_X == 0 && MAX_Y == 0);

    // Verifying that the class has been initialized (and this function is 
    // being called exactly once. Otherwise, MAX_X and MAX_Y would have been
    // set to the valuses from the screen
    
    getmaxyx(stdscr, MAX_Y, MAX_X);
    noecho();   // Stops getc() from printing text on the screen
    raw();      // The raw() function lets us read keyboard strokes before 
                // a line is completed (return is pressed) -- line buffering
    banner(banner_text);
    try{
        curs_set(0);    // Make the cursor invisible (I don't like the cursor) -__-
    }
    catch (std::exception e)
    {
        // TODO: Add message to be passed onto a log file. I think having a log
        // file is a nice idea for an kind of application, as long as you don't
        // dump a line into it every second or two
    }
    getch();    // The user can press any key to continue to the next window
    clear();    // Clearing the stdscr to be used by other windows
    refresh();  
}

void DisplayHandler::terminate()
{
    endwin();
}

void DisplayHandler::print_line_in_middle(std::string line, int y_level)
{   
    int string_length = line.length();
    int startx = (MAX_X-string_length)/2;
    mvprintw(y_level, startx, "%s", line.c_str());
}

WINDOW* DisplayHandler::setup_main_window()
{
    // Usage: setup_main_window(height, width, start_y, start_x)
    // This creates a window with the given specifications
    WINDOW* main_window = setup_window(MAX_Y, MAX_X, 0, 0);
    box(main_window, 0, 0);
    wrefresh(main_window);
    return main_window;
}

WINDOW* DisplayHandler::setup_window(int height, int width, int starty, int startx)
{
    WINDOW* current_window = newwin(height, width, starty, startx);

    // The steps mentioned above only modify the internal data structures. In
    // order to actually modify what is hwon on the screen, we need to call the
    // refresh window function which updates the contents on the screen as well

    wrefresh(current_window);
    return current_window;
}

void DisplayHandler::banner(std::string message)
{
    // The string in our banner could consist of multiple lines. We want to
    // print this block of data exactly in the middle of our screen. The
    // simplest way to do this is to count the number of lines and arrange their
    // y coordinates accordingly. Then, each line gets printed by aligning its
    // center with the center of the page
    
    // const char* test_message = "Another piece of random text";
    // The initial idea was to use std::string to make the implementation
    // convenient. However, it seems that ncurses do not support std::string in
    // their implementation yet. Will have to stick to const char* for now
    // mvprintw(2,2,"%s", message.c_str());
   
    int line_count = 0;
    std::istringstream string_buffer;
    std::string line;
    string_buffer.str(message);
    while(getline(string_buffer, line))
    {
        line_count++;
    }

    // mvprintw(0,3,"Printing %d lines in total", line_count);
    // print_line_in_middle("Printing 2 lines in total", 0);

    int y_level = (MAX_Y - line_count)/2;
    string_buffer.clear();

    // The string stream object maintains an internal set of variables which
    // keep track of its state. These variables, for an instance, track things
    // like EOF etc. Since we reached end of file in the last use of this
    // object, we need to clear() the state variables before reusing the object

    string_buffer.str(message);
    while(getline(string_buffer, line))
    {
        print_line_in_middle(line, y_level++);
    }

}

