/* This class extends the functionality of a todolist-entry by lettign it store
 * todo-list entries that also encode a priority for the task
 *
 */

#ifndef __PRIORITY_TODOLIST_H_INCLUDED__
#define __PRIORITY_TODOLIST_H_INCLUDED__

class PriorityToDoListEntry : public ToDoListEntry
{
    protected:

    public:
        PriorityToDoListEntry();
        PriorityToDoListEntry(std::string todo_message);
}

#endif
