#include <iostream>
//#include <graphics.h>
//#include <winbgim.h>
#include <C:\\msys64\\mingw32\\include\\graphics.h>
#include <C:\\msys64\\mingw32\\include\\winbgim.h>
#include <math.h>
using namespace std;

int DIMX=150,DIMY=50,SPL=30,CT1=DIMX/2,CT2=DIMY/2;
//declare dimensiuni initiale
int X=DIMX,Y=DIMY;
int startpx=100,startpy=100,L=0;

// DIMX= Latimea initiala a blocurilor
// DIMY= Lungimea initiala a blocurilor
// SPL=  Padding-ul dintre loop si blocuri
// CT1=  Impartire triunghi coord x
// CT2=  Impartire triunghi coord y

struct area{
            int x,y,xx,yy;}S[50]; //creem o arie pt a determina unde am dat click cu mouse-ul
int nrb=1;

//use this struct to define the data
struct data {
    int value;          //value of the variable
    char name[16];      //the name of our variable. max 16 chars
    bool isVar = false; //check if the spot is taken
    bool isNeg = false; //check if nr is negative
} variable[255];        //an array for the variables. max 255

void createarea(int x,int y,int xx,int yy)
{
    S[nrb].x=x;
    S[nrb].y=y;
    S[nrb].xx=xx;
    S[nrb].yy=yy;
    nrb++;
}

void ProcessBlock(int x,int y,int X,int Y, int &L)
{
    setlinestyle(0,2,3);
    line(x,y,x+X,y);
    line(x,y,x,y+Y);
    line(x+X,y,x+X,y+Y);
    line(x,y+Y,x+DIMX,y+Y);
    L += 50;

    createarea(x,y,X,Y);
    //floodfill(x,y,WHITE);
}

void Normal_Loop(int x,int y,int conditions,int &L,int X,int Y,int S)
{
    int c1_x,c1_y,c2_x,c2_y;
    setlinestyle(0,2,3);
    c1_x=x+S;     c1_y=y+Y;
    c2_x=x+X;     c2_y=y+Y;
    int copyL = L + 50*(1 + conditions);
    L = y + 50*(1 + conditions);
    //desenam
    line(x,y,x+X,y);
    line(x+X,y,x+X,y+Y);
    line(x+S,y+Y,x+X,y+Y);
    line(x,y,x,L);
    line(x+S,y+Y,x+S,L);
    line(x,L,x+S,L);
    //desenam conditiile
    for(int i=1;i<=conditions;i++)
    {
        line(c2_x,c2_y,c2_x,c2_y+Y);
        line(c2_x,c2_y+Y,c1_x,c1_y+Y);

        //CONDITIONS NAME
        c1_y+=Y;   c2_y+=Y;
    }
    //floodfill(x,y,WHITE);
    createarea(x,y,x+X,y+Y);

    L = copyL;
}
void Reverse_Loop(int x,int y,int conditions,int &L,int X,int Y,int S)
{
    int c1_x,c1_y,c2_x,c2_y;
    c1_x=x+S;     c1_y=y;
    c2_x=x+X;     c2_y=y;
    int copyL = L + 50*(1 + conditions);
    L=y+(50*(1+conditions));
    setlinestyle(0,2,3);
    //desneam conditiile
    for(int i=1;i<=conditions;i++)
    {
        line(c1_x,c1_y,c2_x,c2_y);
        line(c2_x,c2_y,c2_x,c2_y+Y);
        //CONDITIONS NAME
        c1_y+=Y;   c2_y+=Y;

    }
    //desenam
    line(c1_x,c1_y,c2_x,c2_y);
    line(x,y,x,L);
    line(x,L,x+X,L);
    line(x+X,L,x+X,L);
    line(x+X,L,x+X,L-Y);
    line(x,y,x+S,y);
    line(x+S,L-Y,x+S,y);
    //floodfill(x,y,WHITE);
    createarea(x,y,x+X,y+Y);
    L = copyL;
}

void True_Triangle(int x,int y,int Ax,int Ay,int X,int Y,int C1,int C2)
{
    int Mx,My;
    setlinestyle(0,2,3);
    line(x,y,x,y+Y);
    line(x,y+Y,x+C1,y+Y);
    line(x,y,x+C1,y+Y);
    Mx= Ax+C2;  My=Ay+C2;

}
void False_Triangle(int x,int y,int Bx,int By,int X,int Y,int C1,int C2)
{
    int Mx,My;
    setlinestyle(0,2,3);
    line(x+X,y,x+X,y+Y);
    line(x+X,y+Y,x+C1,y+Y);
    line(x+C1,y+Y,x+X,y);
    Mx= Bx-(C2*2);  My=By+C2;


}

