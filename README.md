# Memory Leak Playground

These are my personal notes for myself to help with future debugging. Every `new` or `malloc`  in C++ requires a `delete`/`delete[]` or `free`. Not deallocating allocated stack memory results in memory leaks.

## TL;DR

1. Build: `cmake -B build && cmake --build build`
2. Run a leak example: `./build/app/mem_leak missing_delete`
3. Run `Valgrind` against it: `valgrind --leak-check=full ./build/app/mem_leak missing_delete`
4. Or run all examples at once: `valgrind --leak-check=full ./build/app/mem_leak all`
5. Use `Top` to watch memory usage: `top -p $(pgrep mem_leak)`

## Leak Examples

The app includes 5 runnable examples, one per common leak category:

| Command | What leaks | Why |
|---|---|---|
| `missing_delete` | `new int[100]` | No matching `delete[]` |
| `lost_pointer` | `new int(1)` | Pointer reassigned before freeing the original |
| `error_path` | `new int[50]` | Early return skips `delete[]` |
| `container` | 5x `new int` in a `vector<int*>` | `vector::clear()` destroys pointers, not pointees |
| `circular` | Two `shared_ptr<Node>` | Circular references keep ref counts above zero |

Run a single example to isolate one leak type in Valgrind output:

```shell
valgrind --leak-check=full ./build/app/mem_leak error_path
```

Or run them all:

```shell
valgrind --leak-check=full ./build/app/mem_leak all
```

Run with no arguments to see usage:

```shell
./build/app/mem_leak
```

## `Valgrind`

`Valgrind` displays memory leaks in programs. Running `valgrind FILE` shows how much memory, if any, was leaked:

![Valgrind displaying memory leak](/docs/valgrind.png)

Running `Valgrind` with `--leak-check=full` reveals the place where the memory leak may be happening and the stack trace:

![Valgrind displaying culprit and stack trace](/docs/valgrind-leak-check.png)

After fixing the leak, running `Valgrind` again displays the happy news:

![Valgrind no leaks](/docs/valgrind-no-leak.png)

## `Top`

`Top` displays Linux processes, but it's not so helpful to run by itself - processes shift around and it's hard to keep track of the one you want:

![Top displaying Linux Processes](/docs/top.png)

We can use the `-p` switch and pass `Top` the PID to watch just our app running:

![Top displaying just one](/docs/top-p.png)

Finding the process each time is repetitive, so we can filter out the PID from the list of processes using:

```shell
ps -aux | grep mem_leak | head -n 1 | awk '{print $2}'
```

Together with the previous command we get:

```shell
top -p $(ps -aux | grep mem_leak | head -n 1 | awk '{print $2}')
```

Which displays the memory usage of the app with the new PID each time `Top` is run. Now press `E` to see the memory displayed in different formats, e.g. MB, GB, TB, etc.

![Top displaying different memory format](/docs/top-p-e.png)
