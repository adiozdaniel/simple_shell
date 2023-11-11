# THE GATES OF HELL

![plot](./test/shell.jpeg)

This **SIMPLE SHELL** program was written entirely in C as a milestone project for ALX Africa Software Engineering. It replicates functionalities of UNIX shell (sh).

## Installation

* Clone this repository.
* cd to **test** directory
* Compile it using ```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 ../*.c -o hsh```
* run ```./hsh```

### Usage

After compilation, the resulting program can run stand-alone, either in interactive or non-interactive mode.

#### Interactive Mode

In interactive mode, simply run the program and wait for the prompt to appear. From there, you can type commands freely, exiting with either the "exit" command or ctrl-D.

#### Non-Interactive Mode

In non-interactive mode, echo your desired command and pipe it into the program like this:

```sh
echo "ls" | ./shell
```

In non-interactive mode, the program will exit after finishing your desired command(s).

#### Included Built-Ins

Our shell has support for the following built-in commands:

| Command             | Definition                                                                                |
| ------------------- | ----------------------------------------------------------------------------------------- |
| exit [n]            | Exit the shell, with an optional exit status, n.                                          |
| env                 | Print the environment.                                                                    |
| setenv [var] [value] | Set an environment variable and value. If the variable exists, the value will be updated. |
| unsetenv [var]      | Remove an environment variable.                                                           |
| cd [dir]            | Change the directory.                                                                     |
| help [built-in]     | Read documentation for a built-in.                                                        |

## Contact

Feel free to reach out with any questions, suggestions, or contributions to:

* **Engr. Happy Felix Chukwuma**
  * [Contact Engr. Happy Chukwuma](mailto:<happychukwuma@gmail.com>?subject=[_Collaboration_on_SIMPLE_SHELL])

* **Engr. Adioz Daniel**
  * [Contact Engr. Adioz Daniel](mailto:<adiozdaniel@gmail.com>?subject=[_Collaboration_on_SIMPLE_SHELL])
