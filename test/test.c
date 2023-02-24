// Copyright 2023 Camilo Suárez Sandí

#include "test.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "vector.h"

#define ADD_TEST(a, b, c) \
  if ((!(c))) {          \
    (a)++;            \
  } else {            \
    (b)++;            \
  }

int main() {
  int pass = 0;
  int fail = 0;

  ADD_TEST(pass, fail, test_vector());
  ADD_TEST(pass, fail, test_vector_push());
  ADD_TEST(pass, fail, test_vector_of_vectors());

  printf("Tests passed: %d/%d.\n", pass, pass + fail);
  printf("Tests failed: %d/%d.\n", fail, pass + fail);
}

int test_vector() {
  int error = EXIT_SUCCESS;

  Vector vector;  // Vector<int32_t>

  error = vector_new(&vector, sizeof(int32_t));

  if (!error) {
    assert(vector.length == 0);
    assert(vector.capacity == VECTOR_DEFAULT_CAPACITY);
    assert(vector.size_of_value == sizeof(int32_t));
    assert(vector.values != NULL);
  }

  vector_drop(&vector);

  return error;
}

int test_vector_push() {
  int error = EXIT_SUCCESS;

  Vector vector;  // Vector<int32_t>

  error = vector_new(&vector, sizeof(int32_t));

  if (!error) {
    error = vector_push(&vector, (void*) 1);
  }

  if (!error) {
    assert(vector.length == 1);
    assert(vector.values[0] == (void*) 1);
  }

  vector_drop(&vector);

  return error;
}

int test_vector_of_vectors() {
  int error = EXIT_SUCCESS;

  Vector* vector_1 = calloc(1, sizeof(Vector));  // Vector<Vector<int32_t>>

  error = vector_new(vector_1, sizeof(Vector));

  if (!error) {
    Vector* vector_2 = calloc(1, sizeof(Vector));  // Vector<int32_t>

    error = vector_new(vector_2, sizeof(int32_t));

    if (!error) {
      error = vector_push(vector_1, vector_2);
    }
  }

  if (!error) {
    assert(vector_1->length == 1);

    Vector* vector_2 = (Vector*) vector_1->values[0];

    error = vector_push(vector_2, (void*) 1);
  }

  if (!error) {
    Vector* vector_2 = (Vector*) vector_1->values[0];

    assert(vector_2->length == 1);

    vector_drop(vector_2);

    free(vector_2);
  }

  vector_drop(vector_1);

  free(vector_1);

  return error;
}
