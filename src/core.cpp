#include "core.h"

char *create_stack(void) {
  const int PAGESIZE = getpagesize();
  void *stack =
      mmap(nullptr, PAGESIZE, PROT_READ | PROT_WRITE,
           MAP_STACK | MAP_GROWSDOWN | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (stack == MAP_FAILED) {
    return nullptr;
  }
  return (static_cast<char *>(stack) + PAGESIZE);
}
void cleanup_stack(char *stack) {
  if (stack != nullptr)
    munmap(stack, getpagesize());
}
/*int set_cgroups(char *cg_name) { std::cout << "continue...\n"; }*/

static int set_hostname(std::string &hostname) {
  struct utsname uts;
  if (sethostname(hostname.c_str(), hostname.length()) == -1)
    return 0;

  if (uname(&uts) == -1)
    return 0;
  return 1;
}

static void set_env(std::string &hostname) {
  setenv("TERM", "xterm-256color", 1);
  setenv("PS1", "[\\u@\\h \\W]\\$ ", 1);
  setenv("PATH", "/bin:/sbin:/usr/bin:/usr/sbin", 1);
  set_hostname(hostname);
}

int exec_container(void *arg) {
  std::string hostname("zcontainer");
  if (mount(nullptr, "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1) {
    std::cerr << "Error: making mounts private => " << strerror(errno)
              << std::endl;
    return -1;
  }

  if (clearenv() != 0) {
    std::cerr << "Error: Failed to clear env\n";
    return -1;
  }

  set_env(hostname);
  if (chroot(CONTAINER_ROOTFS) != 0) {
    std::cerr << "Error: chroot failed=> " << strerror(errno) << std::endl;
    return -1;
  }

  chdir("/");
  if (mount("proc", "/proc", "proc", 0, nullptr) != 0) {
    std::cerr << "Error: mounting /proc failed: " << strerror(errno)
              << std::endl;
    return -1;
  }

  const char *cmmd[] = {"/bin/sh", nullptr};
  execvp(cmmd[0], (char *const *)cmmd);

  std::cerr << "Error: execv failed => " << strerror(errno) << std::endl;
  return -1;
}
