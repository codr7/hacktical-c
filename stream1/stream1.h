#ifndef HACKTICAL_STREAM1_H
#define HACKTICAL_STREAM1_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "vector/vector.h"

struct hc_stream {  
  size_t (*read)(struct hc_stream *, uint8_t *, size_t);
  size_t (*write)(struct hc_stream *, const uint8_t *, size_t);
  void (*deinit)(struct hc_stream *);
};

size_t hc_read(struct hc_stream *s, uint8_t *data, size_t n);
size_t hc_write(struct hc_stream *s, const uint8_t *data, size_t n);

char *hc_gets(struct hc_stream *s, struct hc_malloc *malloc);
char hc_getc(struct hc_stream *s);
size_t hc_putc(struct hc_stream *s, char data);
size_t hc_puts(struct hc_stream *s, const char *data);

size_t hc_vprintf(struct hc_stream *s,
		  const char *spec,
		  va_list args);

size_t hc_printf(struct hc_stream *s, const char *spec, ...);

void hc_stream_deinit(struct hc_stream *s);

struct hc_file_stream_opts {
  bool close_file;
};

struct hc_file_stream {
  struct hc_stream stream;
  FILE *file;
  struct hc_file_stream_opts opts;
};

#define hc_file_stream_init(s, f, ...)				\
  _hc_file_stream_init(s, f, (struct hc_file_stream_opts){	\
      .close_file = false,					\
      ##__VA_ARGS__						\
    })

extern struct hc_stream hc_file_stream;

struct hc_file_stream *_hc_file_stream_init(struct hc_file_stream *s,
					    FILE *file,
					    struct hc_file_stream_opts opts);

struct hc_stream *hc_stdout();

struct hc_memory_stream {
  struct hc_stream stream;
  struct hc_vector data;
  size_t rpos;
};

extern struct hc_stream hc_memory_stream;

struct hc_memory_stream *hc_memory_stream_init(struct hc_memory_stream *s,
					       struct hc_malloc *malloc);

const char *hc_memory_stream_string(struct hc_memory_stream *s);

#endif
