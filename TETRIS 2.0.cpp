#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cwchar>
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
using namespace std;

//VARIABLES GLOBALES
int pantalla[31][32];
bool hayLadrilloEnJuego;
int cargaGravedad;
int cargaPasivaGravedad;
int puntaje;
int velocidad;

//FUNCIONES
string menu();
void puntuaciones();
void gotoxy(int x,int y);
void dibujarCuadro(int x1,int y1,int x2,int y2);
void cargando(int xs,int ys,int xi,int yi);
void dimensionFuente(int largoFuente, int anchoFuente);
void ocultarCursor();
void definirTablero(int a[31][32]);
void mostrarInfo(string nombreJugador);
void hacerLimpieza(int a[31][32], int laFila);
void chequearLineasCompletas(int a[31][32]);
void crearLadrillo(int a[31][32]);
void moverDerecha(int a[31][32]);
void moverIzquierda(int a[31][32]);
void moverAbajo(int a[31][32]);
void rotarPieza(int a[31][32]);
void dibujarPantalla(int a[31][32]);
void reiniciarPantalla(int a[31][32]);
int salir(int x,int y,int x1, int y1);
char gotoxy1 (int xCord, int yCord);

struct estructuraJugador
{      
   string nombre;
   int puntaje;
};   

int main(int argc, char** argv) {
	int y=9;
	int enJuego;
	int i=0;
	estructuraJugador *jugador = new estructuraJugador[10];
	while(enJuego!=1)
	{
		DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MAXIMIZE, MF_BYCOMMAND);
		DrawMenuBar(GetConsoleWindow());
		HWND consoleWindow = GetConsoleWindow();
		dimensionFuente(18, 12);
		SetWindowPos( consoleWindow, 0, 15, 15, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
		system("mode con: cols=80 lines=25");
		jugador[i].nombre=menu();
		
		system("mode con: cols=80 lines=26");
		srand(time(NULL));
		ocultarCursor();
		
		int fin;
		fin=0;
		
	    dimensionFuente(20, 20);
		definirTablero(pantalla);
		hayLadrilloEnJuego=false;
		
		gotoxy(12,1);cout<<"T  E  T  R  I  S"<<endl;
		
		while(fin==0)
		{	
			dibujarPantalla(pantalla);
			mostrarInfo(jugador[i].nombre);
			
			for(int x=10;x<=29;x++)
			{
				if(pantalla[4][x]==2)
				{
					fin++;
				}
			}
			
			if(!hayLadrilloEnJuego)
			{
				crearLadrillo(pantalla);
				hayLadrilloEnJuego=true;
			}
			
			if(kbhit())
			{	
				char tocar=getch();
				if((tocar=='a' || tocar==IZQUIERDA) && hayLadrilloEnJuego)
				{	
					moverIzquierda(pantalla);
					cargaGravedad++;
				}
				if( (tocar=='d' || tocar==DERECHA) && hayLadrilloEnJuego)
				{
					moverDerecha(pantalla);
					cargaGravedad++;
				}
				if( (tocar=='s' || tocar==ABAJO) && hayLadrilloEnJuego)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if( (tocar=='w' || tocar==' ' || tocar==ARRIBA ) && hayLadrilloEnJuego)
				{
					rotarPieza(pantalla);
				}
			}
			else
			{
				Sleep(10);
				cargaPasivaGravedad++;
			}
			
			//Modificamos la velocidad segun el puntaje
			if(puntaje>=0 && puntaje<=299){velocidad=1;
			}
			if(puntaje>=300 && puntaje<=599){velocidad=2;
			}
			if(puntaje>=600 && puntaje<=899){velocidad=3;
			}
			if(puntaje>=900 && puntaje<=1299){velocidad=4;
			}
			if(puntaje>=1300 && puntaje<=1799){velocidad=5;
			}
			if(puntaje>=1800 && puntaje<=2299){velocidad=6;
			}
			if(puntaje>=2300 && puntaje<=2999){velocidad=7;
			}
			
			//Aplicamos las gravedades
			if(velocidad==1)
			{
				if(cargaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==8)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			if(velocidad==2)
			{
				if(cargaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==7)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			if(velocidad==3)
			{
				if(cargaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==6)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			if(velocidad==4)
			{
				if(cargaGravedad==3)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==5)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			if(velocidad==5)
			{
				if(cargaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			if(velocidad==6)
			{
				if(cargaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==3)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			if(velocidad==7)
			{
				if(cargaGravedad==4)
				{
					moverAbajo(pantalla);
					cargaGravedad=0;
					cargaPasivaGravedad=0;
				}
				if(cargaPasivaGravedad==2)
				{
					moverAbajo(pantalla);
					cargaPasivaGravedad=0;
					cargaGravedad=0;
				}
			}
			chequearLineasCompletas(pantalla);
			
			if(fin>=1)
			{
				//GAME OVER
				gotoxy(35,8);cout<<"GAME OVER";
				Sleep(1000);
				jugador[i].puntaje=puntaje;
				reiniciarPantalla(pantalla);
				puntaje=0;
				velocidad=1;
			}
		}
		system("cls");
		dimensionFuente(17,12);
		puntuaciones();
		for (int e=0;e<=9;e++){
			gotoxy(31,y); cout<<jugador[e].nombre<<endl;
			gotoxy(41,y); cout<<jugador[e].puntaje<<endl;
			y=y+1;
		}
		gotoxy(20,21);cout<<"Quiere salir del juego? 1/Si  2/No";
		gotoxy(20,22);cin>>enJuego;
		if (enJuego!=1 && enJuego!=2){
			gotoxy(20,23);cout<<"Respesta no disponible"<<endl;
			gotoxy(20,24);cin>>enJuego;
		}
		y=9;
		i=i+1;
	}
	return 0;
}

char gotoxy1 (int xCord, int yCord){
	HANDLE hCon;
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=xCord;
	dwPos.Y=yCord;
	
	SetConsoleCursorPosition(hCon,dwPos);
}

void dimensionFuente(int largoFuente, int anchoFuente)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = anchoFuente;                   // Width of each character in the font
	cfi.dwFontSize.Y = largoFuente;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ocultarCursor(){
	HANDLE hCon;
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = FALSE;
	
	SetConsoleCursorInfo(hCon, &cci);
}

void definirTablero(int a[31][32])
{
	for(int y=3;y<=24;y++)
	{
		for(int x=9;x<=30;x++)
		{
			if(x==9 || y==3 || x==30 || y==24)
			{
				pantalla[y][x]=9;
			}
		}
	}
}

void mostrarInfo(string nombreJugador)
{
	gotoxy1(35,7);cout<<"JUGADOR: "<<nombreJugador;
	gotoxy1(35,11);cout<<"PUNTAJE: "<<puntaje;
	gotoxy1(35,13);cout<<"Velocidad: "<<velocidad;
	gotoxy1(35,20);cout<<"Controles: ";
	gotoxy1(35,21);cout<<"- W - A - S - D - ESPACIO -";
	gotoxy1(35,22);cout<<"- ^ - < - v - > - flechas -";
}
void hacerLimpieza(int a[31][32], int laFila)
{
	for(int x=10;x<=29;x++)
	{
		a[laFila][x]=0;
	}
	for(int y=laFila;y>=5;y--)
	{
		for(int x=10;x<=29;x++)
		{
			a[y][x]=a[y-1][x];
		}
	}
	
	puntaje=puntaje+100;
}
void chequearLineasCompletas(int a[31][32])
{
	int cantidadCompleta;
	bool limpio;
	limpio=false;
	
	for(int y=24;y>=4;y--)
	{
		cantidadCompleta=0;
		
		for(int x=9;x<=30;x++)
		{
			if(a[y][x]==2)
			{
				cantidadCompleta++;
			}
			
			if(cantidadCompleta==20 && !limpio)
			{
				hacerLimpieza(pantalla, y);
				limpio=true;
			}
		}
	}
}
void crearLadrillo(int a[31][32])
{
	int random;
	random=rand()%3;
	if(random==0)
	{
		//Cuadrado
		pantalla[4][19]=1;
		pantalla[4][20]=1;
		pantalla[5][19]=1;
		pantalla[5][20]=1;
		system("COLOR 02");
	}
	if(random==1)
	{
		//Palo
		pantalla[4][19]=1;
		pantalla[5][19]=1;
		pantalla[6][19]=1;
		pantalla[7][19]=1;
		system("COLOR 03");
	}
	if(random==2)
	{
		//Z
		pantalla[4][19]=1;
		pantalla[4][20]=1;
		pantalla[5][20]=1;
		pantalla[5][21]=1;
		system("COLOR 0C");
	}
}

void moverDerecha(int a[31][32])
{
	bool movio;
	movio=false;
	for(int y=3;y<=24;y++)
	{
		for(int x=9;x<=30;x++)
		{	
			//CUADRADO - HACIA LA DERECHA
			if(a[y][x]==1 && a[y+1][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && !movio && a[y][x+2]==0 && a[y+1][x+2]==0) 
			{
				a[y][x+1]=1;
				a[y][x+2]=1;
				a[y+1][x+1]=1;
				a[y+1][x+2]=1;
				
				a[y][x]=0;
				a[y+1][x]=0;
				movio=true;
			}
			//PALO - HACIA LA DERECHA
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+2][x]==1 && a[y+3][x]==1 && !movio && a[y][x+1]==0 && a[y+1][x+1]==0 && a[y+2][x+1]==0 && a[y+3][x+1]==0) 
			{
				a[y][x+1]=1;
				a[y+1][x+1]=1;
				a[y+2][x+1]=1;
				a[y+3][x+1]=1;
				
				a[y][x]=0;
				a[y+1][x]=0;
				a[y+2][x]=0;
				a[y+3][x]=0;
				movio=true;
			}
			//PALO HORIZONTAL HACIA LA DERECHA
			if(a[y][x]==1 && a[y][x+1]==1 && a[y][x+2]==1 && a[y][x+3]==1 && !movio && a[y][x+4]==0)
			{
				a[y][x+4]=1;
				a[y][x+3]=1;
				a[y][x+2]=1;
				a[y][x+1]=1;
				
				a[y][x]=0;
				movio=true;
			}
			//Z HORIZONTAL HACIA LA DERECHA
			if(a[y][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && a[y+1][x+2]==1 && !movio && a[y][x+2]==0 && a[y+1][x+3]==0)
			{
				a[y][x]=0;
				a[y][x+1]=1;
				a[y][x+2]=1;
				a[y+1][x+1]=0;
				a[y+1][x+2]=1;
				a[y+1][x+3]=1;
				movio=true;
			}
			//ZETA-VERTICAL HACIA LA DERECHA
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+1][x-1]==1 && a[y+2][x-1]==1 && !movio && a[y][x+1]==0 && a[y+1][x+1]==0 && a[y+2][x]==0)
			{
				a[y][x+1]=1;
				a[y+1][x+1]=1;
				a[y+2][x]=1;
				a[y+1][x]=1;
				
				a[y][x]=0;
				a[y+1][x-1]=0;
				a[y+2][x-1]=0;
				movio=true;
			}
		}
	}
}

void moverIzquierda(int a[31][32])
{
	bool movio;
	movio=false;
	for(int y=3;y<=24;y++)
	{
		for(int x=9;x<=30;x++)
		{
			//CUADRADO HACIA LA IZQUIERDA
			if(a[y][x]==1 && a[y+1][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && !movio && a[y][x-1]==0 && a[y+1][x-1]==0)
			{
				a[y][x]=1;
				a[y][x-1]=1;
				a[y+1][x]=1;
				a[y+1][x-1]=1;
				
				a[y][x+1]=0;
				a[y+1][x+1]=0;
				movio=true;
			}
			//PALO HACIA LA IZQUIERDA
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+2][x]==1 && a[y+3][x]==1 && !movio && a[y][x-1]==0 && a[y+1][x-1]==0 && a[y+2][x-1]==0 && a[y+3][x-1]==0) 
			{
				a[y][x-1]=1;
				a[y+1][x-1]=1;
				a[y+2][x-1]=1;
				a[y+3][x-1]=1;
				
				a[y][x]=0;
				a[y+1][x]=0;
				a[y+2][x]=0;
				a[y+3][x]=0;
				movio=true;
			}
			//PALO HORIZONTAL HACIA LA IZQUIERDA
			if(a[y][x]==1 && a[y][x+1]==1 && a[y][x+2]==1 && a[y][x+3]==1 && !movio && a[y][x-1]==0)
			{
				a[y][x-1]=1;
				a[y][x]=1;
				a[y][x+1]=1;
				a[y][x+2]=1;
				
				a[y][x+3]=0;
				movio=true;
			}
			//Z HORIZONTAL HACIA LA IZQUIERDA
			if(a[y][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && a[y+1][x+2]==1 && !movio && a[y][x-1]==0 && a[y+1][x]==0)
			{
				a[y][x-1]=1;
				a[y][x]=1;
				a[y+1][x]=1;
				a[y+1][x+1]=1;
				
				a[y][x+1]=0;
				a[y+1][x+2]=0;
				movio=true;
			}
			//ZETA-VERTICAL HACIA LA IZQUIERDA
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+1][x-1]==1 && a[y+2][x-1]==1 && !movio && a[y][x-1]==0 && a[y+1][x-2]==0 && a[y+2][x-2]==0)
			{
				a[y][x-1]=1;
				a[y+1][x-1]=1;
				a[y+1][x-2]=1;
				a[y+2][x-2]=1;
				
				a[y][x]=0;
				a[y+1][x]=0;
				a[y+2][x-1]=0;
				movio=true;
			}
		}
	}
}

void moverAbajo(int a[31][32])
{
	bool movio;
	movio=false;
	for(int y=3;y<=24;y++)
	{
		for(int x=9;x<=30;x++)
		{
			//Si detecta un cuadrado y no ha movido
			if(a[y][x]==1 && a[y+1][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && !movio)
			{
				//Si en abajo hay un bloque se queda quieto y crea otro bloque nuevo arriba
					if(a[y+2][x]==9 || a[y+2][x+1]==9 || a[y+2][x]==2 || a[y+2][x+1]==2)
					{
						a[y][x]=2;
						a[y+1][x]=2;
						a[y][x+1]=2;
						a[y+1][x+1]=2;
						
						hayLadrilloEnJuego=false;
					}
					else//sino hay un bloque abajo, sigue
					{
						a[y+1][x]=1;
						a[y+1][x+1]=1;
						a[y+2][x]=1;
						a[y+2][x+1]=1;
						
						a[y][x]=0;
						a[y][x+1]=0;
					}
					movio=true;
			}
			//Si encuentra un ladrillo-palo
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+2][x]==1 && a[y+3][x]==1 && !movio) 
			{
				//Si abajo hay un bloque o un limite, lo trunca
				if(a[y+4][x]==9 || a[y+4][x]==2)
				{
					a[y][x]=2;
					a[y+1][x]=2;
					a[y+2][x]=2;
					a[y+3][x]=2;
					hayLadrilloEnJuego=false;	
				}
				else //Sino hay un bloque abajo sigue
				{
					a[y+1][x]=1;
					a[y+2][x]=1;
					a[y+3][x]=1;
					a[y+4][x]=1;
						
					a[y][x]=0;
				}
				movio=true;
			}
			//Si encuentra un palo horizontal
			if(a[y][x]==1 && a[y][x+1]==1 && a[y][x+2]==1 && a[y][x+3]==1 && !movio)
			{
				//Si abajo hay un bloque o un limite, lo trunca
				if(a[y+1][x]==9 || a[y+1][x]==2 || a[y+1][x+1]==9 || a[y+1][x+1]==2 || a[y+1][x+2]==9 || a[y+1][x+2]==2 || a[y+1][x+3]==9 || a[y+1][x+3]==2)
				{
					a[y][x]=2;
					a[y][x+1]=2;
					a[y][x+2]=2;
					a[y][x+3]=2;
					hayLadrilloEnJuego=false;	
				}
				else //Sino hay un bloque abajo sigue
				{
					a[y+1][x]=1;
					a[y+1][x+1]=1;
					a[y+1][x+2]=1;
					a[y+1][x+3]=1;
						
					a[y][x]=0;
					a[y][x+1]=0;
					a[y][x+2]=0;
					a[y][x+3]=0;
				}
				movio=true;
			}
			//Si encuentra una Z horizontal
			if(a[y][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && a[y+1][x+2]==1 && !movio)
			{
				//Si abajo hay un bloque o un limite, lo trunca
				if(a[y+2][x+1]==9 || a[y+2][x+2]==9 || a[y+2][x+1]==2 || a[y+2][x+2]==2 || a[y+1][x]==9 || a[y+1][x]==2)
				{
					a[y][x]=2;
					a[y][x+1]=2;
					a[y+1][x+1]=2;
					a[y+1][x+2]=2;
					hayLadrilloEnJuego=false;	
				}
				else//Si no hay nada, lo baja
				{
					a[y+1][x]=1;
					a[y+1][x+1]=1;
					a[y+2][x+1]=1;
					a[y+2][x+2]=1;
					
					a[y][x]=0;
					a[y][x+1]=0;
					a[y+1][x+2]=0;
					movio=true;
				}
			}
			//Si encuentra una ZETA VERTICAL
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+1][x-1]==1 && a[y+2][x-1]==1 && !movio)
			{
				//Si abajo hay un bloque o un limite, lo trunca
				if(a[y+3][x-1]==9 || a[y+3][x-1]==2 || a[y+2][x]==9 || a[y+2][x]==2)
				{
					a[y][x]=2;
					a[y+1][x]=2;
					a[y+1][x-1]=2;
					a[y+2][x-1]=2;
					hayLadrilloEnJuego=false;					
				}
				else//Si no hay nada abajo, lo baja
				{
					a[y+1][x]=1;
					a[y+2][x]=1;
					a[y+2][x-1]=1;
					a[y+3][x-1]=1;
						
					a[y][x]=0;
					a[y+1][x-1]=0;
					movio=true;
				}
			}
		}
	}
}
void rotarPieza(int a[31][32])
{
	bool roto;
	roto=false;
	for(int y=3;y<=24;y++)
	{
		for(int x=9;x<=30;x++)
		{
			//ROTAR PALO VERTICAL
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+2][x]==1 && a[y+3][x]==1 && !roto && a[y+1][x-1]==0 && a[y+1][x-2]==0 && a[y+1][x+1]==0 && a[y+1][x+2]==0) 
			{
				a[y+1][x+1]=1;
				a[y+1][x-1]=1;
				a[y+1][x+2]=1;
				
				a[y][x]=0;
				a[y+2][x]=0;
				a[y+3][x]=0;
				roto=true;
			}
			//ROTAR PALO HORIZONTAL
			if(a[y][x]==1 && a[y][x+1]==1 && a[y][x+2]==1 && a[y][x+3]==1 && !roto)
			{
				a[y][x]=0;
				a[y][x+2]=0;
				a[y][x+3]=0;
				
				a[y-1][x+1]=1;
				a[y][x+1]=1;
				a[y+1][x+1]=1;
				a[y+2][x+1]=1;
				
				roto=true;
			}
			//ROTAR Z HORIZONTAL
			if(a[y][x]==1 && a[y][x+1]==1 && a[y+1][x+1]==1 && a[y+1][x+2]==1 && !roto)
			{
				a[y][x+1]=1;
				a[y+1][x+1]=1;
				a[y][x+2]=1;
				a[y-1][x+2]=1;
				
				a[y][x]=0;
				a[y+1][x+2]=0;
				roto=true;
			}
			//ROTAR ZETA VERTICAL
			if(a[y][x]==1 && a[y+1][x]==1 && a[y+1][x-1]==1 && a[y+2][x-1]==1 && !roto && a[y+1][x-2]==0)
			{
				a[y+1][x-1]=1;
				a[y+1][x-2]=1;
				a[y+2][x-1]=1;
				a[y+2][x]=1;
				
				a[y][x]=0;
				a[y+1][x]=0;
				roto=true;
			}
		}
	}
}

