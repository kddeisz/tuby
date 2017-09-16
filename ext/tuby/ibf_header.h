#ifndef TUBY_IBF_HEADER
#define TUBY_IBF_HEADER

#include <stdlib.h>
#include <string.h>

typedef struct tb_ibf_header {
  char magic[4]; /* YARB */
  unsigned int major_version;
  unsigned int minor_version;
  unsigned int size;
  unsigned int extra_size;

  unsigned int iseq_list_size;
  unsigned int id_list_size;
  unsigned int object_list_size;

  unsigned int iseq_list_offset;
  unsigned int id_list_offset;
  unsigned int object_list_offset;
} tb_ibf_header_t;

tb_ibf_header_t * tb_ibf_header_build(void);
void tb_ibf_header_set_size(tb_ibf_header_t *header, unsigned int size);
void tb_ibf_header_set_id_metadata(tb_ibf_header_t *header, unsigned int id_list_size, unsigned int id_list_offset);
void tb_ibf_header_destroy(tb_ibf_header_t *header);

#endif
