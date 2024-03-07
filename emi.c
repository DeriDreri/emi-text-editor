#include "emi.h"

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
  for (int y = 0; y < editor_config.screen_cols; y++) {
    write(STDOUT_FILENO, "~\r\n",3);
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
    die("getWindowSize");
  }
}

int main()
{

  enableRawMode();
  initEditor();

  while(1) {
    editorRefreshScreen();
    editorProcessKeyPress();
  } 

  return EXIT_SUCCESS;
}
