/*  circular_buf.h */

#ifndef CIRCULAR_BUF_H
#define CIRCULAR_BUF_H


typedef struct
{
    void *p_arr ; // pointer to array inside application
    int index ;
    size_t size ;
}CIRCULR_BUFF ;

/* Accessing mechanism functions  */
void buffer_init( CIRCULR_BUFF *buf , void *buff_p , size_t buf_size ) ;
void serve_next( CIRCULR_BUFF *buf  , size_t ele_size , void *ele_p) ;
void serve_back( CIRCULR_BUFF *buf  , size_t ele_size , void *ele_p) ;

#endif //CIRCULAR_BUF_H