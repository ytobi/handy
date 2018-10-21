#ifndef HANDY_HANDY_NUMERIC_H
#define HANDY_HANDY_NUMERIC_H

typedef struct _numeric_struct  * handy_numeric;

struct _numeric_struct
{
    void (*to_base)         ( handy_numeric * n, int base );
    void (*get_value)       ( handy_numeric * n );
    void (*set_value)       ( handy_numeric * n, void * v);

    void (*free)            ( handy_numeric * s );

    void * _data;
    int _size;
};

handy_numeric handy_create_numeric();
#endif //HANDY_HANDY_NUMERIC_H
