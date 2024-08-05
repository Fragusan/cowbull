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
#include "colors.h" //libreria de github para colorear fondos y textos
//https://github.com/p-ranav/tabulate no fue posble implementar porque es solo para c++ version 11 en adelante
#include <fstream> // para leer y escribir archivos
#include <conio.h> //para usar la función kbhit() que detecta las teclas que se presionan
#include <vector> // para manejar vectores
#include <algorithm> //para utilizar count() y reverse ();
//#include "dnc/JSON.hpp" //para manipular json  https://github.com/joaquinrmi/JSON/tree/master
#include <sstream> // para trabajar con escritura de archivo y conversion/ serializacion
# include <cctype> //poder utilizar uppercase
#include <iomanip> // paqra utilizar setw en la verificacion del tamaño de los numeros generados
#include "Player.h"

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
void menuPrincipal(); // menu principal
void rules(); // reglas
int level (); // deberiamos construir un getter, un setter y un menu 
void parpadeo(const char* txt, int y); // texto que parpadea
void logoText(); // pinta el logo en texto ascii
void dibujoVaquita(); // pinta imagen ascii
void salida();// menu para finalizar el programa
void startGame ();//menu de preinicio de juego
//int generarNum(int lvl); // genera cifras aleatorias sin repetir la cifra
string generarNum(int lvl);
void changeUserName();
void cuadrito(int xs, int ys, int xe, int ye, int esquina1, int esquina2, int esquina3, int esquina4);
int stringToInt(const string& str);
void intento (int id);
int stringToInt(const string& str);
//player findPlayerById(int findId) ;
void looser (int id);
char* stringToChar(string str);
void winner(int id);
string invertirText(const string& txt);
string intToString(int num);
void cartelGanaste();
int asignarId();
bool tieneUser();
void updatePlayer(int updateId, string newUser, string newPass, int newToros,
                  int newVacas, int newLvl, int newIntentos, string newCode);
                  
                  //int updateId, const string &newUser = "", const string &newPass = "", int newToros = -1, int newVacas = -1, int newLvl = -1, int newIntentos = -1, const string &newCode = ""


static bool userIsOld=false; //la intentaremos usar para definir si es la primera vez o no de un jugador 


