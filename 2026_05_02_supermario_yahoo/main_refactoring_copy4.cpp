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

void clearMap(char map[mapHeight][mapWidth + 1]);
void createLevel(int lvl,
                 TObject &mario,
                 TObject *&brick,
                 int &brickLength,
                 TObject *&moving,
                 int &movingLength,
                 int &score,
                 int &maxLvl);
void deleteMoving(TObject *&moving, int &movingLength, int i);
TObject *getNewBrick(TObject *&brick, int &brickLength);
TObject *getNewMoving(TObject *&moving, int &movingLength);
void horizonMoveMap(float dx,
                    TObject &mario,
                    TObject *brick,
                    int brickLength,
                    TObject *&moving,
                    int &movingLength);
void horizonMoveObject(TObject *obj,
                       TObject *brick,
                       int &brickLength,
                       TObject *&moving,
                       int &movingLength,
                       int &level,
                       TObject &mario,
                       int &score,
                       int maxLvl);
bool isCollision(TObject o1, TObject o2);
void initObject(TObject *obj,
                float xPos,
                float yPos,
                float oWidth,
                float oHeight,
                char inType);
bool isPosInMap(int x, int y);
void marioCollision(TObject &mario,
                    TObject *&moving,
                    int &movingLength,
                    TObject *&brick,
                    int brickLength,
                    int &score,
                    int level,
                    int maxLvl);
void playerDead(int level,
                TObject *mario,
                TObject *&brick,
                int &brickLength,
                TObject *&moving,
                int &movingLength,
                int &score,
                int &maxLvl);
void putObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj);
void putScoreOnMap(char map[mapHeight][mapWidth + 1], int score);
void setObjectPos(TObject *obj, float xPos, float  yPos);
void showMap(char map[mapHeight][mapWidth + 1]);
void vertMoveObject(TObject *obj,
                    TObject *&brick,
                    int &brickLength,
                    TObject *&moving,
                    int &movingLength,
                    TObject &mario,
                    int &level,
                    int &score,
                    int maxLvl);

void clearMap(char map[mapHeight][mapWidth + 1]) {
        for (int i = 0; i < mapWidth; i++)
                map[0][i] = ' ';
        map[0][mapWidth] = '\0';
        for (int j = 1; j < mapHeight; j++)
                strcpy(map[j], map[0]);
}

void showMap(char map[mapHeight][mapWidth + 1]) {
        map[mapHeight -  1][mapWidth - 1] = '\0';
        for (int j = 0; j < mapHeight; j++) {
                mvprintw(j, 0, "%s", map[j]);
        }
        refresh();
}

void setObjectPos(TObject *obj, float xPos, float  yPos) {
        obj->x = xPos;
        obj->y = yPos;
}

void initObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
        setObjectPos(obj, xPos, yPos);
        obj->width = oWidth;
        obj->height = oHeight;
        obj->vertSpeed = 0;
        obj->cType = inType;
        obj->horizSpeed = 0.2;
}

void playerDead(int level, TObject *mario, TObject *&brick, int &brickLength, TObject *&moving, int &movingLength, int &score, int &maxLvl) {
        bkgd(COLOR_PAIR(2));
        refresh();
        usleep(300000);
        bkgd(COLOR_PAIR(1));
        refresh();
        mario->x = 39;
        mario->y = 10;
        mario->vertSpeed = 0;
        mario->IsFly = false;

        createLevel(level, *mario, brick, brickLength, moving, movingLength, score, maxLvl);
}

void vertMoveObject(TObject *obj, TObject *&brick, int &brickLength, TObject *&moving, int &movingLength, TObject &mario, int &level, int &score, int maxLvl) {
        obj->IsFly = true;
        obj->vertSpeed += 0.05;
        setObjectPos(obj, obj->x, obj->y + obj->vertSpeed);
        for (int i = 0; i < brickLength; i++) {
                if (isCollision(*obj, brick[i])) {
                        if (obj->vertSpeed > 0) {
                                obj->IsFly = false;
                        }

                        if ((brick[i].cType == '?') && (obj->vertSpeed < 0) && (obj == &mario)) {
                                brick[i].cType = '-';
                                initObject(getNewMoving(moving, movingLength), brick[i].x, brick[i].y-3, 3, 2, '$');
                                moving[movingLength - 1].vertSpeed = -0.7;
                        }

                        obj->y -= obj->vertSpeed;
                        obj->vertSpeed = 0;
                        if (brick[i].cType == '+'){
                                level++;
                                if (level > maxLvl) level = 1;

                                bkgd(COLOR_PAIR(3));
                                refresh();
                                usleep(300000);
                                bkgd(COLOR_PAIR(1));
                                refresh();
                                createLevel(level, mario, brick, brickLength, moving, movingLength, score, maxLvl);
                        }
                        break;
                }
        }
}

