#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <clocale>
#include <cstdio>
#include <locale> //Para aceptar los acentos, y letras ñ
#include <string> // para manejar texto
#include <cstring>//para manejar texto y conversiones
#include <windows.h>//api de windows
#include <ctime> // ayudara a implementar aleatoriedad en la generación de números
#include "colors.h" 
//https://github.com/p-ranav/tabulate no fue posble implementar porque es solo para c++ version 11 en adelante
#include <fstream> // para leer y escribir archivos

using namespace std;

//prototipos
void sinMaximVentana(); // no funciona, la idea es que no se pueda modificar el tamaño de la ventana
void alternarLocale(); //habilita y desabilita entre las opciones de escritura español y los caracteres ascii extendidos
void gotoxy(int, int); //para colocar texto y menus en pcoordenadas de pantalla
void cuadrito(int, int, int, int); // genera rectangulos decorativos en patalla
void margen(); //usa el anterior con valores seteados para pantalla
void textoCentro (char *, int); // centra texto en la altura de coordenas de y que se le indique
void titulo(); // mentiene la cabecera del juego aún luego de borrar la pantalla de la consola
void charger(string txt); // barra de carga de adorno
void hiddenCur(); // esconde el cursosr
void showCur(); // muestra el cursor 
void menu(); // menu principal
void rules(); // reglas
int level (); // deberiamos construir un getter, un setter y un menu 




class player {
	private:
		string user;
		int pass;
		int id;
	public:
		int toros;
		int vacas;
		int level;
		int intentos;
		int code;
		
	player(string u = "defaultUser", int p = 0, int i = 0, int t = 0, int v = 0, int l = 1, int in = 0, int c = 0)
        : user(u), pass(p), id(i), toros(t), vacas(v), level(l), intentos(in), code(c) {}
        
    void setUser(const string& u) {
        user = u;
    }

    void setPass(int p) {
        pass = p;
    }

    void setId(int i) {
        id = i;
    }

    void setToros(int t) {
        toros = t;
    }

    void setVacas(int v) {
        vacas = v;
    }

    void setLevel(int l) {
        level = l;
    }

    void setIntentos(int in) {
        intentos = in;
    }

    void setCode(int c) {
        code = c;
    }

    // Getters
    string getUser() const {
        return user;
    }

    int getPass() const {
        return pass;
    }

    int getId() const {
        return id;
    }

    int getToros() const {
        return toros;
    }

    int getVacas() const {
        return vacas;
    }

    int getLevel() const {
        return level;
    }

    int getIntentos() const {
        return intentos;
    }

    int getCode() const {
        return code;
    }
};


int main() {
	void sinMaximVentana();
	system("mode con: cols=100 lines=30");
	system("color 70");
    // Configurar la localización inicial a Spanish
    setlocale(LC_CTYPE, "Spanish_Spain.1252");
    //cout << "Caracteres españoles: ñ, á, é, í, ó, ú\n";
	alternarLocale();
	margen();
	//titulo();cout <<"\n"<< endl;
	//pruebas de logo
    gotoxy(8, 1); printf("VV     VV   AAA    CCCCC    AAA    SSSSS     TTTTTTT  OOOOO  RRRRRR   OOOOO   SSSSS  \n");
    gotoxy(8, 2); printf("VV     VV  AAAAA  CC    C  AAAAA  SS           TTT   OO   OO RR   RR OO   OO SS      \n");
    gotoxy(8, 3); printf(" VV   VV  AA   AA CC      AA   AA  SSSSS       TTT   OO   OO RRRRRR  OO   OO  SSSSS  \n");
    gotoxy(8, 4); printf("  VV VV   AAAAAAA CC    C AAAAAAA      SS      TTT   OO   OO RR  RR  OO   OO      SS \n");
    gotoxy(8, 5);printf("   VVV    AA   AA  CCCCC  AA   AA  SSSSS       TTT    OOOO0  RR   RR  OOOO0   SSSSS\n");                                    
	
	gotoxy(32,8); printf("         32233 13333331 33253         \n");
    gotoxy(32,9);printf("733333331 57 551      155 757133333337\n");
    gotoxy(32,10);printf("6       753632          544327       6\n");
    gotoxy(32,11);printf("51        74  9        9  47        15\n");
    gotoxy(32,12);printf(" 53       5   72      27   5       32 \n");
    gotoxy(32,13);printf("   5577754     0      0     3277155   \n");
    gotoxy(32,14);printf("        31764  6      9  66713        \n");
    gotoxy(32,15);printf("         9 33  9      8  33 9         \n");
    //gotoxy(32;16);printf("          32   9      6   23          \n");
    gotoxy(32,16);printf("           9  6177777716  9           \n");
    gotoxy(32,17);printf("          3411          1153          \n");
    gotoxy(32,18);printf("          6   515    515   6          \n");
    gotoxy(32,19);printf("          57    7    7    75          \n");
    gotoxy(32,20);printf("           3223333333333223           \n");
    gotoxy(32,21);printf("              4333333334               \n");
	
	hiddenCur();
	//charger("GENERANDO NÚMERO...");
	charger("CARGANDO JUEGO...");
	system("pause");
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
	//control horizontal
	for (i= xs; i<= xe; i++){
		gotoxy(i,ys); printf("%c\n", 205);
		gotoxy(i,ye); printf("%c\n", 205);
	}
	//control vertical
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

void margen(){
	cuadrito(1,0,98,28); // recuadro de pantalla
}

void titulo(){
	cuadrito(40,1,60,3); // cuadro del titulo
	textoCentro("VACAS TOROS", 2);
}

//no funcniona como se esperaba
//deberia recibir un argumento para cambiar el texto
void charger(string txt){
	int i;
	char* charArray = new char[txt.length() + 1]; // +1 para el carácter nulo
    strcpy(charArray, txt.c_str());
    
	alternarLocale();
	textoCentro(charArray, 25);
	alternarLocale();
	for(i=4; i<= 95; i++){
		gotoxy(i, 26); printf("%c\n", 176);
	}
	
		for(i=4; i<= 95; i++){
		gotoxy(i, 26); printf("%c\n", 178);
		Sleep(23);
	}
	gotoxy(35,27);system("pause");
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
		textoCentro("*********************",6);
		scanf("%i", &opc);
	}while (opc<1 || opc > 8);

	switch(opc){
		case 1:
			printf("primera opcion");
			rules();
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

void rules(){
	//llamar a lvl y guardar el mismo para poder escribir
	int lvl= 3; //de momento
	alternarLocale();
	cout <<"Generaré un número de "<< lvl<< " cifras\n Tu mision será adivinarlo\n (puedes cambiar esa cantidad en la opción "<< YELLOW BG_BLUE <<"\033[1mLEVEL" << BLACK << "\033[48;2;204;204;204m\033[38;2;12;12;12m)" <<endl;
	//system("color 70");
	system("pause");
}

//int level (int lvl){
	
	//return 8
//}