void BranchingBlock(int x,int y,int X,int Y,int C1,int C2)
{
    int Ax,Ay,Bx,By;
    Ax=x;        Ay=y;
    Bx=x+X;   By=y;
    setlinestyle(0,2,3);
    line(x,y,x+X,y);
    True_Triangle(x,y,Ax,Ay,X,Y,C1,C2);
    False_Triangle(x,y,Bx,By,X,Y,C1,C2);
    createarea(x,y,x+X,y+Y);
}

// blocks for Legend
void ProcessBlockL(int x,int y)
{
    setlinestyle(0,2,3);
    rectangle(x-CT1,y-CT2,x+CT1,y+CT2);
    //floodfill(x,y,WHITE);
}

void Normal_LoopL(int x,int y,int conditions,int &L)
{
    int c1_x,c1_y,c2_x,c2_y;
    setlinestyle(0,2,3);
    c1_x=x+SPL;       c1_y=y+DIMY;
    c2_x=x+DIMX;     c2_y=y+DIMY;
    L=y+(50*(1+conditions));
    line(x,y,x+DIMX,y);
    line(x+DIMX,y,x+DIMX,y+DIMY);
    line(x+SPL,y+DIMY,x+DIMX,y+DIMY);
    line(x,y,x,L);
    line(x+SPL,y+DIMY,x+SPL,L);
    line(x,L,x+SPL,L);

    for(int i=1;i<=conditions;i++)
    {
        line(c2_x,c2_y,c2_x,c2_y+DIMY);
        line(c2_x,c2_y+DIMY,c1_x,c1_y+DIMY);

        //CONDITIONS NAME
        c1_y+=DIMY;   c2_y+=DIMY;
    }
    //floodfill(x,y,WHITE);
}
void Reverse_LoopL(int x,int y,int conditions,int &L)
{
    int c1_x,c1_y,c2_x,c2_y;
    c1_x=x+SPL;       c1_y=y;
    c2_x=x+DIMX;     c2_y=y;
    L=y+(50*(1+conditions));
    setlinestyle(0,2,3);
    for(int i=1;i<=conditions;i++)
    {
        line(c1_x,c1_y,c2_x,c2_y);
        line(c2_x,c2_y,c2_x,c2_y+DIMY);
        //CONDITIONS NAME
        c1_y+=DIMY;   c2_y+=DIMY;

    }
    line(c1_x,c1_y,c2_x,c2_y);
    line(x,y,x,L);
    line(x,L,x+DIMX,L);
    line(x+DIMX,L,x+DIMX,L);
    line(x+DIMX,L,x+DIMX,L-DIMY);
    line(x,y,x+SPL,y);
    line(x+SPL,L-DIMY,x+SPL,y);
    //floodfill(x,y,WHITE);
}
void True_TriangleL(int x,int y,int Ax,int Ay)
{
    char text[]={"DA"};
    int lat,lun,Mx,My;
    setlinestyle(0,2,3);
    line(x,y,x,y+DIMY);
    line(x,y+DIMY,x+CT1,y+DIMY);
    line(x,y,x+CT1,y+DIMY);
    Mx= Ax+CT2;  My=Ay+CT2;
    settextstyle(4,0,1);
    outtextxy(Mx,My,text);
    //print "DA" in middle of the triangle

}
void False_TriangleL(int x,int y,int Bx,int By)
{
    char text[]={"NU"};
    int lat,lun,Mx,My;
    lat=textwidth(text);
    lun=textheight(text);
    setlinestyle(0,2,3);
    line(x+DIMX,y,x+DIMX,y+DIMY);
    line(x+DIMX,y+DIMY,x+CT1,y+DIMY);
    line(x+CT1,y+DIMY,x+DIMX,y);
    Mx= Bx-(CT2*2);  My=By+CT2;
    settextstyle(4,0,1);
    outtextxy(Mx,My,text);
    //print "NU" in middle of the triangle

}

void BranchingBlockL(int x,int y)
{
    //int Lg=textwidth(text);
    //int Lt=textheight(text);
    int Ax,Ay,Bx,By;
    Ax=x;        Ay=y;
    Bx=x+DIMX;   By=y;
    setlinestyle(0,2,3);
    line(x,y,x+DIMX,y);
    True_TriangleL(x,y,Ax,Ay);
    False_TriangleL(x,y,Bx,By);
    //floodfill(x,y,WHITE);
    //outtextxy();
}


