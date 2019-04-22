#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
//#include <random>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int maxcol = 50;
int maxlin = 30;

class P1 {
	public:
	int col=5;
    int lin=5;
    string obj;
    string frastro;
    int score;
    int rastro;
    int passos;
    int jornada;
    boolean direita;
    boolean esquerda;
    boolean acima;
    boolean abaixo;
	};

	class P2 {
	public:
	int col;
    int lin;
    string obj;
    string frastro;
    int score;
    int rastro;
    int passos;
    int jornada;
    boolean direita;
    boolean esquerda;
    boolean acima;
    boolean abaixo;
	};


void gotoXY(int x, int y);
void initSetup();
void loop();
void automove();
void gameover(int col, int lin);

//DECLARA€AO DAS VARIAVEIS GLOBAIS


P1 p1;
P2 p2;
int gateEnterX=5;
int gateEnterY=40;
int gateExitX=5;
int gateExitY=2;
char tecla;
int sleep =0;
int passos=0;
int jornada=0;
string obj;
string frastro;
int col;
int lin;
int  score=0;
bool acima=false;
bool abaixo=false;
bool esquerda = false;
bool direita = true;
bool sair = false;
int vetX[99];
int vetY[99];
int rastro=1;
int maxRastro=90;
int foodXa;
int foodYa;
int foodXb;
int foodYb;
bool food = false;


void addToVet(int x, int y) {
    for(int p = rastro+1; p >= 0; p--) {
        vetX[p+1]=vetX[p];
        vetY[p+1]=vetY[p];
        if(p>3&&vetX[p]==col&&vetY[p]==lin) {
            gameover(vetX[0],vetY[0]);
        }
    }
    vetX[0]=x;
    vetY[0]=y;
}

void figuraRastro(int c, int l, string fig) {
    gotoXY(c,l);
    cout << fig;
}

void drawRastro() {
    for(int p = 1; p < rastro; p++) {
        if(vetX[p]!= 0)
            figuraRastro(vetX[p],vetY[p],frastro);
    }
}

void gameover(int col, int lin) {
    gotoXY(col,lin);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout <<"X";
    for(int p = 1; p < rastro; p++) {
    	 figuraRastro(vetX[p],vetY[p],"x");
    	 Sleep(150);
	//cout <<"X";
	}
    //getch();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    figuraRastro(foodXa,foodYa," ");
    figuraRastro(foodXb,foodYb," ");
    gotoXY(maxcol/2-4,maxlin/2);
    cout<<"GAME OVER";
    gotoXY(maxcol+1,8);
    cout<<"\a";
    cout<<"Jogar novamente? Sim=Y, Nao=N";
    do {
        char r = getch();
        if(r == 'y') {
            system("cls");
            initSetup();
            loop();
        }
        if(r=='n') {
            exit(0);
        }
    } while(1);



}

void moveRight() {
    if(col < maxcol-1) {
        col++;
        direita=true;
        esquerda=false;
        acima=false;
        abaixo=false;		
		addToVet(col,lin);	
		
        
    } else {
        gameover(col,lin);
    }
}

void moveLeft() {
    if(col >1) {
        col--;
        direita=false;
        esquerda=true;
        acima=false;
        abaixo=false;
        addToVet(col,lin);
    } else {
        gameover(col,lin);
    }

}
void moveUp() {
    if(lin > 1) {
        lin--;
        direita=false;
        esquerda=false;
        acima=true;
        abaixo=false;
        addToVet(col,lin);
    } else {
        gameover(col,lin);
    }
}

void moveDown() {
    if(lin < maxlin - 1) {
        lin++;
        direita=false;
        esquerda=false;
        acima=false;
        abaixo=true;
        addToVet(col,lin);
    } else {
        gameover(col,lin);
    }

}

void automove() {
    if(direita)moveRight();
    if(esquerda)moveLeft();
    if(acima)moveUp();
    if(abaixo)moveDown();
}

void figuraHead(int c, int l, string obj) {
    gotoXY(c,l);
    cout << obj;
}

void clear() {
    for(int p = rastro; p < rastro+2; p++) {
        figuraRastro(vetX[p],vetY[p]," ");
    }
}