void deleteMoving(TObject *&moving, int &movingLength, int i) {
        movingLength--;
        moving[i] = moving[movingLength];
        moving = (TObject*)realloc(moving, sizeof(TObject) * movingLength);
}

void marioCollision(TObject &mario, TObject *&moving, int &movingLength, TObject *&brick, int brickLength, int &score, int level, int maxLvl) {
        if (moving == NULL) return;

        for (int i = 0; i < movingLength; i++) {
                if (isCollision(mario, moving[i])) {
                        if (moving[i].cType == 'o') {
                                if (mario.IsFly && (mario.vertSpeed > 0) && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)) {
                                        score += 50;
                                        deleteMoving(moving, movingLength, i);
                                        i--;
                                        continue;
                                } else {
                                        playerDead(level, &mario, brick, brickLength, moving, movingLength, score, maxLvl);
                                        return;
                                }
                        }
                        if (moving[i].cType == '$') {
                                score += 100;
                                deleteMoving(moving, movingLength, i);
                                i--;
                                continue;
                        }
                }
        }
}

void horizonMoveObject(TObject *obj, TObject *brick, int &brickLength, TObject *&moving, int &movingLength, int &level, TObject &mario, int &score, int maxLvl) {
        obj->x += obj->horizSpeed;
        for (int i = 0; i < brickLength; i++) {
                if (isCollision(*obj, brick[i])) {
                        obj->x -= obj->horizSpeed;
                        obj->horizSpeed = -obj->horizSpeed;
                        return;
                }
        }

        if (obj->cType == 'o') {
                TObject tmp = *obj;
                vertMoveObject(&tmp, brick, brickLength, moving, movingLength, mario, level, score, maxLvl);
                if (tmp.IsFly) {
                        obj->x -= obj->horizSpeed;
                        obj->horizSpeed = -obj->horizSpeed;
                }
        }

}

bool isPosInMap(int x, int y) {
        return x >= 0 && x < mapWidth && y >= 0 && y < mapHeight;
}

void putObjectOnMap(char map[mapHeight][mapWidth + 1], TObject obj) {
        int ix = (int)round(obj.x);
        int iy = (int)round(obj.y);
        int iWidth = (int)round(obj.width);
        int iHeight = (int)round(obj.height);

        for (int i = ix; i < (ix + iWidth); i++) {
                for (int j = iy; j < (iy + iHeight); j++) {
                        if (isPosInMap(i, j))
                                map[j][i] = obj.cType;
                }
        }
}

