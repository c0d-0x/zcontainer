#include "src/core.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <linux/sched.h>
#include <ostream>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int ret;
  void *cus_stack = nullptr;
  uint flags = SIGCHLD | CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS |
               CLONE_NEWNS | CLONE_NEWNET;

  if ((cus_stack = create_stack()) == nullptr) {
    std::cerr << "Failed to create a custom stack\n";
    exit(1);
  }

  clone(exec_container, cus_stack, flags, 0);
  wait(&ret);
  if (umount(CONTAINER_PROC) != 0) {
    std::cerr << "Error: Failed to umount rootfs\n";
  }

  std::cout << "CONTAINER_EXIT_CODE: " << ret << std::endl;
  return 0;
}
