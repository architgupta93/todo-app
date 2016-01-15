// Implementing the functionality for system calls (keystrokes etc.) and
// exercising different functions available from other classes/files
//
// Author: Archit Gupta, Nehal Bhandari
// Date: December 24, 2015

#include "process.h"

char valid_keystroke(DisplayHandler* display, char input)
{
    if ((input <= 'z' && input >= 'a') || (input <= 'Z' && input >= 'A'))
    {
        return 0;
    }
    return input;    
}

ListPreviewManager::ListPreviewManager()
{
    ListPreviewManager(NULL, NULL);
}

ListPreviewManager::ListPreviewManager(WINDOW *win, ToDoList *td)
{
    list_window  = win;
    td_list = td;
    if (td_list != NULL)
    {
        entry_under_cursor = td->get_list_top();
    }
    m_mode = VISUAL;
    m_exit_signal = false;
    m_cursor_y = Y_OFFSET;
    m_cursor_x = X_OFFSET;
}

void ListPreviewManager::print_todo_list_in_window(ToDoListEntry*
first_entry_to_print)
{
    int initial_y_cursor = m_cursor_y;
    while(first_entry_to_print != NULL)
    {
        first_entry_to_print->print(list_window, m_cursor_y,
            first_entry_to_print == entry_under_cursor);
        m_cursor_y += first_entry_to_print->get_message_length();
        first_entry_to_print = first_entry_to_print->get_next_todo_entry();
    }
    m_cursor_y = initial_y_cursor;
    wrefresh(list_window);
}

void ListPreviewManager::process(char input)
{
    switch (input)
    {
        #define F_DEF(INPUT, FUNCTION, NON_FUNC_MODE)\
            case INPUT:\
                if (m_mode == NON_FUNC_MODE)\
                {\
                   entry_under_cursor->insert_text(list_window, m_cursor_y,\
                     m_cursor_x, INPUT);\
                    wrefresh(list_window);\
                } else {\
                    FUNCTION(); \
                }  break;
        #include "keystrokes.def"
        #undef F_DEF
        default:
            entry_under_cursor->insert_text(list_window, m_cursor_y, m_cursor_x, 
                input);
            wrefresh(list_window);
            // TODO: Add another window to the screen that flashes text messages
            // when a known/unknow key is pressed, saying what the key does
            break;
    }   
}

// Key stroke related functions have been described here

void ListPreviewManager::move_cursor_left(){
    if (m_mode == EDIT)
    {
        wmove(list_window, m_cursor_y, --m_cursor_x);
        wrefresh(list_window);
    }
}

void ListPreviewManager::move_cursor_right(){
    if (m_mode == EDIT)
    {
        wmove(list_window, m_cursor_y, ++m_cursor_x);
        wrefresh(list_window);
    }
}

void ListPreviewManager::move_cursor_up(){
    if(entry_under_cursor->get_prev_todo_entry() != NULL)
    {
        if (m_mode == VISUAL)
        {
            entry_under_cursor->refresh(list_window, m_cursor_y, false);
            entry_under_cursor = entry_under_cursor->get_prev_todo_entry();
            m_cursor_y -= entry_under_cursor->get_message_length();
            entry_under_cursor->refresh(list_window, m_cursor_y, true);
            wrefresh(list_window);
        }
        else if (m_mode == EDIT)
        {
            entry_under_cursor = entry_under_cursor->get_prev_todo_entry();
            m_cursor_y -= entry_under_cursor->get_message_length();
            wmove(list_window, m_cursor_y, m_cursor_x); 
            wrefresh(list_window);
        }
    }

}

void ListPreviewManager::move_cursor_down(){
    if(entry_under_cursor->get_next_todo_entry() != NULL)
    {
        if (m_mode == VISUAL)
        {
            entry_under_cursor->refresh(list_window, m_cursor_y, false);
            m_cursor_y += entry_under_cursor->get_message_length();
            entry_under_cursor = entry_under_cursor->get_next_todo_entry();
            entry_under_cursor->refresh(list_window, m_cursor_y, true);
            wrefresh(list_window);
        }
        else if (m_mode == EDIT)
        {
            m_cursor_y += entry_under_cursor->get_message_length();
            entry_under_cursor = entry_under_cursor->get_next_todo_entry();
            wmove(list_window, m_cursor_y, m_cursor_x);
            wrefresh(list_window);
        }
    }
}

void ListPreviewManager::switch_to_edit_mode(){
    if (m_mode == VISUAL)
    {
        m_mode = EDIT;
        curs_set(m_mode);
        entry_under_cursor->refresh(list_window, m_cursor_y, false);
        wmove(list_window, m_cursor_y, X_OFFSET);
        wrefresh(list_window);
    }
}

void ListPreviewManager::switch_to_visual_mode(){
    m_mode = VISUAL;
    curs_set(m_mode);
    entry_under_cursor->refresh(list_window, m_cursor_y, true);
    wrefresh(list_window);
}

void ListPreviewManager::switch_to_insert_mode(){
    m_mode = INSERT;
    curs_set(m_mode);
    entry_under_cursor->refresh(list_window, m_cursor_y, false);
    wmove(list_window, m_cursor_y, m_cursor_x);
    wrefresh(list_window);
}

void ListPreviewManager::two_tap_delete(){
    char repeat = getch();
    if (repeat == 'd')
    {
        ToDoListEntry* next_todo_entry = 
            entry_under_cursor->get_next_todo_entry();
        td_list->remove_todo_entry(entry_under_cursor);
        entry_under_cursor = next_todo_entry;
        print_todo_list_in_window(entry_under_cursor);
    }
}

void ListPreviewManager::two_tap_quit(){
    m_exit_signal = true;
}

void ListPreviewManager::toggle_mark_unmark(){
    entry_under_cursor->toggle_mark_unmark();
    entry_under_cursor->refresh(list_window, m_cursor_y, true);
    wrefresh(list_window);
}

