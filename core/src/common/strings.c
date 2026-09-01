// core/nadia_strings.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *nadia_string_copy(const char *data)
{
    char *out = (char *) malloc(strlen(data) + 1);

    if (!out)
    {
        fprintf(stderr, "Malloc failed.\n");
        return NULL;
    }

    strcpy(out, data);
    return out;
}
