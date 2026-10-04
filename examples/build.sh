#!/bin/sh

comp="cc"
flags="-lraylib -lX11 -lm -lGL -lpthread -ldl -lrt -o"

use() {
    printf "How to:\n
    \e[1;37m$ build.sh -c\e[0m
        Compile all C files.
    \e[1;37m$ build.sh -d\e[0m
        Delete all created bins.
    \e[1;37m$ build.sh\e[0m
        Show this message.
    \e[1;37m$ build.sh -h\e[0m
        Show this message.
    \e[1;37m$ build.sh -u [file].c\e[0m
        Compile one C file.\n"
}

compile_all() {
    for f in *.c; do
        [ -e "$f" ] || continue
        "$comp" $flags "${f%.c}.out" "$f" && printf "Compiled: $f\n" || printf "Failed: $f\n" >&2
    done
}

del() {
    bins=$(ls -I "*.c" -I "*.sh" -I "*.txt")
    rm -fv $bins
}

compile_one() {
    "$comp" $flags "${1%.c}" "$1" && printf "Compiled: $1\n" || printf "Failed: $1\n"
}

case "$1" in
    "-c") compile_all      ;;
    "-d") del              ;;
    "-h") use              ;;
    "-u") compile_one "$2" ;;
    *)    use              ;;
esac
