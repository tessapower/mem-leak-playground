# Memory Leak Playground

These are my personal notes for myself to help with future debugging. Every `new` or `malloc`  in C++ requires a `delete`/`delete[]` or `free`. Not deallocating allocated stack memory results in memory leaks.

## TL;DR

1. Build the project from the project root or using IDE: `make build`
2. Run the program from the command line: `make run` or `./cmake-build-debug/app/my_app`
3. Open another `Tmux` pane and run `Top` to see memory usage: `top -p $(ps -aux | grep my_app | head -n 1 | awk '{print $2}')`
4. Press `E` to see memory usage in mb in `Top`.
5. Run `Valgrind` to find the memory leak: `valgrind --leak-check=full ./my_app`

## `Top`

`Top` displays Linux processes, but it's not so helpful to run by itself - processes shift around and it's hard to keep track of the one you want:

![Top displaying Linux Processes](/docs/top.png)

We can use the `-p` switch and pass `Top` the PID to watch just our app running:

![Top displaying just one](/docs/top-p.png)

Finding the process each time is repetitive, so we can filter out the PID from the list of processes using:

```shell
ps -aux | grep my_app | head -n 1 | awk '{print $2}'
```

Together with the previous command we get:

```shell
top -p $(ps -aux | grep my_app | head -n 1 | awk '{print $2}')
```

Which displays the memory usage of the app with the new PID each time `Top` is run. Now press `E` to see the memory displayed in different formats, e.g. MB, GB, TB, etc.

![Top displaying different memory format](/docs/top-p-e.png)

## `Valgrind`

`Valgrind` displays memory leaks in programs. Running `valgrind FILE` shows how much memory, if any, was leaked:

![Valgrind displaying memory leak](/docs/valgrind.png)

Running `Valgrind` with `--leak-check=full` reveals the place where the memory leak may be happening and the stack trace:

![Valgrind displaying culprit and stack trace](/docs/valgrind-leak-check.png)

After fixing the leak, running `Valgrind` again displays the happy news:

![Valgrind no leaks](/docs/valgrind-no-leak.png)