int main() {
	sinMaximVentana();
	SetConsoleTitle("Jugando VACAS TOROS");
	system("mode con: cols=100 lines=30");
	system("color 70");
    // Configurar la localización inicial a Spanish
    setlocale(LC_CTYPE, "Spanish_Spain.1252");
    //cout << "Caracteres españoles: ñ, á, é, í, ó, ú\n";
	alternarLocale();
	margen();
	//pruebas de logo
    logoText();                                  
	
	dibujoVaquita();
	
	hiddenCur();
	parpadeo("PRESIONA ENTER PARA INICIAR", 24);
	charger("CARGANDO JUEGO...");
	
	showCur();
	system("cls");
	Sleep(150);
	menuPrincipal();
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

//funcion para controlar las posiciones del texto y del cursor con coordenadas
void gotoxy(int x, int y){
	HANDLE hcon;
	hcon= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void cuadrito(int xs, int ys, int xe, int ye){ // genera marcos decorativos
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

void cuadrito(int xs, int ys, int xe, int ye, int esquina1, int esquina2, int esquina3, int esquina4){ //hacer sobrecarga de metodo para cuadro anidado
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
	gotoxy(xs,ys); printf("%c\n", esquina1);
	//segunda esquina
	gotoxy(xe,ys); printf("%c\n", esquina2);
	//tercera esquina
	gotoxy(xe,ye); printf("%c\n", esquina3);
	//cuarta esquina
	gotoxy(xs,ye); printf("%c\n", esquina4);
}

void textoCentro (char *texto, int y){//centra el texto en pantalla a la altura de y que se le indique (usa gotoxy())
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
	Sleep(23);//retardo para apariencia de carga
	}
}

//oculta el cursor
void hiddenCur(){
	printf("\e[?25l");
}

//muestra el cursor
void showCur(){
	printf("\e[?25h");
}

void menuPrincipal (){
	int opc;
	
	do{
		system("cls");
		system("color 70");
		margen();
		titulo();
		showCur();
		
		textoCentro("MENU PRINCIPAL",5);
		textoCentro("*********************",6);
		alternarLocale();
		hiddenCur();
		textoCentro("Usa el teclado númerico para seleccionar una de las opciones", 8);
		gotoxy(20, 10);printf("1. NUEVA PARTIDA");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		gotoxy(20, 11);printf("2. CONTINUAR");//
		gotoxy(20, 12);printf("3. OPCIONES"); // MUSICA, CAMBIAR COLOR, SONIDOS, NIVEL
		gotoxy(20, 13);printf("4. RÉCORDS");
		gotoxy(20, 14);printf("5. AYUDA");
		gotoxy(20, 15);printf("0. SALIR");
		gotoxy(20, 17);printf("OPCIÓN SELECCIONADA: -> ");
		showCur();
		alternarLocale();
		scanf("%i", &opc);
	}while (opc<0 || opc > 5);

	switch(opc){
		case 0:
			salida();
			break;
		case 1:
			charger("CARGANDO NUEVA SESIÓN...");
			alternarLocale();
			startGame();
			break;
		case 2:
			alternarLocale();
			textoCentro("OPCION AÚN NO DISPONIBLE", 18);
			Sleep(600);
			alternarLocale();
			menuPrincipal();
			break;
		case 3:
			alternarLocale();
			textoCentro("OPCION AÚN NO DISPONIBLE", 18);
			Sleep(600);
			alternarLocale();
			menuPrincipal();
			break;
		case 4:
			alternarLocale();
			textoCentro("OPCION AÚN NO DISPONIBLE", 18);
			Sleep(600);
			alternarLocale();
			menuPrincipal();
			break;
		case 5:
			rules();
			break;
		default :
			cout << WINE;
			textoCentro("OPCION INGRESADA NO VÁLIDA", 7);
			cout << BLACK;
			Sleep(600);
			menuPrincipal();
			break;
	}
}

void sinMaximVentana(){//funciona en windows con permisos elevados
	HWND consoleWindow; 
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

}

void rules(){
	int opc;
	int lvl= 3; //de momento, debe poder llmaarlo desde el player seteado

	do{
	system("cls");
	margen();
	titulo();
	textoCentro("MENU AYUDA",5);
	textoCentro("*********************",6);
	// recuadro 9- 19
	cuadrito(18,8,78,19);
	alternarLocale();
	gotoxy(20, 9); cout << "Generaré un número de " << lvl << " cifras, tu mision será adivinarlo" ;//
	gotoxy(20, 10); cout << "(puedes cambiar esa cantidad en la opción " << YELLOW BG_BLUE << "\033[1mLEVEL" << BLACK <<  "\033[48;2;204;204;204m\033[38;2;12;12;12m)";
	gotoxy(20,11); cout << "Tendras intentos ilimitados, por cada uno de ellos te dare" ;
	gotoxy(20,12); cout << "pistas para ayudarte." ;
	gotoxy(20,13); cout << "Si alguno de los números de tu ingreso está presente en el" ;
	gotoxy(20,14); cout << "número secreto, veras " << BG_LYELLOW << "VACA\033[48;2;204;204;204m\033[38;2;12;12;12m junto a la cantidad de cifras"  ;
	gotoxy(20,15); cout << "en pantalla. Si además de estar presente, está en la" ;
	gotoxy(20,16); cout << "posición correcta, veras "<< BG_LGREEN <<"TORO\033[48;2;204;204;204m\033[38;2;12;12;12m. Si no hay aciertos ni de" ;
	gotoxy(20,17); cout << "posición ni de cifra, veras "<< WHITE BG_RED <<"0V0T\033[48;2;204;204;204m\033[38;2;12;12;12m. Ganarás la partida al" ;
	gotoxy(20,18); cout << "obtener tantos "<< BG_LGREEN << "TORO\033[48;2;204;204;204m\033[38;2;12;12;12m como el nivel de dificultad seteado";// 
	textoCentro("Usa el teclado númerico para seleccionar una de las opciones", 21);
		gotoxy(20, 23);printf("1. VOLVER AL MENÚ PRINCIPAL");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		gotoxy(20, 24);printf("0. SALIR");
		showCur();
		gotoxy(20, 26);printf("OPCIÓN SELECCIONADA: -> ");
		alternarLocale();
		scanf("%i", &opc);
		
	}while (opc<0 || opc > 1);
	
	switch(opc){
		case 0:
			salida();
			break;
		case 1:
			menuPrincipal();
			break;
		
	}
		
	system("pause");
}


void parpadeo(const char* txt, int y) {// chat gpt me ayudo
    bool show = true;
    int longitud = strlen(txt);
    char* espacio = new char[longitud + 1]; // +1 para el carácter nulo
    // Rellena el array con espacios y añade el carácter nulo al final
    memset(espacio, ' ', longitud);
    espacio[longitud] = '\0';

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 13) { // solo si se presiona enter
                // Limpia el texto antes de romper el bucle
                textoCentro(espacio, y);
                break;
            }
        }
        if (show) {
            textoCentro(const_cast<char*>(txt), y);
        } else {
            textoCentro(espacio, y);
        }
        show = !show;

        Sleep(500); // retardo
        // Mueve el cursor hacia atrás para sobreescribir el texto
        gotoxy(0, y);
    }
    delete[] espacio; // Libera la memoria 
}

