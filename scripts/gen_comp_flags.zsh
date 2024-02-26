#!/usr/bin/env zsh
set -e

FILE=cpp/compile_flags.txt
pref="-I"

cat <<EOF >$FILE
/opt/gcc-arm-none-eabi/bin/arm-none-eabi-g++
-std=c++23,
EOF

pushd cpp
files="$(fd 'include*' -t d ..)"
popd

# Split the string on newlines and loop through each line
for line in ${(f)files}; do
    # Prefix each line with '-I' and print
    echo "$pref$line" >> $FILE
done
