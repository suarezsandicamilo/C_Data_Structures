// Copyright 2023 Camilo Suárez Sandí

#include "vector.h"

int vector_new(Vector* vector, size_t size_of_value) {
  int error = EXIT_SUCCESS;

  vector->length = 0;
  vector->capacity = VECTOR_DEFAULT_CAPACITY;
  vector->size_of_value = size_of_value;

  vector->values = calloc(vector->capacity, vector->size_of_value);

  if (vector->values == NULL) {
    vector->capacity = 0;
    vector->size_of_value = 0;

    error = EXIT_FAILURE;
  }

  return error;
}

void vector_free(Vector* vector) { free(vector->values); }

void vector_drop(Vector* vector, void fn(void*)) {
  for (size_t index = 0; index < vector->capacity; index++) {
    void* value = vector->values[index];

    if (fn != NULL) {
      fn(value);
    }
  }

  vector_free(vector);
}

int vector_push(Vector* vector, void* value) {
  int error = EXIT_SUCCESS;

  if (vector->size_of_value != sizeof(*value)) {
    error = EXIT_FAILURE;
  }

  if (!error) {
    if (vector->length == vector->capacity) {
      // TODO:
      // error = vector_increase_capaciy();
    }
  }

  if (!error) {
    vector->values[vector->length++] = value;
  }

  return error;
}
