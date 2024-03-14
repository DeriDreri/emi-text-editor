#ifndef TERM_H
#define TERM_H

/*** defines ***/ 
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <ctype.h>

/*** functions ***/
void enableRawMode();
void disableRawMode();
char editorReadKey();
void die(const char *s);
int getWindowSize(int *rows, int *cols);

/*** structs ***/ 

struct editorConfig {
  int screen_rows;
  int screen_cols;
  struct termios original_termios; //Original terminal settings to restore
};

#endif // !TERM_H
