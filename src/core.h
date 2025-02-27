#ifndef CORE_H
#define CORE_H
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <linux/sched.h>
#include <ostream>
#include <sched.h>
#include <signal.h>
#include <string>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTAINER_ROOTFS "rootfs"
#define CONTAINER_PROC "rootfs/proc"

/* TODO: To be implementation  sys_clone3 syscall*/
int clone3(struct clone_args *cl_args);
char *create_stack(void);
void cleanup_stack(char *stack);
int set_cgroups(char *cg_name);
int exec_container(void *arg);
int set_cgroups(char *cg_name);
#endif // !CORE_H
