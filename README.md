<img src="https://holbertonschool.com.au/wp-content/uplloads/2023/02/Holberton-School.png"> 

# C - Simple Shell 🐚                 
This project is an implementation of a simple UNIX command interpreter, created as part of the Holberton School curriculum. 

## Learning Objectives 🧠

- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How does a shell work
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of main
- How does the shell use the PATH to find the programs
- How to execute another program with the execve system call
- How to suspend the execution of a process until one of its children terminates
- What is EOF / "end-of-file"?

## Project File Table 📁
The following files are included in this project:

| File                                          | Description                                  |
| --------------------------------------------- | -------------------------------------------- |
| [man\_1\_simple\_shell](./man_1_simple_shell) | Manual file                                  |
| [AUTHORS](./AUTHORS)                          | File listing all Authors                     |
| [shell.h](./shell.h)                          | Header file containing prototypes and macros |
| [prompt.c](./prompt.c)      | Displays shell prompt only when running in interactive mode. |
| [main.c](./main.c)                            | Main loop of shell                            |
| [execute.c](./execute.c)                      |                                               |
| [exit.c](./exit.c)                            |                                               |
| [get\_path.c](./get_path.c)                   |                                               |
| [get\_tokens.c](./get_tokens.c)               |                                               |
| [input\_read.c](./input_read.c)               |                                               |
| [builtins.c](./builtin.c)                     |                                               |
| [custom\_funcs.c](./custom_funcs.c)           |                                               |

## Compile ⚙️

Compile program with:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

     
