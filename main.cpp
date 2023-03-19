#include <iostream>
#include <vector>
#include <cstdlib> // для функции rand()
#include <ctime> // для инициализации генератора случайных чисел

using namespace std;

int nextStep(int row, int col, vector<vector<int>>& matrix) {
    int count = 0;
    int height = matrix.size();
    int width = matrix[0].size();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = row + i; //координаты соседа
            int c = col + j;
            if (r >= 0 && r < height && c >= 0 && c < width) { //проверка на выход за границы массива
                count += matrix[r][c]; //добавление соседа
            }
        }
    }
    count -= matrix[row][col];

    if (matrix[row][col] == 1 && count < 2) {
        return 0;
    } else if (matrix[row][col] == 1 && count > 3) {
        return 0;
    } else if (matrix[row][col] == 0 && count == 3) {
        return 1;
    } else {
        return matrix[row][col];
    }
}

void New(vector<vector<int>>& matrix) { //новое состояние доски
    vector<vector<int>> new_matrix = matrix;

    int height = matrix.size();
    int width = matrix[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new_matrix[i][j] = nextStep(i, j, matrix);
        }
    }

    matrix = new_matrix;
}

void printMatrix(vector<vector<int>>& matrix) {
    int height = matrix.size();
    int width = matrix[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] == 1){
                cout<<"* ";
            }
            else{
                cout<<"o ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isEqual(vector<vector<int>>& arr1, vector<vector<int>>& arr2) {
    int height = arr1.size();
    int width = arr1[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr1[i][j] != arr2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool contains(vector<vector<vector<int>>>& states, vector<vector<int>>& state) {
    for (auto& s : states) {
        if (isEqual(s, state)) {
            return true;
        }
    }

    return false;
}

bool livingCells(vector<vector<int>>& matrix) {
    int height = matrix.size();
    int width = matrix[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] == 1) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    srand(time(NULL)); // инициализация генератора случайных чисел

    int width = 10;
    int height = 10;

    vector<vector<int>> matrix(height, vector<int>(width, 0)); // доска пустая по умолчанию

    // рандомное заполнение доски
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = rand() % 2;
        }
    }

    vector<vector<vector<int>>> states; //для хранения всех предыдущих состоянией
    bool game_running = true;

    while (game_running) {
        printMatrix(matrix);
        New(matrix);
        if (!livingCells(matrix)) {
            printMatrix(matrix);
            cout << "All cells have died." << endl;
            game_running = false;
        } else if (contains(states, matrix)) {
            printMatrix(matrix);
            cout << "The matrix has repeated." << endl;
            game_running = false;
        }
        states.push_back(matrix); //добавление такущего состояния в трехмерный вектор
    }

    return 0;
}