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
