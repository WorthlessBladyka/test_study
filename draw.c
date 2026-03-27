#include <ncurses.h>

// Функция отрисовки игрового поля
int draw(int x_ball, int y_ball, int x_lt_pad, int y_lt_pad, 
         int x_rt_pad, int y_rt_pad, int score_left, int score_right) {

    clear();  // очистка экрана (аналог printf("\033[H\033[J"))

    // Игровое поле 25 строк (y) и 80 столбцов (x)
    for (int y = 1; y <= 25; y++) {
        for (int x = 1; x <= 80; x++) {

            // Верхняя и нижняя границы (y == 1, y == 5, y == 25)
            if ((y == 5) || (y == 25) || (y == 1)) {
                mvprintw(y - 1, x - 1, "-");
            }
            // Мяч
            else if ((x_ball == x) && (y_ball == y)) {
                mvprintw(y - 1, x - 1, "0");
            }
            // Левая ракетка (вертикальная черта) – занимает 3 клетки
            else if ((x_lt_pad == x) && ((y_lt_pad == y) || (y_lt_pad == y - 1) || (y_lt_pad == y - 2))) {
                mvprintw(y - 1, x - 1, "|");
            }
            // Правая ракетка
            else if ((x_rt_pad == x) && ((y_rt_pad == y) || (y_rt_pad == y - 1) || (y_rt_pad == y - 2))) {
                mvprintw(y - 1, x - 1, "|");
            }
            // Левая и правая границы поля (x == 1 или x == 80)
            else if ((x == 1) || (x == 80)) {
                mvprintw(y - 1, x - 1, "|");
            }
            // Вывод счета левого игрока (позиция y=3, x=20)
            else if ((y == 3) && (x == 20)) {
                mvprintw(y - 1, x - 1, "%02d", score_left);
            }
            // Пропуск второго символа для выравнивания
            else if ((y == 3) && (x == 21)) {
                // пусто, чтобы не нарушать формат
            }
            // Вывод счета правого игрока (позиция y=3, x=60)
            else if ((y == 3) && (x == 60)) {
                mvprintw(y - 1, x - 1, "%02d", score_right);
            }
            // Пропуск второго символа
            else if ((y == 3) && (x == 61)) {
            }
            // Остальное – пустое место
            else {
                mvprintw(y - 1, x - 1, " ");
            }
        }
    }
    refresh();  // обновление экрана
    return 0;
}