# ECS150_P1

We used the skeleton code provided on CSIF as a starting point.

We then implemented `pwd` using `getcdw()`, and printed the execution results
to stderr.

Next, we checked if the command entered by the users contains `>`, which means 
that the output of command is redirected to another file different from `
stdout`. If `>` is found in the original command, we extract the name of the 
redirected file and the command withouth redirection separately. After using 
`dup2()`, we can use `execvp()` to output to the specified file. Then we used 
`strtok()` to split the command using space as the delimiter so we can tell 
apart the arguments of the command. We than store the arguments into a list to 
be used later for `execvp()`. We used the structure of 
`fork() -> exec() -> wait()` provided in the text to make system calls and 
capture any potential errors if they arise.

If the original command does not contain any redirection, we directly split the
the command using `strtok()`. Since `cd` is irrevelant to any redirection, we
implement it at this block. For other commands, we used `fork -> exec -> wait`
to make the system calls.

The code we used for splitting the input command referenced this website:
https://www.cplusplus.com/reference/cstring/strtok/.

The code we used for creating a new file and redirect output to it is referenced
from this website:
https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection.
