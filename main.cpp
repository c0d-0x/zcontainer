#include "src/core.h"

int main(int argc, char *argv[]) {
  int ret;
  char *cus_stack = nullptr;
  uint flags =
      SIGCHLD | CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWNET;

  if ((cus_stack = create_stack()) == nullptr) {
    std::cerr << "Failed to create a custom stack\n";
    exit(1);
  }

  clone(exec_container, cus_stack, flags, 0);
  wait(&ret);
  cleanup_stack(cus_stack);
  if (umount(CONTAINER_PROC) != 0) {
    std::cerr << "Error: Failed to umount rootfs\n";
  }

  std::cout << "CONTAINER_EXIT_CODE: " << ret << std::endl;
  return 0;
}
