
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "parse.h"
#include "init_parse.h"

int main(int argc, char** argv) {
    init_parse_config_file("./data/init.rc");

    return 0;
}