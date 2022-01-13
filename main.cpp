#include <iostream>
#include <C:\\msys64\\mingw32\\include\\graphics.h>
#include <C:\\msys64\\mingw32\\include\\winbgim.h>
//#include <graphics.h>
//#include <winbgim.h>
#include <math.h>
#include <windows.h>
using namespace std;

//Tudor Tescu
void start();
//Tudor Tescu
void info();

//Fabian Pintea

//declare dimensiuni initiale
// DIMX= Latimea initiala a blocurilor
// DIMY= Lungimea initiala a blocurilor
// SPL=  Padding-ul dintre loop si blocuri
// CT1=  Impartire triunghi coord x
// CT2=  Impartire triunghi coord y
int DIMX = 500;
int DIMY = 50, SPL = 30, CT1 = DIMX/2, CT2 = DIMY/2;
int X = DIMX, Y = DIMY;

#define DEFAULT_X 100
#define DEFAULT_Y 100
int startpx = 100, startpy = 100, L = 0;

//Tudor Tescu
//use this struct to define the data
struct data {
    int value;          //value of the variable
    char name[16];      //the name of our variable. max 16 chars
    bool isVar = false; //check if the spot is taken
    bool isNeg = false; //check if nr is negative
} variable[255];        //an array for the variables. max 255

//Tudor Tescu
int totalLine = 0, codeLine = 0, commentLine = 0;
struct node {
    char line[1023];

    node *left = NULL;
    node *below = NULL;
}*treeTop;

//Tudor Tescu
void reset(node *&t);

//Fabian Pintea
//blocks for Legend
void ProcessBlockL(int x, int y) {
    setlinestyle(0, 2, 3);
    rectangle(x-75, y-25, x+75, y+25);
}

//Fabian Pintea
void Normal_LoopL(int x, int y, int conditions, int &L) {
    int c1_x, c1_y, c2_x, c2_y, X = 150;
    setlinestyle(0, 2, 3);
    c1_x = x+SPL;         c1_y = y+DIMY;
    c2_x = x+X;           c2_y = y+DIMY;
    L = y + (50*(1 + conditions));
    line(x, y, x+X, y);
    line(x+X, y, x+X, y+DIMY);
    line(x+SPL, y+DIMY, x+X, y+DIMY);
    line(x, y, x, L);
    line(x+SPL, y+DIMY, x+SPL, L);
    line(x, L, x+SPL, L);

    //desenam conditiile din loop
    for(int i = 1; i <= conditions; i++) {
        line(c2_x, c2_y, c2_x, c2_y+DIMY);
        line(c2_x, c2_y+DIMY, c1_x, c1_y+DIMY);

        //CONDITIONS NAME
        c1_y += DIMY;   c2_y += DIMY;
    }
}

//Fabian Pintea
void Reverse_LoopL(int x, int y, int conditions, int &L) {
    int c1_x, c1_y, c2_x, c2_y, X=150;
    c1_x = x+SPL;       c1_y = y;
    c2_x = x+X;         c2_y=y;
    L = y + (50*(1 + conditions));
    setlinestyle(0, 2, 3);
    //desenam conditiile din loop
    for(int i = 1; i <= conditions; i++) {
        line(c1_x, c1_y, c2_x, c2_y);
        line(c2_x, c2_y, c2_x, c2_y+DIMY);
        //CONDITIONS NAME
        c1_y += DIMY;   c2_y += DIMY;

    }

    line(c1_x, c1_y, c2_x, c2_y);
    line(x, y, x, L);
    line(x, L, x+X, L);
    line(x+X, L, x+X, L);
    line(x+X, L, x+X, L-DIMY);
    line(x, y, x+SPL, y);
    line(x+SPL, L-DIMY, x+SPL, y);
}

//Fabian Pintea
void True_TriangleL(int x, int y, int Ax, int Ay) {
    char text[] = {"DA"};
    int Mx, My, X = 150, T1 = X/2;

    setlinestyle(0, 2, 3);
    line(x, y, x, y+DIMY);
    line(x, y+DIMY, x+T1, y+DIMY);
    line(x, y, x+T1, y+DIMY);
    Mx = Ax+CT2;  My = Ay+CT2; //calculam mijloacele
    settextstyle(4, 0, 1);
    outtextxy(Mx, My, text);
}

//Fabian Pintea
void False_TriangleL(int x, int y, int Bx, int By) {
    char text[] = {"NU"};
    int Mx, My, X = 150, T1 = X/2;

    setlinestyle(0, 2, 3);
    line(x+X, y, x+X, y+DIMY);
    line(x+X, y+DIMY, x+T1, y+DIMY);
    line(x+T1, y+DIMY, x+X, y);
    Mx = Bx - (CT2*2);  My = By+CT2; //calculam mijloacele
    settextstyle(4, 0, 1);
    outtextxy(Mx, My, text);
}

