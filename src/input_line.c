#include <stdlib.h>
#include "input_line.h"

input_line *input_line_create(void)
{
    input_line *input = malloc(sizeof(input_line));
    input->_data = mud_string_create_empty(256);
    input->_cursor_index = 0;

    return input;
}

void input_line_destroy(input_line *input)
{
    if(!input) return;

    mud_string_destroy(input->_data);
    free(input);
}

void input_line_add_char(input_line *input, mud_char_t ch)
{
    if(!input) return;
    if(ch == '\n') return; // Don't allow newlines to be added to the input line.

    mud_string_append(input->_data, &ch, 1);
    ++input->_cursor_index;
    input->_dirty = true;
}

void input_line_delete_char(input_line *input)
{
    if(!input) return;

    mud_string_delete_char(input->_data);
    --input->_cursor_index;
    if(input->_cursor_index < 0)
        input->_cursor_index = 0;
    input->_dirty = true;
}

void input_line_clear(input_line *input)
{
    if(!input) return;

    mud_string_clear(input->_data);
    input->_dirty = true;
}

mud_string *input_line_get_contents(input_line *input)
{
    if(!input) return NULL;

    return input->_data;
}

void input_line_set_contents(input_line *input, mud_string *str)
{
    if(!input) return;
    if(!str) return;

    // Clear the current input.
    mud_string_clear(input->_data);

    // Add the new input.
    int i;
    for(i = 0; i < mud_string_length(str); ++i)
        input_line_add_char(input, mud_string_get_data(str)[i]);
    input->_dirty = true;
}

int input_line_get_cursor(input_line *input)
{
    if(!input) return -1;

    return input->_cursor_index;
}

void input_line_set_cursor(input_line *input, int index)
{
    if(!input) return;

    input->_cursor_index = index;
    if(input->_cursor_index < 0)
        input->_cursor_index = 0;
    if(input->_cursor_index > mud_string_length(input->_data))
        input->_cursor_index = mud_string_length(input->_data);
    input->_dirty = true;
}

void input_line_adjust_cursor(input_line *input, int adjustment)
{
    if(!input) return;

    input_line_set_cursor(input, input->_cursor_index + adjustment);
}

bool input_line_is_dirty(input_line *input)
{
    if(!input) return false;

    return input->_dirty;
}

void input_line_clear_dirty(input_line *input)
{
    if(!input) return;

    input->_dirty = false;
}
