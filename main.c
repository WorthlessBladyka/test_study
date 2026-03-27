// I WANT TO PLAY WITH YOU YOUR FRIEND, AI
#include <ncurses.h>
#include "var.h"
#include "hod.h"
#include "draw.h"

// int ball_place(int *x_ball, int *y_ball, int *x_lt_pad, int *y_lt_pad, int *x_rt_pad, int *y_rt_pad, int *dx, int *dy);

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    while ((score_left < 21) && (score_right < 21)) {
        draw(x_ball, y_ball, x_lt_pad, y_lt_pad, x_rt_pad, y_rt_pad, score_left, score_right);
        hod(&x_ball, &y_ball, &y_lt_pad, &y_rt_pad, &dx, &dy);
        // ball_place(&x_ball, &y_ball, &x_lt_pad, &y_lt_pad, &x_rt_pad, &y_rt_pad, &dx, &dy);
    }

    // Вывод победителя
    clear();
    if (score_left >= 21) {
        mvprintw(12, 35, "Победил левый игрок!");
    } else {
        mvprintw(12, 35, "Победил правый игрок!");
    }
    mvprintw(14, 35, "Нажмите любую клавишу для выхода...");
    refresh();
    getch();
    endwin();
    return 0;
}