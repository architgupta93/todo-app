// Base class implementing the "todo-List" in the application. This class is
// responsible for handling the backend of a todo lists (functions like adding
// an entry to the list, marking an entry as done or removing an entry from the
// list)
//                                                                            
// Author: Archit Gupta                                
// Date: Dec 23, 2015 

#include "todolist.h"
#include <assert.h>

// Function definitions for ToDoListEntry Class

ToDoListEntry::ToDoListEntry()
{
    ToDoListEntry("");
}

ToDoListEntry::ToDoListEntry(std::string todo_message):
    m_todo_message(todo_message)
{
    m_done = false;
    int message_length_in_chars = todo_message.length();
    message_length = (message_length_in_chars % MAX_X == 0) ?
    message_length_in_chars/((int) MAX_X) : 1 + message_length_in_chars/((int)
    MAX_X);
    next_todo_entry = NULL;
    prev_todo_entry = NULL;
    cursor_y_position_from_top = 0;
}

void ToDoListEntry::print(WINDOW* win, int y_offset, bool highlight)
{
    // Functions in this class only update the internal data structures in the
    // WINDOW class. The refresh of the screen is handled by ListPreviewManager.
    // We should not have any wrefresh operations here. This is done so that the
    // latter class can handle multiple internal changes before actually
    // displaying them on the screen.
    if(highlight)
    {
        wattron(win, A_STANDOUT);
        mvwprintw(win, y_offset, X_OFFSET, "%s", m_todo_message.c_str());
        wattroff(win, A_STANDOUT);
    }
    else{
        mvwprintw(win, y_offset, X_OFFSET, "%s", m_todo_message.c_str());
    }
    wmove(win, y_offset, X_OFFSET);
}

void ToDoListEntry::clear(WINDOW* win, int y_offset)
{
    wmove(win, y_offset, X_OFFSET);
    wclrtoeol(win);
}

void ToDoListEntry::refresh(WINDOW* win, int y_offset, bool highlight)
{
    clear(win, y_offset);
    print(win, y_offset,  highlight);
}

void ToDoListEntry::set_next_todo_entry(ToDoListEntry* entry)
{
    next_todo_entry = entry;
}

void ToDoListEntry::set_prev_todo_entry(ToDoListEntry* entry)
{
    prev_todo_entry = entry;
}

void ToDoListEntry::remove_from_list()
{
    // This function removes a todo entry from the list by setting
    // the prev and next entries of its 'next' and 'prev' entries
    // respectively. Its simple. It only sounds tricky
    
    if (prev_todo_entry != NULL)
    {
        prev_todo_entry->set_next_todo_entry(next_todo_entry);
    }
    else {
        // This means that the entry we just deleted was the first entry in the
        // list. In this case, the prev_todo_entry for the next_todo_entry
        // should be set to NULL, which happens automatically in the next
        // statement
    }
    if (next_todo_entry != NULL)
    {
        next_todo_entry->set_prev_todo_entry(prev_todo_entry);
    }
    else {
        // This means that this entry was the last entry in the list. What
        // should happen in this case has been handled in the previous if/else
        // block. The only tricky part is the case when this happens to be the
        // only entry in the list. In that case, we don't really have any
        // pointers to update. TODO: Keep in mind that this instance has to be
        // erased and the first/last entries of the list have to be updated
        // whenever this function is called
    }
}

void ToDoListEntry::insert_text(WINDOW* win, int& cursor_y, int& cursor_x,
    char input_key)
{
    // I don't plan on keeping all the keys valid. The definitions.h file has
    // a description for the first and last ascii characters from the ASCII
    // table. These characters can be used in the INSERT mode. Nothing will
    // hapeen if you try to use any other keys/key-combinations. The only other
    // keys that are supported are BACKSPACE and DEL (also defined in the file
    // definitions.h

    unsigned position_wrt_string = cursor_y_position_from_top*MAX_X + 
    ((unsigned)cursor_x - X_OFFSET);
    if ((input_key >= (char) FIRST_WRITABLE_ASCII_CHAR) && (input_key <= (char)
LAST_WRITEABLE_ASCII_CHAR))
    {
        // Usage: string.insert(<where_to_insert>, <how_many_characters>, <>);
        m_todo_message.insert(position_wrt_string, 1, input_key);
        refresh(win, cursor_y-cursor_y_position_from_top, false);
        wmove(win, cursor_y, ++cursor_x);
    } 
    else if (input_key == (char) M_KEY_BACKSPACE)
    {
        if (position_wrt_string>0)
        {
            m_todo_message.erase(m_todo_message.begin()+position_wrt_string-1);
            refresh(win, cursor_y-cursor_y_position_from_top, false);
            wmove(win, cursor_y, --cursor_x);
        }
    } 
    else if (input_key == (char) M_KEY_DELETE)
    {
        m_todo_message.erase(m_todo_message.begin()+position_wrt_string-1);
        refresh(win, cursor_y-cursor_y_position_from_top, false);
    }
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
        list_entry->remove_from_list();
        if (list_entry->get_prev_todo_entry() == NULL)
        {
            assert(list_entry == first_todo_entry);
            first_todo_entry = list_entry->get_next_todo_entry();
        }
        if (list_entry->get_next_todo_entry() == NULL)
        {
            assert(list_entry == last_todo_entry);
            last_todo_entry = list_entry->get_prev_todo_entry();
        }
        // The reasoning for the above if blocks is in described in the
        // functions: ToDoList::new_todo_entry(std::String todo_message) and
        // ToDoListEntry::remove_from_list()

        delete list_entry;
    }
    catch (std::exception e)
    {
        return FAILURE;
    }
       
    return true;
}

void ToDoList::new_todo_entry(std::string todo_message)
{
    // If the todo-list is empty at this point, both first and last entries
    // point to NULL. As soon as the first entry is inserted, we will set both
    // the first and last entries to point to this newly inserted entry. This
    // new entry should have both next and prev entries set to null. It can only
    // be accessed as the top entry of the list

    ToDoListEntry* new_entry = new ToDoListEntry(todo_message);

    if (last_todo_entry != NULL)
    {
        assert(first_todo_entry != NULL);   // Insure that the first entry
                                            // doesn't point to NULL if the 
                                            // last entry doesn't point to NULL
        last_todo_entry->set_next_todo_entry(new_entry);
        new_entry->set_prev_todo_entry(last_todo_entry);
    }
    else {  
        assert(first_todo_entry == NULL);
        first_todo_entry = new_entry;
        last_todo_entry = new_entry; 
    }

    // Rules to follow with this nomenclature:
    // next_todo_entry for the last_todo_entry is always NULL
    // last_todo_entry for the first_todo_entry is always NULL
}

// Function definitions for the sample ToDoList class

SampleToDoList::SampleToDoList()
{
    new_todo_entry("Complete the ToDo Application");
    new_todo_entry("Continue work on statistical mechanics");
}
