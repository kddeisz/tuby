#ifndef TUBY_BORROWED
#define TUBY_BORROWED

typedef enum {
  METHOD_VISI_UNDEF     = 0x00,
  METHOD_VISI_PUBLIC    = 0x01,
  METHOD_VISI_PRIVATE   = 0x02,
  METHOD_VISI_PROTECTED = 0x03,
  METHOD_VISI_MASK = 0x03
} rb_method_visibility_t;

typedef struct rb_scope_visi_struct {
  rb_method_visibility_t method_visi : 3;
  unsigned int module_func : 1;
} rb_scope_visibility_t;

typedef struct rb_cref_struct {
  VALUE flags;
  const VALUE refinements;
  const VALUE klass;
  struct rb_cref_struct * const next;
  const rb_scope_visibility_t scope_visi;
} rb_cref_t;

#if defined(HAVE_LONG_LONG)
typedef unsigned LONG_LONG rb_serial_t;
#elif defined(HAVE_UINT64_T)
typedef uint64_t rb_serial_t;
#else
typedef unsigned long rb_serial_t;
#endif

struct tb_iseq_inline_cache_entry {
  rb_serial_t ic_serial;
  const rb_cref_t *ic_cref;
  union {
    size_t index;
    VALUE value;
  } ic_value;
};

union tb_iseq_inline_storage_entry {
  struct {
    struct rb_thread_struct *running_thread;
    VALUE value;
  } once;
  struct tb_iseq_inline_cache_entry cache;
};

#endif
