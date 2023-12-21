#ifndef AIROS_CHAN_H_
#define AIROS_CHAN_H_

#include <stdlib.h>

#ifdef _cplusplus
extern "C"
{
#endif

    typedef struct _airos_chan_t
    {
        unsigned int busy;
        union
        {
            char v_int8;
            short v_int16;
            long v_int32;
            unsigned char v_uint8;
            unsigned short v_uint16;
            unsigned long v_uint32;
            float v_float;
        };

    } airos_chan_t;

void airos_chan_write_int8(airos_chan_t *chan, char v);
void airos_chan_write_int16(airos_chan_t *chan, short v);
void airos_chan_write_int32(airos_chan_t *chan, long v);
void airos_chan_write_uint8(airos_chan_t *chan, unsigned char v);
void airos_chan_write_uint16(airos_chan_t *chan, unsigned short v);
void airos_chan_write_uint32(airos_chan_t *chan, unsigned long v);
void airos_chan_write_float(airos_chan_t *chan, float v);
char airos_chan_read_int8(airos_chan_t *chan);
short airos_chan_read_int16(airos_chan_t *chan);
short airos_chan_read_int16(airos_chan_t *chan);
long airos_chan_read_int32(airos_chan_t *chan);
unsigned char airos_chan_read_uint8(airos_chan_t *chan);
unsigned short airos_chan_read_uint16(airos_chan_t *chan);
unsigned long airos_chan_read_uint32(airos_chan_t *chan);
float airos_chan_read_float(airos_chan_t *chan);

#ifdef _cplusplus
}
#endif

#endif