void logoText(){
	gotoxy(8, 1); printf("VV     VV   AAA    CCCCC    AAA    SSSSS     TTTTTTT  OOOOO  RRRRRR   OOOOO   SSSSS  \n");
    gotoxy(8, 2); printf("VV     VV  AAAAA  CC    C  AAAAA  SS           TTT   OO   OO RR   RR OO   OO SS      \n");
    gotoxy(8, 3); printf(" VV   VV  AA   AA CC      AA   AA  SSSSS       TTT   OO   OO RRRRRR  OO   OO  SSSSS  \n");
    gotoxy(8, 4); printf("  VV VV   AAAAAAA CC    C AAAAAAA      SS      TTT   OO   OO RR  RR  OO   OO      SS \n");
    gotoxy(8, 5);printf("   VVV    AA   AA  CCCCC  AA   AA  SSSSS       TTT    OOOO0  RR   RR  OOOO0   SSSSS\n");
}

void cartelGanaste() {//comienzan en 33 en x y ocupan 13-15 en y, usa asci extendidos
    gotoxy(33, 13);
    printf("%c%c%c%c %c%c%c%c %c%c %c %c%c%c%c %c%c%c%c %c%c%c%c%c %c%c%c%c\n", 201, 205,205, 187, 201, 205, 205, 187, 201, 187, 201, 201, 205, 205, 187, 201, 205, 205, 187, 201, 205, 203, 205, 187, 201, 205, 205, 187);
    gotoxy(33, 14);
    printf("%c  %c %c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c   %c   %c%c%c\n", 186, 203, 204, 205, 205, 185, 186, 92, 92, 186, 204, 205, 205, 185, 200, 205, 205, 187, 186, 204, 205, 185);
    gotoxy(33, 15);
    printf("%c%c%c%c %c  %c %c %c%c %c  %c %c%c%c%c   %c   %c%c%c%c\n", 200, 205, 205, 188, 202, 202, 202, 200, 188, 202, 202, 200, 205, 205, 188, 202, 200, 205, 205, 188);
}

void dibujoVaquita(){
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
}

void salida(){
	int opc;
	
	do{
	system("cls");
	system("color 40");
	margen();
    logoText();
    textoCentro("MENU SALIR",8);
	textoCentro("*********************",9);
	cuadrito(22,11,78,16);//13
	alternarLocale();
	textoCentro("ESTÁS A PUNTO DE CERRAR EL JUEGO", 13);
	textoCentro("¿DESEAS SALIR?", 14);
	textoCentro("Usa el teclado númerico para seleccionar una de las opciones", 18);
		gotoxy(20, 20);printf("1. VOLVER AL MENÚ PRINCIPAL");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		gotoxy(20, 21);printf("0. SALIR");
		showCur();
		gotoxy(20, 23);printf("OPCIÓN SELECCIONADA: -> ");
		scanf("%i", &opc);
	}while (opc<0 || opc > 1);
	
	switch(opc){
		case 0:
			cout << "" << WHITE << endl ;
			textoCentro("SU ALMA SE VENDIÓ AL DIABLO DE MANERA SATISFACTORIA", 13);
			//cout << "\033[48;2;204;204;204m\033[38;2;12;12;12m"  ;
			gotoxy(20, 24);
			userIsOld=false;
			Sleep(650);
			exit(0);
			break;
		case 1:
			alternarLocale();
			menuPrincipal();
			break;
	}
	
}

int asignarId(){
	int accID=0;
	
	ifstream archivoLectura("db.json", ios::app);
	if(archivoLectura.is_open()){
		string renglon;
		while (getline(archivoLectura, renglon)){
			accID+=1;
		}
		archivoLectura.close();
	}
	return accID;
}

bool tieneUser(){
	return userIsOld;
}

