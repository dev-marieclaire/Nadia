// input.c

#include <stdbool.h>

enum mouse_states
{
    STATE_CLICKING,
    STATE_MOVING
};

typedef struct point_t
{ int x, y; } point_t;

struct
{
    unsigned short int *state;
    bool pressed;
} keyboard_t;

struct
{
    point_t absolute;
    point_t relative;
    point_t click_pos;

    int     state;
    float   sensitivity;
} mouse_t;

