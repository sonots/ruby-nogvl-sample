require "mkmf"

have_header('ruby/thread.h') && have_func('rb_thread_call_without_gvl', 'ruby/thread.h')
$CFLAGS="-g -O0" # debug

create_makefile("nogvl/nogvl")