void updatePlayer(int updateId, string newUser, string newPass, int newToros,
                  int newVacas, int newLvl, int newIntentos, string newCode){
				  

        fstream archivoR("db.json", ios::in | ios::out); // se lo llama en modo lectura y escritura
        string renglon; //line
        streampos posPrev; //prevPos;
                  	
            while (getline(archivoR, renglon)) {
                stringstream ss(renglon);
                string token;//variable de txt para almacenar la info
                  		
                posPrev = archivoR.tellg();
        		posPrev -= renglon.length() + 1; // Ajusta para nueva línea
        				
        		getline(ss, token, ',');
        				
        		int id = stringToInt(token.substr(token.find(":") + 2));
        				
        		if (id == updateId) {
            		userIsOld = true; //mueve la bandera a que si existe un user con ese id
            				
            			getline(ss, token, ','); // lvl
						int lvl = newLvl == -1 ? stringToInt(token.substr(token.find(":") + 2)) : newLvl;

            			getline(ss, token, ','); // code
           				string code = newCode.empty() ? token.substr(token.find(":") + 2) : newCode;

           				getline(ss, token, ','); // toros
            			int toros = newToros == -1 ? stringToInt(token.substr(token.find(":") + 2)) : newToros;

            			getline(ss, token, ','); // vacas
            			int vacas = newVacas == -1 ? stringToInt(token.substr(token.find(":") + 2)) : newVacas;

            			getline(ss, token, ','); // intentos
            			int intentos = newIntentos == -1 ? stringToInt(token.substr(token.find(":") + 2)) : newIntentos;

            			getline(ss, token, ','); // user
            			string user = newUser.empty() ? token.substr(token.find(":") + 2) : newUser;

            			getline(ss, token, ','); // pass
            			string pass = token.substr(token.find(":") + 2); // este no se modifica
            				
            				
        				player usuarioModificado;
			            usuarioModificado.setUser(user);
			            usuarioModificado.setPass(pass);
			            usuarioModificado.setId(id);
			            usuarioModificado.setToros(toros);
			            usuarioModificado.setVacas(vacas);
			            usuarioModificado.setLevel(lvl);
			            usuarioModificado.setIntentos(intentos);
			            usuarioModificado.setCode(code);
				            
			            archivoR.seekp(posPrev);
			            
			            archivoR << "ID: " << usuarioModificado.getId()
			                 << ", lvl : " << usuarioModificado.getLevel()
			                 << ", code : " << usuarioModificado.getCode()
			                 << ", toros: " << usuarioModificado.getToros()
			                 << ", vacas: " << usuarioModificado.getVacas()
			                 << ", intentos : " << usuarioModificado.getIntentos()
			                 << ", user : " << usuarioModificado.getUser()
			                 << ", pass :" << usuarioModificado.getPass() << "\n";
			                 
			            break;
            				
            			}
        				
					  }
					archivoR.close();
}

