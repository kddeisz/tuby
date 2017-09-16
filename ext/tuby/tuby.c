#include "tuby.h"
#include "line_info.h"
#include "iseq.h"

void Init_tuby(void) {
  VALUE rb_cTuby = rb_define_module("Tuby");
  VALUE rb_cTubyISeq = rb_define_class_under(rb_cTuby, "InstructionSequence", rb_cObject);
  VALUE rb_cTubyLineInfo = rb_define_class_under(rb_cTuby, "LineInfo", rb_cObject);

  rb_define_method(rb_cTubyISeq, "to_binary", tb_iseq_to_binary, 0);

  rb_define_alloc_func(rb_cTubyLineInfo, tb_line_info_build);
  rb_define_method(rb_cTubyLineInfo, "initialize", tb_line_info_initialize, 2);
}
