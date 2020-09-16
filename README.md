## Getting started
- There is a [github repository](https://github.com/Swoorup/mysh) that obeys the order of proceedings pretty nicely. 
- Please make sure to do a `lexer` -> `parser` -> `expander` -> `executor` to make your life easier. [Here](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) is a solid start.
- Make sure that you understand the [shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
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
- malloc
- free
- write
- open
- read
- close
- fork (Create child process.) https://www.geeksforgeeks.org/fork-system-call
- wait (Stop parent process until child process exit.) https://www.geeksforgeeks.org/wait-system-call-c/
- waitpid (The waitpid() function shall be equivalent to wait() if the pid argument is (pid_t)-1 and the options argument is 0. Otherwise, its behavior shall be modified by the values of the pid and options arguments.)
