// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

void setTextColor(int textColorIndex, int textBackgroundIndex) { // Смена цвета текста
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (textBackgroundIndex << 4) + textColorIndex);
}

void stdOutput(int rowNumber) {
    for (int i = 0; i < 30; i++)
        cout << ' ';
    if (rowNumber == 0 || rowNumber == 23) {
        for (int i = 0; i < 60; i++)
            cout << '#';
    }
    else {
        cout << '#';
        for (int i = 0; i < 58; i++)
            cout << ' ';
        cout << '#';
    }
    cout << '\n';
}

void signedOutput(string option, bool selection) {
    size_t len = option.length();
    for (int i = 0; i < 30; i++)
        cout << ' ';
    cout << '#';
    for (int i = 0; i < (58 - len) / 2; i++)
        cout << ' ';
    if (selection)
        setTextColor(0, 15);
    cout << option;
    setTextColor(15, 0);
    for (int i = 0; i < (58 - len) / 2; i++)
        cout << ' ';
    cout << '#';
    cout << '\n';
}
void tableOutput(int currentNum) {
    for (int i = 0; i < 24; i++) {
        if (i == 6)
            signedOutput(" THE SNAKE GAME ", 1);
        else if (i == 12)
            signedOutput(" PLAY ", currentNum == 1);
        else if (i == 14)
            signedOutput(" SETTINGS ", currentNum == 2);
        else if (i == 16)
            signedOutput(" EXIT ", currentNum == 3);
        else
            stdOutput(i);
    }
}

int main()
{
    int currentNum = 1;
    tableOutput(currentNum);
    setTextColor(15, 0);
    while (TRUE) {
        int input;
        while (TRUE) {
            Sleep(5000);
            if (_kbhit()) {
                input = _getch();
                if (input == 224)
                    input = _getch();
                break;
            }
        }
        if (input == 80 || input == 77) {
            system("cls");
            currentNum += 1;
            currentNum = currentNum == 4 ? 1 : currentNum;
            tableOutput(currentNum);
        }
        else if (input == 72 || input == 75) {
            system("cls");
            currentNum -= 1;
            currentNum = currentNum == 0 ? 3 : currentNum;
            tableOutput(currentNum);
        }
        else if (input == 13) {
            if (currentNum != 3)
                break;
            else
                return 0;
        }
        else if (input == 27) {
            return 0;
        }
    }
    switch (currentNum) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        return 0;
    }
}