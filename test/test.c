//

#include <assert.h>
#include <stdint.h>

#include "vector.h"

void test_vector() {
  Vector vector;  // Vector<int32_t>

  vector_new(&vector, sizeof(int32_t));

  vector_drop(&vector, NULL);
}

void test_vector_push() {
  int error = EXIT_SUCCESS;

  Vector vector;  // Vector<int32_t>

  error = vector_new(&vector, sizeof(int32_t));

  if (!error) {
    assert(vector.length == 0);

    error = vector_push(&vector, (void*) 1);
  }

  if (!error) {
    assert(vector.length == 1);
    assert(vector.values[0] == (void*) 1);
  }

  vector_drop(&vector, NULL);
}

int main() {
  //

  test_vector();
  test_vector_push();
}
