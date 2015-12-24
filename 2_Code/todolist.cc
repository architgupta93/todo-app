// Base class implementing the "todo-List" in the application. This class is
// responsible for handling the backend of a todo lists (functions like adding
// an entry to the list, marking an entry as done or removing an entry from the
// list)
//                                                                            
// Author: Archit Gupta                                
// Date: Dec 23, 2015 

#include "todolist.h"

// Function definitions for ToDoListEntry Class

ToDoListEntry::ToDoListEntry()
{
    m_done = false;
    m_todo_message = "";
    next_todo_entry = NULL;
    prev_todo_entry = NULL;
}

ToDoListEntry::ToDoListEntry(string todo_message):m_todo_message(todo_message)
{
    m_done = false;
    next_todo_entry = NULL;
    prev_todo_entry = NULL;
}

void ToDoListEntry::set_next_todo_entry(ToDoListEntry* entry)
{
    next_todo_entry = entry;
}

void ToDoListEntry::set_prev_todo_entry(ToDoListEntry* entry)
{
    prev_todo_entry = entry;
}

// Function definitions for ToDoList Class

ToDoList::ToDoList()
{
    first_todo_entry = NULL;
    last_todo_entry = NULL;
}

bool ToDoList::remove_todo_entry(ToDoListEntry* list_entry)
{
    try
    {
       list_entry.prev_todo_entry->set_next_todo_entry
           (list_entry.next_todo_entry);
       list_entry.next_todo_entry->set_prev_todo_entry
           (list_entry.prev_todo_entry);
    }
    catch (std::exception e)
    {

        return FAILURE;
    }
       
    return true;
}

void ToDoList::new_todo_entry(string todo_message)
{
    ToDoListEntry* new_entry = new ToDoListEntry(todo_message);
    last_todo_entry->set_next_todo_entry(new_entry);
    new_entry->set_prev_todo_entry(last_todo_entry);
}