void horizonMoveMap(float dx, TObject &mario, TObject *brick, int brickLength, TObject *&moving, int &movingLength) {
        mario.x -= dx;
        for (int i = 0; i < brickLength; i++) {
                if (isCollision(mario, brick[i])) {
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

bool isCollision(TObject o1, TObject o2) {
        return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

TObject *getNewBrick(TObject *&brick, int &brickLength) {
        brickLength++;
        brick = (TObject*)realloc(brick, sizeof(TObject) * brickLength);
        return brick + brickLength - 1;
}

TObject *getNewMoving(TObject *&moving, int &movingLength) {
        movingLength++;
        moving = (TObject*)realloc(moving, sizeof(TObject) * movingLength);
        return moving + movingLength - 1;
}

void putScoreOnMap(char map[mapHeight][mapWidth + 1], int score) {
        char c[30];
        sprintf(c, "Score: %d", score);
        int len = strlen(c);
        for (int i = 0; i < len; i++) {
                map[1][i+5] = c[i];
        }
}

void createLevel(int lvl, TObject &mario, TObject *&brick, int &brickLength, TObject *&moving, int &movingLength, int &score, int &maxLvl) {
        brick = NULL;
        moving = NULL;
        brickLength = 0;
        movingLength = 0;

        initObject(&mario, 39, 10, 3, 3, '@');
        score = 0;

        switch (lvl) {
                case 1:
                        initObject(getNewBrick(brick, brickLength), 20, 20, 40, 5, '#');

                        initObject(getNewBrick(brick, brickLength), 30, 10, 5, 3, '?');
                        initObject(getNewBrick(brick, brickLength), 50, 10, 5, 3, '?');

                        initObject(getNewBrick(brick, brickLength), 60, 15, 40, 10, '#');

                        initObject(getNewBrick(brick, brickLength), 60, 100, 10, 3, '-');
                        initObject(getNewBrick(brick, brickLength), 70, 5, 5, 3, '?');
                        initObject(getNewBrick(brick, brickLength), 75, 5, 5, 3, '-');
                        initObject(getNewBrick(brick, brickLength), 80, 5, 5, 3, '?');
                        initObject(getNewBrick(brick, brickLength), 85, 5, 10, 3, '-');

                        initObject(getNewBrick(brick, brickLength), 100, 20, 20, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 120, 15, 10, 10, '#');
                        initObject(getNewBrick(brick, brickLength), 134, 20, 40, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 177, 15, 5, 10, '+');

                        initObject(getNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');

                        break;

                case 2:
                        initObject(getNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 60, 15, 10, 10, '#');
                        initObject(getNewBrick(brick, brickLength), 80, 20, 20, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 120, 15, 10, 10, '#');
                        initObject(getNewBrick(brick, brickLength), 150, 20, 40, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 210, 15, 10, 10, '+');

                        initObject(getNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 65, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 125, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 160, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 175, 10, 3, 2, 'o');

                        break;

                case 3:
                        initObject(getNewBrick(brick, brickLength), 20, 20, 40, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 80, 20, 15, 5, '#');
                        initObject(getNewBrick(brick, brickLength), 120, 15, 15, 10, '#');
                        initObject(getNewBrick(brick, brickLength), 160, 10, 15, 15, '+');

                        initObject(getNewMoving(moving, movingLength), 25, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 50, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 80, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 90, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 120, 10, 3, 2, 'o');
                        initObject(getNewMoving(moving, movingLength), 130, 10, 3, 2, 'o');

                        break;


                default:
                        createLevel(1, mario, brick, brickLength, moving, movingLength, score, maxLvl);
                        break;
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

        createLevel(level, mario, brick, brickLength, moving, movingLength, score, maxLvl);

        while (1) {
                clearMap(map);

                int ch = getch();
                if (!mario.IsFly && ch == ' ') mario.vertSpeed = -0.9;
                if (ch == 'a') horizonMoveMap(1, mario, brick, brickLength, moving, movingLength);
                if (ch == 'd') horizonMoveMap(-1, mario, brick, brickLength, moving, movingLength);
                if (ch == 27) break;

                if (mario.y > mapHeight - mario.height) playerDead(level, &mario, brick, brickLength, moving, movingLength, score, maxLvl);

                vertMoveObject(&mario, brick, brickLength, moving, movingLength, mario, level, score, maxLvl);
                marioCollision(mario, moving, movingLength, brick, brickLength, score, level, maxLvl);

                for (int i = 0; i < brickLength; i++)
                        putObjectOnMap(map, brick[i]);
                for (int i = 0; i < movingLength; i++) {
                        vertMoveObject(moving + i, brick, brickLength, moving, movingLength, mario, level, score, maxLvl);
                        horizonMoveObject(moving + i, brick, brickLength, moving, movingLength, level, mario, score, maxLvl);
                        if (moving[i].y > mapHeight) {
                                deleteMoving(moving, movingLength, i);
                                i--;
                                continue;
                        }
                        putObjectOnMap(map, moving[i]);
                }

                putObjectOnMap(map, mario);
                putScoreOnMap(map, score);

                showMap(map);
                usleep(10000);
        }

        endwin();

        free(brick);
        free(moving);

        return 0;
}
