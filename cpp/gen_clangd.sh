#!/usr/bin/env bash
set -e

cat << EOF > .clangd
# https://clangd.llvm.org/config.html
#
CompileFlags:
  Compiler: arm-none-eabi-g++
  Add: [
    -std=c++20,
EOF

files=($(fd "include*" -t d ..))
for inc in "${files[@]}"; do
	printf "    -I$inc,\n" >> .clangd
done
printf "   ]" >> .clangd
