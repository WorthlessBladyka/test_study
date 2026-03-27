// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

// Функция физики мяча (пока не реализована)
// int ball_place(int *x_ball, int *y_ball,
//                int *x_lt_pad, int *y_lt_pad,
//                int *x_rt_pad, int *y_rt_pad,
//                int *dx, int *dy) {
// }

// Функция управления ракетками и перемещения мяча
int hod(int *x_ball, int *y_ball,
        int *y_lt_pad, int *y_rt_pad,
        int *dx, int *dy) {

    char c;
    int flag = 1;

    while (flag) {
        flag = 0;
        scanf("%c", &c);

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
        }
        // Перевод строки – продолжение цикла (ожидание корректного ввода)
        else if (c == '\n') {
            flag = 1;
        }
        // Любой другой символ – ошибка, повтор запроса
        else {
            flag = 1;
            printf("Неверный ввод");
        }

        // Если введена команда движения ракетки, мяч перемещается
        if (flag == 0) {
            *x_ball += *dx;
            *y_ball += *dy;
        }
    }
    return 0;
}

// Функция отрисовки игрового поля
int draw(int x_ball, int y_ball,
         int x_lt_pad, int y_lt_pad,
         int x_rt_pad, int y_rt_pad,
         int score_left, int score_right) {

    // Очистка экрана (ANSI-код)
    printf("\033[H\033[J");

    // Игровое поле 25 строк (y) и 80 столбцов (x)
    for (int y = 1; y <= 25; y++) {
        for (int x = 1; x <= 80; x++) {

            // Верхняя и нижняя границы (y == 1, y == 5, y == 25)
            // Обратите внимание: в исходном коде y == 5 – линия, но она не описана в условии,
            // возможно, планировалась сетка. Оставим как есть.
            if ((y == 5) || (y == 25) || (y == 1)) {
                printf("-");
            }
            // Мяч
            else if ((x_ball == x) && (y_ball == y)) {
                printf("0");
            }
            // Левая ракетка (вертикальная черта) – занимает 3 клетки
            else if ((x_lt_pad == x) && ((y_lt_pad == y) || (y_lt_pad == y - 1) || (y_lt_pad == y - 2))) {
                printf("|");
            }
            // Правая ракетка
            else if ((x_rt_pad == x) && ((y_rt_pad == y) || (y_rt_pad == y - 1) || (y_rt_pad == y - 2))) {
                printf("|");
            }
            // Левая и правая границы поля (x == 1 или x == 80)
            else if ((x == 1) || (x == 80)) {
                printf("|");
            }
            // Вывод счета левого игрока (позиция y=3, x=20)
            else if ((y == 3) && (x == 20)) {
                printf("%02d", score_left);
            }
            // Пропуск второго символа для выравнивания
            else if ((y == 3) && (x == 21)) {
                // пусто, чтобы не нарушать формат
            }
            // Вывод счета правого игрока (позиция y=3, x=60)
            else if ((y == 3) && (x == 60)) {
                printf("%02d", score_right);
            }
            // Пропуск второго символа
            else if ((y == 3) && (x == 61)) {
            }
            // Остальное – пустое место
            else {
                printf(" ");
            }
        }
        printf("\n"); // переход на новую строку
    }
    return 0;
}

int main() {
    // Начальные координаты
    int y_lt_pad = 14;   // вертикальная позиция левой ракетки (верхний край)
    int x_lt_pad = 3;    // горизонтальная позиция левой ракетки
    int y_rt_pad = 14;   // вертикальная позиция правой ракетки
    int x_rt_pad = 78;   // горизонтальная позиция правой ракетки
    int x_ball = 40;     // начальная x мяча
    int y_ball = 15;     // начальная y мяча
    int score_left = 0;  // счет левого игрока
    int score_right = 0; // счет правого игрока
    int dx = 1;          // скорость по x (1 вправо)
    int dy = 1;          // скорость по y (1 вниз)

    // Игра продолжается, пока никто не набрал 21 очко
    while ((score_left < 21) && (score_right < 21)) {
        draw(x_ball, y_ball,
             x_lt_pad, y_lt_pad,
             x_rt_pad, y_rt_pad,
             score_left, score_right);

        hod(&x_ball, &y_ball,
            &y_lt_pad, &y_rt_pad,
            &dx, &dy);

        // Функция физики пока закомментирована
        // ball_place(&x_ball, &y_ball,
        //            &x_lt_pad, &y_lt_pad,
        //            &x_rt_pad, &y_rt_pad,
        //            &dx, &dy);
    }
    return 0;
}