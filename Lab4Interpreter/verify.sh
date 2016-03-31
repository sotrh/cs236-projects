#!/bin/bash
LB='\033[1;36m'
NC='\033[0m'
valgrind --leak-check=full $1 "tests/in$2" "actual"
diff "actual" "tests/out$2" && echo -e ${LB}"Test '"$2"' passed"${NC}