//Fabian Pintea
void BranchingBlockL(int x, int y) {
    int Ax, Ay, Bx, By, X = 150;

    Ax = x;        Ay = y;
    Bx = x+X;      By = y;

    setlinestyle(0, 2, 3);
    line(x, y, x+X, y);

    True_TriangleL(x, y, Ax, Ay);   //if triangle
    False_TriangleL(x, y, Bx, By);  //else triangle
}

//Fabian Pintea
//main menu
int windowx = 1680, windowy = 1000; //window default resolution

void menu(bool isInitial = false) {
    if (isInitial) {
        settextstyle(4, 0, 4);
        setbkcolor(WHITE);
        setcolor(BLACK);
    }
    setfillstyle(SOLID_FILL, WHITE);
    settextstyle(0, 0, 3);

    setlinestyle(1, 1, 2);

    line(windowx-550, 0, windowx-550, windowy);
    line(windowx-550, windowy-325, windowx, windowy-325);
    outtextxy(windowx-400, windowy-300, "Thank you!");

    //area where the node info should be shown is [windowx-550,windowy-280,windowx,windowy-280]

    //smiley
    circle(windowx-275, windowy-145, 120);

    // Set color of background to black
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);

    // Use fill ellipse for creating eyes
    fillellipse(windowx-310, windowy-195, 15, 30);
    fillellipse(windowx-240, windowy-195, 15, 30);

    // Use ellipse for creating mouth
    ellipse(windowx-275, windowy-120, 205, 335, 39, 32);
    ellipse(windowx-275, windowy-120, 205, 335, 39, 33);
    ellipse(windowx-275, windowy-120, 205, 335, 39, 34);
}

//Fabian Pintea
void legenda(int L) {
    int bordx = windowx-250, bordy = 70;

    settextstyle(4, 0, 4);
    outtextxy(bordx-20, bordy, "Legenda");
    bordy += 40;

    settextstyle(4, 0, 3);
    outtextxy(bordx-250, bordy+20, "Process Block");
    ProcessBlockL(bordx+75, bordy+25);
    bordy += DIMY;
    bordy += 20;

    outtextxy(bordx-100, bordy+50, "Loop");
    Normal_LoopL(bordx, bordy, 2, L);
    bordy *= 2;
    bordy += 40;

    outtextxy(bordx-180, bordy, "Reverse L");
    Reverse_LoopL(bordx, bordy-50, 2, L);
    bordy += (DIMY*2);
    bordy += 20;

    outtextxy(bordx-190, bordy+20, "If Statment");
    BranchingBlockL(bordx, bordy);

    settextstyle(4,0,4);
    bordy += 100;
}

//Tudor Tescu
//creates a new variable in the struct above
void CreateInteger(int value, char name[]) {
    int i = 0;
    while (variable[i].isVar && i < 255) {
        if (i == 254) {
            printf("Error. Max number of variables already entered.");
            exit(400);
        }
        if (strcmp(variable[i].name, name) == 0) {
            printf("Warning - variable %.*s is already defined. Setting value to 0.\n\n",
                strlen(name), name);
            variable[i].value = 0;
            return ;
        }

        i++;
    }

    value = 0;
    variable[i].isVar = true;
    variable[i].value = value;
    for (int k = 0; k < strlen(name); k++)
        variable[i].name[k] = name[k];
}

//Tudor Tescu
//function to check if a certain key is the first part of the line
int FirstChars(char location[], char key[]) {
    char *p = strstr(location, key);
    if (!p)
        return 0; //if the line is empty, return 0
    else {
        int setIndex = p - location; //calculate the start index of the pointer

        for (int i = 0; i < setIndex; i++) { //go through the line until the start of pointer
            if (location[i] != ' ')
                return 0; //if there is a different character than ' ' before the key, return 0
        }
    }

    //printf(location);

    return 1;
}

//Tudor Tescu
//function that counts lines. for debug purposes
void CountLines(int &totalLine, int &codeLine, int &commentLine, char line[]) {
    totalLine++;
    if (FirstChars(line, "//"))
        commentLine++;
    else if (strlen(line) != 1)
        codeLine++;
}

//Tudor Tescu
//check if a var is part of the struct. returns pos in struct if found, (-1) if not found.
int CheckVar(data vars[], char key[]) {
    //printf("/////////////////////////////////\n");
    for (int i = 0; i < 255; i++) {
        //printf("name in struct: <%s>\n", vars[i].name);

        if (strcmp(vars[i].name, key) == 0)
            return i;
    }
    //printf("///////////////////////////////////\n");
    return -1;
}

