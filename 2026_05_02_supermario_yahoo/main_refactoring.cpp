#include <math.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
        float x, y;
        float width, height;
        float vertSpeed;
        bool IsFly;
        char cType;
        float horizSpeed;
} TObject;

void ClearMap(char map[mapHeight][mapWidth + 1]) {
        for (int i = 0; i < mapWidth; i++)
                map[0][i] = ' ';
        map[0][mapWidth] = '\0';
        for (int j = 1; j < mapHeight; j++)
                strcpy(map[j], map[0]);
}

void ShowMap(char map[mapHeight][mapWidth + 1]) {
        map[mapHeight -  1][mapWidth - 1] = '\0';
        for (int j = 0; j < mapHeight; j++) {
                mvprintw(j, 0, "%s", map[j]);
        }
        refresh();
}

void SetObjectPos(TObject *obj, float xPos, float  yPos) {
        (*obj).x = xPos;
        (*obj).y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
        SetObjectPos(obj, xPos, yPos);
        (*obj).width = oWidth;
        (*obj).height = oHeight;
        (*obj).vertSpeed = 0;
        (*obj).cType = inType;
        (*obj).horizSpeed = 0.2;
}

void CreateLevel(int lvl, int &score, int &maxLvl);
bool IsCollision(TObject o1, TObject o2);
TObject *GetNewMoving(TObject *&moving, int &movingLength);

void PlayerDead(int level, TObject &mario, int &score, int &maxLvl) {
        bkgd(COLOR_PAIR(2));
        refresh();
        usleep(300000);
        bkgd(COLOR_PAIR(1));
        refresh();
        CreateLevel(level, mario, score, maxLvl);
}

void VertMoveObject(TObject *obj, TObject *brick, int bricklength, int &level, &score, int maxLvl) {
        (*obj).IsFly = true;
        (*obj).vertSpeed += 0.05;
        SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
        for (int i = 0; i < brickLength; i++) {
                if (IsCollision(*obj, brick[i])) {
                        if (obj[0].vertSpeed > 0) {
                                obj[0].IsFly = false;
                        }

                        if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)) {
                                brick[i].cType = '-';
                                InitObject(GetNewMoving(), brick[i].x, brick[i].y-3, 3, 2, '$');
                                moving[movingLength - 1].vertSpeed = -0.7;
                        }

                        (*obj).y -= (*obj).vertSpeed;
                        (*obj).vertSpeed = 0;
                        if (brick[i].cType == '+'){
                                level++;
                                if (level > maxLvl) level = 1;

                                bkgd(COLOR_PAIR(3));
                                refresh();
                                usleep(300000);
                                bkgd(COLOR_PAIR(1));
                                refresh();
                                CreateLevel(level, mario, score, maxLvl);
                        }
                        break;
                }
        }
}

void DeleteMoving(TObject *&moving, int &movingLength, int i) {
        movingLength--;
        moving[i] = moving[movingLength];
        moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
}

void MarioCollision(TObject &mario, int &score, int level, int &maxLvl) {
        for (int i = 0; i < movingLength; i++) {
                if (IsCollision(mario, moving[i])) {
                        if (moving[i].cType == 'o') {
                                if ((mario.IsFly == true) && (mario.vertSpeed > 0) && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)) {
                                        score += 50;
                                        DeleteMoving(moving, movingLength, i);
                                        i--;
                                        continue;
                                } else {
                                       PlayerDead(level, mario, score, maxLvl);
                                }
                                }
                                if (moving[i].cType == '$') {
                                        score += 100;
                                        DeleteMoving(moving, movingLength, i);
                                        i--;
                                        continue;
                                }
                        }
        }
}

void HorizonMoveObject(TObject *obj) {
        obj[0].x += obj[0].horizSpeed;
        for (int i = 0; i < brickLength; i++) {
                if (IsCollision(obj[0], brick[i])) {
                        obj[0].x -= obj[0].horizSpeed;
                        obj[0].horizSpeed = -obj[0].horizSpeed;
                        return;
                }
        }

        if (obj[0].cType == 'o') {
                TObject tmp = *obj;
                VertMoveObject(&tmp, level, score, maxLvl);
                if (tmp.IsFly == true) {
                        obj[0].x -= obj[0].horizSpeed;
                        obj[0].horizSpeed = -obj[0].horizSpeed;
                }
        }

}