//main menu
int windowx=1300,windowy=850;
void menu()
{
    settextstyle(4,0,4);
    setbkcolor(WHITE);
    setcolor(BLACK);

    outtextxy(windowx/4,25,"Nassi-Schneiderman Diagram");

    setlinestyle(1,1,2);
    line(0,60,windowx,60);

    line(windowx-550,65,windowx-550,windowy);
    line(windowx-550,windowy-280,windowx,windowy-280);
    //area where the node info should be shown is [windowx-550,windowy-280,windowx,windowy-280]
}

void legenda(int L)
{
    int bordx=windowx-250,bordy=150;

    settextstyle(4,0,4);
    outtextxy(bordx-20,bordy-50,"Legenda");

    settextstyle(4,0,3);
    outtextxy(bordx-240,bordy+20,"Process Block");
    ProcessBlockL(bordx+75,bordy+25);
    bordy+=DIMY;

    outtextxy(bordx-100,bordy+50,"Loop");
    Normal_LoopL(bordx,bordy,2,L);
    bordy*=2;

    outtextxy(bordx-240,bordy,"Reverse Loop");
    Reverse_LoopL(bordx,bordy-50,2,L);
    bordy+=(DIMY*2);

    outtextxy(bordx-210,bordy+20,"If Statement");
    BranchingBlockL(bordx,bordy);

    settextstyle(4,0,4);
    bordy+=100;
    outtextxy(bordx-100,bordy,"Made by");
    outtextxy(bordx-150,bordy+50,"Tudor Tescu");
    outtextxy(bordx-45,bordy+100,"&");
    outtextxy(bordx-150,bordy+150,"Fabian Pintea");
}
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

//function that counts lines. for debug purposes
void CountLines(int &totalLine, int &codeLine, int &commentLine, char line[]) {
    totalLine++;
    if (FirstChars(line, "//"))
        commentLine++;
    else if (strlen(line) != 1)
        codeLine++;
}

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

int totalLine = 0, codeLine = 0, commentLine = 0;
struct node {
    char line[1023];

    node *left = NULL;
    node *below = NULL;
}*treeTop;

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

void CopyToLeft(node *&location, node *key) {
    if (location->below)
        CopyToLeft(location->below, key);
    else
        location->left = key;
}

node* GetLeft(node *what) {
    if (what->below)
        return GetLeft(what->below);
    else
        return what;
}

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

//searching and displaying on another text the code
/*
int searchA(int x,int y)
{
    int i,ok=0;
    for(i=1;i<=50;i++)
    {
        //S[nrb].x,y,xx,yy;
        if((S[i].x<x&&S[i].y<y)&&(S[i].xx>x&&S[i].yy>y))
           {
             ok=1;
             break;
           }
    }
    if(ok==1)
    {
        initwindow(300,300);
        floodfill(0,0,WHITE);
        outtext("TEST");
    }
}

// showarea
void showarea()
{
    int i;
    for(i=1;i<=50;i++)
    {
        cout<<"x="<<S[i].x<<" ";
        cout<<"y="<<S[i].y<<endl;
        cout<<"xx="<<S[i].xx<<" ";
        cout<<"yy="<<S[i].yy<<endl;
        cout<<endl;
    }
}

void click(int x,int y)
{
     searchA(x,y);

}

*/

int crtLine = 0;

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

void DrawNS(node *t) {
 //printf("help\n");
    int S = SPL;
    if (t) {
        if (GetLineType(t->line) == 0) {
            ProcessBlock(startpx, startpy + L, X, Y, L);
            printf("draw basic ------ %s", t->line);
            DrawNS(t->below);
        }
        else if (GetLineType(t->line) == 4) {
            printf("draw while ------- %s", t->line);
            Normal_Loop(startpx, startpy + L, CountConditions(t->left), L, X, Y, S);
            DrawNS(t->below);
        }
        else if (GetLineType(t->line) == 5) {
            printf("draw do/while ------- %s", t->line);
            Reverse_Loop(startpx, startpy + L, CountConditions(t->left), L, X, Y, S);
            DrawNS(t->below);
        }
    }
}