//Tudor Tescu
//check if a var is a number and return its positive value. return -1 if not
int IsNumber(char expression[]) {
    char numbers[] = {"0123456789"};
    bool isNum = true;
    int i = 0;
    int value = 0;

    if (expression[0] == '-') {
        i++;
    }
    while (i < strlen(expression)) {
        if (!strchr(numbers, expression[i++])) {
            isNum = false;
            return -1;
        }
        i++;
    }
    if (isNum) {
        for (int i = 0; i < strlen(expression); i++) {
            value = value * 10 + (expression[i] - 48);
        }

        //printf("Assigned value %d.\n", value);
        return value;
    }

    return -1;
}

//Tudor Tescu
int GetLineType(char line[]) {
    if (FirstChars(line, "if "))
        return 1;
    else if (FirstChars(line, "else"))
        return 2;
    else if (FirstChars(line, "for "))
        return 3;
    else if (FirstChars(line, "while "))
        return 4;
    else if (FirstChars(line, "do"))
        return 5;
    else if (FirstChars(line, "{"))
        return 6;
    else if (FirstChars(line, "}"))
        return 7;

    //default case, basic line
    return 0;
}

//Tudor Tescu
void NewNode(node *&n, char value[]) {
    if (!n) {
        n = new node;
        //printf("help??? %s\n", value);
        n->left = NULL;
        n->below = NULL;
        strcpy(n->line, value);
        printf("made node %s", value);
    }
    else {
        NewNode(n->below, value);
    }
}

//Tudor Tescu
void PrintTree(node *t) {
    //printf("help\n");
    if (t)
        printf("%s\n", t->line);
    if (t->left) {
        printf("Left of <<<%s>>>   ", t->line);
        PrintTree(t->left);
    }
    if (t->below) {
        printf("Below <<<%s>>>   ", t->line);
        PrintTree(t->below);
    }
}

//Tudor Tescu
void CopyToLeft(node *&location, node *key) {
    if (location->below)
        CopyToLeft(location->below, key);
    else
        location->left = key;
}

//Tudor Tescu
node* GetLeft(node *what) {
    if (what->below)
        return GetLeft(what->below);
    else
        return what;
}

//Tudor Tescu
int k = 0;
void MakeTree(node *&crt, char data[][128], int &last) {
    int lPar = 0;
    int rPar = 0;
    //printf("last %d line %s\n", last, data[last]);
    NewNode(crt, data[last++]);
    while (strcmp(data[last], "\0") && last < k) {
        while( !(GetLineType(data[last-1]) >= 1 && GetLineType(data[last-1]) <= 5) && strcmp(data[last], "\0") ) {
            if (GetLineType(data[last]) == 6)
                lPar++;
            else if (GetLineType(data[last]) == 7)
                rPar++;
            NewNode(crt->below, data[last]);

            last++;

            if (GetLineType(data[last]) == 7) {
                NewNode(crt->below, data[last]);
                //last++;
                printf("W1_exit\n");
                return;
            }
        }
        //printf("crt line %s\n", data[last]);
        if (last >= k)
            break;
        //printf("%d %d\n", last, k);

        last--;
        node *aux;
        aux = NULL;

        if (GetLineType(data[last]) >= 1 && GetLineType(data[last]) <= 6) {
            printf("help1\n");
            lPar = 0;
            rPar = 0;
            lPar++;
            last++;
            int i = last;
            NewNode(aux, data[i]);
            i++;
            while (strcmp(data[i], "\0") && lPar != rPar) {
                //printf("LINE %s\n", data[i]);
                if (GetLineType(data[i]) == 6)
                    lPar++;
                else if (GetLineType(data[i]) == 7)
                    rPar++;

                printf("lPar %d rPar %d\n", lPar, rPar);

                if ( !(GetLineType(data[i-1]) >= 1 && GetLineType(data[i-1]) <= 5) ) {
                    NewNode(aux->below, data[i]);
                    i++;
                }
                else if (GetLineType(data[i-1]) >= 1 && GetLineType(data[i-1]) <= 5) { //if is if/for/etc
                    //printf("left?\n");
                    node *aux2;
                    aux2 = GetLeft(aux);
                    MakeTree(aux2->left, data, i);
                    i++;
                    aux2 = NULL;
                }

                if (lPar == rPar || GetLineType(data[i]) == 7) {
                    NewNode(aux->below, data[i]);
                    i++;
                    printf("eqpar l%d r%d\n", lPar, rPar);
                    lPar = 0;
                    rPar = 0;
                    break;
                }

            }

            CopyToLeft(crt, aux);
            last = i;
        }
    }
}

int crtLine = 0;

//Tudor Tescu
int CountConditions (node *t) {
    int conditions = 0;
    while (t) {
        if (GetLineType(t->line) != 6 && GetLineType(t->line) != 7) {
            conditions++;
            printf("        %s\n", t->line);

        }
        t = t->below;
    }

    return conditions;
}

