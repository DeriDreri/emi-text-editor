#include "../include/emi.h"
#include "../include/termios.h"
#include <unistd.h>

/*** data ***/

extern struct editorConfig editor_config;

/*** input ***/

void editorProcessKeyPress() {
  char c = editorReadKey();

  switch(c) {
    case CTRL_KEY('q'):
      //Clears screen before exit
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);
      break;
    default:
      printf("%d\r\n", c);
      break;
  }
}

/*** output ***/ 

void editorDrawRows() {
  for (int y = 0; y < editor_config.screen_rows; y++) {
    write(STDOUT_FILENO, "~", 1);

    if (y < editor_config.screen_rows-1) {
      write(STDIN_FILENO, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  editorDrawRows();

  write(STDOUT_FILENO, "\x1b[1;2H", 6);
}

/*** entry point ***/

void initEditor() {
  if (getWindowSize(&editor_config.screen_rows, &editor_config.screen_cols) == -1) {
    die("Unable to determine windows size");
  }
}

int main()
{
  enableRawMode();
  initEditor();
  editorRefreshScreen();

  while(1) {
    editorProcessKeyPress();
  } 

  return EXIT_SUCCESS;
}
