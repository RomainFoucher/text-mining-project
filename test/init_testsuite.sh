#!/bin/bash

path_ref='../ref/linux64/'
path_our='../release/'
path_dbg='../debug/'
path_dict_words='../words.txt'
path_dict_empty='./empty.txt'

./build.sh $path_ref $path_dict_words || exit 2
./build.sh $path_ref $path_dict_empty || exit 2

./build.sh $path_our $path_dict_words || exit 3
./build.sh $path_our $path_dict_empty || exit 3

./build.sh $path_dbg $path_dict_words || exit 4
./build.sh $path_dbg $path_dict_empty || exit 4