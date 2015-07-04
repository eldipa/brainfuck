# Brainfuck

## Usage

```shell
$ brainfuck <data-array-size> e|c <source>
```

``<data-array-size>`` the size of the data array of the interpreter.
``e|c`` the operation mode: ``e`` execute the code, ``c`` compile it to C++.
``<source>`` the source code file.

## Examples

Read until an EOF or \0 and print in reverse order.

```shell
$ cat examples/tac/code
+[>,]<-[+.<-].

$ echo -n '123456789' | brainfuck 256 e examples/tac/code
987654321

```

Echo the stdin to stdout until EOF

```shell
$ cat examples/echo/code
+[,.] # This is simpler than in C!

$ brainfuck 256 c examples/echo/code
#include <iostream>
#include <vector>

#define N 256
#define AT(x) ((x) % 256)

int main(int argc, char *argv[]) {
int dataptr = 0;
signed char c = 0;
std::vector<signed char> data(N, 0);
data[AT(dataptr)] += 1;
while(data[AT(dataptr)]) {
c = std::cin.get();
data[AT(dataptr)] = std::cin.eof() ? 0 : c;
std::cout << data[AT(dataptr)];
}
return 0;
}

```

### Debugging

```shell
$ cat examples/abort/code
+>++>+++>++++>@<----<---<--<- # PI = 14, PD = 4, Data: 1, 2, 3, 4, 0 , ..., 0

$ brainfuck 16 e examples/abort/code
PI 0000000E
PD 00000004
Data
01 02 03 04 00 00 00 00 00 00 00 00 00 00 00 00

```

## Instruction Set

``>`` Increment in 1 the data pointer.
``<`` Decrement in 1 the data pointer.
``+`` Increment in 1 the value pointed by the data pointer.
``-`` Decrement in 1 the value pointed by the data pointer.
``.`` Print to ``stdout`` the value pointed by the data pointer.
``,`` Read from ``stdin`` and save the value in the slot pointed by the data pointer.
``[`` If the value pointed by the data pointer is zero, update the instruction pointer to the next instruction following the matching ``]``, otherwise do nothing.
``]`` If the value pointed by the data pointer is not zero, update the instruction pointer to the next instruction following the matching ``[``, otherwise do nothing.
``$`` Finish the program.
``@`` Print to ``stderr`` the data and the instruction pointers and the data array.