//Fabian Pintea
void ProcessBlock(int x, int y, int X, int &Y, int &L, node *t) {
    setlinestyle(0, 2, 3);
    line(x, y, x+X, y);
    line(x, y, x, y+50);
    line(x+X, y, x+X, y+50);
    line(x, y+50, x+X, y+50);
    L += 50;
    outtextxy(x+5, y+20, t->line);
    Y += 50;
}

//Fabian Pintea
void ProcessBlock_EMPTY(int x, int y, int X, int Y) {
    setlinestyle(0, 2, 3);
    line(x, y, x+X, y);
    line(x, y, x, y+50);
    line(x+X, y, x+X, y+50);
    line(x, y+50, x+X, y+50);
}

//Fabian Pintea
void Normal_Loop(int x, int y, int conditions, int &L, int X, int &Y, int S, node *t) {
    int c1_x, c1_y, c2_x, c2_y;
    setlinestyle(0, 2, 3);
    c1_x = x+S;     c1_y = y+50;
    c2_x = x+X;     c2_y = y+50;
    int copyL = L + 50*(1 + conditions) + (startpy);
    L = L + 50*(1 + conditions);

    //desenam
    line(x, y, x+X, y);
    line(x+X, y, x+X, y+50);
    line(x+S, y+50, x+X, y+50);
    line(x, y, x, copyL);
    line(x+S, y+50, x+S, copyL);
    line(x, copyL, x+S, copyL);
    outtextxy(x+10, y+15, t->line);

    //desenam conditiile
    t = t->left->below;
    for(int i = 1; i <= conditions; i++) {
        line(c2_x, c2_y, c2_x, c2_y+50);
        line(c2_x, c2_y+50, c1_x, c1_y+50);

        //CONDITIONS NAME
        outtextxy(c1_x+10, c1_y+20, t->line);
        t = t->below;
        c1_y += 50;   c2_y += 50;
        Y += 50;
    }
    Y += 50;
}

//Fabian Pintea
void Reverse_Loop(int x, int y, int conditions, int &L, int X, int &Y, int S, node *t) {
    int c1_x, c1_y, c2_x, c2_y;
    c1_x = x+S;     c1_y = y;
    c2_x = x+X;     c2_y = y;
    int copyL = L + 50*(1 + conditions) + (startpy);
    L = L + 50*(1 + conditions);
    setlinestyle(0, 2, 3);
    outtextxy(x, y+10, t->line);
    node *p;
    p = new node;
    p = t->left->below;

    //desneam conditiile
    for(int i = 1; i <= conditions; i++) {
        line(c1_x, c1_y, c2_x, c2_y);
        line(c2_x, c2_y, c2_x, c2_y+50);

        //CONDITIONS NAME
        outtextxy(c1_x+10, c1_y+20, p->line);
        p = p->below;
        c1_y += 50;   c2_y += 50;
        Y += 50;
    }
    //desenam
    line(c1_x, c1_y, c2_x, c2_y);
    line(x, y, x, copyL);
    line(x, copyL, x+X, copyL);
    line(x+X, copyL, x+X, copyL);
    line(x+X, copyL, x+X, copyL-50);
    line(x, y, x+S, y);
    line(x+S, copyL-50, x+S, y);
    outtextxy(x+5, copyL-30, p->line);

    Y += 50;
}

//Fabian Pintea
void True_Triangle(int x, int y, int Ax, int Ay, int X, int Y, int C1, int C2) {
    int Mx, My;
    setlinestyle(0, 2, 3);
    line(x, y, x, y+50);
    line(x, y+50, x+C1, y+50);
    line(x, y, x+C1, y+50);
}

//Fabian Pintea
void False_Triangle(int x, int y, int Bx, int By, int X, int Y, int C1, int C2) {
    int Mx, My;
    setlinestyle(0, 2, 3);
    line(x+X, y, x+X, y+50);
    line(x+X, y+50, x+C1, y+50);
    line(x+C1, y+50, x+X, y);
}

//Fabian Pintea
void IFF(int x, int &y, int &Y, int C1, int L, node *t) {
    ProcessBlock(x, y+50, C1, Y, L, t);
}

//Fabian Pintea
void ELSEF(int x, int &y, int &Y, int C1, int L, node *t) {
    ProcessBlock(C1+x, y+50, C1, Y, L, t);
}

//Fabian Pintea
void ELSEFE(int x, int y, int Y, int C1) {
    ProcessBlock_EMPTY(C1+x, y+50, C1, y+100);
}

//Fabian Pintea
void IFFE(int x, int y, int Y, int C1) {
    ProcessBlock_EMPTY(x, y+50, C1, y+100);
}

