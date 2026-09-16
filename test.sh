#!/bin/sh

set -xe

gcc raygraph.c ./examples/"$1".c -o ./examples/"$1".out -lraylib -lX11 -lm -lGL -lpthread -ldl -lrt && ./examples/"$1".out
