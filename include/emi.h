// TODO Split the header file into smaller header files

#ifndef EMI_H
#define EMI_H

/*** includes ***/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>

/*** defines ***/

// Converts ASCII char into code of CTRL+matching key press
// Terminals erase 3 upper bits of ASCII character to create its CTRL key press code
#define CTRL_KEY(k) ((k) & 0x1f)

/*** function declarations ***/

void initEditor();

#endif // !EMI_H

