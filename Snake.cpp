// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//options[0] - size
//options[1] - speed
//options[2] - color
//options[3] - walls

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include "configuration.h"
#include "settings.h"
#include "output.h"
#include "game.h"

using namespace std;

int main()
{
    int maxScore = 0;
    system("title The Snake Game");
    Configuration config;
    int options[4];
    (config.isCorrect()) ? config.values(options) : config.create(options);
    while (TRUE) {
        setTextColor(options[2], 0);
        int currentNum = 1;
        menuOutput(currentNum, options[2]);
        while (TRUE) {
            int input;
            input = _getch();
            if (input == 224)
                input = _getch();
            if (input == 80 || input == 77) {
                system("cls");
                currentNum += 1;
                currentNum = currentNum == 4 ? 1 : currentNum;
                menuOutput(currentNum, options[2]);
            }
            else if (input == 72 || input == 75) {
                system("cls");
                currentNum -= 1;
                currentNum = currentNum == 0 ? 3 : currentNum;
                menuOutput(currentNum, options[2]);
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
            system("cls");
            game(maxScore, options);
            break;
        case 2:
            system("cls");
            setOptions(options);
            for (int i = 0; i < 4; i++) {
                cout << options[i] << " ";
            }
            cout << '\n';
            break;
        case 3:
            return 0;
        }
        system("cls");
    }
}