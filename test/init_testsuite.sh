#!/bin/bash

path_ref='../ref/linux64/'
path_our='../release/'
path_dbg='../debug/'

path_dict_words='../words.txt'
path_dict_empty='./empty.txt'
path_dict_same_freq='./dict_same_freq.txt'

./build.sh $path_ref $path_dict_words || exit 1
./build.sh $path_ref $path_dict_empty || exit 1
./build.sh $path_ref $path_dict_same_freq || exit 1

./build.sh $path_our $path_dict_words || exit 1
./build.sh $path_our $path_dict_empty || exit 1
./build.sh $path_our $path_dict_same_freq || exit 1

./build.sh $path_dbg $path_dict_words || exit 1
./build.sh $path_dbg $path_dict_empty || exit 1
./build.sh $path_dbg $path_dict_same_freq || exit 1
