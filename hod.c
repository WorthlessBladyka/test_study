#include <ncurses.h>
#include "var.h"
#include "hod.h"

// Функция управления ракетками и перемещения мяча
int hod(int *x_ball, int *y_ball,
        int *y_lt_pad, int *y_rt_pad,
        int *dx, int *dy) {

    int c;
    int flag = 1;

    // Устанавливаем таймаут ввода: 2000 миллисекунд (2 секунды)
    if (time_hard > 301) time_hard -= 60;
    timeout(time_hard);

    while (flag) {
        flag = 0;
        c = getch();  // ожидание ввода или ERR по таймауту

        // Если таймаут (нет ввода) — выходим из цикла, перемещаем мяч
        if (c == ERR) {
            break;
        }

        // Управление левой ракеткой: A – вверх, Z – вниз
        if ((c == 'a') || (c == 'A')) {
            if (*y_lt_pad > 6) {
                *y_lt_pad -= 1;
            }
        } else if ((c == 'z') || (c == 'Z')) {
            if (*y_lt_pad < 22) {
                *y_lt_pad += 1;
            }
        }
        // Управление правой ракеткой: K – вверх, M – вниз
        else if ((c == 'k') || (c == 'K')) {
            if (*y_rt_pad > 6) {
                *y_rt_pad -= 1;
            }
        } else if ((c == 'M') || (c == 'm')) {
            if (*y_rt_pad < 22) {
                *y_rt_pad += 1;
            }
        }
        // Пробел – бездействие (мяч всё равно двигается)
        else if (c == ' ') {
            // Ничего не делаем, просто выходим с flag=0
        }
        // Любой другой символ – ошибка, повтор запроса
        else {
            flag = 1;
            printf("%d", time_hard);
            refresh();
        }
    }

    // Сбрасываем таймаут в блокирующий режим для остальной программы
    timeout(-1);

    // Перемещаем мяч (при любом выходе из цикла)
    *x_ball += *dx;
    *y_ball += *dy;

    return 0;
}