void startGame (){
	int opc;
	int id= asignarId();
	//replantear con la nueva funcnion que modifica  y la variable estatica (-1 para primera ejecucion)
	
	player p1;// se instancia de manera generica
	
	//se tuvo que realizar está implementacion adiconal porque 
	//cualquiera de los dos codigos si terminaban en 0 no los almacenaba
	
	//para el code del juego
	string code= generarNum(p1.getLevel()); //genera un codigo aleatorio  de 3 cifras
	stringstream codeFormateado;
	codeFormateado << setw(3) << setfill('0') << code;
	string codeString = codeFormateado.str();
	p1.setCode(codeString); //seteado code verificado
	
	//para el pass del usuario (se esta seteando contraseñas sin tener una función de hash lo cual es un error grave de seguridad)
	string pass=generarNum(6);
	stringstream passFormateada;
	passFormateada << setw(6) << setfill('0') << pass;
	string passString = passFormateada.str();
	p1.setPass(invertirText(passString)); //seteado pass verificado que cumpla con la contidad de digitos y le damos vuelta
	
	//el id se asgina de manera ascendente por orden de jugada
	p1.setId(id);
	Sleep(150); //intentando que suelte el archivo en lectura para escritura
	
	//player(string u = "Anonimo", int p = 0, int i = 0, int t = 0, int v = 0, int l = 3, int in = 0, int c = 0)
        //: user(u), pass(p), id(i), toros(t), vacas(v), level(l), intentos(in), code(c)
    //guardamos en archivo con los nuevos valores seteados
	ofstream archivoE("db.json", ios::app);
    if(archivoE.is_open()){
    
    	archivoE << "ID: "<< p1.getId() <<", lvl : 3, code : " << p1.getCode() << ", toros: 0, vacas: 0, intentos : 0, user : " << p1.getUser() << ", pass :" << p1.getPass() << ",\n"; 
		archivoE.close();
		
	}else{
		printf("No se pudo");
	}
    
    Sleep(100);    
	do{
	system("cls");
	alternarLocale();
	margen();
	titulo();
	textoCentro("NUEVA PARTIDA",5);
	textoCentro("*********************",6);
	cout << WINE;
	textoCentro("ADVERTENCIA: LAS OPCIONES EN ROJO DE ESTE MENU PUEDEN FALLAR",7);
	cout << BLACK;
	// recuadro 9- 19
	cuadrito(18,8,78,16);
	alternarLocale();
	gotoxy(20, 9); cout << "Se te asigno el "<<WHITE BG_CYAN "ID N° " << p1.getId() << BG_COW BLACK;//
	// int generarNum(6);
	gotoxy(20, 10); cout << "Tu contraseña será: " << GREEN << p1.getPass() << BLACK;
	gotoxy(20,12); cout << ORANGE; parpadeo("Ingrese su nombre de usuario", 12); cout << BLACK;
	hiddenCur();
	gotoxy(20,12); cout << "Recuerda estas credenciales para poder acceder a las" ;
	gotoxy(20,13); cout << "estadísticas de tu progreso.";
	gotoxy(20,14); cout << "Si no ingresas un nombre de usuario jugaras como '"<< BG_ORANGE << p1.getUser() << BG_COW << "'" ;
	gotoxy(20,15); cout << "¿Estás listo para comenzar en el nivel " << p1.getLevel() <<" ?";
	//gotoxy(20,13); cout << "Si alguno de los números de tu ingreso está presente en el" ;
	
	textoCentro("Usa el teclado númerico para seleccionar una de las opciones", 17);
		gotoxy(20, 19);printf("1. INICIAR PARTIDA");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		cout << WINE;
		gotoxy(20, 20);printf("2. MODIFICAR EL NOMBRE DE USUARIO");
		gotoxy(20, 21);printf("3. MODIFICAR NIVEL");
		gotoxy(20, 22);printf("4. ESTE NO ES MI USUARIO");//
		cout << BLACK;
		gotoxy(20, 23);printf("0. SALIR");
		showCur();
		gotoxy(20, 25);printf("OPCIÓN SELECCIONADA: -> ");
		alternarLocale();
		scanf("%i", &opc);
		
	}while(opc<0 || opc > 4);
	switch(opc){
		case 0:
			alternarLocale();
			salida();
			break;
		case 1:
			intento(id);
			break; 
		case 2:
			changeUserName();
			break;
		case 3:
			cout << WHITE << BG_WINE;
			textoCentro("DISCULPA, OPCION EN CONSTRUCCION",23);
			textoCentro("SE REDIRECCIONARÁ  AL MENU PRINCIPAL", 24);
			cout << BLACK << BG_COW;
			Sleep(1250);
			menuPrincipal ();
			break;
		case 4:
			cout << WHITE << BG_WINE;
			textoCentro("DISCULPA, OPCION EN CONSTRUCCION",23);
			textoCentro("SE REDIRECCIONARÁ  AL MENU PRINCIPAL", 24);
			cout << BLACK << BG_COW;
			Sleep(1250);
			menuPrincipal ();
			break;
		default:
			cout << WHITE << BG_WINE;
			textoCentro("LA OPCIÓN SELECCIONADA FUERA DE RANGO",23);
			cout << BLACK << BG_COW;
			Sleep(1250);
			menuPrincipal ();
			break;
	}
}


string invertirText(const string& txt){
	string alReves=txt;
	int n= alReves.length();
	for( int i=0; i< n/2; i++){
		swap(alReves[i], alReves[n-i-1]);
	}
	return alReves;
}

string generarNum(int lvl){
	srand(static_cast<unsigned int>(time(NULL)));// uso del time para generar una semillita jaja
	vector<int> digitos;
	while (digitos.size()< static_cast<size_t>(lvl)){// se analiza el tamaño del vector comparandolo contra  el lvl que es convertido para poder comparar
		int digito = rand() % 10;
		if(count (digitos.begin(), digitos.end(), digito) == 0){// count se fija cuantas veces aparece, se pone el rango en inicio y fin, 
			digitos.push_back(digito);
		}
	}
	//int numero =0;
	/*for(int digito : digito){
		numero = numero *10 + digito;
	}*/
	/*for (size_t i = 0; i < digitos.size(); ++i) {
    numero = numero * 10 + digitos[i];
}*/
	string numero;
	for (size_t i=0; i< digitos.size();i++){
		numero = numero + to_string(digitos[i]);
	}
	return numero;
}

