# pipex

This is a [42 School](https://www.42lausanne.ch/) project. It is a program which goal is to make familiar with 
UNIX pipes and I/O redirection.
<br>
It is executed as follows:

```shell
./pipex file1 cmd1 ... cmdN file2
```

It behaves like the following:

```shell
 < file1 cmd1 | ... | cmdN > file2
```

It also features a HereDoc implementation:

```shell
/pipex here_doc LIMITER cmd cmd1 file
```

Equivalent to:
```shell
cmd << LIMITER | cmd1 >> file
```

Like most 42 C projects, there are some constraints. First, only those functions are allowed: `open, close, read,
write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe,unlink, wait, waitpid`.
Second, the code must follow the [norm](https://github.com/MagicHatJo/-42-Norm/blob/master/norme.en.pdf).

This project is also an important prerequisite for another project, which consists of a small shell.


### Note that this project is WIP and not fully functional yet
