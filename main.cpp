#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <clocale>
#include <cstdio>
#include <locale> //Para aceptar los acentos, y letras ñ
#include <cstring>
#include <windows.h>
#include "colors.h" //
//https://github.com/p-ranav/tabulate no fue posble implementar porque es solo para c++ version 11 en adelante


using namespace std;

//prototipos
void sinMaximVentana();
void alternarLocale();
void gotoxy(int, int);
void cuadrito(int, int, int, int);
void textoCentro (char *, int);
void titulo();
void charger();
void hiddenCur();
void showCur();
void menu();

int main() {
	void sinMaximVentana();
	system("mode con: cols=100 lines=30");
	system("color 70");
    // Configurar la localización inicial a Spanish
    setlocale(LC_CTYPE, "Spanish_Spain.1252");
    //cout << "Caracteres españoles: ñ, á, é, í, ó, ú\n";
	//printf("%c\n", 178);
	alternarLocale();
	titulo();
	cout <<"\n"<< endl;
	//gotoxy(4,27);system("pause");
	hiddenCur();
	charger();
	showCur();
	system("cls");
	titulo();
	menu();
	return 0;
}

// Función que alterna la configuración regional
void alternarLocale() {
    // Obtener la configuración regional actual
    const char* localeActual = setlocale(LC_CTYPE, NULL);

    // Verificar la configuración regional actual y alternar
    if (localeActual && strcmp(localeActual, "Spanish_Spain.1252") == 0) {
        setlocale(LC_CTYPE, "C");
    } else {
        setlocale(LC_CTYPE, "Spanish_Spain.1252");
    }
}

//funcion para controlar las posiciones del texto y del cursor
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void cuadrito(int xs, int ys, int xe, int ye){
	int i;
	
	for (i= xs; i<= xe; i++){
		gotoxy(i,ys); printf("%c\n", 205);
		gotoxy(i,ye); printf("%c\n", 205);
	}
	
	for (i= ys; i<= ye; i++){
		gotoxy(xs,i); printf("%c\n", 186);
		gotoxy(xe,i); printf("%c\n", 186);
	}
	//primera esquina
	gotoxy(xs,ys); printf("%c\n", 201);
	//segunda esquina
	gotoxy(xe,ys); printf("%c\n", 187);
	//tercera esquina
	gotoxy(xe,ye); printf("%c\n", 188);
	//cuarta esquina
	gotoxy(xs,ye); printf("%c\n", 200);
}

void textoCentro (char *texto, int y){
	int longitud = strlen(texto);
	gotoxy(50-(longitud/2), y); printf(texto);
}

void titulo(){
	cuadrito(1,0,98,28); // recuadro de pantalla
	cuadrito(40,1,60,3); // cuadro del titulo
	textoCentro("VACAS TOROS", 2);
}

//no funcniona como se esperaba
void charger(){
	int i;
	alternarLocale();
	textoCentro("GENERANDO NÚMERO...", 24);
	alternarLocale();
	for(i=3; i<= 95; i++){
		gotoxy(i, 25); printf("%c\n", 176);
	}
	
		for(i=3; i<= 95; i++){
		gotoxy(i, 25); printf("%c\n", 178);
		Sleep(23);
	}
	system("pause");
}

//oculta el cursor
void hiddenCur(){
	printf("\e[?25l");
}

//muestra el cursor
void showCur(){
	printf("\e[?25h");
}

void menu (){
	int opc;
	
	do{
		system("cls");
		titulo();
		showCur();
		
		textoCentro("MENU PRINCIPAL",5);
		textoCentro("***********************",6);
		scanf("%i", &opc);
	}while (opc<1 || opc > 8);

	switch(opc){
		case 1:
			printf("primera opcion");
			break;
		case 2:
			printf("segunda opcion");
			break;
		case 3:
			printf("tercera opcion");
			break;
		case 4:
			printf("cuarta opcion");
			break;
		case 5:
			printf("quinta opcion");
			break;
		case 6:
			printf("sexta opcion");
			break;
	}
}

void sinMaximVentana(){
	/*HWND consoleWindow; 
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
*/
}
