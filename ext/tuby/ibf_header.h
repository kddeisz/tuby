#ifndef TUBY_IBF_HEADER
#define TUBY_IBF_HEADER

#include <stdlib.h>
#include <string.h>

typedef unsigned int tb_ibf_offset_t;
typedef struct tb_ibf_header {
  char magic[4]; /* YARB */
  unsigned int major_version;
  unsigned int minor_version;
  unsigned int size;
  unsigned int extra_size;

  unsigned int iseq_list_size;
  unsigned int id_list_size;
  unsigned int object_list_size;

  tb_ibf_offset_t iseq_list_offset;
  tb_ibf_offset_t id_list_offset;
  tb_ibf_offset_t object_list_offset;
} tb_ibf_header_t;

tb_ibf_header_t * tb_ibf_header_build(void);
void tb_ibf_header_destroy(tb_ibf_header_t *header);

#endif
