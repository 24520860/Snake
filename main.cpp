#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[100];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "O";
        }
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];
        if (Huong == 0) A[0].x = A[0].x + 1; 
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1; 
        if (Huong == 3) A[0].y = A[0].y - 1; 
    }
};

// Vẽ khung (width x height)
void VeKhung(int width, int height) {
    for (int x = 0; x <= width; x++) {
        gotoxy(x, 0); cout << "#";              
        gotoxy(x, height); cout << "#";        
    }
    for (int y = 0; y <= height; y++) {
        gotoxy(0, y); cout << "#";              
        gotoxy(width, y); cout << "#";         
    }
}

int main() {
    CONRAN r;
    int Huong = 0;
    char t;
    const int width = 50, height = 20;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's') Huong = 1;
        }
        system("cls"); 
        VeKhung(width, height);
        r.Ve();
        r.DiChuyen(Huong);

        if (r.A[0].x <= 0 || r.A[0].x >= width || r.A[0].y <= 0 || r.A[0].y >= height) {
            gotoxy(width / 2 - 5, height / 2);
            cout << "GAME OVER!";
            break;
        }
        Sleep(150);
    }
    gotoxy(0, height + 2);
    return 0;
}
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
