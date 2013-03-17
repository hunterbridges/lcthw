#!/bin/sh
rm -rf build/include
mkdir build/include
for NAME in `find src -name *.h`
do
    cp $NAME build/include
done

cd build/include
touch liblcthw.h
for HEADER in `ls -1`
do
    echo "#include \"$HEADER\"" >> liblcthw.h
done

cat liblcthw.h

# makeheaders -h src/lcthw/bstree.h src/lcthw/darray.h src/lcthw/darray_algos.h src/lcthw/hashmap.h src/lcthw/hashmap_algos.h src/lcthw/list.h src/lcthw/list_algos.h src/lcthw/radixmap.h src/lcthw/string_algos.h > build/liblcthw.h
# cat src/lcthw/bstrlib.h | col -b >> build/liblcthw.h
