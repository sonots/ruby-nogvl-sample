#include "nogvl.h"

VALUE run_sleep();
VALUE run_infinite_loop();
VALUE run_multithread();

void
Init_nogvl(void)
{
    VALUE mNogvl = rb_define_module("Nogvl");
    rb_define_singleton_method(mNogvl, "sleep", run_sleep, 0);
    rb_define_singleton_method(mNogvl, "infinite_loop", run_infinite_loop, 0);
    rb_define_singleton_method(mNogvl, "multithread", run_multithread, 0);
}
