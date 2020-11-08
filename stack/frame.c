#include "frame.h"

#include <stdlib.h>

frame_t* frame_alloc(uint8_t *frame, size_t frame_len, uint8_t *hdr, size_t hdr_len, frame_type_t type)
{
    frame_t *_frame = (frame_t*) malloc(frame_len);

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