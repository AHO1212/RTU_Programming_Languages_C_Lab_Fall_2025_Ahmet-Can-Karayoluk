#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc > 1) {
    printf("Hello from AhmetCanKarayoluk! You gave me %d argument(s):\n",
           argc - 1);
    for (int i = 1; i < argc; i++) {
      printf("  Arg %d: %s\n", i, argv[i]);
    }
  } else {
    printf("Hello from YourName! No extra arguments provided.\n");
  }
  return 0;
}
