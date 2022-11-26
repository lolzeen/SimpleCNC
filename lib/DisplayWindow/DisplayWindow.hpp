#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H
#include <Arduino.h>

// content
// id
// options

enum rows {FIRST_ROW=0, SECOND_ROW=1};
class DisplayWindow
{
    public:
        void set_content(uint8_t row_specifier, const char* content);
        
        
        const char* get_content(uint8_t row_specifier);



        
};
// previous window
// next window



#endif // DISPLAYWINDOW_H