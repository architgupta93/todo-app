// Header file for handling the system ls (keystrokes etc.) and exercising
// different functions available from other classes/files
//
// Author: Archit Gupta, Nehal Bhandari
// Date december 24, 2015

#ifndef __PROCESS_H_INCLUDED__
#define __PROCESS_H_INCLUDED__

#include "display.h"
#include "user.h"
#include "todolist.h"
#include "definitions.h"
#include <ncurses.h>

enum PreviewMode{
    VISUAL,
    EDIT,
    INSERT
};

char valid_keystroke(DisplayHandler* display, char input);

class PreviewManager
{
    public:
        PreviewManager();
        bool exit_signal() { return m_exit_signal; }

    protected:      // Can be accessed by functions of child classes
        WINDOW* win;            // Window in which this list class will be displayed
        PreviewMode m_mode;
        bool m_exit_signal;
        int m_cursor_y;
        int m_cursor_x;
};

class ListPreviewManager : public PreviewManager
{
    public:
        ListPreviewManager();
        ListPreviewManager(WINDOW* _win, ToDoList* td);
        void print_todo_list_in_window(ToDoListEntry* first_entry_to_print);
        void process(char input);

    protected:
        void move_cursor_left();
        void move_cursor_right();
        void move_cursor_up();
        void move_cursor_down();
        void switch_to_edit_mode();
        void switch_to_visual_mode();
        void switch_to_insert_mode();
        void two_tap_delete();
        void toggle_mark_unmark();
        void two_tap_quit();
        void step_modes_back();
        void add_todo_entry();

    private:
        ToDoList* td_list;      // The todo list whose preview is being managed
                                // by this manager
        ToDoListEntry* entry_under_cursor;
};

#endif