//Fabian Pintea
void casesIF(int x, int &y, int X, int &Y, int conditionsIF, int conditionsELSE, int C1, int C2, int &L, node *t, node *p) {
    if(conditionsIF >= conditionsELSE) {
        for(conditionsIF; conditionsIF >= 1; conditionsIF--) {
            y = Y-150;
            IFF(x, y, Y, C1, L, t);
            printf("///////////IFF    Y  %d /////////////\n", Y);
            printf("conditions - %d\n\n", conditionsIF);

            if(conditionsELSE >= 1) {
                ELSEF(x, y, Y, C1, L, p);
                Y -= 50;
                conditionsELSE--;
            }
            else {
                ELSEFE(x, y, Y, C1);
                //Y -= 50;
            }
            if(t->below)
                t = t->below;
            if(p->below)
                p = p->below;
        }
    }
    else if (conditionsELSE > conditionsIF) {
        for(conditionsELSE; conditionsELSE >= 1; conditionsELSE--) {
            y = Y-150;

            ELSEF(x, y, Y, C1, L, p);
            printf("///////////ELSEF   y %d --- Y %d /////////////\n", y, Y);

            if(conditionsIF >= 1) {
                IFF(x, y, Y, C1, L, t);
                Y -= 50;
                conditionsIF--;
            }
           else {
                IFFE(x, y, Y, C1);
                //Y -= 50;
            }
            if(t->below)
                t = t->below;
            if(p->below)
                p = p->below;
        }
    }
    Y += 50;
}

//Fabian Pintea si Tudor Tescu
void BranchingBlock(int x, int y, int X, int &Y, int conditionsIF, int C1, int C2, int &L, node *t) {
    int Ax, Ay, Bx, By, copyL, conditionsELSE = 0;
    Ax = x;     Ay = y;
    Bx = x+X;   By = y;
    setlinestyle(0, 2, 3);
    line(x, y, x+X, y);
    True_Triangle(x, y, Ax, Ay, X, Y, X/2, C2);
    False_Triangle(x, y, Bx, By, X, Y, X/2, C2);

    outtextxy(x+175, y+15, t->line);
    conditionsELSE = CountConditions(t->below->left);
    node *p;
    p = new node;

    //Tudor Tescu - asistenta in parcurgerea arborelui, doar acest if
    if (t) {
        if (t->below) {
            p = t->below;//else
            if (t->below->left) {
                p = t->below->left;
                if (t->below->left->below)
                    p = t->below->left->below;
            }
        }
    }
    t = t->left->below;//if


    casesIF(x, y, X, Y, conditionsIF, conditionsELSE, X/2, C2, L, t, p);
    Y += 50;
    if (conditionsIF >= conditionsELSE)
        L = L + (50*(1 + conditionsIF));
    else if (conditionsIF < conditionsELSE)
        L = L + (50*(1 + conditionsELSE));
}

//Fabian Pintea si Tudor Tescu
void DrawNS(node *t) {
    printf("X %d    Y %d\n", X, Y);

    menu(true);
    legenda(L);
    int S = SPL,C1 = CT1, C2 = CT2;
    settextstyle(1, 0, 1);
    if (t) {
        if (t->line[0] != '\0') {
            if (GetLineType(t->line) == 0) {
                ProcessBlock(startpx, startpy + L, X, Y, L,t);
                printf("draw basic ------ %s", t->line);
                DrawNS(t->below);
            }
            else if (GetLineType(t->line) == 1) {
                if(GetLineType(t->below->line)==2) {
                    printf("draw if with else ------- %s%s", t->line,t->below->line);
                    BranchingBlock(startpx, startpy + L, X, Y,CountConditions(t->left), C1, C2, L, t);
                    DrawNS(t->below->below);

                }
                else {
                     printf("draw if ------- %s", t->line);
                     BranchingBlock(startpx, startpy + L, X, Y,CountConditions(t->left), C1, C2, L, t);
                     DrawNS(t->below);
                }

            }
            else if (GetLineType(t->line) == 3) {
                printf("draw for ------- %s", t->line);
                Normal_Loop(startpx, startpy + L, CountConditions(t->left), L, X, Y, S,t);
                DrawNS(t->below);
            }
            else if (GetLineType(t->line) == 4) {
                printf("draw while ------- %s", t->line);
                Normal_Loop(startpx, startpy + L, CountConditions(t->left), L, X, Y, S,t);
                DrawNS(t->below);
            }
            else if (GetLineType(t->line) == 5) {
                printf("draw do/while ------- %s", t->line);
                Reverse_Loop(startpx, startpy + L, CountConditions(t->left), L, X, Y, S,t);
                DrawNS(t->below);
            }
        }
        else {
            DrawNS(t->below);
        }
    }
    menu();
}

//Fabian Pintea
void ResetCoord() {
    Y = 250+startpy-100;
    X = 500+startpx-100;
    L = 0;
}