void changeUserName(){ // revisar el cambio en el constructor
	int opc;
	int IDFind;
	int passFind;
	int IDDB;
	int passDB;
	string user;
	
	do{
	system("cls");

	margen();
	titulo();
	textoCentro("MODIFICAR EL NOMBRE DE USUARIO",5);
	textoCentro("*********************",6);
	// recuadro 9- 19
	cuadrito(18,8,78,11);
	alternarLocale();
	gotoxy(20, 9); cout << "Para modificar tu nick de usuario necesitamos";//
	// int generarNum(6);
	gotoxy(20,10); cout << "que ingreses tu ID y contraseña";
	//gotoxy(20,11); cout << "Recuerda estas credenciales para poder acceder a las" ;
	alternarLocale();
	cuadrito(18,11,78,16, 204,185,188,200);//segundo cuadrito
	alternarLocale();
	gotoxy(20,12); cout << "Ingresá por favor tu ID:" ;
	showCur();
	gotoxy(20,13); cin >> IDFind ;
	hiddenCur();
	gotoxy(20,14); cout << "Ingresá por favor tu contraseña:";
	showCur();
	gotoxy(20,15); cin >> passFind ;
	
	if( !(passFind >= 102345 && passFind <= 987654)){
		gotoxy(20,13); cout << WINE <<"LA CONTRASEÑA DEBE SER DE 6 NÚMEROS";
		gotoxy(20,14); cout << WINE <<"ASI TENÍA 5 CIFRAS, AGREGÁ 0 AL FINAL";
		Sleep(1500);
		alternarLocale();
		cout << BLACK;
		changeUserName();
	}
	//gotoxy(20,13); cout << "Si alguno de los números de tu ingreso está presente en el" ;
	
	gotoxy(19,17);printf("Usa el teclado númerico para seleccionar una de las opciones");
		gotoxy(19, 19);printf("1. CONFIRMAR ID Y CONTRASEÑA");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		gotoxy(19, 20);printf("2. OLVIDE MIS DATOS");
		gotoxy(19, 21);printf("3. VOLVER AL MENU PRINCIPAL");
		gotoxy(19, 22);printf("0. SALIR");
		showCur();
		gotoxy(19, 25);printf("OPCIÓN SELECCIONADA: -> ");
		alternarLocale();
		scanf("%i", &opc);
		
	}while(opc<0 || opc > 3);
	switch(opc){
		case 0:
			salida();
			break;
		case 1:
		cout << WINE ;
		textoCentro("DISCULPA, OPCION EN CONSTRUCCION",23);
		textoCentro("SE REDIRECCIONARA  AL MENU PRINCIPAL", 24);
		cout << BLACK;
		Sleep(1250);
		menuPrincipal ();
		break;
		case 2:
		cout << WINE ;
		textoCentro("DISCULPA, OPCION EN CONSTRUCCION",23);
		textoCentro("SE REDIRECCIONARA  AL MENU PRINCIPAL", 24);
		cout << BLACK;
		Sleep(1250);
		menuPrincipal ();
		break;
		case 3:
			menuPrincipal ();
			break;
	}
}

