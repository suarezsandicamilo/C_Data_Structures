//

#include <assert.h>
#include <stdint.h>

#include "vector.h"

int test_vector() {
  int error = EXIT_SUCCESS;

  Vector vector;  // Vector<int32_t>

  error = vector_new(&vector, sizeof(int32_t));

  if (!error) {
    assert(vector.length == 0);
    assert(vector.capacity = VECTOR_DEFAULT_CAPACITY);
    assert(vector.size_of_value = sizeof(int32_t));
    assert(vector.values != NULL);
  }

  vector_drop(&vector, NULL);

  return error;
}

int test_vector_push() {
  int error = EXIT_SUCCESS;

  Vector vector;  // Vector<int32_t>

  error = vector_new(&vector, sizeof(int32_t));

  if (!error) {
    error = vector_push(&vector, (void*)1);
  }

  if (!error) {
    assert(vector.length == 1);
    assert(vector.values[0] == (void*)1);
  }

  vector_drop(&vector, NULL);

  return error;
}

int test_vector_of_vectors() {
  int error = EXIT_SUCCESS;

  Vector* vector_1 = calloc(1, sizeof(Vector));  // Vector<Vector<int32_t>>

  error = vector_new(vector_1, sizeof(Vector));

  if (!error) {
    Vector* vector_2 = calloc(1, sizeof(int32_t));  // Vector<int32_t>

    error = vector_push(vector_1, vector_2);
  }

  // TODO: Call vector drop

  return error;
}

int main() {
  test_vector();
  test_vector_push();
  //   test_vector_of_vectors();
}
