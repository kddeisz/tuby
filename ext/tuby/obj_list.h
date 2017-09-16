#ifndef TUBY_OBJ_LIST
#define TUBY_OBJ_LIST

#include <stdlib.h>
#include <ruby.h>

typedef struct tb_obj_list tb_obj_list_t;

tb_obj_list_t * tb_obj_list_build(void);
int tb_obj_list_append(tb_obj_list_t *obj_list, VALUE *contents);
void tb_obj_list_destroy(tb_obj_list_t *obj_list);

#endif
