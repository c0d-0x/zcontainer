#ifndef CORE_H
#define CORE_H
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <linux/sched.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define CONTAINER_ROOTFS "rootfs"
#define CONTAINER_PROC "rootfs/proc"
int clone3(struct clone_args *cl_args);
void *create_stack(void);
int set_cgroups(char *cg_name);
int exec_container(void *arg);
#endif // !CORE_H
