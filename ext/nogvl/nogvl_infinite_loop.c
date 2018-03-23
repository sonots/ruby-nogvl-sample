#include "nogvl.h"
#include <stdio.h>

#define N_LOOP 100000000000

// rb_thread_call_without_gvl
struct nogvl_infinite_loop_args {
    long n_loop;
    int stop;
};

// rb_thread_call_without_gvl
static void* nogvl_infinite_loop(void *ptr)
{
    struct nogvl_infinite_loop_args *args = ptr;
    printf("infinite_loop(%ld)\n", args->n_loop);
    for (size_t i = 0; !args->stop && i < args->n_loop; i++);
    return (void*)Qnil;
}

// rb_thread_call_without_gvl
static void nogvl_infinite_loop_ubf(void *ptr)
{
    struct nogvl_infinite_loop_args *args = ptr;
    args->stop = 1;
}

VALUE run_infinite_loop()
{
    struct nogvl_infinite_loop_args args;
    args.n_loop = N_LOOP;
    args.stop = 0;
    return (VALUE)rb_thread_call_without_gvl(nogvl_infinite_loop, &args, nogvl_infinite_loop_ubf, &args);
}
