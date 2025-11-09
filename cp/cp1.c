#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef double (*TFun)(double);
double Y(double);
double V(double);
double Phi(double);
double find_min(TFun, double, double, double);
double find_max(TFun, double, double, double);
void print_func(TFun, double, double, double);
void print_graph(TFun, double, double, double);
int count_pos(TFun, double, double, double);

int main()
{
    setlocale(LC_ALL, "RUS");
    int choice, func_choice, op_choice;
    double x, start, end, step;
    TFun selected_func;
    while (1) {
        printf("\n=====================================\n");
        printf("               МЕНЮ\n");
        printf("=====================================\n");
        printf("1. Вычислить значение\n");
        printf("2. Табулировать\n");
        printf("3. Выполнить операцию\n");
        printf("4. Построить график\n");
        printf("5. Посчитать количество положительных значений\n");
        printf("6. Выход\n");
        printf("=====================================\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\nВыберите функцию:\n");
            printf("1 - Y(x) = (sin(x^2 + x^-1 + x^1/3) / (tg(e^(cos(x^1/2) * 10^-6)\n");
            printf("2 - V(x) = 2 * (cos(x^2))^3 + (sin(x^3))^2 - 0.08 * Phi(x)\n");
            printf("3 - Phi(x) = x^3 + 0.2 (x<1), x+x (x>=1)\n");
            printf("Ваш выбор: ");
            scanf("%d", &func_choice);
            printf("Введите x: ");
            scanf("%lf", &x);

            switch (func_choice) {
            case 1:
                printf("S(%.3f) = %.8f\n", x, Y(x));
                break;
            case 2:
                printf("V(%.3f) = %.8f\n", x, V(x));
                break;
            case 3:
                printf("Y(%.3f) = %.8f\n", x, Phi(x));
                break;
            default:
                printf("Неверный выбор функции!\n");
            }
            break;

        case 2:
            printf("\nВыберите функцию:\n");
            printf("1 - Y(x) = (sin(x^2 + x^-1 + x^1/3) / (tg(e^(cos(x^1/2) * 10^-6)\n");
            printf("2 - V(x) = 2 * (cos(x^2))^3 + (sin(x^3))^2 - 0.08 * Phi(x)\n");
            printf("3 - Phi(x) = x^3 + 0.2 (x<1), x+x (x>=1)\n");
            printf("Ваш выбор: ");
            scanf("%d", &func_choice);
            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &end);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            switch (func_choice) {
            case 1:
                print_func(Y, start, end, step);
                break;
            case 2:
                print_func(V, start, end, step);
                break;
            case 3:
                print_func(Phi, start, end, step);
                break;
            default:
                printf("Неверный выбор функции!\n");
            }
            break;

        case 3:
            printf("\nВыберите функцию:\n");
            printf("1 - Y(x) = (sin(x^2 + x^-1 + x^1/3) / (tg(e^(cos(x^1/2) * 10^-6)\n");
            printf("2 - V(x) = 2 * (cos(x^2))^3 + (sin(x^3))^2 - 0.08 * Phi(x)\n");
            printf("3 - Phi(x) = x^3 + 0.2 (x<1), x+x (x>=1)\n");
            printf("Ваш выбор: ");
            scanf("%d", &func_choice);

            switch (func_choice) {
            case 1: selected_func = Y; break;
            case 2: selected_func = V; break;
            case 3: selected_func = Phi; break;
            default:
                printf("Неверный выбор функции!\n");
                continue;
            }

            printf("\nВыберите операцию:\n");
            printf("1 - Найти минимум\n");
            printf("2 - Найти максимум\n");
            printf("Ваш выбор: ");
            scanf("%d", &op_choice);

            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &end);
            printf("Введите шаг (точность): ");
            scanf("%lf", &step);

            switch (op_choice) {
            case 1: {
                double min_val = find_min(selected_func, start, end, step);
                printf("Минимум функции: f(%.3f) = %.8f\n", min_val, selected_func(min_val));
                break;
            }
            case 2: {
                double max_val = find_max(selected_func, start, end, step);
                printf("Максимум функции: f(%.3f) = %.8f\n", max_val, selected_func(max_val));
                break;
            }
            default:
                printf("Неверный выбор операции!\n");
            }
            break; // ДОБАВЛЕН break для case 3

        case 4:
            printf("\nВыберите функцию:\n");
            printf("1 - Y(x) = (sin(x^2 + x^-1 + x^1/3) / (tg(e^(cos(x^1/2) * 10^-6)\n");
            printf("2 - V(x) = 2 * (cos(x^2))^3 + (sin(x^3))^2 - 0.08 * Phi(x)\n");
            printf("3 - Phi(x) = x^3 + 0.2 (x<1), x+x (x>=1)\n");
            printf("Ваш выбор: ");
            scanf("%d", &func_choice);
            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &end);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            switch (func_choice) {
            case 1:
                print_graph(Y, start, end, step);
                break;
            case 2:
                print_graph(V, start, end, step);
                break;
            case 3:
                print_graph(Phi, start, end, step);
                break;
            default:
                printf("Неверный выбор функции!\n");
            }
            break;

        case 5:
            printf("\nВыберите функцию:\n");
            printf("1 - Y(x) = (sin(x^2 + x^-1 + x^1/3) / (tg(e^(cos(x^1/2) * 10^-6)\n");
            printf("2 - V(x) = 2 * (cos(x^2))^3 + (sin(x^3))^2 - 0.08 * Phi(x)\n");
            printf("3 - Phi(x) = x^3 + 0.2 (x<1), x+x (x>=1)\n");
            printf("Ваш выбор: ");
            scanf("%d", &func_choice);

            switch (func_choice) {
            case 1: selected_func = Y; break;
            case 2: selected_func = V; break;
            case 3: selected_func = Phi; break;
            default:
                printf("Неверный выбор функции!\n");
                continue;
            }

            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &end);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            int positive_count = count_pos(selected_func, start, end, step);
            printf("Количество положительных значений функции на интервале [%.2lf, %.2lf]: %d\n", start, end, positive_count);
            break;

        case 6:
            printf("Выход из программы...\n");
            return 0;

        default:
            printf("Неверный выбор меню!\n");
        }
    }
}

