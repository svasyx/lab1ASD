#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "locale.h"
#include "string.h"
#include "windows.h"
#include "time.h"



int amountofelem(FILE* fr);           //Отримування к-сті елементів
void getfilename(char filename[]);    //Зчитування імені файлу
void swapelements(int& a, int& b);    //Міняємо елементи місцями
int ChoiceSort(int array[], int size);//сортування Вибором
void shellSort(int array[], int size);//сортування шелла
struct bucket;
void сountSort(int arr[], int sizem);//сортування підрахунком
void masivefil (FILE* fr, char* filename, int size, int array[], int lower, int upper);//заповнення масиву ранд числами
void manualmasiv(FILE* fr1, int mas[], int sizem, int check);//ручний ввід масиву
void workwithmasive(FILE* fr, FILE* fr1, int array[], int size, int check);//зчитування масиву з файлу,вивід на екран

void workwithsorted(FILE* fr1, int array[], int size);//робота з відсортованим масивом
int scann(int& N);//зчитування змінних введених з клавіатури


clock_t beg, end;
int main() {
    FILE* fr = NULL;  //файловий дескриптор 
    FILE* fr1 = NULL; //файловий дескриптор результуючого файлу
    int* array = NULL;//масив 1
    int* mas = NULL;  //масив 2
    int choose = 0, //Змінна пункту меню,відповідає за вибір типу сортування
        check = 0,  //Змінна,що зберігає в собі вид сортування(викорустовується в                    умовному операторі для передачі аргументів в функції сортування
        filew = 0,  //Змінна пункту меню що відповідає за тип роботи з фалом
        lower = 0,  //Ліва границя рандому для масиву
        upper = 0,  // права границя рандому масиву
        amount = 0, //к-сть елементів у файлі
        size = 0, //розмір масиву,що був зчитаний з файлу
        masw = 0, //змінна пункту меню,що відповідає за тип роботи з масивом
        sizem = 0; //розмір масиву що було введено вручну в консоль користувачем

    clock_t beg, //початок відрахунку часу виконання алгоритму
        end; //кінець відрахунку часу виконання алгоритму

    char filename[256];//змінна з назвою файлу

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));//зкидування часу для рандому

    printf("Виберіть тип сортування\n1)Сортування вибором\n2)Сотування методом       Шелла\n3)Сортування підрахунком\n4)Завершити програму\n");

        scann(choose);//зчитування пункту меню

    if (choose == 1) {
        check = 1;
    }
    else if (choose == 2) {
        check = 2;
    }
    else if (choose == 3) {
        check = 3;
    }
    else if (choose == 4) {
        return 0;
    }
    else {
        printf("Ви ввели не 1/2/3/4, або не число ");
        exit(0);
    }

    printf("Як ви хочете працювати з масивом:\n1)Ввести з файлу\n2)Ввести вручну в консоль\n");

    scann(masw);//зчитування пункту меню

    if (masw == 1) {

        printf("Як ви хочете працювати з файлом\n1)Відкрити існуючий\n2)Створити новий\n");
        scann(filew);//зчитування пункту меню

        if (filew == 1) {

            printf("Введіть назву файлу у вигляді назва_файлу.txt: ");
            getfilename(filename);//зчитування пункту меню

            if ((fr = fopen(filename, "r")) == NULL)
            {
                printf("Не вдалося відкрити файл %s! \n", filename);
                return 0;
            }
            amount = amountofelem(fr);//отримування к-сті елементів
            printf("Кількість елементів у файлі: %d\n", amount);

            workwithmasive(fr, fr1, array, amount, check);//передача аргументів для роботи з             масивом

        }
        else if (filew == 2) {

            printf("Введіть назву файлу у вигляді назва_файлу.txt: ");
            getfilename(filename);//зчитування пункту меню


            printf("Введіть розмір масиву: ");
            scann(size);//зчитування пункту меню
            if (size == 0) {

                printf("Розмір має бути більше 0");
                return 0;
            }
            printf("Введіть нижню границю рандому масиву: ");
            scann(lower);//зчитування пункту меню
            printf("Введіть верхню границю рандому масиву: ");
            scann(upper);//зчитування пункту меню

            if (lower > upper) {

                printf("Нижня границя має бути менша за верxню");
                return 0;
            }

                        masivefil(fr, filename, size, array, lower, upper);//передача аргументів для             заповнення масиву

                if ((fr = fopen(filename, "r")) == NULL)
                {
                    printf("Не вдалося відкрити файл %s! \n", filename);
                    return 0;
                }

            amount = amountofelem(fr);//отримування к-сті елементів
            printf("Кількість елементів у файлі: %d\n", amount);

            workwithmasive(fr, fr1, array, amount, check);//передача аргументів для роботи з             масивом
        }
        else {
            printf("Ви ввели не 1/2, або не число ");
            return 0;
        }

    }
    else if (masw == 2) {

        printf("Введіть розмір масиву:\n");

        scann(sizem);//зчитування пункту меню
        manualmasiv(fr1, mas, sizem, check);//передача аргументів для ручного заповнення         масиву

    }
    else {
        printf("Ви ввели не 1/2, або не число ");
        return 0;
    }

    return 0;
}


