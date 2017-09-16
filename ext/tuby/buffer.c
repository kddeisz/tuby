#include "buffer.h"

struct tb_buffer {
  size_t size;
  size_t capacity;
  char *content;
};

Buffer * tb_buffer_build(void) {
  Buffer *buffer = (Buffer *) malloc(sizeof(Buffer));
  buffer->size = 0;
  buffer->capacity = 2048;
  buffer->content = (char *) malloc(sizeof(char) * buffer->capacity);
  buffer->content[0] = '\0';
  return buffer;
}

void tb_buffer_append(Buffer *buffer, const void *content, unsigned long size) {
  size_t new_size = buffer->size + size;
  while (new_size >= buffer->capacity) {
    buffer->capacity *= 2;
    buffer->content = (char *) realloc(buffer->content, buffer->capacity);
  }

  memcpy(buffer->content + buffer->size, (const char *) content, size);
  buffer->size = new_size;
  buffer->content[buffer->size] = '\0';
}

const char * tb_buffer_output(Buffer *buffer) {
  char *output = malloc(sizeof(char) * buffer->size);
  strncpy(output, buffer->content, buffer->size);
  return output;
}

size_t tb_buffer_size(Buffer *buffer) {
  return buffer->size;
}

void tb_buffer_destroy(Buffer *buffer) {
  free(buffer->content);
  free(buffer);
}
