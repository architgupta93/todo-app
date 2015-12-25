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
        void skip_me();

    protected:
        ToDoListEntry* next_todo_entry;
        ToDoListEntry* prev_todo_entry;

    private:
        bool m_done;
        std::string m_todo_message;
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

    private:
        ToDoListEntry* first_todo_entry;
        ToDoListEntry* last_todo_entry;
};

#endif
