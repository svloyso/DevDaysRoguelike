#include "myvisitor.h"
#include <string>

void MyVisitor::init_map ()
{
    codes["1111"] = "\u253C";
    codes["1110"] = "\u2534";
    codes["1101"] = "\u2524";
    codes["0111"] = "\u251C";
    codes["1011"] = "\u252C";
    codes["0101"] = "\u2502";
    codes["1010"] = "\u2500";
    codes["1100"] = "\u2518";
    codes["0110"] = "\u2514";
    codes["0011"] = "\u250C";
    codes["1001"] = "\u2510";
    codes["0100"] = "\u2575";
    codes["0010"] = "\u2576";
    codes["0001"] = "\u2577";
    codes["1000"] = "\u2574";
    codes["0000"] = " ";
}