#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct
{
    unsigned int w, h;
    unsigned int x, y;
} display_t;

int display_get_width(const display_t *s);
int display_get_height(const display_t *s);

#endif // End of DISPLAY_H.
