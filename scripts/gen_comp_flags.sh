#!/usr/bin/env bash
set -e

FILE=cpp/compile_flags.txt

cat <<EOF >$FILE
/opt/gcc-arm-none-eabi/bin/arm-none-eabi-g++
-std=c++20,
EOF

pushd cpp
files=($(fd "include*" -t d ..))
popd

pref="-I"
for inc in "${files[@]}"; do
	echo "${pref}${inc}" >>$FILE
done
