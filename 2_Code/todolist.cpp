/* Base class implementing the "todo-List" in the application. This class is
responsible for handling the backend of a todo lists (functions like adding
an entry to the list, marking an entry as done or removing an entry from the
list)
                                                                           
Author: Archit Gupta                                
Date: Dec 23, 2015 
*/

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
    next_todo_entry = NULL;
    prev_todo_entry = NULL;
    cursor_y_position_from_top = 0;
    update_message_block_length();
}

void ToDoListEntry::update_message_block_length()
{
    if (!m_todo_message.empty())
    {
        int message_length_in_chars = m_todo_message.length();
        const int LINE_SIZE = (WRITABLE_X - X_OFFSET);
        message_block_length = (message_length_in_chars % LINE_SIZE == 0) ?
        message_length_in_chars/LINE_SIZE : 1 + message_length_in_chars/LINE_SIZE;
    } else {
        message_block_length = 1;
    }
}

void ToDoListEntry::print_multiline_message(WINDOW* win, int y_offset)
{
    size_t length = 0;  // Assume the default value of a string to be ""
    int original_y_offset = y_offset;
    const int print_step_size = WRITABLE_X - X_OFFSET;
    char print_block[print_step_size+1];
    size_t print_block_start_point = 0;
    size_t print_length_in_chars = (size_t) m_todo_message.length();
    while (print_length_in_chars > print_step_size)
    {
        length = m_todo_message.copy(print_block, print_step_size, print_block_start_point); 
        // This step copies (WRITABLE_X-OFFSET) characters into this array. Since the
        // first character is printed at x=X_OFFSET. NOTHING IS PRINT AT X =
        // WRITABLE_X
        print_block[length]='\0';
        print_block_start_point += print_step_size;
        print_length_in_chars -= print_step_size;
        mvwprintw(win, y_offset++, X_OFFSET, "%s", print_block);
    }
    length = m_todo_message.copy(print_block, print_length_in_chars, 
    print_block_start_point); 
    print_block[length]='\0';
    mvwprintw(win, y_offset, X_OFFSET, "%s", print_block);
    wmove(win, original_y_offset, X_OFFSET);
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
        print_multiline_message(win, y_offset);
        wattroff(win, A_STANDOUT);
    }
    else{
        print_multiline_message(win, y_offset);
    }
}

void ToDoListEntry::clear(WINDOW* win, int y_offset)
{
    int cursor_position = y_offset + message_block_length;
    // The todo-messsage begins at y_offset and ends at y_offset +
    // message_block_length-1. The condition used in the code below 
    // seems appropriate
    while(cursor_position > y_offset)
    {
        wmove(win, --cursor_position,  X_OFFSET);
        wclrtoeol(win);
    }
}

void ToDoListEntry::refresh(WINDOW* win, int y_offset, bool highlight)
{
    clear(win, y_offset);
    print(win, y_offset,  highlight);
}

bool ToDoListEntry::check_end_point(bool up_as_true)
{
    if (up_as_true)
    {
        if (cursor_y_position_from_top == 0)
        {
            return true;
        }
        return false;
    } 
    else {
        if (cursor_y_position_from_top == message_block_length-1){
            return true;
        }
        return false;
    }
}

void ToDoListEntry::update_cursor_position(WINDOW* win, int& cursor_y, int&
cursor_x, bool up_as_true)
{
    if (up_as_true)
    {
        if (cursor_y_position_from_top > 0)
        {
            cursor_y_position_from_top--;
            wmove(win, --cursor_y, cursor_x);
        }
    }
    else {
        cursor_y_position_from_top++;
        cursor_x = (cursor_x <= x_limit()) ? cursor_x : x_limit();
        wmove(win, ++cursor_y, cursor_x);
    }
}

ToDoListEntry* ToDoListEntry::insert_new_entry_above()
{
    return insert_new_entry_above("");
}

ToDoListEntry* ToDoListEntry::insert_new_entry_above(std::string todo_message)
{
    ToDoListEntry* inserted_entry = new ToDoListEntry(m_todo_message);
    inserted_entry->next_todo_entry = this;
    this->prev_todo_entry = inserted_entry;
    return inserted_entry;
}

ToDoListEntry* ToDoListEntry::insert_new_entry_below()
{
    return insert_new_entry_below("");
}

ToDoListEntry* ToDoListEntry::insert_new_entry_below(std::string todo_message)
{
    ToDoListEntry* inserted_entry = new ToDoListEntry(todo_message);
    inserted_entry->prev_todo_entry = this;
    this->next_todo_entry = inserted_entry;
    return inserted_entry;
}