void dibujarPantalla(int a[31][32])
{
	for(int y=3;y<=24;y++)
	{
		for(int x=9;x<=30;x++)
		{
			if(y==3 && x>=9 && x<=30)
			{
				gotoxy1(x,y);printf("%c",205);
			}
			if(y==24 && x>=9 && x<=30)
			{
				gotoxy1(x,y);printf("%c",205);
			}
			if(x==9 && y>=3 && y<=24)
			{
				gotoxy1(x,y);printf("%c",186);
			}
			if(x==30 && y>=3 && y<=24)
			{
				gotoxy1(x,y);printf("%c",186);
			}
			
			if(a[y][x]==1)
			{
				gotoxy1(x,y);printf("%c",219);
			}
			if(a[y][x]==0)
			{
				gotoxy1(x,y);printf(" ");
			}
			if(a[y][x]==2)
			{
				gotoxy1(x,y);printf("%c",219);
			}
			//Esquinas
			if(y==3 && x==9)
			{
				gotoxy1(x,y);printf("%c",201);
			}
			if(y==3 && x==30)
			{
				gotoxy1(x,y);printf("%c",187);
			}
			if(y==24 && x==9)
			{
				gotoxy1(x,y);printf("%c",200);
			}
			if(y==24 && x==30)
			{
				gotoxy1(x,y);printf("%c",188);
			}
		}
	}
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
 
string menu(){
	int opc;
	string nombre;
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	dibujarCuadro(2,1,76,3);
	dibujarCuadro(0,0,78,24);
	int y;
	int i=0;
	do
	{		
		SetConsoleTextAttribute(hConsole, 1);
		gotoxy(35,2); cout << "TETRIS";
		cout<<"\n\n\n";
		gotoxy(18,6); cout<<"\20 1.JUGAR";
		gotoxy(18,7); cout<<"\21 2.SALIR";
		gotoxy(18,11); cout<<"Opcion: ";
		cin>>opc;
		
	}while(opc!=1 && opc!=2);
	
	if(opc==1)
	{
		gotoxy(18,6); cout<<"Ingrese el nombre del jugador: ";
		gotoxy(18,7); cout<<"                               ";
		gotoxy(18,8); cout<<"                               ";
		gotoxy(18,9); cout<<"                               ";
		gotoxy(18,11); cout<<"                               ";
		gotoxy(18,8);cin>>nombre;
		return nombre;
	}
	system("cls");

switch(opc){
	case 1:
		cargando(2,15,77,15); break;
	case 2:
		salir(20,4,60,15); break; 
	}
}

void puntuaciones()
{	
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	dibujarCuadro(2,1,76,3);
	dibujarCuadro(0,0,78,24);
	SetConsoleTextAttribute(hConsole, 1);
	gotoxy(35,2); cout << "TETRIS";
	gotoxy(28,6); cout<<"TABLA DE PUNTUACIONES";
}

void dibujarCuadro(int x1,int y1,int x2,int y2){                            
	int i;
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hConsole, 13);
	
    for (i=x1;i<x2;i++){
		gotoxy(i,y1); 
		printf("%c",205);
		gotoxy(i,y2); 
		printf("%c",205);
    }

                                                           
    for (i=y1;i<y2;i++){
		gotoxy(x1,i); 
	    printf("%c",186);
		gotoxy(x2,i); 
		printf("%c",186);
	}
	
    gotoxy(x1,y1); 
	printf("%c",201);
    gotoxy(x1,y2); 
	printf("%c",200);
    gotoxy(x2,y1);
	printf("%c",187);
    gotoxy(x2,y2);
    printf("%c",188);

}

