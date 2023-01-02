#include <iostream>
#include <Windows.h>
#include<conio.h>
#include <vector>

using namespace std;

/* 키보드 값 */
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

/* 색상 열거형 정의*/
enum {
    black,
    blue,
    green,
    cyan,
    red,
    purple,
    brown,
    lightgray,
    darkgray,
    lightblue,
    lightgreen,
    lightcyan,
    lightred,
    lightpurple,
    yellow,
    white,
};

/* 함수 선언 */
void init();
void gotoxy(int, int);
void DrawTitle();
int DrawMenu();
int keyControl();
void DrawInfo();
void DrawMap();
void setColor(int, int);
void gameLoop();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void RandomNum();

int tempMap[6][6] = {
    {-1,-1,-1,-1,-1,-1},
    {-1,0,0,0,0,-1},
    {-1,0,0,0,0,-1},
    {-1,0,0,0,0,-1},
    {-1, 0,0,0,0,-1},
    {-1,-1,-1,-1,-1,-1}
};

int map[6][6] = {
    {-1,-1,-1,-1,-1,-1},
    {-1,0,0,0,0,-1},
    {-1,0,0,0,0,-1},
    {-1,0,0,0,0,-1},
    {-1, 0,0,0,0,-1},
    {-1,-1,-1,-1,-1,-1}
};

int limitNumber = 2;
vector <pair<int, int>> Pt;

int main(void) {
    init();
    
    while (true) {
        DrawTitle();
        int menuCode = DrawMenu();
        if (menuCode == 0) {
            gameLoop();
        }
        else if (menuCode == 1) {
            DrawInfo();
        }
        else if (menuCode == 2) {
            return 0;
        }
        system("cls");
        setColor(white, black);
    }


	return 0;
}

void init() {
    system("title 2048"); 
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1; //두께 : 1
    c.bVisible = 0; //커서 숨기기
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void gotoxy(int x, int y) {
    COORD Pos;        //x, y를 가지고 있는 구조체
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void DrawTitle() {
    gotoxy(24, -7);
    cout << "\n\n\n\n";
    cout << "                                   #####    ###   #        #####\n";
    cout << "                                  #     #  #   #  #    #  #     #\n";
    cout << "                                        #  #   #  #    #  #     #\n";
    cout << "                                   #####  #     # #    #   #####\n";
    cout << "                                  #       #     # ####### #     #\n";
    cout << "                                  #        #   #       #  #     #\n";
    cout << "                                  #        #   #       #  #     #\n";
    cout << "                                  #######   ###        #   #####\n";
    cout << "\n\n\n\n";
}

int DrawMenu() {
    int x = 24;
    int y = 12;
    gotoxy(24-2, 12);
    cout << ">   게임 시작";
    gotoxy(24, 13);
    cout << "게임 정보";
    gotoxy(24, 14);
    cout << "종료";

    while (true) {
        int n = keyControl();
        switch (n)
        {
            case UP: {
                if (y > 12) {
                    gotoxy(x - 2, y);
                    cout << " ";
                    gotoxy(x - 2, --y);
                    cout << ">";
                }
                break;
            }
           
            case DOWN: {
                if (y < 14) {
                    gotoxy(x - 2, y);
                    cout << " ";
                    gotoxy(x - 2, ++y);
                    cout << ">";
                }
                break;
            }
           
            case SUBMIT: {
                return y - 12;
            }
        }
    }
}

int keyControl() {
    int i = _getch();
    if (i == 224) {
        i = _getch();
        switch (i) 
        {
        case 72: return UP; break;
        case 80: return DOWN; break;
        case 75: return LEFT; break;
        case 77: return RIGHT; break;
        }
    }
    else if (i == 32) {
        return SUBMIT;
    }
}

void DrawInfo() {
    system("cls");
    cout << "How to play : \n";
    cout << "Use your arrow keys to move the tiles.\nTiles with the same number merge into one when they touch.\nAdd them up to reach 2048!\n";
    cout << "Development : balhyo-younjisang";

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }
}

void DrawMap() {
    system("cls");

    for (int h = 0; h < 6; h++) {
        for (int w = 0; w < 6; w++) {
            int t = tempMap[h][w];

            if (t == 0) {
                setColor(yellow, black);
                cout << "b";
            }
            else if (t == -1) {
                setColor(white, black);
                cout << "#";
            }
            else if (t == 1024) {
                setColor(white, black);
                system("cls");
                gotoxy(24, 12);
                cout << "You Win!";
                return;
            }
            else {
                setColor(cyan, white);
                Pt.push_back(make_pair(h, w));
                cout << t;
            }
        }
        cout << "\n";
    }
    //Sleep(2000);
}

void setColor(int forground, int background) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int code = forground + background * 16;
    SetConsoleTextAttribute(consoleHandle, code);
}