void ToDoListEntry::remove_from_list()
{
    // This function removes a todo entry from the list by setting
    // the prev and next entries of its 'next' and 'prev' entries
    // respectively. Its simple. It only sounds tricky
    
    if (prev_todo_entry != NULL)
    {
        prev_todo_entry->next_todo_entry = this->next_todo_entry;
    }
    else {
        // This means that the entry we just deleted was the first entry in the
        // list. In this case, the prev_todo_entry for the next_todo_entry
        // should be set to NULL, which happens automatically in the next
        // statement
    }
    if (next_todo_entry != NULL)
    {
        next_todo_entry->prev_todo_entry = this->prev_todo_entry;
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

void ToDoListEntry::insert_text(WINDOW* win, int cursor_y, int cursor_x,
    char input_key)
{
    // I don't plan on keeping all the keys valid. The definitions.h file has
    // a description for the first and last ascii characters from the ASCII
    // table. These characters can be used in the INSERT mode. Nothing will
    // hapeen if you try to use any other keys/key-combinations. The only other
    // keys that are supported are BACKSPACE and DEL (also defined in the file
    // definitions.h

    unsigned position_wrt_string = cursor_y_position_from_top*(WRITABLE_X-X_OFFSET)
    + ((unsigned)cursor_x - X_OFFSET);
    if ((input_key >= (char) FIRST_WRITABLE_ASCII_CHAR) && 
        (input_key <= (char) LAST_WRITEABLE_ASCII_CHAR))
    {
        // Usage: string.insert(<where_to_insert>, <how_many_characters>, <>);
        m_todo_message.insert(position_wrt_string, 1, input_key);
        refresh(win, cursor_y-cursor_y_position_from_top, false);
    } 
    else if (input_key == (char) M_KEY_BACKSPACE)
    {
        if (position_wrt_string>0)
        {
            m_todo_message.erase(m_todo_message.begin()+position_wrt_string-1);
            refresh(win, cursor_y-cursor_y_position_from_top, false);
        }
    } 
    else if (input_key == (char) M_KEY_DELETE)
    {
        if (position_wrt_string<m_todo_message.length())
        {
            m_todo_message.erase(m_todo_message.begin()+position_wrt_string-1);
            refresh(win, cursor_y-cursor_y_position_from_top, false);
        }
    }
    update_message_block_length();
}

int ToDoListEntry::x_limit()
{
    if (cursor_y_position_from_top == message_block_length-1)
    {
        if (!m_todo_message.empty())
        {
            int chars_in_a_line = (WRITABLE_X - X_OFFSET);
            int message_length_in_chars = m_todo_message.length();
            return X_OFFSET-1+(message_length_in_chars % chars_in_a_line);
        }
        return X_OFFSET;
    }
    return WRITABLE_X;
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

void ToDoList::save_list(std::string filename){
    // Write all the todo-list entries into a file.
    try
    {
        // Try opening a file pipe to write the todo-list entries
    }
    catch (std::exception e)
    {
    
    }
}

bool ToDoList::load_list(std::string filename){
    // Save all the todo-list entries from a file.
    try
    {
        // If the file exists, try writing the todo-list entries into it.
    
    }
    catch (std::exception e)
    {
    
        return false;
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


    if (last_todo_entry != NULL)
    {
        assert(first_todo_entry != NULL);   // Insure that the first entry
                                            // doesn't point to NULL if the 
                                            // last entry doesn't point to NULL
       ToDoListEntry* new_entry = last_todo_entry->insert_new_entry_below(
       todo_message); 
       last_todo_entry = new_entry;
    }
    else {  
        assert(first_todo_entry == NULL);
        ToDoListEntry* new_entry = new ToDoListEntry(todo_message);
        first_todo_entry = new_entry;
        last_todo_entry = new_entry; 
    }

    // Rules to follow with this nomenclature:
    // next_todo_entry for the last_todo_entry is always NULL
    // last_todo_entry for the first_todo_entry is always NULL
}

ToDoListEntry* ToDoList::new_todo_entry(ToDoListEntry* entry)
{
    return new_todo_entry(entry, "");
}

ToDoListEntry* ToDoList::new_todo_entry(ToDoListEntry* entry, std::string
todo_message)
{
    // By calling this function, one can insert a ToDo entry BEFORE the "entry"
    // that has been passed as a function parameter
    ToDoListEntry* inserted_entry = entry->insert_new_entry_below(todo_message);
    if (entry == last_todo_entry)
    {
        last_todo_entry = inserted_entry;
    }
    return inserted_entry;
}

// Function definitions for the sample ToDoList class

SampleToDoList::SampleToDoList()
{
    new_todo_entry("Complete the ToDo Application");
    new_todo_entry("Generate the results for STEAM chapter in Masters thesis");
    //new_todo_entry("");
}
