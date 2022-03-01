# Tests and Assembly


### Use `ifcc-wrapper.sh`

The `.sh` file `ifcc-wrapper.sh` is just a wrapper shell file to call `ifcc` compiler on a specific file, and output the generated text as assembly `.s` file in a specified filepath.

The example bellow shows how to use it, to compile `testfiles/1_return42.c` inside `assembly/1.s`:

```shell
(base)  ❮ onyr ★  kenzae❯ ❮ tests❯❯ ./ifcc-wrapper.sh /home/onyr/Documents/4if/s2/gram_langages/PLD-Compilateur/tests/assembly/1.s testfiles/1_return42.c 
(base)  ❮ onyr ★  kenzae❯ ❮ tests❯❯ cat assembly/1.s 
.globl  main
 main: 
        movl    $42, %eax
        ret
```


### Use `ifcc-test.py`

This simple CLI program is used to automate testing, with Python.

```shell
(base)  ❮ onyr ★  kenzae❯ ❮ tests❯❯ python -V
Python 3.7.9
(base)  ❮ onyr ★  kenzae❯ ❮ tests❯❯ python ifcc-test.py 
usage: ifcc-test.py [-h] [-d] [-v] [-w PATH] PATH [PATH ...]
ifcc-test.py: error: the following arguments are required: PATH
```
