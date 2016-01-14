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

enum PreviewMode{
    VISUAL,
    EDIT,
    INSERT
};

char valid_keystroke(DisplayHandler* display, char input);

class ListPreviewManager
{
    public:
        ListPreviewManager();
        ListPreviewManager(WINDOW* win, ToDoList* td);
        void print_todo_list_in_window(ToDoListEntry* first_entry_to_print);
        bool exit_signal(){ return m_exit_signal; }
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

    private:
        WINDOW* list_window;    // Window in which this list will be displayed
        ToDoList* td_list;      // The todo list whose preview is being managed
                                // by this manager
        ToDoListEntry* entry_under_cursor;
        PreviewMode m_mode;
        bool m_exit_signal;
        int m_cursor_x, m_cursor_y;
};

#endif
