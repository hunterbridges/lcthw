#!/bin/sh
makeheaders -h src/lcthw/bstree.h src/lcthw/darray.h src/lcthw/darray_algos.h src/lcthw/hashmap.h src/lcthw/hashmap_algos.h src/lcthw/list.h src/lcthw/list_algos.h src/lcthw/radixmap.h src/lcthw/string_algos.h > build/liblcthw.h
cat src/lcthw/bstrlib.h | col -b >> build/liblcthw.h
