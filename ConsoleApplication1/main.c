#include <stdio.h>
#include <windows.h>

#define MAXN 10000
int n = 0, tree[2 * MAXN], a[MAXN], option, tm, tl, tr;

// Функция для построения дерева отрезков из массива
void build(int a[], int vertex, int tl, int tr);

// Функция для подсчета суммы элементов в заданном интервале массива
int sum(int vertex, int tl, int tr, int l, int r);

// Функция для обновления значения элемента массива и пересчета дерева отрезков
void update(int vertex, int tl, int tr, int pos, int new_val);

// Функция для поиска позиции суммы в дереве отрезков
int findPrefixSumPosition(int vertex, int tl, int tr, int x);

// Функция для вывода текущего состояния дерева отрезков
void printTree(int vertex, int tl, int tr, int level);

// Функция для чтения данных из файла
void readFromFile();

// Функция для записи данных в файл
void writeToFile();

int main() {
    system("chcp 1251");
    system("color F0");
    while (1) {

        printf("Выберите опцию (1/2/3/4/5/6/7/8):\n");
        // Опции для работы с деревом отрезков
        printf("1. Построить дерево отрезков\n");
        printf("2. Запрос суммы в интервале\n");
        printf("3. Обновление элемента\n");
        printf("4. Вывести текущее состояние дерева\n");
        printf("5. Поиск префикса массива с заданной суммой\n");
        printf("6. Считать данные с файла\n");
        printf("7. Записать данные в файл\n");
        printf("8. Выйти\n");
        scanf("%d", &option);
        while (getchar() != '\n');


        if (option == 1) {
            // Запрос пользователем размера массива и его элементов
            printf("Введите размер массива: ");
            scanf("%d", &n);
            printf("Введите элементы массива:\n");
            for (int i = 0; i < n; i++) {
                scanf("%d", &a[i]);
            }
            build(a, 1, 0, n - 1);
            printf("Дерево отрезков построено.\n");
        }
        else if (option == 2) {
            // Запрос интервала для вычисления суммы элементов
            int l, r;
            printf("Введите левую границу интервала: ");
            scanf("%d", &l);
            printf("Введите правую границу интервала: ");
            scanf("%d", &r);
            int result = sum(1, 0, n - 1, l, r);
            printf("Сумма элементов в интервале [%d, %d]: %d\n", l, r, result);
        }
        else if (option == 3) {
            int pos, new_val;
            printf("Введите индекс элемента для обновления: ");
            scanf("%d", &pos);
            printf("Введите новое значение элемента: ");
            scanf("%d", &new_val);
            update(1, 0, n - 1, pos, new_val);
            printf("Элемент обновлён.\n");
        }
        else if (option == 4) {
            printf("Текущее состояние дерева отрезков:\n");
            printTree(1, 0, n - 1, 0);
        }
        else if (option == 5) {
            int x;
            printf("Введите значение x для поиска позиции суммы: ");
            scanf("%d", &x);
            if (n == 0) {
                printf("Дерево еще не построено. Выберите опцию 1 для построения дерева.\n");
            }
            else {
                int position = findPrefixSumPosition(1, 0, n - 1, x);
                printf("Позиция суммы больше или равной %d: %d\n", x, position);
            }
        }
        else if (option == 6) {
            readFromFile();
        }
        else if (option == 7) {
            writeToFile();
        }
        else if (option == 8) {
            // Завершение программы
            printf("Программа завершена.\n");
            break;
        }
        else {
            // Ошибка при выборе опции
            printf("Неправильный выбор опции. Попробуйте снова.\n");
        }
    }
    return 0;
}

void readFromFile() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &a[i]);
    }
    fclose(file);
    build(a, 1, 0, n - 1);
    printf("Данные считаны из файла.\n");
}

void writeToFile() {
    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии/создании файла.\n");
        return;
    }
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", a[i]);
    }
    fclose(file);
    printf("Данные записаны в файл.\n");
}

void build(int a[], int vertex, int tl, int tr) {
    if (tl == tr)
        tree[vertex] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(a, vertex * 2, tl, tm);
        build(a, vertex * 2 + 1, tm + 1, tr);
        tree[vertex] = tree[vertex * 2] + tree[vertex * 2 + 1];
    }
}

int sum(int vertex, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return tree[vertex];
    int tm = (tl + tr) / 2;
    return sum(vertex * 2, tl, tm, l, (r < tm ? r : tm)) + sum(vertex * 2 + 1, tm + 1, tr, (l > tm + 1 ? l : tm + 1), r);
}

void update(int vertex, int tl, int tr, int pos, int new_val) {
    if (n == 0) {
        printf("Дерево еще не построено. Выберите опцию 1 для построения дерева.\n");
        return;
    }
    if (tl == tr)
        tree[vertex] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(vertex * 2, tl, tm, pos, new_val);
        else
            update(vertex * 2 + 1, tm + 1, tr, pos, new_val);
        tree[vertex] = tree[vertex * 2] + tree[vertex * 2 + 1];
    }
}

int findPrefixSumPosition(int vertex, int tl, int tr, int x) {
    if (tl == tr) {
        return tl;
    }
    else {
        int tm = (tl + tr) / 2;
        if (tree[vertex * 2] >= x) {
            return findPrefixSumPosition(vertex * 2, tl, tm, x);
        }
        else {
            return findPrefixSumPosition(vertex * 2 + 1, tm + 1, tr, x - tree[vertex * 2]);
        }
    }
}

void printTree(int vertex, int tl, int tr, int level) {
    if (n == 0) {
        printf("Дерево еще не построено. Выберите опцию 1 для построения дерева.\n");
        return;
    }

    if (tl == tr) {
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("[%d] = %d\n", tl, tree[vertex]);
    }
    else {
        int tm = (tl + tr) / 2;
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("[v] = %d\n", tree[vertex]);
        printTree(vertex * 2, tl, tm, level + 1);
        printTree(vertex * 2 + 1, tm + 1, tr, level + 1);
    }
}