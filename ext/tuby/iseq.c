#include "buffer.h"
#include "obj_list.h"
#include "ibf_header.h"
#include "iseq.h"
#include "line_info.h"
#include "borrowed.h"

typedef struct tb_iseq_location_struct {
  VALUE pathobj;
  VALUE base_label;
  VALUE label;
  VALUE first_lineno;
} tb_iseq_location_t;

typedef struct tb_iseq {
  enum iseq_type {
    ISEQ_TYPE_TOP,
    ISEQ_TYPE_METHOD,
    ISEQ_TYPE_BLOCK,
    ISEQ_TYPE_CLASS,
    ISEQ_TYPE_RESCUE,
    ISEQ_TYPE_ENSURE,
    ISEQ_TYPE_EVAL,
    ISEQ_TYPE_MAIN,
    ISEQ_TYPE_DEFINED_GUARD
  } type;

  tb_iseq_location_t location;
  tb_line_info_t *line_info_list;

  union tb_iseq_inline_storage_entry *is_entries;

  unsigned int is_size;
  unsigned int ci_kw_size;
  unsigned int line_info_size;
} tb_iseq_t;

tb_iseq_location_t * tb_iseq_location_build(const char *filename) {
  VALUE label = rb_str_new_cstr("<main>");
  VALUE compiled = Qtrue;
  VALUE pathobj = rb_ary_new3(2, rb_str_new_cstr(filename), &compiled);

  tb_iseq_location_t *location = (tb_iseq_location_t *) malloc(sizeof(tb_iseq_location_t));
  location->pathobj = pathobj;
  location->base_label = label;
  location->label = label;
  location->first_lineno = INT2FIX(1);

  return location;
}

tb_iseq_t * tb_iseq_build(const char *filename) {
  tb_iseq_t *iseq = (tb_iseq_t *) malloc(sizeof(tb_iseq_t));
  iseq->type = ISEQ_TYPE_TOP;

  tb_iseq_location_t *location = tb_iseq_location_build(filename);
  iseq->location = *location;
  iseq->is_entries = NULL;

  iseq->is_size = 0;
  iseq->ci_kw_size = 0;

  return iseq;
}

void tb_iseq_set_line_info(tb_iseq_t *iseq, VALUE line_info_list) {
  iseq->line_info_size = RARRAY_LEN(line_info_list);
  iseq->line_info_list = (tb_line_info_t *) malloc(sizeof(tb_line_info_t) * iseq->line_info_size);

  long idx;
  tb_line_info_t *line_info;

  for (idx = 0; idx < iseq->line_info_size; idx++) {
    line_info = tb_line_info_struct(RARRAY_AREF(line_info_list, idx));
    iseq->line_info_list[idx] = *line_info;
  }
}

static void tb_id_list_to_idx_list(long size, tb_obj_list_t *obj_list, VALUE *ids_list, long *idx_list) {
  VALUE id;
  long idx;

  for (idx = 0; idx < size; idx++) {
    id = RARRAY_AREF(*ids_list, idx);
    idx_list[idx] = tb_obj_list_append(obj_list, &id);
  }
}

VALUE tb_iseq_to_binary(VALUE self) {
  tb_buffer_t *buffer = tb_buffer_build();
  tb_obj_list_t *obj_list = tb_obj_list_build();
  tb_ibf_header_t *header = tb_ibf_header_build();

  tb_buffer_append(buffer, header, sizeof(tb_ibf_header_t));
  tb_buffer_append(buffer, RUBY_PLATFORM, strlen(RUBY_PLATFORM) + 1);

  VALUE ids_list = rb_funcall(self, rb_intern("ids_list"), 0, NULL);
  long id_idx_list_size = RARRAY_LEN(ids_list);
  long id_idx_list[id_idx_list_size];
  tb_id_list_to_idx_list(id_idx_list_size, obj_list, &ids_list, id_idx_list);
  tb_ibf_header_set_id_metadata(header, id_idx_list_size, 0);

  tb_ibf_header_set_size(header, tb_buffer_size(buffer));
  tb_buffer_overwrite(buffer, header, sizeof(tb_ibf_header_t));

  const char *output = tb_buffer_output(buffer);
  size_t output_size = tb_buffer_size(buffer);

  tb_buffer_destroy(buffer);
  tb_obj_list_destroy(obj_list);
  tb_ibf_header_destroy(header);

  return rb_str_new(output, output_size);
}

//   unsigned int iseq_size;
//   const VALUE *iseq_encoded; /* encoded iseq (insn addr and operands) */
//
//   /**
//    * parameter information
//    *
//    *  def m(a1, a2, ..., aM,                    # mandatory
//    *        b1=(...), b2=(...), ..., bN=(...),  # optional
//    *        *c,                                 # rest
//    *        d1, d2, ..., dO,                    # post
//    *        e1:(...), e2:(...), ..., eK:(...),  # keyword
//    *        **f,                                # keyword_rest
//    *        &g)                                 # block
//    * =>
//    *
//    *  lead_num     = M
//    *  opt_num      = N
//    *  rest_start   = M+N
//    *  post_start   = M+N+(*1)
//    *  post_num     = O
//    *  keyword_num  = K
//    *  block_start  = M+N+(*1)+O+K
//    *  keyword_bits = M+N+(*1)+O+K+(&1)
//    *  size         = M+N+O+(*1)+K+(&1)+(**1) // parameter size.
//    */
//
//   struct {
//     struct {
//       unsigned int has_lead   : 1;
//       unsigned int has_opt    : 1;
//       unsigned int has_rest   : 1;
//       unsigned int has_post   : 1;
//       unsigned int has_kw     : 1;
//       unsigned int has_kwrest : 1;
//       unsigned int has_block  : 1;
//       unsigned int ambiguous_param0 : 1; /* {|a|} */
//     } flags;
//
//     unsigned int size;
//
//     int lead_num;
//     int opt_num;
//     int rest_start;
//     int post_start;
//     int post_num;
//     int block_start;
//
//     const VALUE *opt_table; /* (opt_num + 1) entries. */
//     /* opt_num and opt_table:
//      *
//      * def foo o1=e1, o2=e2, ..., oN=eN
//      * #=>
//      *   # prologue code
//      *   A1: e1
//      *   A2: e2
//      *   ...
//      *   AN: eN
//      *   AL: body
//      * opt_num = N
//      * opt_table = [A1, A2, ..., AN, AL]
//      */
//
//     const struct rb_iseq_param_keyword {
//       int num;
//       int required_num;
//       int bits_start;
//       int rest_start;
//       const ID *table;
//       const VALUE *default_values;
//     } *keyword;
//   } param;
//
//   const ID *local_table;    /* must free */
//
//   /* catch table */
//   const struct iseq_catch_table *catch_table;
//
//   /* for child iseq */
//   const struct rb_iseq_struct *parent_iseq;
//   struct rb_iseq_struct *local_iseq; /* local_iseq->flip_cnt can be modified */
//
//   struct rb_call_info *ci_entries; /* struct rb_call_info ci_entries[ci_size];
//             * struct rb_call_info_with_kwarg cikw_entries[ci_kw_size];
//             * So that:
//             * struct rb_call_info_with_kwarg *cikw_entries = &body->ci_entries[ci_size];
//             */
//   struct rb_call_cache *cc_entries; /* size is ci_size = ci_kw_size */
//
//   VALUE mark_ary;     /* Array: includes operands which should be GC marked */
//
//   unsigned int local_table_size;
//   unsigned int ci_size;
//   unsigned int stack_max; /* for stack overflow check */
// };
