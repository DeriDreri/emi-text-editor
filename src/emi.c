#include "../include/emi.h"
#include "../include/termios.h"
#include <stdio.h>
#include <stdlib.h>
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

void editorDrawRows(struct appendBuffer *buffer) {
  for (int y = 0; y < editor_config.screen_rows; y++) {

    // Display welcome message
    if (y == editor_config.screen_rows / 3) {
      char welcome[80];

      // Place at 1/3 height of the screen 
      int welcomeLength = snprintf(welcome, sizeof(welcome), "Emi editor -- version %s", EMI_VERSION);
      welcomeLength = welcomeLength > editor_config.screen_cols ? editor_config.screen_cols : welcomeLength;
      
      // Center it 
      int padding = (editor_config.screen_cols / 2) - (welcomeLength / 2);
      if (padding) {
        abAppend(buffer, "~", 1);
        padding--;
      }
      while (padding--) {
        abAppend(buffer, " ", 1);
      }

      abAppend(buffer, welcome, welcomeLength);
    } else {
      abAppend(buffer, "~", 1);
    }

    // Clear the line 
    abAppend(buffer, "\x1b[K", 3);
    if (y < editor_config.screen_rows-1) {
      abAppend(buffer, "\r\n", 2);
    }
  }
}

void editorRefreshScreen() {
  struct appendBuffer buffer = ABUF_INIT;

  abAppend(&buffer, "\x1b[?25l", 6);
  abAppend(&buffer, "\x1b[H", 3);

  editorDrawRows(&buffer);

  abAppend(&buffer, "\x1b[1;2H", 6);
  abAppend(&buffer, "\x1b[?25h", 6);
  
  write(STDOUT_FILENO, buffer.base, buffer.len);
  abFree(&buffer);
}

/*** buffer ***/

void abAppend(struct appendBuffer *buffer, const char *string, const int len) {
  char * new = realloc(buffer -> base, buffer -> len + len);

  if (new == NULL) return;
  memcpy(&new[buffer -> len], string, len);

  buffer -> base = new;
  buffer -> len += len;
}

void abFree(struct appendBuffer *bufffer) {
  free(bufffer -> base);
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

  while(1) {
    editorRefreshScreen();
    editorProcessKeyPress();
  } 

  return EXIT_SUCCESS;
}
