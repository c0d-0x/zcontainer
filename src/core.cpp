#include "core.h"
#include <iostream>
void *create_stack(void) {
  const int PAGESIZE = getpagesize();
  void *stack =
      mmap(nullptr, PAGESIZE, PROT_READ | PROT_WRITE,
           MAP_STACK | MAP_GROWSDOWN | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (stack == MAP_FAILED) {
    return nullptr;
  }
  return (static_cast<char *>(stack) + PAGESIZE);
}
/*int set_cgroups(char *cg_name) { std::cout << "continue...\n"; }*/

int exec_container(void *arg) {
  std::cout << "Hello world from child PID: " << getpid() << std::endl;

  unshare(CLONE_NEWNS);
  if (clearenv() != 0) {
    std::cerr << "Error: Failed to clear env\n";
    return -1;
  }

  setenv("TERM", "xterm-256color", 1);
  setenv("PS1", "[\\u@\\h \\W]\\$ ", 1);
  setenv("PATH", "/bin:/sbin:/usr/bin:/usr/sbin", 1);

  if (chroot(CONTAINER_ROOTFS) != 0) {
    std::cerr << "Error: chroot failed: " << strerror(errno) << std::endl;
    return -1;
  }

  chdir("/");
  if (mount("proc", "/proc", "proc", 0, nullptr) != 0) {
    std::cerr << "Error: mount /proc failed: " << strerror(errno) << std::endl;
    return -1;
  }

  char *cmmd[] = {"/bin/sh", nullptr};
  execvp(cmmd[0], cmmd);

  std::cerr << "Error: execv failed: " << strerror(errno) << std::endl;
  return -1;
}
