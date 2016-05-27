/* The primary purpose of this object is to be able to debug the code. Currently, there is no way to get feedback from the application, which is pretty annoying. This should, hopefully, fix that problem. Later, this can be used to display different status messages in the application, like the current mode, last pressed action key etc.

Author: Archit Gupta
Date: May 26, 2016
*/

#include "process.h"

class StatusBar
{
    public:
        StatusBar();    // Constructor
        bool print();
        bool refresh();
        void update_list(ToDoList* cList);
        void update_list_entry(ToDoListEntry* cListEntry);
        void set_mode(PreviewMode mode);

    private:
        WINDOW* win;
        PreviewMode currentListMode;        
        ToDoListEntry* currentListEntry;
        ToDoList* currentList;
};
