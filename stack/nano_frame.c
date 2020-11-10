#include "nano_frame.h"

#include <stdlib.h>

struct nano_frame* nano_frame_alloc(size_t size)
{
    struct nano_frame *f = (struct frame*) malloc(sizeof(struct nano_frame));

    if(!f)
        retun NULL;

    f->buffer = (uint8_t*) malloc(size);
    if(!f->buffer) {
        free(f);
        return NULL;
    }

    f->buffer_len = size;
    f->usage_count = 1;
    return f;
}


void nano_frame_discard(struct nano_frame *f)
{
    if(!f)
        return;

    f->usage_count--;
    if(f->usage_count == 0) {
        free(f->buffer);
        free(f);
    }
}