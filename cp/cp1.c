#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef double (*TFun)(double);
double Y(double);
double V(double);
double find_min(TFun, double, double, double);
double find_max(TFun, double, double, double);
void print_func(TFun, double, double, double);
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
    printf("                                |                Группа: бИПТ-251                  |\n");;
    printf("                                |                                                  |\n");
    printf("                                |__________________________________________________| \n");
    printf("\n");

    int func_choice;
    TFun selected_func;
    char* func_name;

    while (1) {
        printf("\nВыберите функцию:\n");
        printf("\n");
        printf("1 - Монотонная функция Y(x)\n");
        printf("2 - Кусочная функция V(x)\n");
        printf("\n");
        printf("Монотонная функция\n");
        printf("         sin(x^2 + x^-1 + x^1/3)\n");
        printf("Y(x) = ___________________________ * 10^-6\n");
        printf("            tg(e^cos(x^1/2))\n");
        printf("\n");
        printf("Кусочная функция\n");
        printf("         __\n");
        printf("        |\n");
        printf("        | 2 * cos^3(x^2) + sin^2(x^3) - 0.08 * (x^3 + 0.2), при x < 1\n");
        printf("V(x) =  | \n");
        printf("        | 2 * cos^3(x^2) + sin^2(x^3) - 0.08 * (x + x), при x >=1\n");
        printf("        |__\n");
        printf("Ваш выбор: ");
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
                printf("\n=====================================\n");
                printf("               МЕНЮ\n");
                printf("=====================================\n");
                printf("1. Вычислить значение %s\n", func_name);
                printf("2. Табулировать %s\n", func_name);
                printf("3. Определить минимум/максимум %s\n", func_name);
                printf("4. Построить график %s\n", func_name);
                printf("5. Посчитать количество положительных значений %s\n", func_name);
                printf("0. Вернуться к выбору функции\n");
                printf("=====================================\n");
                printf("Ваш выбор: ");
                scanf("%d", &choice);
            }
            else {
                choice = auto_next;
                auto_next = 0;
            }

            switch (choice) {
            case 0:
                printf("Возврат к выбору функции...\n");
                break;

            case 1:
                printf("Введите x для вычисления %s: ", func_name);
                scanf("%lf", &x);
                printf("%s(%.3f) = %.8f\n", func_name, x, selected_func(x));
                if (oper_suggest(1) == 1) {
                    auto_next = 2;
                }
                break;

            case 2:
                printf("Введите начало интервала для табуляции %s: ", func_name);
                scanf("%lf", &start);
                printf("Введите конец интервала для табуляции %s: ", func_name);
                scanf("%lf", &end);
                printf("Введите шаг для табуляции %s: ", func_name);
                scanf("%lf", &step);
                print_func(selected_func, start, end, step);
                if (oper_suggest(2) == 1) {
                    auto_next = 4;
                }
                break;


            case 3:
                printf("\nВыберите операцию для %s:\n", func_name);
                printf("1 - Найти минимум %s\n", func_name);
                printf("2 - Найти максимум %s\n", func_name);
                printf("0 - Вернуться назад\n");
                printf("Ваш выбор: ");
                scanf("%d", &op_choice);

                if (op_choice == 0) break;

                printf("Введите начало интервала для поиска экстремумов %s: ", func_name);
                scanf("%lf", &start);
                printf("Введите конец интервала для поиска экстремумов %s: ", func_name);
                scanf("%lf", &end);
                printf("Введите шаг (точность) для поиска экстремумов %s: ", func_name);
                scanf("%lf", &step);

                switch (op_choice) {
                case 1: {
                    double min_val = find_min(selected_func, start, end, step);
                    printf("Минимум функции %s: f(%.3f) = %.8f\n", func_name, min_val, selected_func(min_val));
                    break;
                }
                case 2: {
                    double max_val = find_max(selected_func, start, end, step);
                    printf("Максимум функции %s: f(%.3f) = %.8f\n", func_name, max_val, selected_func(max_val));
                    break;
                }
                default:
                    printf("Неверный выбор операции!\n");
                }
                break;

            case 4:
                printf("Введите начало интервала для построения графика %s: ", func_name);
                scanf("%lf", &start);
                printf("Введите конец интервала для построения графика %s: ", func_name);
                scanf("%lf", &end);
                printf("Введите шаг для построения графика %s: ", func_name);
                scanf("%lf", &step);
                print_graph(selected_func, start, end, step);
                if (oper_suggest(4) == 1) {
                    auto_next = 2;
                }
                break;

            case 5:
                printf("Введите начало интервала для анализа положительных значений %s: ", func_name);
                scanf("%lf", &start);
                printf("Введите конец интервала для анализа положительных значений %s: ", func_name);
                scanf("%lf", &end);
                printf("Введите шаг для анализа положительных значений %s: ", func_name);
                scanf("%lf", &step);
                int positive_count = count_pos(selected_func, start, end, step);
                printf("Количество положительных значений функции %s на интервале [%.2lf, %.2lf]: %d\n", func_name, start, end, positive_count);
                break;

            default:
                printf("Неверный выбор меню!\n");
            }

            if (choice == 0) break;
        }
    }
}