/*Функція amountofelem
Функція підрахунку кількості елементів
Вхід:
fr - файловий дескриптор,передача за посиланням
Результат:
К-сть елементів у файлі
*/

int amountofelem(FILE* fr) {
    int count = 0; //змінна кількості елементів
    int whileDigit = 0;//тимчасова змінна що потрібна для того щоб поки сканф в неї записував     значення то лічильник збільшувався на 1
        while (!feof(fr)) {
            if (fscanf(fr, "%d", &whileDigit) > 0) //поки буде зчитувати числа сканф,тобто                 повертати не 0 значення
            {

                count++;
            }
        }
    rewind(fr);//перемотка файлу
    if (ferror(fr)) {
        printf("Не поставлено показник в початок файлу\n");
        exit(0);
    }
    return count;//повертаємо к-сть елементів
}


/*Функція getfilename
Функція вводу та перевірки на правильність назви файлу для роботи
Вхід:
filename - масив символів, передача по значенню
Результат:
Строка в якій міститься назва файлу введена користувачем
*/

void getfilename(char filename[]) {

    do {

        fgets(filename, 1024, stdin);//зчитуємо ім'я файлу

    } while (filename[0] == '\n');
    filename[strlen(filename) - 1] = ' ';
}

/*Функція swapelements
Функція заміни елементів місцями
Вхід:
a - 1 елемент для заміни,передача по посиланню
b - 2 елемент для заміни,передача по посиланню
Результат:
Поміняні місцями елементи
*/

void swapelements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

/*Функція ChoiceSort
Функція сортування вибором
Вхід:
array - масив чисел,передача за значенням
size - розмір масиву,за значенням
Результат:
Відсортований масив
*/

void swap(int& arg1, int& arg2)
{
    int tmp = arg1;
    arg1 = arg2;
    arg2 = tmp;
}

int ChoiceSort(int array[], int size) {


    beg = clock();

    int min = 0;

    for (int i = 0; i < size - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        swap(array[i], array[min]);
    }


    end = clock();



    return 0;
}

/*Функція shellSort
Функція сортування Шелла
Вхід:
masiv - масив чисел,передача за значенням
size - розмір масиву,передача за значенням
Результат:
Відсортований масив
*/

void shellSort(int masiv[], int size)
{

    beg = clock();

    int icount, jcount, krok;
    int temp;
    for (krok = size / 2; krok > 0; krok /= 2) //виконуємо ділення на 2,щоб порівнювати         числа

        for (icount = krok; icount < size; icount++)
        {
            temp = masiv[icount];
            for (jcount = icount; jcount >= krok; jcount -= krok)
            {
                if (temp < masiv[jcount - krok]) //якщо поточний елемент менший за поточний     - крок то міняємо місцями ці елементи

                    masiv[jcount] = masiv[jcount - krok];
                else
                    break;
            }
            masiv[jcount] = temp;
        }
    end = clock();


}






