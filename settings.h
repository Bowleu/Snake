#pragma once
#include "output.h"
#include "configuration.h"
#include <algorithm>

void setOptions(int options[4]) {
    Configuration config;
	int currentNum = 1;
    settingsOutput(currentNum, options, options[2]);
    while (TRUE) {
        int input;
        input = _getch();
        if (input == 224)
            input = _getch();
        if (input == 80) {
            system("cls");
            currentNum += 1;
            currentNum = currentNum == 6 ? 1 : currentNum;
            settingsOutput(currentNum, options, options[2]);
        }
        else if (input == 72) {
            system("cls");
            currentNum -= 1;
            currentNum = currentNum == 0 ? 5 : currentNum;
            settingsOutput(currentNum, options, options[2]);
        }
        else if (input == 75 || input == 77) {
            system("cls");
            int allowedValues[4] = { 0, 0, 0, 0 };
            config.getAllowedValues(allowedValues, currentNum);
            auto it = find(allowedValues, allowedValues + 4, options[currentNum - 1]);
            int index = distance(allowedValues, it);
            options[currentNum - 1] = (input == 75) ? allowedValues[(index + 3) % 4] : allowedValues[(index + 1) % 4];
            settingsOutput(currentNum, options, options[2]);
        }
        else if (input == 13) {
            if (currentNum == 5)
                return;
        }
        else if (input == 27) {
            return;
        }
    }
	
}