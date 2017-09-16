#include "line_info.h"

VALUE rb_cTubyLineInfo;

static void tb_line_info_destroy(tb_line_info_t *line_info) {
  free(line_info);
}

static VALUE tb_line_info_create(VALUE self) {
  tb_line_info_t *line_info = (tb_line_info_t *) malloc(sizeof(tb_line_info_t));
  return Data_Wrap_Struct(self, NULL, tb_line_info_destroy, line_info);
}

static VALUE tb_line_info_initialize(VALUE self, VALUE position, VALUE line_no) {
  tb_line_info_t *line_info;
  Data_Get_Struct(self, tb_line_info_t, line_info);

  line_info->position = position;
  line_info->line_no = line_no;

  return self;
}

tb_line_info_t * tb_line_info_struct(VALUE self) {
  tb_line_info_t *line_info;
  Data_Get_Struct(rb_cTubyLineInfo, tb_line_info_t, line_info);
  return line_info;
}

void Init_tuby_line_info() {
  VALUE rb_cTuby = rb_define_module("Tuby");
  rb_cTubyLineInfo = rb_define_class_under(rb_cTuby, "LineInfo", rb_cObject);

  rb_define_alloc_func(rb_cTubyLineInfo, tb_line_info_create);
  rb_define_method(rb_cTubyLineInfo, "initialize", tb_line_info_initialize, 2);
}