void bordar(int lin, int col) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    for(int c =0; c<=col; c++) {
        gotoXY(c,0);
        cout << "\xDB";
    }

    for(int l =0; l<=lin; l++) {
        gotoXY(0,l);
        cout << "\xDB";
    }

    for(int c =0; c<=col; c++) {
        gotoXY(c,lin);
        cout << "\xDB";
    }

    for(int l =0; l<=lin; l++) {
        gotoXY(col,l);
        cout << "\xDB";
    }


}

void drawFood() {
    figuraHead(foodXa,foodYa, " ");
    figuraHead(foodXb,foodYb, " ");
    foodXa = rand()%(49) + 1;
    foodYa = rand()%(29) + 1;
    figuraHead(foodXa,foodYa, "$");
    foodXb = rand()%(49) + 1;
    foodYb = rand()%(29) + 1;
    figuraHead(foodXb,foodYb, "#");
    food=true;
    Sleep(sleep*2);
}

void loop() {
    do {
        figuraHead(col,lin,obj);
        drawRastro();
        gotoXY(gateEnterY,gateEnterX);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "+";
		gotoXY(gateExitY,gateExitX);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "X";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		passos++;
		jornada++;
        if(passos > 100){
        rastro--;passos=0;	
		}
		if (rastro<1)gameover(col, lin);
		        if(lin==gateEnterX && col == gateEnterY)
        {
        	lin=gateExitX;
        	col=gateExitY;
        	direita=true;
		}
        if(kbhit()) {
            tecla = getch();
            switch(tecla) {
            case 'd':
                if(!esquerda) {
                    moveRight();
                }			   else {
                    automove();
                }
                break;
            case 'a':
                if(!direita) {
                    moveLeft();
                }			   else {
                    automove();
                }
                break;
            case 'w':
                if(!abaixo) {
                    moveUp();
                }			   else {
                    automove();
                }
                break;
            case 's':
                if(!acima) {
                    moveDown();
                }			   else {
                    automove();
                }
                break;
            case 'p':
                getch();
                break;
            case 'x':
                sair = true;
                break;
            default:
                automove();
                break;
            }
        }
        else
        {
            automove();
        }
        if(food==true) {
            if(col==foodXa && lin==foodYa || col==foodXb && lin==foodYb) {
                if(rastro < maxRastro)   	rastro++;
                if(sleep > 10) sleep--;
                score=score+rastro+(maxcol-passos);
                passos=0;
                food=false;
                cout<<"\a";
            }
        } else {
            drawFood();
        }
        gotoXY(maxcol+1,1);
        cout << "Pontos: " << score<<"\n";
        gotoXY(maxcol+1,2);
        cout << "Calda: " << rastro-1<<"\n";
        gotoXY(maxcol+1,3);
        //cout << "Passos: " << passos<<"\n";
        //gotoXY(maxcol+1,4);
        cout << "Jornada: " << jornada<<"\n";
        gotoXY(maxcol+1,4);
        cout << "Velocidade: " << 100-sleep<<"\n";
        gotoXY(maxcol+1,5);
        cout << "Total score: " << score+rastro+passos+jornada*((100-sleep)) <<"\n";
        gotoXY(maxcol+1,maxlin+1);
        Sleep(sleep);
        clear();
        if(sair)break;
    } while(1);

}
void initSetup() {
    srand((int)time(0));
    col=1;
    lin=1;
    obj="$";
    frastro="o";
    score=0;
    rastro=5;
    passos=0;
    jornada=0;
    sleep=99;
    direita=true;
    esquerda=false;
    acima=false;
    abaixo=false;
    bordar(maxlin,maxcol);
    //figuraHead(p1.col,p1.lin, obj);
    figuraHead(col,lin, obj);
    addToVet(col,lin);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    drawFood();

}

	
int main() {
	//p1.col = 5;
	//cout << p1.col;
	//getch();
    initSetup();
    loop();
    return 0;
}

void gotoXY(int x, int y)
{
    CursorPosition.X = x; // Locates column
    CursorPosition.Y = y; // Locates Row
    SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}
	

