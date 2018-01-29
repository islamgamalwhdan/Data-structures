/* circular_buf.c */
#include <string.h> // for memcpy .

#include "circular_buf.h"

void buffer_init( CIRCULR_BUFF *buf , void *buff_p , size_t buf_size ) 
{
	buf->p_arr = buff_p ;
	buf->size = buf_size ;
	buf->index = 0;
}

void serve_next( CIRCULR_BUFF *buf , size_t ele_size , void *ele_p)
{
    int index = buf->index ;
    memcpy(ele_p, buf->p_arr + index*ele_size , ele_size) ;
    buf->index = (buf->index +1)%buf->size ;
}
void serve_back(CIRCULR_BUFF *buf , size_t ele_size , void *ele_p)
{
    int index = buf->index ;
    memcpy(ele_p , buf->p_arr +index*ele_size , ele_size) ;
    if(--index == -1)
        buf->index = buf->size ;
    else
        buf->index = index ;
}