// Base class implementing the "todo-List" in the application. This class is
// responsible for handling the backend of a todo lists (functions like adding
// an entry to the list, marking an entry as done or removing an entry from the
// list)
//                                                                             
// Author: Archit Gupta                                                        
// Date: Dec 23, 2015 

#ifndef __TODOLIST_H_INCLUDED__
#define __TODOLIST_H_INCLUDED__

#include "definitions.h"
#include <ncurses.h>
#include <string>

class ToDoListEntry
{
    public:
        // Writing constructors for the class first
        ToDoListEntry();
        ToDoListEntry(std::string todo_message);

        // Functions for setting up the pointers for next and previous elements
        // in a doubly linked list
        ToDoListEntry* insert_new_entry_above();
        ToDoListEntry* insert_new_entry_below();
        ToDoListEntry* get_prev_todo_entry(){ return prev_todo_entry; }
        ToDoListEntry* get_next_todo_entry(){ return next_todo_entry; }
        void remove_from_list();
        void print(WINDOW* win, int y_offset, bool highlight);
        void print_multiline_message(WINDOW* win, int y_offset);
        void clear(WINDOW* win, int y_offset);
        void refresh(WINDOW* win, int y_offset, bool highlight);
        int get_message_block_length(){ return message_block_length; }
        void toggle_mark_unmark(){ m_done = !m_done; }
        void insert_text(WINDOW* win, int& cursor_y, int& cursor_x, char input_key);
        int x_limit();  // Gives the max value that the cursor can
                                    // move to in the x direction, when on this
                                    // entry for each y coordinate
        bool check_end_point(bool up_as_true);
                        // Give the endpoint which has to be checked (upper end
                        // given in as true and lower end given in as false.
                        // Used to check if an up/down keystroke has reached the
                        // end of the entry, in which case, a new entry should
                        // be switched to. This also updates the internal cursor
                        // trackers (increases/decreases them by 1 as required)
        void set_cursor_bottom(){ cursor_y_position_from_top = message_block_length-1; }
        void set_cursor_top(){ cursor_y_position_from_top = 0; }
        void update_cursor_position(WINDOW* win, int& cursor_y, int&
cursor_x, bool up_as_true);

    protected:
        void update_message_block_length(); // Internal function

    private:
        bool m_done;
        std::string m_todo_message;
        int message_block_length;   // This refers to the number of lines that will
                                    // be required to print this todo-message
        int cursor_y_position_from_top;
                                // While in the edit mode, this variable tells
                                // us the y coordinate of the cursor wrt the
                                // first line of the todo-list entry (needed for
                                // adding content to m_todo_string)
        ToDoListEntry* next_todo_entry;
        ToDoListEntry* prev_todo_entry;
};

class ToDoList
{
    public:
        // Setting up constructors. Not sure if specialized constructors would
        // be required for our application
        ToDoList();

        // functionality for adding and removing items from the ToDoList
        void new_todo_entry(std::string todo_message);
        ToDoListEntry* new_todo_entry(ToDoListEntry* entry);
        bool remove_todo_entry(ToDoListEntry* list_entry);
        ToDoListEntry* get_list_top(){ return first_todo_entry; }

    private:
        ToDoListEntry* first_todo_entry;
        ToDoListEntry* last_todo_entry;
};

class SampleToDoList : public ToDoList
{
    // This class serves as an example for testing and verification purposes. We
    // will assign static todo items than can be used to test displaying
    // contents on screen, navigating through to-do items etc.

    public:
        SampleToDoList();
};

#endif
