// TODO Split the header file into smaller header files

#ifndef EMI_H
#define EMI_H

/*** includes ***/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*** defines ***/

// Converts ASCII char into code of CTRL+matching key press
// Terminals erase 3 upper bits of ASCII character to create its CTRL key press code
#define CTRL_KEY(k) ((k) & 0x1f)
// Default constructor for appendBuffer
#define ABUF_INIT {NULL, 0}
// Version of the editor
#define EMI_VERSION "0.0.1"
/*** structs ***/

struct appendBuffer {
  char *base;
  int len;
};

/*** function declarations ***/

void initEditor();
void abAppend(struct appendBuffer *buffer, const char *string, const int len);
void abFree(struct appendBuffer * buffer);

#endif // !EMI_H

