#include "nogvl.h"
#include <stdio.h>

// rb_thread_call_without_gvl
struct nogvl_sleep_args {
    int seconds;
};

// rb_thread_call_without_gvl
static void* nogvl_sleep(void *ptr)
{
    struct nogvl_sleep_args *args = ptr;
    printf("sleep(%d)\n", args->seconds);
    sleep(args->seconds);
    return (void*)Qnil;
}

VALUE run_sleep()
{
    struct nogvl_sleep_args args;
    args.seconds = 100;
    return (VALUE)rb_thread_call_without_gvl(nogvl_sleep, &args, RUBY_UBF_IO, NULL);
}