int main()
{   int C1=CT1,C2=CT2,S=SPL;
    initwindow(windowx,windowy);
    FILE *input = fopen("input.txt", "r");
    floodfill(0,0,WHITE);
    menu();
    legenda(L);


    if (!input) {
        printf("Error - input file empty");
        exit(1);
    }

    //saving the code in a 2d array, as tokens
    char line[1023];
    char code[1024][128] = {0};
    while (fgets(line, sizeof(line), input)) {
        if (strcmp(line, "\0") && strcmp(line, "\n")) {
            strcpy(code[k], line);
            k++;
        }
    }

    //checking if the code is correct
    //printf("Checking the code below...\n");
    //getchar();
    //system("clear");
    for (int i = 0; i < k; i++) {
        int var = 0;
        //count the lines for debug
        CountLines(totalLine, codeLine, commentLine, code[k]);

        strcpy(line, code[i]);

        if (strlen(line) == 1) {
            printf("Empty line %d\n", totalLine);
            //IGNORE LINE
        }
        else if (FirstChars(line, "//")) {
            printf("Commented line %d\n", totalLine);
            //IGNORE LINE
        }//check if an int variable is defined
        else if (FirstChars(line, "int ")) {
            printf("Declared int on line %d\n", totalLine);

            //extract the variable name
            char name[16] = {0};
            int i = 4, k = 0;
            while(i < strlen(line)-1) {
                name[k++] = line[i++];
            }

            CreateInteger(1, name);
            //MakeNode(tree, line, "basic");
        }//check if the line is an IF check
        else if (FirstChars(line, "if ")) {
            printf("If check on line %d\n", totalLine);
            //MakeNode(tree, line, "if");
        }
        else if (FirstChars(line, "else")) {
            printf("Else check on line %d\n", totalLine);
            //MakeNode(tree, line, "else");
        }
        else if (FirstChars(line, "{")) {
            printf("Opened accolade on line %d\n", totalLine);
            //MakeNode(tree, line, "openAcc");
        }
        else if (FirstChars(line, "}")) {
            printf("Closed accolade on line %d\n", totalLine);
            //MakeNode(tree, line, "closeAcc");
        }
        else if (FirstChars(line, "fopen ")) {
            printf("Open file on line %d\n", totalLine);
            //MakeNode(tree, line, "basic");
        }
        else if (FirstChars(line, "for ")) {
            printf("For iteration on line %d\n", totalLine);
            //MakeNode(tree, line, "for");
        }
        else if (FirstChars(line, "while ")) {
            printf("While iteration on line %d\n", totalLine);
            //MakeNode(tree, line, "while");
        }
        else if (FirstChars(line, "do")) {
            printf("do/while iteration on line %d\n", totalLine);
        }
        else if (FirstChars(line, "printc ")) {
            printf("Output to console on line %d\n", totalLine);
            //MakeNode(tree, line, "basic");
        }
        else if (FirstChars(line, "printf ")) {
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
            while (line[i++] == ' ' && i < strlen(line)) {} //will end at i+1
            i--;
            while (line[i] != ' ' && i < strlen(line)) {
                name[k++] = line[i++];
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
                while(i < strlen(line)-1) {
                    expression[k++] = line[i++];
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
            if (!FirstChars(line, "//") && !FirstChars(line, "\n")) {
                printf("Error on line %d. Undefined instruction.\n", totalLine);
                exit(1000);
            }
        }
        //printf("\n\n");
    }
    //getchar();
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

    //aici facem o parcurgere left, root



    /*
    if(ismouseclick(WM_LBUTTONDBLCLK))
    {
        getmouseclick(WM_LBUTTONDBLCLK, x, y);
        cout<<"Mouse clicked at"<<endl;
        cout<<"x="<<x<<" "<<"y="<<y;
        //click(x,y);
        //showarea();
    }
    */

    /*
    Testing purposes
    ProcessBlock(startpx+75,startpy+25);
    startpy+=DIMY;
    Normal_Loop(startpx,startpy,2,L);
    startpy*=2;
    ProcessBlock(startpx+75,startpy+25);
    startpy+=DIMY;
    ProcessBlock(startpx+75,startpy+25);
    startpy+=DIMY;
    Reverse_Loop(startpx,startpy,2,L);*/


    //Individual display

    //ProcessBlock(startpx,startpy,X,Y);
    //Normal_Loop(startpx+L, startpy+L, 3, L, X, Y, S);
    //Normal_Loop(startpx,startpy,2,L,X,Y,S);
    //Reverse_Loop(startpx,startpy,2,L,X,Y,S);
    //BranchingBlock(startpx,startpy,X,Y,C1,C2);


    //search in file
    //simple,if,else,while,for,etc.
    //while reading code->display blocks
    //if ( for in for ) modify X and Y ( S AND C1,C2 if necesarry), startpx,startpy
    //else return to X=DIMX,Y=DIMY,S=SPL,C1=CT1,C2=CT2
    printf("\n///////////// DRAWING DEBUG ////////////\n\n");
    settextstyle(0, 0, 2);
    DrawNS(treeTop);

    getch();
    closegraph();
    return 0;
}
