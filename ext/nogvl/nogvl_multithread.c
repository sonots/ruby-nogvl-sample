#include "nogvl.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define N_THREAD 3
#define N_LOOP 100000000000

int stop_multithread = 0;

pid_t gettid(void)
{
    return syscall(SYS_gettid);
}

void *thread_process(void *p)
{
    pid_t current_tid = gettid();
    printf("tid: %d\n", current_tid);
    for (size_t i = 0; !stop_multithread && i < N_LOOP; i++);
    pthread_exit(NULL);
    return 0;
}

int invoke_threads()
{
    pthread_t thread[N_THREAD];
    int ret;
    for (int i = 0; i < N_THREAD; i++) {
        ret = pthread_create(&thread[i], NULL, (void *)thread_process, NULL);
        if (ret < 0) return -1; // failure
    }
    for (int i = 0; i < N_THREAD; i++) {
        ret = pthread_join(thread[i], NULL);
        if (ret != 0) return -1;  // failure
    }
    return 0;
}

// rb_thread_call_without_gvl
struct nogvl_multithread_args {
    long n_thread;
    long n_loop;
};

// rb_thread_call_without_gvl
static void* nogvl_multithread(void *ptr)
{
    struct nogvl_multithread_args *args = ptr;
    printf("N_THREAD %ld\n", args->n_thread);
    printf("N_LOOPD %ld\n", args->n_loop);
    invoke_threads();
    return (void*)Qnil;
}

// rb_thread_call_without_gvl
struct nogvl_multithread_ubf_args {
};

// rb_thread_call_without_gvl
static void nogvl_multithread_ubf(void *ptr)
{
    stop_multithread = 1;
}

VALUE run_multithread()
{
    struct nogvl_multithread_args args;
    args.n_thread = N_THREAD;
    args.n_loop = N_LOOP;
    struct nogvl_multithread_ubf_args ubf_args;
    return (VALUE)rb_thread_call_without_gvl(nogvl_multithread, &args, nogvl_multithread_ubf, &ubf_args);
}
