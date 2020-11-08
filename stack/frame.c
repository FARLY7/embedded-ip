#include "frame.h"

#include <stdlib.h>

struct frame* frame_alloc(uint8_t *frame, size_t frame_len, uint8_t *hdr, size_t hdr_len, frame_type_t type)
{
    struct frame *_frame = (struct frame*) malloc(frame_len);

    if(_frame == NULL) { 
        retun NULL;
    }

    _frame->frame = frame;
    _frame->frame_len = frame_len;
    _frame->hdr = hdr;
    _frame->hdr_len = hdr_len;
    _frame->type = type;
    
    return _frame;
}


void frame_free(frame_t *frame)
{
    if(frame != NULL) {
        free(frame);
    }
}