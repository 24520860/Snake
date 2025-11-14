#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[200];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0].x = 12; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 10; A[2].y = 10;
    }
	
	// Tạo hình rắn
    void Ve() {
    	gotoxy(A[0].x, A[0].y); 
		cout << "x";
		
        for (int i = 1; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "o";
        }
    }
	
	// Điều hướng
    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        if (Huong == 0) A[0].x = A[0].x + 1;	// Phải
        if (Huong == 1) A[0].y = A[0].y + 1;	// Xuống
        if (Huong == 2) A[0].x = A[0].x - 1; 	// Trái
        if (Huong == 3) A[0].y = A[0].y - 1;	// Lên
    }
	
	// Kiểm tra ăn mồi
    bool KiemTraAnMoi(Point moi) {
        return (A[0].x == moi.x && A[0].y == moi.y);
    }
	
	// Tăng độ dài
    void TangDoDai() {
        A[DoDai] = A[DoDai - 1];
        DoDai++;
    }
};

// Vẽ khung trò chơi
void VeKhung(int width, int height) {
    for (int x = 0; x <= width; x++) {
        gotoxy(x, 0); cout << "#";			// Viền trên
        gotoxy(x, height); cout << "#"; 	// Viền dưới
    }
    for (int y = 0; y <= height; y++) {
        gotoxy(0, y); cout << "#";      	// Viền trái
        gotoxy(width, y); cout << "#";   	// Viền phải
    }
}

// Vẽ mồi
void VeMoi(Point moi) {
    gotoxy(moi.x, moi.y);
    cout << "*";
}

int main() {
    srand(time(NULL));

    CONRAN r;
    int Huong = 0;
    char t;
    const int width = 50, height = 20;
    Point moi;

    // Sinh mồi ban đầu
    moi.x = rand() % (width - 2) + 1;
    moi.y = rand() % (height - 2) + 1;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a' && Huong != 0) Huong = 2;
            if (t == 'w' && Huong != 1) Huong = 3;
            if (t == 'd' && Huong != 2) Huong = 0;
            if (t == 's' && Huong != 3) Huong = 1;
        }

        system("cls");

        // Vẽ khung và mồi
        VeKhung(width, height);
        VeMoi(moi);

        // Vẽ rắn
        r.Ve();

        // Kiểm tra ăn mồi
        if (r.KiemTraAnMoi(moi)) {
            r.TangDoDai();
            moi.x = rand() % (width - 2) + 1;
            moi.y = rand() % (height - 2) + 1;
        }

        // Di chuyển rắn
        r.DiChuyen(Huong);

        // Kiểm tra va chạm tường
        if (r.A[0].x <= 0 || r.A[0].x >= width || r.A[0].y <= 0 || r.A[0].y >= height) {
            gotoxy(width / 2 - 5, height / 2);
            cout << "GAME OVER!";
            break;
        }
        
        // Kiểm tra chạm thân
        for (int i = 1; i < r.DoDai; i++) {
            if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) {
                gotoxy(width / 2 - 5, height / 2);
                cout << "GAME OVER!";
                return 0;
            }
        }
        
        

        Sleep(100);
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