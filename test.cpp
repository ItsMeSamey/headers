#include <cstdlib>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    (char *)"Choice 1", (char *)"Choice 2", (char *)"Choice 3",
    (char *)"Choice 4", (char *)"Exit",
};

int main() {
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)malloc((n_choices + 1) * sizeof(ITEM *));

  for (i = 0; i < n_choices; ++i)
    my_items[i] = new_item(choices[i], choices[i]);
  my_items[n_choices] = (ITEM *)NULL;

  my_menu = new_menu((ITEM **)my_items);

  int _y = 2, _x = 3;
  menu_format(my_menu, &_y, &_x);
  set_menu_opts(my_menu, O_MOUSE_MENU);
  //   set_menu_opts( my_menu, O_ROWMAJOR | O_MOUSE_MENU);
  mvprintw(LINES - 2, 0, "F1 to Exit");
  post_menu(my_menu);
  refresh();

  while ((c = getch()) != KEY_F(1)) {
    switch (c) {
    case KEY_DOWN:
      menu_driver(my_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(my_menu, REQ_UP_ITEM);
      break;
    case KEY_LEFT:
      menu_driver(my_menu, REQ_LEFT_ITEM);
      break;
    case KEY_RIGHT:
      menu_driver(my_menu, REQ_RIGHT_ITEM);
      break;
    }
  }

  free_item(my_items[0]);
  free_item(my_items[1]);
  free_menu(my_menu);
  endwin();
}
