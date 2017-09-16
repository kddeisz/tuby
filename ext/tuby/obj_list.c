#include "obj_list.h"

typedef struct tb_obj_list_entry {
  VALUE *contents;
  struct tb_obj_list_entry *next;
} tb_obj_list_entry_t;

struct tb_obj_list {
  int size;
  tb_obj_list_entry_t *head;
  tb_obj_list_entry_t *tail;
};

static tb_obj_list_entry_t * tb_obj_list_entry_build(VALUE *contents) {
  tb_obj_list_entry_t *entry = (tb_obj_list_entry_t *) malloc(sizeof(tb_obj_list_entry_t));
  entry->contents = contents;
  entry->next = NULL;
  return entry;
}

static void tb_obj_list_entry_destroy(tb_obj_list_entry_t *entry) {
  free(entry);
}

tb_obj_list_t * tb_obj_list_build(void) {
  tb_obj_list_t *list = (tb_obj_list_t *) malloc(sizeof(tb_obj_list_t));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

int tb_obj_list_append(tb_obj_list_t *list, VALUE *contents) {
  list->size++;
  tb_obj_list_entry_t *next = tb_obj_list_entry_build(contents);

  if (list->head) {
    list->tail->next = next;
    list->tail = next;
  } else {
    list->head = next;
    list->tail = next;
  }
  return list->size - 1;
}

void tb_obj_list_destroy(tb_obj_list_t *list) {
  tb_obj_list_entry_t *previous = list->head;
  tb_obj_list_entry_t *current = list->head;

  while (previous != NULL) {
    current = current->next;
    tb_obj_list_entry_destroy(previous);
    previous = current;
  }

  free(list);
}