void intento (int id){
	char opc;
	int intento=0;
	player pp=findPlayerById(id);
	
	do{
	
	system("cls");
	system("color 70");
	margen();
	titulo();
	gotoxy(36,5); cout <<"JUGANDO EN EL NIVEL " << pp.getLevel();
	textoCentro("*********************",6);
	gotoxy(38,7); cout << "USER: " << pp.getUser() << " "<< pp.getCode();
	gotoxy(38,9); cout << pp.getCode();
	// recuadro 9- 19
	cuadrito(18,8,78,11);
	alternarLocale();
	gotoxy(20, 9); cout << "Debes adivinar un N° de " << pp.getLevel() << " cifras.";//
	
	//gotoxy(20,10); cout << "Intentos realizados N° "<< pp.getIntentos() << ( (pp.getVacas() > 1) ? BG_YELLOW : WHITE BG_RED) && pp.getVacas() << " VACAS" << ( (pp.getToros() > 1) ? BG_LGREEN : WHITE BG_RED) && pp.getToros() << " TOROS";
	
	gotoxy(20,10); 
		cout << "Intentos realizados ";
			
			if(pp.getIntentos() <= 5){
				cout << BG_LGREEN;
			} else if (pp.getIntentos() >5 && pp.getIntentos() < 10){
				cout << BG_ORANGE;
			}else{
				cout << BG_WINE;
			}
				cout << "N° " << pp.getIntentos()<< "\t\t" << BG_COW;
			
			if (pp.getVacas() >= 1) {
    			cout << BG_LYELLOW;
			} else {
    			cout << WHITE BG_RED;
			}
				cout << pp.getVacas() << " VACAS " << BLACK BG_COW <<" ";

			if (pp.getToros() > 1) {
    			cout << BG_LGREEN;
			} else {
    			cout << WHITE BG_RED;
			}
				cout << pp.getToros() << " TOROS " << BLACK BG_COW;;
	
	alternarLocale();
	cuadrito(18,11,78,14, 204,185,188,200);//segundo cuadrito
	alternarLocale();
	gotoxy(20,12); cout << "Ingresá un nuevo intento" ;
	showCur();
	
	/*if( !(passFind >= 102345 && passFind <= 987654)){
		gotoxy(20,13); cout << WINE <<"LA CONTRASEÑA DEBE SER DE 6 NÚMEROS";
		Sleep(800);
		alternarLocale();
		cout << BLACK;
		changeUserName();
	}*/
		cout << WINE;
		textoCentro( "EN ESTE MENU LAS OPCIONES SON CON LETRAS",15);
		cout << BLACK;
		gotoxy(19,16);printf("Usa las teclas asignadas para seleccionar las opciones");
		gotoxy(19, 18);printf("T. INGRESAR INTENTO");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		gotoxy(19, 19);printf("L. RENDIRSE (LOOOSER)");
		gotoxy(19, 20);printf("B. VOLVER AL MENU PRINCIPAL");
		gotoxy(19, 21);printf("E. SALIR");
		showCur();
		gotoxy(20, 13);
		alternarLocale();
		//scanf("%i", &opc);
		cin >> opc;
		opc = toupper(opc);
		
		} while (!(isdigit(opc) || isalpha(opc)));
		
		if(isdigit(opc)){
			//lo que pasará con el digito ingresado
			string numIngresado(1, opc);
			
			//convertimos el int a string del codigo asignado
			ostringstream oss;
    		oss << pp.getCode();
    		string codeAdivinar = oss.str();
    		
			if(codeAdivinar == numIngresado){
				//caso de que adivine en el primer acierto
				winner(id);
			}
			if(!(codeAdivinar.length() == numIngresado.length())){

				cout << WINE;
				gotoxy(20, 9); cout << "Debes adivinar un N° de " << pp.getLevel() << " cifras.";
				cout << BLACK;
				Sleep(1500);
				startGame();//llamada recursiva que no me pertmite
			}
			
			}else if(isalpha(opc)){
			opc= toupper(opc);
			switch (opc){
				case 'T':
					winner(id);//algo
					break;
				case 'L':
					looser(id);
					break;
				case 'B':
					menuPrincipal();
					break;
				case 'E':
					salida();
					break;
				default:
					gotoxy(19,15); cout << WINE << "LA LETRA INGRESADA NO ES UNA OPCIÓN VÁLIDA" << BLACK;
					startGame();//intento(id); // llamada recursiva que no me permite
					break;
			}
		}else{
			gotoxy(19,15); cout << WINE << "LA OPCIÓN INGRESADA NO ES VÁLIDA" << BLACK;
			Sleep(1500);
			startGame();//intento(id);
		}
	
}


player findPlayerById(int findId) {
    ifstream file("db.json");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        // Parse ID
        getline(ss, token, ',');
        int id = stringToInt(token.substr(token.find(":") + 1));

        if (id == findId) {
            // Parse remaining fields
            getline(ss, token, ','); // lvl
            int lvl = stringToInt(token.substr(token.find(":") + 1));

            getline(ss, token, ','); // code
            string code = token.substr(token.find(":") + 1);

            getline(ss, token, ','); // toros
            int toros = stringToInt(token.substr(token.find(":") + 1));

            getline(ss, token, ','); // vacas
            int vacas = stringToInt(token.substr(token.find(":") + 1));

            getline(ss, token, ','); // intentos
            int intentos = stringToInt(token.substr(token.find(":") + 1));

            getline(ss, token, ','); // user
            string user = token.substr(token.find(":") + 2); // Remove space

            getline(ss, token, ','); // pass
            string pass = token.substr(token.find(":") + 1);

            return player(user, pass, id, toros, vacas, lvl, intentos, code);
        }
    }

    // Return a default player with all values set to 0 if not found
    return player("Anonimo", "0", 0, 0, 0, 0, 0, "0");
}

