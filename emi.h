// TODO Split the header file into smaller header files

#ifndef EMI_H
#define EMI_H

/*** includes ***/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>

/*** defines ***/

// Converts ASCII char into code of CTRL+matching key press
// Terminals erase 3 upper bits of ASCII character to create its CTRL key press code
#define CTRL_KEY(k) ((k) & 0x1f)

/*** function declarations ***/

void enableRawMode();
void disableRawMode();
char editorReadKey();
void die(const char *s);
int getWindowSize(int *rows, int *cols);
void initEditor();
/*** structs ***/ 

struct editorConfig {
  int screen_rows;
  int screen_cols;
  struct termios original_termios; //Original terminal settings to restore
};

#endif // !EMI_H