int findSmallest(int* arr, int size)
{
    int smallest = 0;
    for (int i = 0; i < size; i++)
    {
        if (smallest > arr[i])
        {
            smallest = arr[i];
        }
    }
    return smallest;
}

int findBiggest(int* arr, int size)
{
    int biggest = 0;

    for (int i = 0; i < size; i++)
    {
        if (biggest < arr[i])
        {
            biggest = arr[i];
        }
    }

    return biggest;
}

/*Функція countSort
Функція сортування підрахунком

Вхід:
array - масив чисел,передача за значенням
sizem - розмір масиву,передача за значенням
Результат:
Відсортований масив
*/

int* countSort(int* arr, int size, int biggest, int smallest)
{
    int* tmp_arr = NULL;
    int iterator = 0;
    int tmp_size = biggest + abs(smallest) + 1;

    if (!(tmp_arr = (int*)calloc(tmp_size, sizeof(int))))
    {
        printf("Not enough memory for array! LINE: %d", __LINE__);
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        tmp_arr[arr[i] + abs(smallest)]++;
    }

    for (int i = 0; i < tmp_size; i++)
    {
        for (int j = 0; j < tmp_arr[i]; j++)
        {
            arr[iterator] = smallest + i;
            iterator++;
        }
    }

    free(tmp_arr);

    return arr;
}


/*Функція masivefil
Функція Створення масиву та заповнення його випадковими числами
Вхід:
fr - файловий дескриптор,передача за посиланням
filename - Строка в якій міститься назва файлу введена користувачем,передача за посиланням
size - розмір масиву,передача за значенням
array - масив чисел,передача за значенням
lower - нижня границя рандому,передача за значенням
upper - верхня границя рандому,передача за значенням
Результат:
файл з записаним в нього масивом
*/

void masivefil(FILE* fr, char* filename, int size, int array[], int lower, int upper) {
    if ((fr = fopen(filename, "w")) == NULL)
    {
        printf("Не вдалося створити файл %s! \n", filename);
        exit(0);
    }
    array = (int*)malloc(sizeof(int) * size); //Виділення пам'яті для масиву розміром size
    if (!array)
    {
        printf("Не вистачає пам'яті");
        exit(0);
    }
    for (int i = 0; i < size; i++)
    {
        array[i] = lower - 1 + rand() % ((upper - lower) + 1); //заповнюємо випадковими числами, границі рандому ввів      користувач

    }
    for (int i = 0; i < size; i++)
    {
        if (!fprintf(fr, "%d ", array[i])) //записуємо в файл отриманий масив
        {

            printf("Something went wrong");
            exit(0);

        }
    }
    free(array); //звільнення пам'яті
    if (fclose(fr) == EOF) {
        printf("Не вдалося закрити файл %s! \n", filename);
        exit(0);
    }
}

/*Функція manualmasiv
Функція ручного заповнення масиву
Вхід:
fr1 - файловий дескриптор,передача за посиланням
mas - масив чисел,передача за значенням
sizem - розмір масиву,передача за значенням
check - змінна,для вибору типу сортування,передача за значенням
Результат:
Заповнений масив
Виклик функцій сортування
*/

void manualmasiv(FILE* fr1, int mas[], int sizem, int check) {


    if (sizem == 0) {

        printf("Розмірність не може бути 0");
        exit(0);
    }

    mas = (int*)malloc(sizeof(int) * sizem); //виділення пам'яті на масив
    if (!mas)
    {
        printf("Для такого масива не має вільної пам'яті!");
        exit(0);
    }

    printf("\nВведіть масив розмірністю %d\n", sizem);
    for (int i = 0; i < sizem; i++)
    {

        if (!scanf(" %d", &mas[i])) //заповнення масиву з клавіатури
        {

            printf("В масив можна записати тільки числа");
            exit(0);
        }
    }

    printf("Введений масив:\n");
    for (int i = 0; i < sizem; i++)
    {
        printf("%d ", mas[i]);//вивід масиву на екран
    }

    //Передача аргументів у функції сортування

    if (check == 1) {
        ChoiceSort(mas, sizem);
        workwithsorted(fr1, mas, sizem);
    }
    else if (check == 2) {

        shellSort(mas, sizem);
        workwithsorted(fr1, mas, sizem);

    }
    else if (check == 3) {
        countSort(mas, sizem, findBiggest(mas, sizem), findSmallest(mas, sizem));
        workwithsorted(fr1, mas, sizem);
    }
    exit(0);
}

