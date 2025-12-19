#define _CRT_SECURE_NO_WARNINGS
#define SCREENW 80
#define SCREENH 25

#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

typedef double (*TFun)(double);

double Y(double);
double V(double);
double find_min(TFun, double, double, double);
double find_max(TFun, double, double, double);
void print_table(TFun, double, double, double);
void print_graph(TFun, double, double, double);
int count_pos(TFun, double, double, double);
int oper_suggest(int choice);

int main()
{
    setlocale(LC_ALL, "RUS");
    printf("\n");
    printf("                                 __________________________________________________ \n");
    printf("                                |                                                  |\n");
    printf("                                |                 Курсовой проект                  |\n");
    printf("                                |       Разработка программы анализа функций       |\n");
    printf("                                |            Выполнил: Калашников Д.А.             |\n");
    printf("                                |            Руководитель: Курипта О.В.            |\n");
    printf("                                |                Группа: бИПТ-251                  |\n");
    printf("                                |                                                  |\n");
    printf("                                |__________________________________________________| \n");
    printf("\n");

    int func_choice;
    TFun selected_func;
    char* func_name;

    while (1) {
        printf("\n  Выберите функцию:\n");
        printf("\n");
        printf("    1 - Тригонометрическая функция Y(x)\n");
        printf("\n");
        printf("            sin(x^2 + x^-1 + x^1/3)\n");
        printf("    Y(x) = ___________________________ * 10^-6\n");
        printf("               tg(e^cos(x^1/2))\n");
        printf("\n\n");
        printf("\n    2 - Кусочная функция V(x)\n\n");
        printf("             __\n");
        printf("            |\n");
        printf("            |   2 * cos^3(x^2) + sin^2(x^3) - 0.08 * (x^3 + 0.2), при x < 1\n");
        printf("    V(x) =  | \n");
        printf("            |   2 * cos^3(x^2) + sin^2(x^3) - 0.08 * (x + x), при x >= 1\n");
        printf("            |__\n");
        printf("\n");
        printf("\n  Ваш выбор: ");
        scanf("%d", &func_choice);

        switch (func_choice) {
        case 1:
            selected_func = Y;
            func_name = "Y(x)";
            break;
        case 2:
            selected_func = V;
            func_name = "V(x)";
            break;
        default:
            printf("Неверный выбор функции!\n");
            continue;
        }

        int choice = 0, op_choice, auto_next = 0;
        double x, start, end, step;

        while (1) {

            if (auto_next == 0) {
                printf("\n    =====================================\n");
                printf("                      МЕНЮ              \n");
                printf("    =====================================\n");
                printf("    1. Вычислить значение %s\n", func_name);
                printf("    2. Табулировать %s\n", func_name);
                printf("    3. Определить минимум/максимум %s\n", func_name);
                printf("    4. Построить график %s\n", func_name);
                printf("    5. Посчитать количество положительных значений %s\n", func_name);
                printf("    0. Вернуться к выбору функции\n");
                printf("    =====================================\n");
                printf("    Ваш выбор: ");
                scanf("%d", &choice);
            }
            else {
                choice = auto_next;
                auto_next = 0;
            }

            switch (choice) {
            case 0:
                printf("    Возврат к выбору функции...\n");
                goto next_function;

            case 1:
                printf("    Введите x для вычисления %s: ", func_name);
                scanf("%lf", &x);
                printf("%s(%.3f) = %.8f\n", func_name, x, selected_func(x));
                break;

            case 2:
                printf("    Введите начало интервала для табуляции %s: ", func_name);
                scanf("%lf", &start);
                printf("    Введите конец интервала для табуляции %s: ", func_name);
                scanf("%lf", &end);
                printf("    Введите шаг для табуляции %s: ", func_name);
                scanf("%lf", &step);
                print_table(selected_func, start, end, step);
                break;

            case 3:
                printf("\n  Выберите операцию для %s:\n", func_name);
                printf("    1 - Найти минимум %s\n", func_name);
                printf("    2 - Найти максимум %s\n", func_name);
                printf("    0 - Вернуться назад\n");
                printf("    Ваш выбор: ");
                scanf("%d", &op_choice);

                if (op_choice == 0) break;

                printf("    Введите начало интервала: ");
                scanf("%lf", &start);
                printf("    Введите конец интервала: ");
                scanf("%lf", &end);
                printf("    Введите шаг: ");
                scanf("%lf", &step);

                if (op_choice == 1) {
                    double min_x = find_min(selected_func, start, end, step);
                    printf("    Минимум функции %s: f(%.3f) = %.8f\n", func_name, min_x, selected_func(min_x));
                }
                else {
                    double max_x = find_max(selected_func, start, end, step);
                    printf("    Максимум функции %s: f(%.3f) = %.8f\n", func_name, max_x, selected_func(max_x));
                }
                break;

            case 4:
                printf("    Введите начало интервала: ");
                scanf("%lf", &start);
                printf("    Введите конец интервала: ");
                scanf("%lf", &end);
                printf("    Введите шаг: ");
                scanf("%lf", &step);
                print_graph(selected_func, start, end, step);
                break;

            case 5:
                printf("    Введите начало интервала: ");
                scanf("%lf", &start);
                printf("    Введите конец интервала: ");
                scanf("%lf", &end);
                printf("    Введите шаг: ");
                scanf("%lf", &step);
                printf("    Количество положительных значений: %d\n",
                    count_pos(selected_func, start, end, step));
                break;

            default:
                printf("    Неверный выбор меню!\n");
            }
        }

    next_function:;
    }
}

