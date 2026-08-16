#pragma once

#ifndef SCREEN_T_H
#define SCREEN_T_H

typedef struct
{
    unsigned int w, h;
    unsigned int x, y;
} screen_t;

int get_screen_width(const screen_t *s);
int get_screen_height(const screen_t *s);

#endif // End of SCREEN_T_H.
