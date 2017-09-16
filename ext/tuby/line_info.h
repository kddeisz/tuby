#ifndef TUBY_LINE_INFO
#define TUBY_LINE_INFO

#include <ruby.h>

typedef struct tb_line_info {
  unsigned int position;
  unsigned int line_no;
} tb_line_info_t;

VALUE tb_line_info_build(VALUE self);
VALUE tb_line_info_initialize(VALUE self, VALUE position, VALUE line_no);
tb_line_info_t * tb_line_info_struct(VALUE line_info);

#endif
