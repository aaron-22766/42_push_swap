#!/bin/bash

ARG=$(seq $1 | perl -MList::Util=shuffle -e 'print shuffle<STDIN>' | awk '{print}' ORS=' ')
./push_swap "$ARG"
./push_swap $ARG | wc -l
echo $ARG