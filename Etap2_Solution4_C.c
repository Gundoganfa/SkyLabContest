#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define mapWidth 128

// type & struct declerations
typedef enum {false, true} bool;

struct Point { 
   int x, y; 
}; 

struct flower {
    struct Point P1, P2;
    int objId;
};

// function declerations
bool isInMapArea (int x, int y);
bool isFlowerAroundACoord(int* map, int x, int y);
bool isCollusion(int* map);
void printFlower(struct flower *objptr);
void expandFlower(struct flower *objptr);
void printMap(int* map);
void chemicalReaction(int* map, int colX, int colY);
void startChemicalReaction(int *map);
void clearMap(int *map);
void countFlowers(int* map);

// *(map + i*mapWidth + j) means map[i][j]
int main()
{ 
    int map[mapWidth][mapWidth]; 
    // 0 empty, 1 flower1, 2 flower2, 4 flower3, others = collusion
    int i,j, tmp, simulationDays;
    bool collusionDetected;
    time_t t;
    
    struct flower flower1; // a flower is defined by 2 points P1 & P2
    struct flower flower2; // P1 is left bottom corner
    struct flower flower3; // P2 is right upper corner
 
    // Seed random number generator
    srand((unsigned)time(&t));
    
    // INIT SIMULATION
    simulationDays = 1;
    clearMap(map[0]);
    
    // create object ids
    // some of none should be equal to one's id.
    flower1.objId = 1;
    flower2.objId = 2;
    flower3.objId = 4;
    
    // create flower1
    flower1.P1.x = rand() % mapWidth;
    flower1.P1.y = rand() % mapWidth;
    map[flower1.P1.x][flower1.P1.y] = flower1.objId;
    
    // create flower2
    do {
        flower2.P1.x = rand() % mapWidth;
        flower2.P1.y = rand() % mapWidth;
    } while (isFlowerAroundACoord(map[0], flower2.P1.x, flower2.P1.y));
    map[flower2.P1.x][flower2.P1.y] = flower2.objId;
    
    // create flower3
    do {
        flower3.P1.x = rand() % mapWidth;
        flower3.P1.y = rand() % mapWidth;
    } while (isFlowerAroundACoord(map[0], flower3.P1.x, flower3.P1.y));
    map[flower3.P1.x][flower3.P1.y] = flower3.objId;
    
    // fill empty attributes of objects
    flower1.P2 = flower1.P1;
    flower2.P2 = flower2.P1;
    flower3.P2 = flower3.P1;
    
    //printMap(map[0]);printf("\n");
    
    // INIT DONE
    // START SIMULATION
    
    do {
        clearMap(map[0]);
        simulationDays++;
        
        // flowers are blooming
        expandFlower(&flower1);
        expandFlower(&flower2);
        expandFlower(&flower3);
        
        //put all flowers on map to print and/or check if there is a collusion
        for (i=flower1.P1.x; i<=flower1.P2.x; i++)
            for (j=flower1.P1.y; j<=flower1.P2.y; j++)
                map[i][j] += flower1.objId;
        for (i=flower2.P1.x; i<=flower2.P2.x; i++)
            for (j=flower2.P1.y; j<=flower2.P2.y; j++)
                map[i][j] += flower2.objId;
        for (i=flower3.P1.x; i<=flower3.P2.x; i++)
            for (j=flower3.P1.y; j<=flower3.P2.y; j++)
                map[i][j] += flower3.objId;
    } while (isCollusion(map[0])==false);
    
    // collusion occured
    // printMap(map[0]);printf("\n");printf("\n");
    
    // start chemical reactions
    startChemicalReaction(map[0]);
    //printMap(map[0]);
    
    // how many flowers left after chemical reaction?
    printf("Collusion Occured at Day %d\n", simulationDays);
    printf("How many flowers left?\n");
    countFlowers(map[0]);
    
    // end simulation.
    return 0;
}


bool isInMapArea (int x, int y) {
    bool xOk, yOk;
    xOk = (x >= 0) && (x < mapWidth); // target x coord is in Map Area
    yOk = (y >= 0) && (y < mapWidth); // target y coord is in Map Area
    return xOk && yOk;
}

