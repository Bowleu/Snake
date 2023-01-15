#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <map>
using namespace std;
class Configuration {
public:
    void create(int array[4]) {
        ofstream config("config.txt");
        for (auto pair : defaultValues) {
            config << pair.first << ": " << pair.second << '\n';
        }
        config.close();
        array[0] = 16;
        array[1] = 6;
        array[2] = 15;
        array[3] = 1;
    }
    bool isCorrect() {
        ifstream config;
        config.open("config.txt");
        if (!config.is_open()) {
            return 0;
        }
        string line;
        while (getline(config, line)) {
            string lineCopy = line;
            string name;
            int value;
            name = lineCopy.replace(line.find(":"), line.length() - line.find(":"), "");
            lineCopy = line;
            value = stoi(lineCopy.replace(0, line.find(":") + 2, ""));
            if (name == "size") {
                if (find(allowedSize, allowedSize + 3, value) == allowedSize + 3) {
                    config.close();
                    return 0;
                }
            }
            if (name == "speed") {
                if (find(allowedSpeed, allowedSpeed + 3, value) == allowedSpeed + 3) {
                    config.close();
                    return 0;
                }
            }
            if (name == "color") {
                if (find(allowedColor, allowedColor + 3, value) == allowedColor + 3) {
                    config.close();
                    return 0;
                }
            }
            if (name == "walls") {
                if (find(allowedWalls, allowedWalls + 3, value) == allowedWalls + 3) {
                    config.close();
                    return 0;
                }
            }
        }
        config.close();
        return 1;
    }
    void values(int array[4]) {
        ifstream config;
        config.open("config.txt");
        string line;
        array[0] = 16;
        array[1] = 6;
        array[2] = 15;
        array[3] = 1;
        int i = 0;
        while (getline(config, line)) {
            string lineCopy = line;
            string name;
            int value;
            name = lineCopy.replace(line.find(":"), line.length() - line.find(":"), "\0");
            lineCopy = line;
            value = stoi(lineCopy.replace(0, line.find(":") + 2, "\0"));
            array[i] = value;
            i++;
        }
    }
    void getAllowedValues(int array[4], int number) {
        if (number == 1) {
            for (int i = 0; i < 4; i++) {
                array[i] = allowedSize[i];
            }
            return;
        }
        if (number == 2) {
            for (int i = 0; i < 4; i++) {
                array[i] = allowedSpeed[i];
            }
            return;
        }
        if (number == 3) {
            for (int i = 0; i < 4; i++) {
                array[i] = allowedColor[i];
            }
            return;
        }
        if (number == 4) {
            for (int i = 0; i < 4; i++) {
                array[i] = allowedWalls[i];
            }
            return;
        }
        return;
    }
private:
    const map <string, int> defaultValues =
    {
        {"size", 16},
        {"speed", 6},
        {"color", 15},
        {"walls", 1}
    };
    int allowedSize[4] = { 12, 14, 16, 18 };
    int allowedSpeed[4] = { 2, 4, 6, 8 };
    int allowedColor[4] = { 3, 6, 2, 15 };
    bool allowedWalls[4] = { 0, 1, 0, 1};
};