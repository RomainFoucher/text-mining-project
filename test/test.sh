#!/bin/bash


path_ref='../ref/linux64/'
path_our='../release/'
path_dbg='../debug/'


tests_valid=(
  'approx 0 coucou'
  'approx 1 coucou'
  'approx 4 coucou'
  'approx 0 a'
  'approx 1 a'
  'aaaaaaa'
  'approx coucou 1'
  'approx 0 test\napprox 1 test\napprox 2 test\napprox 3 test\napprox 4 test'
  'approx 3 n'
)

function test_case {
  path=$1
  test_=$2
  path_bin="$path"/"$bin"

  echo "$test_" | ./timeout.pl --confess --no-info-on-success -m 512000 "$path"'/TextMiningApp' "$path_bin"
  a=$?
  return $a
}

function print_ok_ko {
  condition=$1

  if [ "$condition" = '0' ]; then
    printf "\e[32mOK\e[0m"
  else
    printf "\e[31mKO\e[0m"
  fi
}

function check_against_ref_on_bin {
  bin=$1

  printf "\e[36mCheck against ref: %s\e[0m\n" "$bin"
  for test_ in "${tests_valid[@]}"; do
    printf "Running %s   " "$test_"
    test_case $path_our "$test_" "$bin"> our.out 2> our.log
    exit_our=$?
    test_case $path_ref "$test_" "$bin"> ref.out 2> ref.log
    exit_ref=$?
    diffed=$(diff our.out ref.out)

    condition=$([ "$diffed" = "" ] && [ $exit_our = $exit_ref ]; echo $?)
    print_ok_ko "$condition"
    printf '\n'
  done
  printf '\n'
}

function check_against_ref {
  check_against_ref_on_bin words.txt.bin
  check_against_ref_on_bin empty.txt.bin
}
check_against_ref


# LEAKS
function check_leak_on_bin {
  bin="$1"
  path_bin="$path_dbg"/"$bin"

  printf '\e[36mCheck leaks: %s\e[0m\n' "$bin"
  for test_ in "${tests_valid[@]}"; do
    printf "Running %s   " "$test_"
    echo "$test_" | "$path_dbg"/TextMiningApp "$path_bin" > dbg.out 2> dbg.err
    exit_dbg=$?

    condition=$([ $exit_dbg = "0" ]; echo $?)
    print_ok_ko "$condition"
    printf '\n'
  done
  printf '\n'
}

function check_leak {
  check_leak_on_bin words.txt.bin
  check_leak_on_bin empty.txt.bin
}
check_leak
