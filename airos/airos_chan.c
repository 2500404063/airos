#include "airos_chan.h"

void airos_chan_write_int8(airos_chan_t *chan, char v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_int8 = v;
}

void airos_chan_write_int16(airos_chan_t *chan, short v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_int16 = v;
}

void airos_chan_write_int32(airos_chan_t *chan, long v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_int32 = v;
}

void airos_chan_write_uint8(airos_chan_t *chan, unsigned char v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_uint8 = v;
}

void airos_chan_write_uint16(airos_chan_t *chan, unsigned short v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_uint16 = v;
}

void airos_chan_write_uint32(airos_chan_t *chan, unsigned long v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_uint32 = v;
}

void airos_chan_write_float(airos_chan_t *chan, float v)
{
    while (chan->busy)
    {
    }
    chan->busy = 1;
    chan->v_float = v;
}

char airos_chan_read_int8(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_int8;
}

short airos_chan_read_int16(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_int16;
}

long airos_chan_read_int32(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_int32;
}

unsigned char airos_chan_read_uint8(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_uint8;
}

unsigned short airos_chan_read_uint16(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_uint16;
}

unsigned long airos_chan_read_uint32(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_uint32;
}

float airos_chan_read_float(airos_chan_t *chan)
{
    while (!chan->busy)
    {
    }
    chan->busy = 0;
    return chan->v_float;
}