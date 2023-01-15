#pragma once

void setTextColor(int, int);

void stdOutput(int rowNumber, int color) {
    setTextColor(color, 0);
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

void setTextColor(int textColorIndex, int textBackgroundIndex) { // Смена цвета текста
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (textBackgroundIndex << 4) + textColorIndex);
}

void signedOutput(string option, bool selection, int color) {
    size_t len = option.length();
    for (int i = 0; i < 30; i++)
        cout << ' ';
    cout << '#';
    for (int i = 0; i < (58 - len) / 2; i++)
        cout << ' ';
    if (selection)
        setTextColor(0, 15);
    else
        setTextColor(15, 0);
    cout << option;
    setTextColor(color, 0);
    for (int i = 0; i < (58 - len) / 2; i++)
        cout << ' ';
    if (len % 2)
        cout << ' ';
    cout << '#';
    cout << '\n';
}

void menuOutput(int currentNum, int color) {
    cout << "\n\n";
    for (int i = 0; i < 24; i++) {
        if (i == 6)
            signedOutput(" THE SNAKE GAME ", 1, color);
        else if (i == 12)
            signedOutput(" PLAY ", currentNum == 1, color);
        else if (i == 14)
            signedOutput(" SETTINGS ", currentNum == 2, color);
        else if (i == 17)
            signedOutput(" EXIT ", currentNum == 3, color);
        else
            stdOutput(i, color);
    }
}
void settingsOutput(int currentNum, int settings[4], int color) {
    cout << "\n\n";
    for (int i = 0; i < 24; i++) {
        if (i == 5)
            signedOutput(" SETTINGS ", 1, color);
        else if (i == 10)
            signedOutput(" SIZE " + (string)"< " + to_string(settings[0]) + " >", currentNum == 1, color);
        else if (i == 12)
            signedOutput(" SPEED " + (string)"< " + to_string(settings[1]) + " >", currentNum == 2, color);
        else if (i == 14) {
            string setColor;
            switch (settings[2]) {
            case 2:
                setColor = "GREEN";
                break;
            case 15:
                setColor = "WHITE";
                break;
            case 6:
                setColor = "SAND";
                break;
            case 3:
                setColor = "BLUE";
                break;
            }
            signedOutput(" COLOR  " + (string)"< " + setColor + " >", currentNum == 3, color);
        }
        else if (i == 16) {
            string answer = settings[3] == TRUE ? "Yes" : "No";
            signedOutput(" WALLS KILL " + (string)"< " + answer + " >", currentNum == 4, color);
        }
        else if (i == 19)
            signedOutput(" BACK ", currentNum == 5, color);
        else
            stdOutput(i, color);
    }
}
void gameLineOutput(int *line , int lineNumber, int size) {
    cout << '#';
    for (int i = 0; i < size * 2; i++) {
        switch (line[i]) {
        case 0: 
            cout << ' ';
            break;
        case 1:
            cout << 'o';
            break;
        case 2:
            cout << '0';
            break;
        case 3:
            cout << (char)2;
            break;
        }
    }
    cout << '#';
    cout << '\n';
}
void gameOutput(int size, int **table) {
    system("cls");
    cout << "\n\n";
    for (int i = 0; i < size * 2 + 32; i++)
        (i < 30) ? cout << ' ' : cout << '#';
    cout << '\n';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 30; j++)
            cout << ' ';
        gameLineOutput(table[i], i, size);
    }
    for (int i = 0; i < size * 2 + 32; i++)
        (i < 30) ? cout << ' ' : cout << '#';
    cout << '\n';
}
