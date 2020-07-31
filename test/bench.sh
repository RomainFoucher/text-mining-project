#!/bin/bash


path_ref='../ref/linux64/'
path_our='../release/'

files=(
  './1_query_approx_0.txt'
  './1_query_approx_1.txt'
  './1_query_approx_2.txt'
  './1_query_approx_3.txt'
  './1_query_approx_4.txt'
  './1_query_approx_5.txt'
  './3000_queries_approx_0.txt'
  './3000_queries_approx_1.txt'
  './30_queries_approx_2.txt'
  './3000_queries_approx_2.txt'
)

TIMEFORMAT='%R'


function bench_file_on_path {
  file="$1"
  path="$2"

  app="$path"/TextMiningApp
  bin="$path"/words.txt.bin
  time $app "$bin"  < "$file" 1> bench.out 2> bench.out
}

function bench_file_versus {
  file="$1"

  time_our=$(bench_file_on_path "$file" $path_our 2>&1)
  time_ref=$(bench_file_on_path "$file" $path_ref 2>&1)

  if (( $(echo "$time_our > $time_ref" | bc -l) )); then
    printf "\e[31mKO\e[0m: (our=%s  ref=%s)" "$time_our" "$time_ref"
  else
    printf "\e[32mOK\e[0m: (our=%s  ref=%s)" "$time_our" "$time_ref"
  fi
}

function bench {
  for file in "${files[@]}"; do
    bench_file_versus "$file"
    printf "%s \n" " $file"
  done
}
bench