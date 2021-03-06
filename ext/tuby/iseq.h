#ifndef TUBY_ISEQ
#define TUBY_ISEQ

#include <stdlib.h>
#include <ruby.h>

typedef struct tb_iseq_location_struct tb_iseq_location_t;
typedef struct tb_iseq tb_iseq_t;

tb_iseq_location_t * tb_iseq_location_build(const char *filename);
tb_iseq_t * tb_iseq_build(const char *filename);
VALUE tb_iseq_to_binary(VALUE self);

#endif
