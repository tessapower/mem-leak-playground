# Memory Leak Playground

Every `new` or `malloc`  in C++ requires a `delete`/`delete[]` or `free`. Not deallocating allocated stack memory results in memory leaks.

1. Build the project from the project root or using IDE: `make build`
2. Run the program from the command line: `make run` or `./dist/my_app`
3. Open another `Tmux` pane and run `Top` to see memory usage: `top -p $(ps -aux | grep my_app | head -n 1 | awk '{print $2}')`
4. Press `E` to see memory usage in mb in `Top`.
5. Run `Valgrind` to find the memory leak: `valgrind --leak-check=full ./my_app`
