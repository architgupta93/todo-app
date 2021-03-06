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

// Function definitions for PreviewManager class

PreviewManager::PreviewManager()
{
    win = NULL;
    m_mode = VISUAL;
    m_exit_signal = false;
    m_cursor_y = Y_OFFSET;
    m_cursor_x = X_OFFSET;
}

// Function definitions specific to ListPreviewManager

ListPreviewManager::ListPreviewManager()
{
    ListPreviewManager(NULL, NULL);
}

ListPreviewManager::ListPreviewManager(WINDOW *_win, ToDoList *td)
{
    win = _win;
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

void ListPreviewManager::printToDoList(ToDoListEntry*
    first_entry_to_print)
{
    int y_cursor = m_cursor_y;
    // TODO: Add functionality to print the todo-list title here (and have a
    // title for the todo list in the first place
    ToDoListEntry* entry_to_print = first_entry_to_print;
    while(entry_to_print != NULL)
    {
        printToDoEntry(entry_to_print, y_cursor);
        y_cursor += entry_to_print->get_message_block_length();
        entry_to_print = entry_to_print->get_next_todo_entry();
    }
    box(win, 0, 0);
    wrefresh(win);
}

void ListPreviewManager::printToDoEntry(ToDoListEntry*
    entry_to_print, int y_cursor)
{
    entry_to_print->print(win, y_cursor,
        entry_to_print == entry_under_cursor);
    #ifdef __DEBUG__
        //getch();
        //box(win, 0, 0);
        wrefresh(win);
    #endif
}

void ListPreviewManager::insert_text(char input)
{
    entry_under_cursor->insert_text(win, m_cursor_y, m_cursor_x, input);
    if ((input >= (char) FIRST_WRITABLE_ASCII_CHAR) && 
        (input <= (char) LAST_WRITEABLE_ASCII_CHAR))
    {
        move_cursor_right();
    } 
    else if (input == (char) M_KEY_BACKSPACE)
    {
        move_cursor_left();
    } 
    wrefresh(win);
}

void ListPreviewManager::process(char input)
{
    switch (input)
    {
        #define F_DEF(INPUT, FUNCTION, NON_FUNC_MODE)\
            case INPUT:\
                if (m_mode == NON_FUNC_MODE)\
                {\
                    insert_text(INPUT);\
                } else {\
                    FUNCTION(); \
                }  break;
        #include "keystrokes.def"
        #undef F_DEF
        default:
            if (m_mode == INSERT)
            {
                insert_text(input);
            }
            else {
                return;
            }
            break;
    }   
}

// Key stroke related functions have been described here

void ListPreviewManager::move_cursor_left(){
    if (m_mode == EDIT || m_mode == INSERT)
    {
        if (m_cursor_x > X_OFFSET)
        {
            wmove(win, m_cursor_y, --m_cursor_x);
            wrefresh(win);
        }
        else{
            int old_cursor_y = m_cursor_y;
            move_cursor_up();
            if (old_cursor_y != m_cursor_y)
            {
                // Change the x cursor value only if the y cursor has changed
                // (i.e. the line under cursor has been switched)
                m_cursor_x = WRITABLE_X;
                wmove(win, m_cursor_y, m_cursor_x);
                wrefresh(win);
            }
        }
    }
}

void ListPreviewManager::move_cursor_right(){
    if (m_mode == EDIT || m_mode == INSERT)
    {
        if (m_cursor_x < entry_under_cursor->x_limit())
        {
            wmove(win, m_cursor_y, ++m_cursor_x);
            wrefresh(win);
        }
        else{
            int old_cursor_y = m_cursor_y;
            move_cursor_down();
            if (old_cursor_y != m_cursor_y)
            {
                // Change the x cursor value only if the y cursor has changed
                // (i.e. the line under cursor has been switched)
                m_cursor_x = X_OFFSET;
                wmove(win, m_cursor_y, m_cursor_x);
                wrefresh(win);
            }
        }
    }
}

void ListPreviewManager::move_cursor_up(){
    if (m_mode == VISUAL)
    {
        if(entry_under_cursor->get_prev_todo_entry() != NULL)
        {
            entry_under_cursor->refresh(win, m_cursor_y, false);
            entry_under_cursor = entry_under_cursor->get_prev_todo_entry();
            m_cursor_y -= entry_under_cursor->get_message_block_length();
            entry_under_cursor->refresh(win, m_cursor_y, true);
            wrefresh(win);
            box(win, 0, 0);
        }
    }
    else
    {
        bool jump_todo_entry = entry_under_cursor->check_end_point(true);
        if (jump_todo_entry)
        {
            if(entry_under_cursor->get_prev_todo_entry() != NULL)
            {
                entry_under_cursor = entry_under_cursor->get_prev_todo_entry();
                entry_under_cursor->set_cursor_bottom();
                m_cursor_x = entry_under_cursor->x_limit();
                wmove(win, --m_cursor_y, m_cursor_x); 
            }
        }
        else {
            entry_under_cursor->update_cursor_position(win, m_cursor_y,
m_cursor_x, true);
        }
        wrefresh(win);
    }
}

void ListPreviewManager::move_cursor_down(){
    if (m_mode == VISUAL)
    {
        if(entry_under_cursor->get_next_todo_entry() != NULL)
        {
            entry_under_cursor->refresh(win, m_cursor_y, false);
            m_cursor_y += entry_under_cursor->get_message_block_length();
            entry_under_cursor = entry_under_cursor->get_next_todo_entry();
            entry_under_cursor->refresh(win, m_cursor_y, true);
            wrefresh(win);
            box(win, 0, 0);
        }
    }
    else
    {
        bool jump_todo_entry = entry_under_cursor->check_end_point(false);
        if (jump_todo_entry)
        {
            if(entry_under_cursor->get_prev_todo_entry() != NULL)
            {
                entry_under_cursor = entry_under_cursor->get_next_todo_entry();
                entry_under_cursor->set_cursor_top();
                m_cursor_x = X_OFFSET;
                wmove(win, ++m_cursor_y, m_cursor_x);
            }
        }
        else {
            entry_under_cursor->update_cursor_position(win, m_cursor_y,
m_cursor_x, false);
        }
        wrefresh(win);
    }
}

// Switching between various modes

void ListPreviewManager::switch_to_edit_mode(){
        PreviewMode last_mode = m_mode;
        m_mode = EDIT;
        curs_set(m_mode);
        if (last_mode == VISUAL)
        {
            entry_under_cursor->refresh(win, m_cursor_y, false);
            wmove(win, m_cursor_y, X_OFFSET);
            wrefresh(win);
        }
}

void ListPreviewManager::switch_to_visual_mode(){
    if (m_mode == EDIT)
    {
        m_mode = VISUAL;
        curs_set(m_mode);
        entry_under_cursor->refresh(win, m_cursor_y, true);
        wrefresh(win);
    }
}

void ListPreviewManager::switch_to_insert_mode(){
    m_mode = INSERT;
    curs_set(EDIT); // Using curs_set(INSERT) makes the cursor invisible -___-
    entry_under_cursor->refresh(win, m_cursor_y, false);
    wmove(win, m_cursor_y, m_cursor_x);
    wrefresh(win);
}

void ListPreviewManager::step_modes_back(){
    switch (m_mode)
    {
        case EDIT:
            switch_to_visual_mode();
            break;
        case INSERT:
            switch_to_edit_mode();
            break;
        default:
            switch_to_visual_mode();
            break;
    }
}

// Adding and deleting ToDo Entries

void ListPreviewManager::add_todo_entry(){
    entry_under_cursor = td_list->new_todo_entry(entry_under_cursor);
    printToDoList(entry_under_cursor);
}

void ListPreviewManager::two_tap_delete(){
    char repeat = getch();
    if (repeat == 'd')
    {
        ToDoListEntry* next_todo_entry = 
            entry_under_cursor->get_next_todo_entry();
        td_list->remove_todo_entry(entry_under_cursor);
        entry_under_cursor = next_todo_entry;
        printToDoList(entry_under_cursor);
    }
}

void ListPreviewManager::two_tap_quit(){
    char repeat = getch();
    if (repeat == 'q')
    {
        m_exit_signal = true;
    }
}

void ListPreviewManager::toggle_mark_unmark(){
    entry_under_cursor->toggle_mark_unmark();
    entry_under_cursor->refresh(win, m_cursor_y, true);
    wrefresh(win);
}

