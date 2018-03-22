require "mkmf"

have_header('ruby/thread.h') && have_func('rb_thread_call_without_gvl', 'ruby/thread.h')
$CFLAGS="-g -O0" # debug

$objs = %w[nogvl.o nogvl_sleep.o nogvl_infinite_loop.o nogvl_multithread.o]

create_makefile("nogvl/nogvl")
