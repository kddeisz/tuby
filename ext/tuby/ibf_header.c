#include "ibf_header.h"

tb_ibf_header_t * tb_ibf_header_build(void) {
  tb_ibf_header_t *header = (tb_ibf_header_t *) malloc(sizeof(tb_ibf_header_t));

  memcpy(header->magic, "YARB", 4);
  header->major_version = 2;
  header->minor_version = 3;

  header->size = 0;
  header->extra_size = 0;

  header->iseq_list_size = 0;
  header->id_list_size = 0;
  header->object_list_size = 0;

  header->iseq_list_offset = 0;
  header->id_list_offset = 0;
  header->object_list_offset = 1;

  return header;
}

void tb_ibf_header_set_size(tb_ibf_header_t *header, unsigned int size) {
  header->size = size;
}

void tb_ibf_header_set_id_metadata(tb_ibf_header_t *header, unsigned int id_list_size, unsigned int id_list_offset) {
  header->id_list_size = id_list_size;
  header->id_list_offset = id_list_offset;
}

void tb_ibf_header_destroy(tb_ibf_header_t *header) {
  free(header);
}
