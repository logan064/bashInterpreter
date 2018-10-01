# bashInterpreter
A C implementation of a bash interpreter that can also support commands like history, !!, and !N.

My program allows for a user to run commands using the POSIX api system calls.
Each command is run using a fork() system call and can be run concurrently by running a command followed by an ' &'.
to exit the program sucessfully type the command "exit".
