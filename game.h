#pragma once
//options[0] - size
//options[1] - speed
//options[2] - color
//options[3] - walls
// TABLE:
// 0 - nothing
// 1 - snake body
// 2 - snake head
// 3 - apple

int apple(int** coordinates, int length, int size) {
	srand(time(0));
	int* allowedApples = new int[size * size * 2 - length];
	bool flag = true;
	int k = 0;
	for (int i = 0; i < size * size * 2; i++) {
		for (int j = 0; j < length; j++) {
			if (coordinates[j][0] * size * 2 + coordinates[j][1] == i)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			allowedApples[k] = i;
			k++;
		}
		flag = 1;
	}
	int index = allowedApples[rand() % (size * size * 2 - length)];
	delete[] allowedApples;
	return index;
}
int moveResult(bool doWallsKill, int size, int positionContent) { // Результат хода
	if (doWallsKill and positionContent == -1)
		return -1; // Выход за пределы поля
	if (positionContent == 1)
		return -1; // Вход головы в тело
	if (positionContent == 0)
		return 0;  // Вход в пустую клетку
	if (positionContent == 2)
		return 1;  // Вход в яблоко
}
void tableFilling(int length, int** coordinates, int** table, int size) { // обновление таблицы
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size * 2; j++)
			if (table[i][j] != 3) 
				table[i][j] = 0;
	}
	for (int i = 0; i < length - 1; i++) {
		if (table[coordinates[i][0]][coordinates[i][1]] != 3)
			table[coordinates[i][0]][coordinates[i][1]] = 1;
	}
	table[coordinates[length - 1][0]][coordinates[length - 1][1]] = 2;
}
int tableCell(int size, int** table, int coordinates[2]) { // значение ячейки в таблице
	if (coordinates[0] >= size || coordinates[1] >= size * 2 || coordinates[0] == -1 || coordinates[1] == -1)
		return -1;
	return table[coordinates[0]][coordinates[1]];
}
bool move(int button, int size, int *length, int** coordinates, int** table, bool doWallsKill) {
	int value;
	int nextMove[2];
	switch (button) {
	case 77:
		coordinates[*length - 1][1] += 1;
		nextMove[0] = coordinates[*length - 1][0];
		nextMove[1] = coordinates[*length - 1][1];
		value = tableCell(size, table, coordinates[*length - 1]);
		coordinates[*length - 1][1] -= 1;
		break;
	case 75:
		coordinates[*length - 1][1] -= 1;
		nextMove[0] = coordinates[*length - 1][0];
		nextMove[1] = coordinates[*length - 1][1];
		value = tableCell(size, table, coordinates[*length - 1]);
		coordinates[*length - 1][1] += 1;
		break;
	case 72:
		coordinates[*length - 1][0] -= 1;
		nextMove[0] = coordinates[*length - 1][0];
		nextMove[1] = coordinates[*length - 1][1];
		value = tableCell(size, table, coordinates[*length - 1]);
		coordinates[*length - 1][0] += 1;
		break;
	case 80:
		coordinates[*length - 1][0] += 1;
		nextMove[0] = coordinates[*length - 1][0];
		nextMove[1] = coordinates[*length - 1][1];
		value = tableCell(size, table, coordinates[*length - 1]);
		coordinates[*length - 1][0] -= 1;
		break;
	}
	int result = moveResult(doWallsKill, size, value);
	int appleIndex;
	switch (result) {
	case 0:
		for (int i = 0; i < *length - 1; i++) {
			coordinates[i][0] = coordinates[i + 1][0];
			coordinates[i][1] = coordinates[i + 1][1];
		}
		coordinates[*length - 1][0] = nextMove[0];
		coordinates[*length - 1][1] = nextMove[1];
		return 0;
	case 1:
		*length += 1;
		coordinates[*length - 1][0] = nextMove[0];
		coordinates[*length - 1][1] = nextMove[1];
		if (*length != size * size * 2){
			appleIndex = apple(coordinates, *length, size);
			table[appleIndex / (size * 2)][appleIndex % (size * 2)] = 3;
		}
		return 0;
	case -1:
		return 1;
	}
}

int game(int maxScore, int options[]) {
	int score = 0;
	int length = 2;
	//int size = options[0] / 2;
	int size = 2;

	clock_t speed = 1000 - options[1] * 100;
	int** table = new int* [size];
	for (int i = 0; i < size; i++) {
		*(table + i) = new int[size * 2];
	}

	int** coordinates = new int*[size * size * 2];
	for (int i = 0; i < size * size * 2; i++) {
		*(coordinates + i) = new int[2];
	}
	coordinates[0][0] = size / 2; // Начальные координаты
	coordinates[0][1] = 1;
	coordinates[1][0] = size / 2;
	coordinates[1][1] = 2;
	//coordinates[2][0] = size / 2;
	//coordinates[2][1] = 3;
	//coordinates[3][0] = size / 2;
	//coordinates[3][1] = 4;

	int appleIndex = apple(coordinates, length, size); // Начальное яблоко
	table[appleIndex / (size * 2)][appleIndex % (size * 2)] = 3;
	tableFilling(length, coordinates, table, size);
	gameOutput(size, table);                           // Начальный вывод и заполение

	bool gameOver = 0;
	clock_t timer = clock();
	int button = 77;
	int lastButton = 77;
	while (!gameOver) {
		int timeStop = speed + clock() - timer;
		Sleep(timeStop);
		if (_kbhit()) {
			button = _getch();
			button = (button == 224) ? _getch() : button;
			button = (button == 77 || button == 72 || button == 75 || button == 80) ? button : lastButton;
			button = ((button == 77 and lastButton == 75) or (button == 75 and lastButton == 77)) ? lastButton : button;
			button = ((button == 80 and lastButton == 72) or (button == 72 and lastButton == 80)) ? lastButton : button;
			lastButton = button;
		}
		timer = clock();
		gameOver = move(button, size, &length, coordinates, table, options[3]);
		score = (length - 4) * 100;
		tableFilling(length, coordinates, table, size);
		gameOutput(size, table);
		if (length == size * 2 * size) {
			cout << "VICTORY!!!" << '\n';
			system("pause");
			return score;
		}
	}
	system("pause");
	return score;
}
