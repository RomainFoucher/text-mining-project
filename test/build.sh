#!/bin/sh

[ $# != 2 ] && echo "need 2 arguments" && exit 1
path=$(pwd)/$1
dict=$(pwd)/$2
bin="$path"/$(basename -- "$dict").bin

echo "cd $path"
cd "$path" || exit 1

make

if test ! -f "$dict"; then echo "$dict dictionary not found"; exit 1; fi

if [ ! "$(./TextMiningCompiler "$dict" "$bin"; echo $?)" ]; then
  echo "failed to generate bin file: $bin"
  exit 1
fi

printf "init %s done\n\n\n" "$path"