bool IsPosInMap(int x, int y) {
        return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PutObjectOnMap(void ShowMap(char map[mapHeight][mapWidth + 1], TObject obj) {
        int ix = (int)round(obj.x);
        int iy = (int)round(obj.y);
        int iWidth = (int)round(obj.width);
        int iHeight = (int)round(obj.height);

        for (int i = ix; i < (ix + iWidth); i++) {
                for (int j = iy; j < (iy + iHeight); j++) {
                        if (IsPosInMap(i, j))
                                map[j][i] = obj.cType;
                }
        }
}

void setCur(int x, int y) {
        move(y, x);
}

void HorizonMoveMap(float dx) {
        mario.x -= dx;
        for (int i = 0; i < brickLength; i++) {
                if (IsCollision(mario, brick[i])) {
                        mario.x += dx;
                        return;
                }
        }
        mario.x += dx;

        for (int i = 0; i < brickLength; i++)
                brick[i].x += dx;
        for (int i = 0; i < movingLength; i++)
                moving[i].x += dx;
}

bool IsCollision(TObject o1, TObject o2) {
        return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

TObject *GetNewBrick(TObject &brick, int &brickLength) {
        brickLength++;
        brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
        return brick + brickLength - 1;
}

TObject *GetNewMoving(TObject *&moving, int &movingLength) {
        movingLength++;
        moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
        return moving + movingLength - 1;
}

void PutScoreOnMap(int score) {
        char c[30];
        sprintf(c, "Score: %d", score);
        int len = strlen(c);
        for (int i = 0; i < len; i++) {
                map[1][i+5] = c[i];
        }
}

void CreateLevel(int lvl, TObject &mario, TObject &brick, int &bricklength, int &score, int &maxLvl) {

        brickLength = 0;
        brick = (TObject*)realloc(brick, 0);
        movingLength = 0;
        moving = (TObject*)realloc(moving, 0);

        InitObject(&mario, 39, 10, 3, 3, '@');
        score = 0;

        if (lvl == 1) {
                brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
                InitObject(GetNewBrick(brick, brickLength), 20, 20, 40, 5, '#');

                InitObject(GetNewBrick(brick, brickLength), 30, 10, 5, 3, '?');
                InitObject(GetNewBrick(brick, brickLength), 50, 10, 5, 3, '?');

                InitObject(GetNewBrick(brick, brickLength), 60, 15, 40, 10, '#');

                InitObject(GetNewBrick(brick, brickLength), 60, 100, 10, 3, '-');
                InitObject(GetNewBrick(brick, brickLength), 70, 5, 5, 3, '?');
                InitObject(GetNewBrick(brick, brickLength), 75, 5, 5, 3, '-');
                InitObject(GetNewBrick(brick, brickLength), 80, 5, 5, 3, '?');
                InitObject(GetNewBrick(brick, brickLength), 85, 5, 10, 3, '-');

                InitObject(GetNewBrick(brick, brickLength), 100, 20, 20, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 120, 15, 10, 10, '#');
                InitObject(GetNewBrick(brick, brickLength), 134, 20, 40, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 177, 15, 5, 10, '+');

                InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
        }

        if (lvl == 2) {
                brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
                InitObject(GetNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 60, 15, 10, 10, '#');
                InitObject(GetNewBrick(brick, brickLength), 80, 20, 20, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 120, 15, 10, 10, '#');
                InitObject(GetNewBrick(brick, brickLength), 150, 20, 40, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 210, 15, 10, 10, '+');

                moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
                InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 125, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
        }

        if (lvl == 3) {
                brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
                InitObject(GetNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 80, 20, 15, 5, '#');
                InitObject(GetNewBrick(brick, brickLength), 120, 15, 15, 10, '#');
                InitObject(GetNewBrick(brick, brickLength), 160, 10, 15, 15, '+');

                InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 50, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 90, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
                InitObject(GetNewMoving(), 130, 10, 3, 2, 'o');
        }

        maxLvl = 3;
}

int main() {
        TObject mario;
        TObject *brick = NULL;
        int brickLength = 0;
        TObject *moving = NULL;
        int movingLength = 0;
        char map[mapHeight][mapWidth + 1];

        int level = 1;
        int score = 0;
        int maxLvl = 3;

        initscr();
        noecho();
        cbreak();
        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);

        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);

        bkgd(COLOR_PAIR(1));

        CreateLevel(level, mario, score, maxLvl);

        while (1) {
                ClearMap(map);

                int ch = getch();
                if ((mario.IsFly == false) && (ch == ' ')) mario.vertSpeed = -0.9;
                if (ch == 'a') HorizonMoveMap(1);
                if (ch == 'd') HorizonMoveMap(-1);
                if (ch == 27) break;

                if (mario.y > mapHeight - mario.height) PlayerDead(level, mario, score, maxLvl);

                VertMoveObject(&mario, brick, brickLength, level, score, maxLvl);
                MarioCollision(mario, score, level, maxLvl);

                for (int i = 0; i < brickLength; i++)
                        PutObjectOnMap(brick[i]);
                for (int i = 0; i < movingLength; i++) {
                        VertMoveObject(moving + i);
                        HorizonMoveObject(moving + i);
                        if (moving[i].y > mapHeight) {
                                DeleteMoving(moving, movingLength, i);
                                i--;
                                continue;
                        }
                        PutObjectOnMap(moving[i]);
                }

                PutObjectOnMap(map, mario);
                PutScoreOnMap(score);

                ShowMap(map);
                usleep(10000);
        }

        endwin();
        return 0;
}
