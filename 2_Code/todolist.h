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
        void set_next_todo_entry(ToDoListEntry* entry);
        void set_prev_todo_entry(ToDoListEntry* entry);
        ToDoListEntry* get_prev_todo_entry(){ return prev_todo_entry; }
        ToDoListEntry* get_next_todo_entry(){ return next_todo_entry; }
        void remove_from_list();
        void print(WINDOW* win, int y_offset, bool highlight);
        void clear(WINDOW* win, int y_offset);
        void refresh(WINDOW* win, int y_offset, bool highlight);
        int get_message_length(){ return message_length; }
        void toggle_mark_unmark(){ m_done = !m_done; }
        void insert_text(WINDOW* win, int& cursor_y, int& cursor_x, char input_key);

    private:
        bool m_done;
        std::string m_todo_message;
        int message_length;     // This refers to the number of lines that will
                                // be required to print this todo-message
        unsigned cursor_y_position_from_top;
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
