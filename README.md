## Getting started
- There is a [github repository](https://github.com/Swoorup/mysh) that obeys the order of proceedings pretty nicely. 
- Please make sure to do a `lexer` -> `parser` -> `expander` -> `executor` to make your life easier. [Here](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) is a solid start.
- Make sure that you understand the [shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Making your own shell](https://www.geeksforgeeks.org/making-linux-shell-c/)
## Partes del Proyecto
- [ ] Lexer: tokenizes input
- [ ] Parser: builds Command Table from tokens
- [ ] Executor: generates processes for each command, creates pipes, redirects
## Roadmap
1. Entender sintáxis y funcionamiento de bash que nos piden.
2. Idear arquitectura **LPEE** que no nos haga _espaguetificar_ el asunto.
3. ???
4. Profit
## Funciones a utilizar
- **malloc**
- **free**
- **write**
- **open**
- **read**
- **close**
- **fork** ([Creates a child process](https://www.geeksforgeeks.org/fork-system-call))
- **wait** ([Stops the parent process until the child process exit](https://www.geeksforgeeks.org/wait-system-call-c/))
- **waitpid** ([The waitpid() function shall be equivalent to wait() if the pid argument is (pid_t)-1 and the options argument is 0. Otherwise, its behavior shall be modified by the values of the pid and options arguments](https://linux.die.net/man/3/waitpid))
- **wait3, wait4** ([Obsolete](https://linux.die.net/man/2/wait3))
- **signal** ([Sets a function to handle a signal](https://www.tutorialspoint.com/c_standard_library/c_function_signal.htm))
- **kill** ([Sends a signal to a process or a group of processes](https://linux.die.net/man/3/kill))
- **exit** ([Terminates a process immediately, special handle for child processes](https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm))
- **getcwd** ([Saves the pathname of your current working directory in a string](https://pubs.opengroup.org/onlinepubs/009695399/functions/getcwd.html))
- **chdir** ([Changes your current working directory](https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/))
- **stat, lstat, fstat** ([Returns information about a file](https://man7.org/linux/man-pages/man2/stat.2.html))
  - stat = Standar
  - lstat = For symbolic links
  - fstat = Gets the file from a file descriptor
