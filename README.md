# Programing language gallop

"gallop" is a new programing language

## Requirement package

- clang (>= 19.0.0)
- llvm (>= 19.0.0)
- cmake (>= 3.29.0)

## What to do after installation

copy the command script file for cmake.

### copy cmake script for Windows

```cmd

cd bootstrap0
copy cmake.cmd.sample cmake.cmd
 
```

### copy cmake script for Unix(or Linux/MacOS X)

```shell

cd bootstrap0
cp cmake.sh.sample cmake.sh

```

## build command

run the following to build the compiler:

### build for Windows

```cmd

cd bootstrap0
cmake.cmd
 
```

### build for Unix(or Linux/MacOS X)


```shell

cd bootstrap0
sh cmake.sh

```
