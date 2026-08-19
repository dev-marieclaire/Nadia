#pragma once

#ifndef DISPLAY_T_H
#define DISPLAY_T_H

typedef struct
{
    unsigned int w, h;
    unsigned int x, y;
} display_t;

int get_display_width(const display_t *s);
int get_display_height(const display_t *s);

#endif // End of DISPLAY_T_H.
