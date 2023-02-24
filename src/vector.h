// Copyright 2023 Camilo Suárez Sandí

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>

#define VECTOR_DEFAULT_CAPACITY 16

typedef struct Vector {
  size_t length;

  size_t capacity;

  size_t size_of_value;

  void** values;
} Vector;

int vector_new(Vector* vector, size_t size_of_value);

void vector_drop(Vector* vector);

int vector_push(Vector* vector, void* value);

#endif  // VECTOR_H_