void cargando(int xs,int ys,int xi,int yi){
	int i;
	gotoxy(30,11);cout<<"CARGANDO...";
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hConsole, 6);
	for(i=xs;i<xi;i++){
		gotoxy(i,ys); 
		printf("%c",176);	
	}
	
	SetConsoleTextAttribute(hConsole, 1);
	for(i=xs;i<xi;i++){
	    gotoxy(i,ys); 
		printf("%c",219);
		Sleep (35);	
	}
system("cls");
}

int salir(int x,int y,int x1,int y1){
	
	int i,abandonar;
	
	do
	{
		for (i=x;i<x1;i++){
			gotoxy(i,y); 
			printf("%c",205);
			gotoxy(i,y1); 
			printf("%c",205);
    	}

                                                           
    	for (i=y;i<y1;i++){
		gotoxy(x,i); 
	    printf("%c",186);                            
		gotoxy(x1,i);                               
		printf("%c",186);
		}
	
    	gotoxy(x,y); 
		printf("%c",201);
    	gotoxy(x,y1); 
		printf("%c",200);
    	gotoxy(x1,y);
		printf("%c",187);
    	gotoxy(x1,y1);
    	printf("%c",188);
	
		gotoxy(28,6); cout<<"Seguro quieres abandonar?";
		gotoxy(28,9.5); cout<<"SI/1";
		gotoxy(46,9.5); cout<<"NO/2";
		gotoxy(35,12); cout<<"Opcion:";
		cin>>abandonar;
	
		if(abandonar==2){
			system("cls");
			dibujarCuadro(2,1,76,3);
			dibujarCuadro(0,0,78,24);                              
        	menu();
		}
		else if(abandonar==1){
			//system("cls");
			exit(0);
		}
	}while(abandonar!=1 && abandonar!=2);
}

void reiniciarPantalla(int a[31][32])
{
	bool limpio;
	limpio=false;
	for(int y=4;y<=23;y++)
	{
		for(int x=10;x<=29;x++)
		{
			a[y][x]=0;
		}
	}
}
