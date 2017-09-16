#include "buffer.h"

struct tb_buffer {
  size_t size;
  size_t capacity;
  char *content;
};

tb_buffer_t * tb_buffer_build(void) {
  tb_buffer_t *buffer = (tb_buffer_t *) malloc(sizeof(tb_buffer_t));
  buffer->size = 0;
  buffer->capacity = 2048;
  buffer->content = (char *) malloc(sizeof(char) * buffer->capacity);
  buffer->content[0] = '\0';
  return buffer;
}

void tb_buffer_append(tb_buffer_t *buffer, const void *content, unsigned long size) {
  size_t new_size = buffer->size + size;
  while (new_size >= buffer->capacity) {
    buffer->capacity *= 2;
    buffer->content = (char *) realloc(buffer->content, buffer->capacity);
  }

  memcpy(buffer->content + buffer->size, (const char *) content, size);
  buffer->size = new_size;
  buffer->content[buffer->size] = '\0';
}

void tb_buffer_overwrite(tb_buffer_t *buffer, const void *content, unsigned long size) {
  memcpy(buffer->content, (const char *) content, size);
}

const char * tb_buffer_output(tb_buffer_t *buffer) {
  char *output = malloc(sizeof(char) * buffer->size);
  strncpy(output, buffer->content, buffer->size);
  return output;
}

size_t tb_buffer_size(tb_buffer_t *buffer) {
  return buffer->size;
}

void tb_buffer_destroy(tb_buffer_t *buffer) {
  free(buffer->content);
  free(buffer);
}