/*Функція workwithmasive
Функція роботи з масивом
Вхід:
fr - файловий дескриптор,передача за посиланням
fr1 - файловий дескриптор,передача за посиланням
masiv - масив чисел,передача за значенням
size - розмір масиву,передача за значенням
check - змінна,для вибору типу сортування,передача за значенням
Результат:
Якщо розмір масиву менше 0 то друк масиву на екран
Виклик функцій сортування
*/

void workwithmasive(FILE* fr, FILE* fr1, int masiv[], int size, int check) {
    masiv = (int*)malloc(sizeof(int) * size);//виділення пам'яті для масиву
    if (!masiv)
    {
        printf("Не вистачає пам'яті на масив");
        exit(0);
    }

    for (int i = 0; i < size; i++)
    {
        if (!fscanf(fr, "%d", &masiv[i]))//читання масиву з файлу
        {

            printf("Something went wrong");
            exit(0);
        }
    }
    if (size < 100) {
        printf("Зчитаний масив: ");//вивід зчитаного масиву
        for (int i = 0; i < size; i++) {
            printf("%d\t", masiv[i]);
        }
    }
    else {

        printf("Size>100,не друкуємо масив");


    }

    //передача зчитаного масиву у функції сортування

    if (check == 1) {
        ChoiceSort(masiv, size);
        workwithsorted(fr1, masiv, size);

    }
    else if (check == 2) {

        shellSort(masiv, size);
        workwithsorted(fr1, masiv, size);
    }
    else if (check == 3) {
        countSort(masiv, size, findBiggest(masiv, size), findSmallest(masiv, size));
        workwithsorted(fr1, masiv, size);

    }
}


/*Функція workwithsorted
Функція роботи з відсортованим масивом
Вхід:
fr1 - файловий дескриптор,передача за посиланням
array - масив чисел,передача за значенням
size - розмір масиву,передача за значенням
Результат:
Запис відсортованого масиву у файл,та якщо розмір масиву менше 100 то друк на екран
*/


void workwithsorted(FILE* fr1, int array[], int size) {

    fr1 = fopen("sortedmasive.txt", "w+");//відкриваємо або створюємо файл для запису     відсортованого масиву

        printf("\nВідсортований масив записано у файл sortedmasive.txt\n");

    for (int i = 0; i < size; i++)
    {

        //записуємо масив в результуючий файл
        if (!fprintf(fr1, "%d ", array[i])) {

            printf("Something went wrong");
            exit(0);

        }

    }
    if (size < 100) {
        for (int i = 0; i < size; i++) {
            printf("%d\t", array[i]);
        }
    }
    else
        printf("Size > 100,не друкуємо відсортований масив");
    if (fclose(fr1) == EOF) {
        printf("Не вдалося закрити файл  \n");
        exit(0);
    }
    printf("\n\nАлгоритм був виконаний за %lf секунд \n\n", (long double)(end - beg) / CLK_TCK);

}

/*Функція scann
Функція введення значень змінних
Вхід:
N - змінна для заповнення,передача за посиланням
Результат:
Змінна з записаним числомі
*/

int scann(int& N) {
    int isEntered = 0;
    do {
        do {
            isEntered = scanf_s("%d", &N);
            while (getchar() != '\n');
            while (isEntered < 1) {
                printf("Ви ввели некоректне значення,повторіть введення: ");
                isEntered = scanf_s("%d", &N);
                while (getchar() != '\n');
            }
        } while (isEntered < 1);
    } while (isEntered != 1);
    return N;
}
