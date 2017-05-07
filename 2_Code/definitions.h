#ifndef __DEFINITIONS_H_INCLUDED__
#define __DEFINITIONS_H_INCLUDED__

enum PreviewMode{
    VISUAL,
    EDIT,
    INSERT
};

#define SUCCESS true
#define FAILURE false
#define X_OFFSET  4
#define Y_OFFSET  2
#define STATUS_BAR_HEIGHT 10
#define WRITABLE_X 80
#define FIRST_WRITABLE_ASCII_CHAR 32
#define LAST_WRITEABLE_ASCII_CHAR 126
#define M_KEY_BACKSPACE 8
#define M_KEY_DELETE 127
#define M_KEY_ESCAPE (char) 27

#endif
