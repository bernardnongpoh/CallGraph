#!/bin/bash
clang -S -emit-llvm  $1   -o temp.bc
opt -load build/src/CallGraph/libCallGraph.so  -callgraph temp.bc -f -enable-new-pm=0 -o /dev/null

#rm temp.bc
