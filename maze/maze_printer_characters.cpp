#include <climits>

#include "maze.h"

namespace maze {
std::map<char, std::string> const MazePrinter::characters{
    /* Single line characters */
    {0x0, "┼"},
    {0x1, "┬"},
    {0x2, "┤"},
    {0x3, "┐"},

    {0x4, "┴"},
    {0x5, "─"},
    {0x6, "┘"},
    {0x7, "─"},

    {0x8, "├"},
    {0x9, "┌"},
    {0xa, "│"},
    {0xb, "│"},

    {0xc, "└"},
    {0xd, "─"},
    {0xe, "│"},
    {0xf, " "},

    /* Double line characters - only used externally */

    {0x10, "╬"},
    {0x11, "╤"},
    {0x12, "╢"},
    {0x13, "╗"},

    {0x14, "╧"},
    {0x15, "═"},
    {0x16, "╝"},
    {0x17, "═"},

    {0x18, "╟"},
    {0x19, "╔"},
    {0x1a, "║"},
    {0x1b, "║"},

    {0x1c, "╚"},
    {0x1d, "═"},
    {0x1e, "║"},
    {0x1f, " "},
};

}  // namespace maze