void gameLoop() {

    srand((int)time(NULL));
    for (int i = 0; i < 2; i++) {
        int x = (rand() % 4) + 1;     
        int y = (rand() % 4) + 1;

        int t = (rand() % limitNumber) + 1;
        if (t % 2) t++;
        map[x][y] = t;
        Pt.push_back(make_pair(x, y));
    }

    while (true) {
        memcpy(tempMap, map, sizeof(tempMap));
        DrawMap();
        switch (keyControl())
        {
            case UP: {
                moveUp();
                break;
            }
            case DOWN: {
                moveDown();
                break;
            }
            case LEFT: {
                moveLeft();
                break;
            }
            case RIGHT: {
                moveRight();
                break;
            }
        }
        RandomNum();
    }
}

void RandomNum() {
    int x = 0, y = 0;
    while (map[x][y] != 0) {
        x = (rand() % 4) + 1;
        y = (rand() % 4) + 1;
    }

    int t = (rand() % limitNumber) + 1;
    if (t % 2) t++;
    map[x][y] = t;
    Pt.push_back(make_pair(x, y));
}


void moveUp() {
   for (auto u : Pt) {
        int x = u.first;
        int y = u.second;
        int dx = x;
        int value = map[x][y];
        gotoxy(x, y);

        while (map[dx - 1][y] == 0) 
            dx--;

        if (map[dx - 1][y] == map[dx][y]) {
            map[x][y] = 0;
            map[dx][y] = 0;
            map[dx - 1][y] = value * 2;
        }
        else {
            map[x][y] = 0;
            map[dx][y] = value;
        }
       
    }
}

void moveDown() {
    for (auto u : Pt) {
        int x = u.first;
        int y = u.second;
        int dx = x;
        int value = map[x][y];
        gotoxy(x, y);

        while (map[dx + 1][y] == 0)
            dx++;
        if (map[dx + 1][y] == map[dx][y]) {
            map[x][y] = 0;
            map[dx][y] = 0;
            map[dx + 1][y] = value * 2;
        }
        else {
            map[x][y] = 0;
            map[dx][y] = value;
        }
    }
}

void moveLeft() {
    for (auto u : Pt) {
        int x = u.first;
        int y = u.second;
        int dy = y;
        int value = map[x][y];
        gotoxy(x, y);

        while (map[x][dy-1] == 0)
            dy--;

        if (map[x][dy-1] == map[x][y]) {
            map[x][y] = 0;
            map[x][dy] = 0;
            map[x][dy-1] = value * 2;
        }
        else {
            map[x][y] = 0;
            map[x][dy] = value;
        }
    }
}

void moveRight() {
    for (auto u : Pt) {
        int x = u.first;
        int y = u.second;
        int dy = y;
        int value = map[x][y];
        gotoxy(x, y);

        while (map[x][dy + 1] == 0)
            dy++;
        if (map[x][dy + 1] == map[x][y]) {
            map[x][y] = 0;
            map[x][dy] = 0;
            map[x][dy + 1] = value * 2;
        }
        else {
            map[x][y] = 0;
            map[x][dy] = value;
        }
    }
}