//Fabian Pintea si Tudor Tescu
void opening() {
    cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    setbkcolor(GREEN);
    floodfill(0, 0, WHITE);
    setcolor(WHITE);
    readimagefile("images/opening.jpg", 0, 0, windowx, windowy);
    settextstyle(6, 0, 6);
    outtextxy(1380/3 - 50, 150, "Nassi-Schneiderman Diagram");

    //introduceti o diagrama
    outtextxy(1380/2 - 125, 450, "Introduceti un cod");

    //diagrama anterioara
    outtextxy(1380/2 - 60, 550, "Codul anterior");

    //curiozitati
    outtextxy(1380/2 - 20, 650, "Informatii");
}

//Tudor Tescu
void InitAlg() {
    reset(treeTop);
    int C1 = CT1, C2 = CT2, S = SPL;
    FILE *input = fopen("input.txt", "r");
    floodfill(0, 0, WHITE);

    if (!input) {
        printf("Error - input file empty");
        exit(1);
    }

    //saving the code in a 2d array, as tokens
    char linie[1023];
    char code[1024][128] = {0};
    while (fgets(linie, sizeof(linie), input)) {
        if (strcmp(linie, "\0") && strcmp(linie, "\n")) {
            strcpy(code[k], linie);
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        int var = 0;
        //count the lines for debug
        CountLines(totalLine, codeLine, commentLine, code[k]);

        strcpy(linie, code[i]);

        if (strlen(linie) == 1) {
            printf("Empty line %d\n", totalLine);
            //IGNORE LINE
        }
        else if (FirstChars(linie, "//")) {
            printf("Commented line %d\n", totalLine);
            //IGNORE LINE
        }//check if an int variable is defined
        else if (FirstChars(linie, "float ")) {
            printf("Declared float on line %d\n", totalLine);//extract the variable name
            char name[16] = {0};
            int i = 6, k = 0;
            while(i < strlen(linie)-1) {
                name[k++] = linie[i++];
            }

            CreateInteger(1, name);
        }
        else if (FirstChars(linie, "unsigned int ")) {//extract the variable name
            char name[16] = {0};
            int i = 13, k = 0;
            while(i < strlen(linie)-1) {
                name[k++] = linie[i++];
            }

            CreateInteger(1, name);
            printf("Declared unsigned int line %d\n", totalLine);
        }
        else if (FirstChars(linie, "double ")) {//extract the variable name
            char name[16] = {0};
            int i = 7, k = 0;
            while(i < strlen(linie)-1) {
                name[k++] = linie[i++];
            }

            CreateInteger(1, name);
            printf("Declared double on line %d\n", totalLine);
        }
        else if (FirstChars(linie, "int ")) {
            printf("Declared int on line %d\n", totalLine);

            //extract the variable name
            char name[16] = {0};
            int i = 4, k = 0;
            while(i < strlen(linie)-1) {
                name[k++] = linie[i++];
            }

            CreateInteger(1, name);
            //MakeNode(tree, line, "basic");
        }//check if the line is an IF check
        else if (FirstChars(linie, "if ")) {
            printf("If check on line %d\n", totalLine);
            //MakeNode(tree, line, "if");
        }
        else if (FirstChars(linie, "else")) {
            printf("Else check on line %d\n", totalLine);
            //MakeNode(tree, line, "else");
        }
        else if (FirstChars(linie, "{")) {
            printf("Opened accolade on line %d\n", totalLine);
            //MakeNode(tree, line, "openAcc");
        }
        else if (FirstChars(linie, "}")) {
            printf("Closed accolade on line %d\n", totalLine);
            //MakeNode(tree, line, "closeAcc");
        }
        else if (FirstChars(linie, "fopen ")) {
            printf("Open file on line %d\n", totalLine);
            //MakeNode(tree, line, "basic");
        }
        else if (FirstChars(linie, "for ")) {
            printf("For iteration on line %d\n", totalLine);
            //MakeNode(tree, line, "for");
        }
        else if (FirstChars(linie, "while ")) {
            printf("While iteration on line %d\n", totalLine);
            //MakeNode(tree, line, "while");
        }
        else if (FirstChars(linie, "do")) {
            printf("do/while iteration on line %d\n", totalLine);
        }
        else if (FirstChars(linie, "printc ")) {
            printf("Output to console on line %d\n", totalLine);
            //MakeNode(tree, line, "basic");
        }
        else if (FirstChars(linie, "printf ")) {
            printf("Print to file on line %d\n", totalLine);
            //MakeNode(tree, line, "basic");
        }//check if we are modifying a variable
        else if (!var) {
            //count until we hit a char != ' '
            int i = 0, k = 0;
            char name[16] = {0};
            //reset char array
            for (int i = 0; i < 16; i++)
                name[i] = '\0';
            while (linie[i++] == ' ' && i < strlen(linie)) {} //will end at i+1
            i--;
            while (linie[i] != ' ' && i < strlen(linie)) {
                name[k++] = linie[i++];
            }//will end at i+1 (on the first space after the name)

            //now we need to check if the name is found in the struct
            var = CheckVar(variable, name);
            if (var >= 0) {
                //after the name, we have " = " so 3 chars.
                //after that, we are in the expression
                i += 3;

                //we are now in the expression and we will save it in an array
                k = 0;
                char expression[1023] = {0};
                while(i < strlen(linie)-1) {
                    expression[k++] = linie[i++];
                }
                //HERE WE HAVE A MATH EQUATION
                printf("Found expression %.*s = %.*s on line %d.\n",
                    strlen(name), name,
                    strlen(expression), expression,
                    totalLine);

                //MakeNode(tree, line, "basic");
            }
            else {
                printf("Variable %s is not defined. Error on line %d.\n", name, totalLine);
                exit(200);
            }

        }//if the line does not match any of the defined operations and is NOT empty and NOT a comment, error 1000
        else {
            if (!FirstChars(linie, "//") && !FirstChars(linie, "\n")) {
                printf("Error on line %d. Undefined instruction.\n", totalLine);
                exit(1000);
            }
        }
        //printf("\n\n");
    }
    //getchar();
    fclose(input);

    printf("\n\n\n///////////////////////////////\n\n\n\n");
    //printing the tokens
    //system("clear");
    printf("Here is the code, saved as tokens.\n\n");
    for (int i = 0; i < k; i++) {
        printf("%s", code[i]);
    }

    printf("\n\n\n///////////////////////////////\n\n\n\n");

    //printing the total amount of lines
    printf("\n\nThe code contains this many lines:\n");
    //for debug
    printf("Total lines: %d\n", totalLine);
    printf("Code lines: %d\n", codeLine);
    printf("Comment lines: %d\n", commentLine);
    //getchar();

    printf("\n\n\n///////////////////////////////\n\n\n\n");

    printf("Tree construction debug:\n\n");
    //system("clear");
    int last = 0;
    MakeTree(treeTop, code, last);
    //getchar();
    printf("\n\n\n///////////////////////////////\n\n\n\n");

    printf("The tree:\n\n");
    //system("clear");
    PrintTree(treeTop);
    printf("\n\n\n///////////////////////////////\n\n\n\n");

    //Pintea Fabian
    printf("\n///////////// DRAWING DEBUG ////////////\n\n");
    settextstyle(0, 0, 2);

    DrawNS(treeTop);
    bool isExit = false;
    while (!isExit) {
        bool clicked = false;

        setfillstyle(SOLID_FILL, BLACK);
        setlinestyle(0, 0, 3);
        //up
        //rectangle(970, 760, 970+70, 760+70);
        rectangle(970+23, 760+70, 970+47, 760+30);
        line(970+23-15, 760+30, 970+47+15, 760+30);
        line(970+23-15, 760+30, 970+23+15, 760+5);
        line(970+47+15, 760+30, 970+23+15, 760+5);
        floodfill(1002, 778, BLACK);
        floodfill(1002, 807, BLACK);

        //down
        //rectangle(970, 920, 970+70, 920+70);
        rectangle(970+23, 920, 970+47, 920+40);
        line(970+23-15, 960, 970+47+15, 960);
        line(970+23-15, 960, 970+23+15, 985);
        line(970+23+15, 985, 970+47+15, 960);
        floodfill(1002, 932, BLACK);
        floodfill(1002, 974, BLACK);

        //left
        //rectangle(890, 840, 890+70, 840+70);
        rectangle(955, 840+23, 915, 840+47);
        line(890+25, 840+15, 890+25, 840+55);
        line(890+25, 840+15, 890, 840+35);
        line(890+25, 840+70-15, 890, 840+35);
        floodfill(927, 872, BLACK);
        floodfill(904, 873, BLACK);

        //right
        //rectangle(1050, 840, 1050+70, 840+70);
        rectangle(1055, 840+23, 1090, 840+47);
        floodfill(1060, 870, BLACK);
        line(1090, 840+15, 1090, 840+70-15);
        line(1090, 840+15, 1115, 840+35);
        line(1090, 840+70-15, 1115, 840+35);
        floodfill(1095, 840+23, BLACK);

        //reset
        //rectangle(970, 840, 970+70, 840+70);
        circle(970+35, 840+35, 20);
        floodfill(970+35, 840+35, BLACK);

        //exit
        //rectangle(1070, 70, 1070+50, 120);
        setlinestyle(SOLID_LINE, 0, 5);
        line(1070, 70, 1070+50, 120);
        line(1070+50, 70, 1070, 120);

        int mouseX = 0;
        int mouseY = 0;
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

        //up -      (970, 760),     (1040, 830)
        //reset -   (970, 840),     (1040, 910)
        //down -    (970, 920),     (1040, 990)
        //left -    (890, 840),     (960, 910)
        //right -   (1050, 840),    (1120, 910)
        //exit -    (1070, 70),     (1120, 120)

        int dif = 50;
        if (mouseX >= 970 && mouseX <= 1040 && mouseY >= 760 && mouseY <= 830) { //up
            //if (startpy - dif > 99)
            startpy -= dif;
            Beep(750, 100);
            printf("pressed UP  ----  startpx %d  ----  startpy %d\n", startpx, startpy);
            cleardevice();
            ResetCoord();
            DrawNS(treeTop);
            continue;
        }
        else if (mouseX >= 970 && mouseX <= 1040 && mouseY >= 840 && mouseY <= 910) { //reset
            startpx = DEFAULT_X;
            startpy = DEFAULT_Y;
            Beep(750, 100);
            Sleep(25);
            Beep(750, 75);
            printf("pressed RESET  ----  startpx %d  ----  startpy %d\n", startpx, startpy);
            cleardevice();
            ResetCoord();
            DrawNS(treeTop);
            continue;
        }
        else if (mouseX >= 970 && mouseX <= 1040 && mouseY >= 920 && mouseY <= 990) { //down
            startpy += dif;
            Beep(750, 100);
            printf("pressed DOWN  ----  startpx %d  ----  startpy %d\n", startpx, startpy);
            cleardevice();
            ResetCoord();
            DrawNS(treeTop);
            continue;
        }
        else if (mouseX >= 890 && mouseY >= 840 && mouseX <= 960 && mouseY <= 910) { //left
            startpx -= dif;
            X = startpx + 500;
            Beep(750, 100);
            printf("pressed LEFT  ----  startpx %d  ----  startpy %d\n", startpx, startpy);
            cleardevice();
            ResetCoord();
            DrawNS(treeTop);
            continue;
        }
        else if (mouseX >= 1050 && mouseY >= 840 && mouseX <= 1120 && mouseY <= 910) { //right
            if (startpx < 200) {
                startpx += dif;
                X = startpx + 500;
                Beep(750, 100);
                printf("pressed RIGHT  ----  startpx %d  ----  startpy %d\n", startpx, startpy);
                cleardevice();
                ResetCoord();
                DrawNS(treeTop);
                continue;
            }
        }
        else if (mouseX >= 1070 && mouseY >= 70 && mouseX <= 1120 && mouseY <= 120) { //exit
            cleardevice();
            Beep(750, 100);
            Sleep(50);
            Beep(500, 75);
            start();
            return ;
        }

        if (mouseX != -1) {
            printf("%d   %d\n", mouseX, mouseY);
        }
    }

    getch();
    closegraph();
}

//Tudor Tescu
//reseteaza arborele in memorie
void reset(node *&t) {
    if (t) {
        if (t->left) {
            reset(t->left);
        }
        if (t->below) {
            reset(t->below);
        }
        t = new node;
        memset(t->line, 0, 1023);
    }
}

//Tudor Tescu si Fabian Pintea
//initializarea alrogitmului. de aici pleaca tot.
void start() {
    ResetCoord();
    reset(treeTop);
    //treeTop = new node;

    k = 0;
    crtLine = 0;
    totalLine = codeLine = commentLine = 0;

    //drawing the menu buttons
    opening();

    bool isExit = false;
    while (!isExit) {
        int mouseX = 0;
        int mouseY = 0;

        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if (mouseX >= 300 && mouseX <= 1380) {
            if (mouseY >= 400 && mouseY <= 500) {
                Beep(750, 100);
                system("notepad.exe input.txt");
                cleardevice();
                InitAlg();
            }
            else if (mouseY >= 501 && mouseY <= 600) {
                Beep(750, 100);
                cleardevice();
                InitAlg();
            }
            else if (mouseY >= 601 && mouseY <= 700) {
                Beep(750, 100);
                info();
            }
        }
    }
}

//Fabian Pintea
void info() {
    cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    setbkcolor(GREEN);
    floodfill(0, 0, WHITE);
    setcolor(WHITE);
    readimagefile("images/about.jpg", 0, 0, windowx, windowy);

    bool isBack = false;
    while (!isBack) {
        int mouseX = 0;
        int mouseY = 0;
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if (mouseX >= 35 && mouseX <= 155 && mouseY >= 850 && mouseY <= 970) {
            Beep(500, 100);
            cleardevice();
            start();
        }
    }
}

//Tudor Tescu si Fabian Pintea
int main()
{
    initwindow(windowx, windowy, "Nassi-Schneiderman Diagram", 120);
    start();

    return 0;
}
//dimensiune fereastra 1680x1000
