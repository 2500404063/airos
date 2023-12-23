#include "airos_chan.h"

#define SCHEDULE_PLACE() airos_task_schedule()

void airos_chan_write_int8(airos_chan_t *chan, char v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_int8 = v;
}

void airos_chan_write_int16(airos_chan_t *chan, short v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_int16 = v;
}

void airos_chan_write_int32(airos_chan_t *chan, long v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_int32 = v;
}

void airos_chan_write_uint8(airos_chan_t *chan, unsigned char v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_uint8 = v;
}

void airos_chan_write_uint16(airos_chan_t *chan, unsigned short v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_uint16 = v;
}

void airos_chan_write_uint32(airos_chan_t *chan, unsigned long v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_uint32 = v;
}

void airos_chan_write_float(airos_chan_t *chan, float v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_float = v;
}

void airos_chan_write_any(airos_chan_t *chan, void *v)
{
    while (chan->busy)
    {
        SCHEDULE_PLACE();
    }
    chan->busy = 1;
    chan->v_any = v;
}

char airos_chan_read_int8(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_int8;
}

short airos_chan_read_int16(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_int16;
}

long airos_chan_read_int32(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_int32;
}

unsigned char airos_chan_read_uint8(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_uint8;
}

unsigned short airos_chan_read_uint16(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_uint16;
}

unsigned long airos_chan_read_uint32(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_uint32;
}

float airos_chan_read_float(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_float;
}

void *airos_chan_read_any(airos_chan_t *chan)
{
    while (!chan->busy)
    {
        SCHEDULE_PLACE();
    }
    return chan->v_any;
}

void airos_chan_solved(airos_chan_t *chan)
{
    chan->busy = 0;
}