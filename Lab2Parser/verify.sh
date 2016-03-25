#!/bin/bash
LB='\033[1;36m'
NC='\033[0m'
valgrind --leak-check=full ./lab "tests/in$1" "actual"
diff "actual" "tests/out$1" && echo -e ${LB}"Test '"$1"' passed"${NC}
