#! /bin/bash

PATH_TO_SRC="../src"
PATH_TO_CMAKE_LISTS="$PATH_TO_SRC/CMakeLists.txt"
CPP_FILES=`find $PATH_TO_SRC -name "*.cpp" | xargs -I % echo -n "% "`
OUTPUT=`sed "s|set(SOURCE_FILES [^)]*)|set(SOURCE_FILES $CPP_FILES)|" "$PATH_TO_CMAKE_LISTS"` && echo "$OUTPUT" > "$PATH_TO_CMAKE_LISTS"