double Y(double x)
{
    return ((sin(x * x + 1 / x + pow(x, 1. / 3)) / tan(exp(cos(sqrt(x))))) * pow(10, -6));
}

double V(double x)
{
    return 2 * pow(cos(x * x), 3) + pow(sin(x * x * x), 2) - 0.08 * Phi(x);
}

double Phi(double x)
{
    if (x < 1)
        return x * x * x + 0.2;
    else
        return x + x;
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
    printf("\nГрафик функции:\n");
    printf("      y\n");
    printf("      |\n");

    const int width = 60;
    const int height = 20;
    double max_val = func(start);
    double min_val = func(start);
    for (double x = start; x <= end; x += step) {
        double val = func(x);
        if (val > max_val) max_val = val;
        if (val < min_val) min_val = val;
    }

    double range = max_val - min_val;
    if (range < 0.001) range = 1.0;

    for (int row = height; row >= 0; row--) {
        if (row == height) {
            printf("%5.1f |", max_val);
        }
        else if (row == 0) {
            printf("%5.1f |", min_val);
        }
        else {
            printf("      |");
        }

        for (int col = 0; col < width; col++) {
            double x = start + (end - start) * col / width;
            double y = func(x);
            int point_row = (int)((y - min_val) * height / range);

            if (point_row == row) {
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("      +");
    for (int i = 0; i < width; i++) printf("-");
    printf("> x\n");

    printf("       %.1f", start);
    for (int i = 0; i < width - 8; i++) printf(" ");
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