double Y(double x)
{
    return (sin(x * x + 1 / x + pow(x, 1. / 3)) / tan(exp(cos(sqrt(x))))) * pow(10, -6);
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

void print_func(double (*func)(double), double start, double end, double step) {
    printf("x\t\tf(x)\n");
    printf("---------------------------------\n");
    for (double x = start; x <= end; x += step) {
        printf("%-12.8f | %-30.8f\n", x, func(x));
    }
}

double find_min(TFun func, double start, double end, double step)
{
    double min_x = start;
    double min_val = func(start);

    for (double x = start + step; x <= end; x += step) {
        double current = func(x);
        if (current < min_val) {
            min_val = current;
            min_x = x;
        }
    }
    return min_x;
}

double find_max(TFun func, double start, double end, double step)
{
    double max_x = start;
    double max_val = func(start);

    for (double x = start + step; x <= end; x += step) {
        double current = func(x);
        if (current > max_val) {
            max_val = current;
            max_x = x;
        }
    }
    return max_x;
}

void print_graph(TFun func, double start, double end, double step)
{
    printf("\nГрафик функции на [%.2f, %.2f]:\n", start, end);
    printf("      y\n");
    printf("      |\n");

    const int width = 60;
    const int height = 20;
    double max_val = -1e10;
    double min_val = 1e10;

    for (double x = start; x <= end; x += (end - start) / 100.0) {
        double y = func(x);
        if (y > max_val) max_val = y;
        if (y < min_val) min_val = y;
    }

    if (func == Y && (max_val - min_val) < 1e-6) {
        max_val = min_val + 1e-5;
        if (max_val == min_val) max_val += 0.1;
    }

    double range = max_val - min_val;
    if (range < 1e-10) range = 1.0;

    printf("Диапазон Y: [%.2e, %.2e]\n", min_val, max_val);

    for (int row = height; row >= 0; row--) {
        double y_label = min_val + (range * row / height);
        if (row == height || row == 0 || row == height / 2) {
            printf("%8.1e |", y_label);
        }
        else {
            printf("         |");
        }

        for (int col = 0; col < width; col++) {
            double x = start + (end - start) * col / width;
            double y = func(x);

            int point_row = (int)((y - min_val) * height / range);
            if (point_row >= 0 && point_row <= height && point_row == row) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("         +");
    for (int i = 0; i < width; i++) printf("-");
    printf("> x\n");

    printf("         %.1f", start);
    for (int i = 0; i < width - 12; i++) printf(" ");
    printf("%.1f\n", end);
}

int count_pos(TFun func, double start, double end, double step)
{
    int count = 0;
    for (double x = start; x <= end; x += step) {
        double y = func(x);
        if (y > 0) {
            count++;
        }
    }
    return count;
}

int oper_suggest(int choice) {
    int temp = 0;
    switch (choice) {
    case 1:
        printf("Для перехода к табуляции введите 1, для возврата в меню 0 -> ");
        break;
    case 2:
        printf("Для перехода к построению графика введите 1, для возврата в меню 0 -> ");
        break;
    case 4:
        printf("Для перехода к табуляции введите 1, для возврата в меню 0 -> ");
        break;
    default:
        return 0;
    }
    scanf("%d", &temp);
    return temp;
}