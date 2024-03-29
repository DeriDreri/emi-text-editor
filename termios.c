#include "emi.h"
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <unistd.h>

/*** data ***/


struct editorConfig editor_config;
/*** terminal functions ***/



void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &editor_config.original_termios) == -1) {
    die("tcgetattr");
  }
  atexit(disableRawMode);

  struct termios raw = editor_config.original_termios; 
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    die("tcsetattr");
  }
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &editor_config.original_termios) == -1) {
    die("tcsetattr");
  }
}

void die(const char *s) {
  // Clears the screen on program abort
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

char editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    //Check for error 
    //EAGAIN means time out which for us is not a bug, it's a feature, so we ignore it 
    if (nread == -1 && errno != EAGAIN) { 
      die("read");
    }
  }
  return c;
}

int getWindowSize(int *rows, int *cols) {
  struct winsize window_size;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1 || window_size.ws_col == 0) {
    return -1;
  }
  *cols = window_size.ws_col;
  *rows = window_size.ws_row;
  return 0;
}
