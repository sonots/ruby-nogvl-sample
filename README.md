# Nogvl-sample

Test testing `rb_thread_call_without_gvl` with pthread.

## How to build

```
bundle install
bundle exec rake compile
```

## How to run

There 3 samples:

```
bundle exec ruby examples/nogvl_sleep.rb
bundle exec ruby examples/nogvl_infinite_loop.rb
bundle exec ruby examples/nogvl_multithread.rb
```

## Result

`examples/nogvl_multithread.rb` should show that 3 threads are utilizing 3 CPU cores with `top` command as:

```
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
30914 sonots    20   0  145948  14744   4716 S 301.6  0.0   0:18.47 ruby test.rb
```

## Effect of No GVL

For example, think of IO, while IO.read is waiting and blocking, users may want to run another computation processing to use CPU with another ruby thread. `rb_thread_call_without_gvl` is used for such purpose.

[mysql2](https://github.com/brianmario/mysql2/blob/eca4d2552f605e14d8d935d67c36d7f83b2bf89b/ext/mysql2/client.c#L438) would be a good example for such case.

## References

https://github.com/ruby/ruby/blob/b6e2c52857056b41de8391816fe373de47f32c84/thread.c#L1414
