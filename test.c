#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *map = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (map == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  strcpy(map, "Hello from parent");

  pid_t pid = fork();

  if (pid == 0) { // Child process
    printf("Child before write: %s\n", map);
    strcpy(map, "Child modified this");
    printf("Child after write: %s\n", map);
    exit(0);
  } else { // Parent process
    wait(NULL);
    printf("Parent after child exits: %s\n", map);
  }

  munmap(map, 4096);
  return 0;
}