bool isFlowerAroundACoord(int* map, int x, int y) {
    int i, j;
    int sum = 0;
    
    for (i=(x-1); i<=(x+1); i++) // set x boundries
        for (j=(y-1); j<=(y+1); j++) // set y boundries 
            if (isInMapArea(x,y))
                sum = sum + *(map + i*mapWidth + j);

    return (sum!=0); // FALSE if no flower around, TRUE if flower around
}

void printFlower(struct flower *objptr) {
    printf("objx : P1=(%d,%d) P2=(%d,%d)\n", (*objptr).P1.x, (*objptr).P1.y, (*objptr).P2.x, (*objptr).P2.y);
}

void expandFlower(struct flower *objptr) {
    int x, y, x1, y1;
    
    // Expand P1 coordinate of Flower
    x = (*objptr).P1.x;
    y = (*objptr).P1.y;
    x1 = x - 1;
    y1 = y - 1;
    if (x1 < 0) {
        x1 = 0;
    }
    if (y1 < 0) {
        y1 = 0;
    }
    (*objptr).P1.x = x1;
    (*objptr).P1.y = y1;
    
    // Expand P2 coordinate of Flower
    x = (*objptr).P2.x;
    y = (*objptr).P2.y;
    x1 = x + 1;
    y1 = y + 1;
    if (x1 >= mapWidth) {
        x1 = (mapWidth-1);
    }
    if (y1 >= mapWidth) {
        y1 = (mapWidth-1);
    }
    (*objptr).P2.x = x1;
    (*objptr).P2.y = y1;
}

bool isCollusion(int* map) {
    int i,j, tmp;
    bool collusionDetected;
    
    for (i=0; i<mapWidth; i++) {
        for (j=0; j<mapWidth; j++) {
            tmp = *(map + i*mapWidth + j);
            collusionDetected = (tmp!=0)&&(tmp!=1)&&(tmp!=2)&&(tmp!=4);
            if (collusionDetected) {
                return true;
            }
        }
    }
    return false;
}

void printMap(int* map) {
    int i, j;
    for (i = 0 ; i < mapWidth ; i++) {
        for (j = 0 ; j < mapWidth ; j++) {
            if (*(map + i*mapWidth + j) == 0)
                printf(".");
            else
                printf("%d", *(map + i*mapWidth + j));
        }
        printf("\n");
    }
}

void chemicalReaction(int* map, int colX, int colY) {
    // zero between (x-2,y-2) and (x+2, y+2)
    int x, y, tempX, tempY, tmp;
    
    for (tempX=(colX-2); tempX<=(colX+2); tempX++){
        for (tempY=(colY-2); tempY<=(colY+2); tempY++){
            x = tempX;
            y = tempY;
            
            if (x < 0) {
                x = 0;
            }
            if (y < 0) {
                y = 0;
            }
            if (x >= mapWidth) {
                x = (mapWidth-1);
            }
            if (y >= mapWidth) {
                y = (mapWidth-1);
            }
            
            tmp = *(map + x*mapWidth + y);
            if ((tmp==1)||(tmp==2)||(tmp==4)) {
                *(map + x*mapWidth + y) = 0;
            }
            
        }
    }
}

void startChemicalReaction(int *map) {
    int i, j, tmp;
    for (i = 0 ; i < mapWidth ; i++) {
        for (j = 0 ; j < mapWidth ; j++) {
            tmp = *(map + i*mapWidth + j);
            if (tmp!=0&&tmp!=1&&tmp!=2&&tmp!=4) {
              chemicalReaction(map, i, j);
            } 
        }
    }
    return;
}

void clearMap(int *map) {
    int i, j;
    for (i = 0 ; i < mapWidth ; i++) {
        for (j = 0 ; j < mapWidth ; j++) {
            *(map + i*mapWidth + j) = 0;
        }
    }
    return;
}

void countFlowers(int* map) {
    int ifl1, ifl2, ifl3;
    int i, j, tmp;
    
    ifl1 = 0;
    ifl2 = 0;
    ifl3 = 0;
    
    for (i = 0 ; i < mapWidth ; i++) {
        for (j = 0 ; j < mapWidth ; j++) {
            tmp = *(map + i*mapWidth + j);
            if (tmp == 1) {
                ifl1++;
            } else if (tmp == 2) {
                ifl2++;
            } else if (tmp == 4) {
                ifl3++;
            }
        }
    }

    printf("Flowers 1: %d\n", ifl1);
    printf("Flowers 2: %d\n", ifl2);
    printf("Flowers 3: %d\n", ifl3);    
    return;
}