int stringToInt(const string& str) {// para conversion gpt ayudo aqui
    /*stringstream ss(str);
    int number;
    ss >> number;
    return number;*/
    return stoi(str); // MODIFICADO POR ACTUALIZACIÓN A C++ V11
}

string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

void looser (int id){
	
	int opc;
	player pp=findPlayerById(id);
	string sUser=pp.getUser();
	char* user= stringToChar(sUser);
	
	do{
	system("cls");
	system("color 40");
	margen();
    logoText();
    textoCentro("MENU RENDIRSE",8);
	textoCentro("*********************",9);
	cuadrito(22,11,78,16);//13
	alternarLocale();
	cout << BG_COW WINE;
	textoCentro(user,12);
	cout << BLACK BG_RED;
	textoCentro(" ESTÁS A PUNTO DE RENDIRTE", 14);
	delete [] user; //liberamos memoria
	//gotoxy(35,13); cout << BG_COW WINE << pp.getUser() << BLACK  BG_RED << " ESTÁS A PUNTO DE RENDIRTE"  ;
	textoCentro("¿NO DESEAS PENSARLO DE NUEVO?", 15);
	textoCentro("Usa el teclado númerico para seleccionar una de las opciones", 18);
		gotoxy(20, 20);printf("1. VOLVER AL MENÚ PRINCIPAL");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
		gotoxy(20, 21);printf("2. RETOMAR EL JUEGO");
		gotoxy(20, 22);printf("0. SALIR");
		showCur();
		gotoxy(20, 24);printf("OPCIÓN SELECCIONADA: -> ");
		scanf("%i", &opc);
	}while (opc<0 || opc > 2);
	
	switch(opc){
		case 0:
			cout << "" << WHITE << endl ;
			textoCentro("QUE RARO ABANDONANDO... ", 13);
			//cout << "\033[48;2;204;204;204m\033[38;2;12;12;12m"  ;
			gotoxy(20, 24);
			userIsOld=false;
			Sleep(700);
			exit(0);
			break;
		case 1:
			alternarLocale();
			menuPrincipal();
			break;
		case 2:
			alternarLocale();
			intento(id);
			break;
	}
}

char* stringToChar(string str){
	char* txt= new char[str.length()+1]; //claramente utilizamnos un constructor para reservar espacio en memoria para un arreglo char de la longitud del texto mas 1 que es donde finaliza
	strcpy(txt, str.c_str());
	return txt; //devuelve un puntero al arreglo de caractteres
}

void winner(int id){//TERMINADO
	int opc;
	player pp=findPlayerById(id);
	int lvl=pp.getLevel();
	string msj1= "JUGANDO EN EL NIVEL ";
	string msj2= msj1 + stringToChar(intToString(lvl));
	string msj3="EL NÚMERO SECRETO ERA: ";
	string msj4= msj3 + stringToChar(pp.getCode());
	
	do{
	system("cls");
	system("color 27");
	margen();
	logoText();
	textoCentro(stringToChar(msj2),8);
	textoCentro("*********************",9);
	cout << "" << BG_LYELLOW BLACK;
	textoCentro(stringToChar(pp.getUser()) ,11);
	cout << "" << BG_GREEN WHITE;
	cartelGanaste();//14-16
	cuadrito(20,10,80,17);
	alternarLocale();
	cout << "" << BG_LYELLOW BLACK;
	textoCentro(stringToChar(msj4),16);
	cout << "" << BG_GREEN WHITE;
	//menu 19
	gotoxy(20, 19); printf("Usa el teclado númerico para seleccionar una de las opciones");
	gotoxy(20, 21);printf("1. JUGAR UNA NUEVA PARTIDA");//en menu 1 y 2 deberia tambien dejarme modificar el nivel de dificultad
	gotoxy(20, 22);printf("2. VOLVER AL MENU PRINCIPAL");
	gotoxy(20, 23);printf("0. SALIR");
	showCur();
	gotoxy(20, 25);printf("OPCIÓN SELECCIONADA: -> ");
	scanf("%i", &opc);
	
	}while (opc<0 || opc > 2);
	
	switch(opc){
		case 0:
			alternarLocale();
			salida();
			break;
		case 1:
			alternarLocale();
			intento(id);
			break;
		case 2:
			alternarLocale();
			menuPrincipal();
			break;
		default:
			//24
			cout << WINE;
			textoCentro("LA OPCIÓN SELECCIONADA NO ES VALIDA", 18);
			break;
	}
	
}
