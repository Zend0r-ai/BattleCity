#include "Framework.h"
#include "engine.h"

#include <iostream>
#include <sstream>

#include <time.h>
#include <stdlib.h>
#include <utility>


pair<int, int> checkArg(char* argument, char* param) {
    if(string(argument) != "-window")
        throw runtime_error("wrong argument");
//        return false;
    int width = 0, height = 0;
    std::stringstream buf(param);
    buf >> width;
    if(buf.peek() != 'x')
        throw runtime_error("wrong parameters");
    buf.ignore(1);
    buf >> height;
    if(!buf.eof())
        throw runtime_error("wrong parameters");

    if (width <= 0 || height <= 0) {
        throw runtime_error("out of range( <= 0)");
    }
    return {width, height};
}

int main(int argc, char *argv[])
{
    if(argc == 2 || argc > 3) {
        std::cerr << "usage: ./BattleCity [-window 'width'x'height']" << std::endl;
        exit(1);
    }
    pair<int, int> size = {600, 400};
    try {
        if(argc == 3)
            size = checkArg(argv[1], argv[2]);
    } catch (exception& e) {
        std::cerr << "Format is invalid: " << e.what() << std::endl;
        exit(1);
    }
    srand(time(NULL));

    return run(new Engine(size.first, size.second));
}