#include "line_info.h"

static void tb_line_info_destroy(tb_line_info_t *line_info) {
  free(line_info);
}

VALUE tb_line_info_build(VALUE self) {
  tb_line_info_t *line_info = (tb_line_info_t *) malloc(sizeof(tb_line_info_t));
  return Data_Wrap_Struct(self, NULL, tb_line_info_destroy, line_info);
}

VALUE tb_line_info_initialize(VALUE self, VALUE position, VALUE line_no) {
  tb_line_info_t *line_info;
  Data_Get_Struct(self, tb_line_info_t, line_info);

  line_info->position = position;
  line_info->line_no = line_no;

  return self;
}

tb_line_info_t * tb_line_info_struct(VALUE self) {
  tb_line_info_t *line_info;
  Data_Get_Struct(self, tb_line_info_t, line_info);
  return line_info;
}
