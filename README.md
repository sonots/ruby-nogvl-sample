# Nogvl-sample

Test testing `rb_thread_call_without_gvl` with pthread.

## How to run

```
bundle install
bundle exec rake compile
bundle exec ruby test.rb
```

## Result

You should see 3 threads are utilizing 3 CPU cores with `top` command as:

```
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
30914 sonots    20   0  145948  14744   4716 S 301.6  0.0   0:18.47 ruby test.rb
```

## Effect of No GVL

For example, think of IO, while IO.read is waiting and blocking, users may want to run another computation processing to use CPU with another ruby thread. `rb_thread_call_without_gvl` is used for such purpose.

[mysql2](https://github.com/brianmario/mysql2/blob/eca4d2552f605e14d8d935d67c36d7f83b2bf89b/ext/mysql2/client.c#L438) would be a good example for such case.