double Y(double x)
{
    if (x <= 0) return NAN;

    return (sin(x * x + 1.0 / x + pow(x, 1.0 / 3.0)) / tan(exp(cos(sqrt(x))))) * 1e-6;
}

double V(double x)
{
    double phi;
    if (x < 1)
        phi = x * x * x + 0.2;
    else
        phi = x + x;

    return 2 * pow(cos(x * x), 3) + pow(sin(x * x * x), 2) - 0.08 * phi;
}

void print_table(TFun func, double start, double end, double step) {
    printf("    x\t\t  f(x)\n");
    printf("    ---------------------------------\n");
    for (double x = start; x <= end; x += step) {
        double val = func(x);

        if (isnan(val) || isinf(val))
            printf("    %-12.8f |   --- (нет значения)\n", x);
        else
            printf("    %-12.8f | %-30.8f\n", x, val);
    }
}

double find_min(TFun func, double start, double end, double step)
{
    double min_val = 1e100;
    double min_x = NAN;

    for (double x = start; x <= end; x += step) {
        double y = func(x);
        if (isnan(y) || isinf(y)) continue;
        if (y < min_val) {
            min_val = y;
            min_x = x;
        }
    }
    return min_x;
}

double find_max(TFun func, double start, double end, double step)
{
    double max_val = -1e100;
    double max_x = NAN;

    for (double x = start; x <= end; x += step) {
        double y = func(x);
        if (isnan(y) || isinf(y)) continue;
        if (y > max_val) {
            max_val = y;
            max_x = x;
        }
    }
    return max_x;
}

void print_graph(TFun func, double start, double end, double step)
{
    char screen[SCREENW][SCREENH];
    double y[SCREENW];

    double ymin = 1e100, ymax = -1e100;
    double hx = (end - start) / (SCREENW - 1);
    double x;

    for (int i = 0; i < SCREENW; i++)
    {
        x = start + i * hx;
        y[i] = func(x);

        if (!isnan(y[i]) && !isinf(y[i]))
        {
            if (y[i] < ymin) ymin = y[i];
            if (y[i] > ymax) ymax = y[i];
        }
    }

    if (ymin < 0) ymin = 0;

    if (ymin > ymax)
    {
        printf("Функция не определена на интервале.\n");
        return;
    }

    double hy = (ymax - ymin) / (SCREENH - 1);

    int x_axis = (int)((ymax - 0) / hy + 0.5);
    if (x_axis < 0 || x_axis >= SCREENH) x_axis = -1;

    int y_axis = -1;
    if (start <= 0 && end >= 0)
    {
        y_axis = (int)((0 - start) / hx + 0.5);
        if (y_axis < 0 || y_axis >= SCREENW) y_axis = -1;
    }

    for (int j = 0; j < SCREENH; j++)
        for (int i = 0; i < SCREENW; i++)
        {
            if (j == x_axis && i == y_axis) screen[i][j] = '+';
            else if (j == x_axis) screen[i][j] = '-';
            else if (i == y_axis) screen[i][j] = '|';
            else screen[i][j] = ' ';
        }

    for (int i = 0; i < SCREENW; i++)
    {
        if (!isnan(y[i]) && !isinf(y[i]))
        {
            int j = (int)((ymax - y[i]) / hy + 0.5);
            if (j >= 0 && j < SCREENH)
                screen[i][j] = '*';
        }
    }

    for (int j = 0; j < SCREENH; j++)
    {
        for (int i = 0; i < SCREENW; i++)
            putchar(screen[i][j]);
        putchar('\n');
    }
}

int count_pos(TFun func, double start, double end, double step)
{
    int c = 0;
    for (double x = start; x <= end; x += step) {
        double y = func(x);
        if (!isnan(y) && y > 0) c++;
    }
    return c;
}

int oper_suggest(int choice)
{
    if (choice == 1)
        printf("    Перейти к табуляции? (1 - да, 0 - нет): ");
    else if (choice == 2)
        printf("    Перейти к построению графика? (1 - да, 0 - нет): ");
    else if (choice == 4)
        printf("    Перейти к табуляции? (1 - да, 0 - нет): ");
    else return 0;

    return -1;
}
