#! /bin/sh

CFLAGS=$(pkg-config --cflags vte-2.90)
LIBS=$(pkg-config --libs vte-2.90)

for obj in "configuration" "terminal" "main"; do
  echo "gcc -c -o ${obj}.o ${CFLAGS} ${obj}.c"
  gcc -c -o ${obj}.o ${CFLAGS} ${obj}.c
done

echo "gcc -o sterm ${LIBS} configuration.o terminal.o main.o"
gcc -o sterm ${LIBS} configuration.o terminal.o main.o
