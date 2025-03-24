#include "error/error.h"

#include "dcgen/tests.c"
#include "error/tests.c"
#include "fix/tests.c"
#include "list/tests.c"
#include "macro/tests.c"
#include "malloc/tests.c"
#include "set/tests.c"
#include "task/tests.c"
#include "time/tests.c"
#include "vector/tests.c"

int main() {
  hc_malloc_init();

  dcgen_tests();
  error_tests();
  fix_tests();
  list_tests();
  macro_tests();
  malloc_tests();
  set_tests();
  task_tests();
  time_tests();
  vector_tests();

  hc_errors_deinit();
  return 0;
}
