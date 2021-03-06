#include <iostream>
#include <string.h>

using namespace std;
/*
Дадена е квадратна матрица от цели числа с размери 10x10,
 която описва лабиринт. Стойност 0 в дадена клетка означава „стена“,
 а стойност 1 означа „проходима клетка“.
 Даден е символен низ, съдържащ само буквите E, W, N и S,
 които указват едностъпкови придвижвания в съответните географски посоки:
 N – нагоре, E – надясно, S – надолу, W – наляво.

Да се напише функция walk, която получава матрица и символен низ от вида,
 определен по-горе и проверява дали символният низ задава валиден път започващ
 от някоя проходима клетка на лабиринта, състоящ се само от проходими клетки и
 завършващ в долния десен ъгъл на лабиринта. Функцията да връща
 булева стойност – истина, ако такава клетка има и даденият низ
 задава валиден път и лъжа в противен случай.
*/
int map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1}
};

bool walk(int map[10][10], const char* commands)
{
    size_t n = strlen(commands);
    int i = 9;
    int j = 9;
    while (n--) {
        j += commands[n] == 'W' ? 1 : (commands[n] == 'E' ? -1 : 0);
        i += commands[n] == 'N' ? 1 : (commands[n] == 'S' ? -1 : 0);
        if (map[i][j] == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << (walk(map, "SESESEE") ? "YES" : "NO") << endl;
    return 0;
}
