#ifndef TUBY_BUFFER
#define TUBY_BUFFER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tb_buffer tb_buffer_t;

tb_buffer_t * tb_buffer_build(void);
void tb_buffer_append(tb_buffer_t *buffer, const void *content, unsigned long size);
const char * tb_buffer_output(tb_buffer_t *buffer);
size_t tb_buffer_size(tb_buffer_t *buffer);
void tb_buffer_destroy(tb_buffer_t *buffer);

#endif
