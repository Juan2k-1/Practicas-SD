#include <iostream>
#include <stdbool.h>

enum TDificultad {VACIO, MUY_FACIL, FACIL, MEDIA, DIFICIL, MUY_DIFICIL};

//Declaración del tipo Cadena
typedef char Cadena[300];

#define cls system("clear")
#define pause system("read -p 'Pulsa return para continuar...  '  a")

//Definición de la clase Sudoku pasada a C

//MÉTODOS PRIVADOS DE LA CLASE

struct RCadena {
	bool Salida; /*TRUE si el campo contenido tiene un sudoku, FALSE si es una cadena vacía*/.
	Cadena Contenido;
};

//Estructura para indicar una Fila, Columna y Valor
struct TFCV {
	int pCod;  //Código del sudoku
	int pFil;  //Fila del tablero
	int pCol;  //Columna del tablero
	char pVal; //Valor que contiene (del 1 al 9 o vacío ‘ ‘)
}

//Estructura para indicar una Fila y una Columna
struct TFC {
	int pCod; //Código del sudoku
	int pFil; //Fila del tablero
	int pCol; //Columna de tablero
}

struct Tablero {
	int Codigo; 	        //Código del juego
	char Tablero[9][9];     //Tablero del juego
	TDificultad Dificultad; //Dificultad
}

//Método que devuelve el número de ocurrencias del carácter pVal en la fila pFil.
//La salida podrá ser 0 = Ninguna ocurrencia, 1=Una ocurrencia, 2=dos o más ocurrencias.
int BuscarPorFila(int pFil, char pVal) {
	int Cuantos = 0;
    	for (int c = 0; c < 9 && Cuantos < 2; c++)
        	if (Tablero.Tablero[pFil][c] == pVal)
            		Cuantos++;
    	return Cuantos;
}

//Método que devuelve el número de ocurrencias del caracter pval, en la columna pCol.
int BuscarPorColumna(int pCol, char pVal) {
	int Cuantos = 0;
    	for (int f = 0; f < 9 && Cuantos < 2; f++)
        	if (Tablero.Tablero[f][pCol] == pVal)
            		Cuantos++;
    	return Cuantos;
}

//Método que devuelve el número de ocurrencias del caracter pval, en bloque del juego que
//contiene la fila pfil y la columna pCol.
int BuscarPorBloque(int pFil, int pCol, char pVal) {
	int minF = (pFil / 3) * 3;
	int minC = (pCol / 3) * 3;
	int maxF = minF + 3;
        int maxC = minC + 3;

        int Cuantos = 0;
        for (int f = minF; f < maxF && Cuantos < 2; f++)
        	for (int c = minC; c < maxC && Cuantos < 2; c++)
            		if (Tablero.Tablero[f][c] == pVal)
                		Cuantos++;
        return Cuantos;
}

//Método que inicializa el atributo Dificultad con pDifi y el Tablero con el carácter ' '
void Inicializar(TDificultad pDifi) {
	Tablero.Dificultad=pDifi;
	for (int f = 0; f < 9; f++)
        	for (int c = 0; c < 9; c++)
            		Tablero.Tablero[f][c] = ' ';
}


//MÉTODOS PÚBLICOS DE LA CLASE

//Método que genera un sudoku aleatorio con una dificultad indicada en pDifi
void Nuevo(TDificultad pDifi) {
    int f, c;
    char Valor;
    Inicializar(pDifi);

    char ValoresActuales[81];
    srand(time(0));

    for (int i = 0; i < 81; i++)
        ValoresActuales[i] = ' ';

    int Pos;
    for (char v = '1'; v <= '9'; v++)
    {
        Pos = rand()%9;
        while (ValoresActuales[Pos] != ' ')
        {
            Pos++;
            if (Pos == 9)
                Pos = 0;
        };
        ValoresActuales[Pos] = v;
        PonerValor(0, Pos, v);
    };

    Pos = 9;
    while (Pos < 81)
    {
        f = Pos / 9;
        c = Pos % 9;
        Valor = ValoresActuales[Pos] != ' ' ? ValoresActuales[Pos] : '0';

        bool EsCorrecto = false;
        while (EsCorrecto == false && Valor < '9')
        {
            Valor++;
            PonerValor(f, c, Valor);
            EsCorrecto = ComprobarValor(f, c, Valor);
        };

        if (EsCorrecto == true)
        {
            ValoresActuales[Pos] = Valor;
            Pos++;
        }
        else
        {
            ValoresActuales[Pos] = ' ';
            PonerValor(f, c, ' ');
            Pos--;
        }
    }

    int NHuecos = 0;
    switch (pDifi)
    {
    case MUY_FACIL:
        NHuecos = 10;
        break;
    case FACIL:
        NHuecos = 30;
        break;
    case DIFICIL:
        NHuecos = 60;
        break;
    case MUY_DIFICIL:
        NHuecos = 70;
        break;
    default:
        NHuecos = 40;
    };

    for (int i = 0; i < NHuecos; i++)
    {
        do
        {
            f = rand()%9;
            c = rand()%9;
        }
        while (ObtenerValor(f, c) == ' ');
        PonerValor(f, c, ' ');
    }

}
}

//Inicializa el objeto con un sudoku vacio
void Borrar() {
	Inicializar(VACIO);
}

//Método que almacena el carácter pVal en la fila pFil y la columna pCol
void PonerValor(int pFil, int pCol, char pVal) {
	Tablero.Tablero[Fila][Columna] = Valor;
}

//Método que devuelve el carácter almacenado en la fila pFil y la columna pCol
char ObtenerValor(int pFil, int pCol) {
	return Tablero.Tablero[Fila][Columna];
}

//Método que devuleve true si solo hay un caracter pVal en la fila pFil,
//en la columna pCol y en el bloque que contiene la fila pFil y la columna pCol.
bool ComprobarValor(int Fila, int Columna, char Valor) {
	bool Salida = true;
    	if (BuscarPorFila(Fila, Valor) != 1 || BuscarPorColumna(Columna, Valor) != 1 || BuscarPorBloque(Fila, Columna, Valor) != 1)
        	Salida = false;
    	return Salida;
}

int NumeroHuecos() {
	int Cuantos = 0;
    	for (int f = 0; f < 9; f++)
        	for (int c = 0; c < 9; c++)
            		if (Tablero.Tablero[f][c] == ' ')
                		Cuantos++;
    	return Cuantos;
}

bool Correcto() {
    bool Salida = true;
    char Valor = '1';
    int f, c;
    while (Valor <= '9' && Salida == true)
    {
        c = 0;
        while (c < 9 && Salida == true)
        {
            if (BuscarPorColumna(c, Valor) != 1)
            {
                Salida = false;
            }
            c++;
        };
        f = 0;
        while (f < 9 && Salida == true)
        {
            if (BuscarPorFila(f, Valor) != 1)
            {
                Salida = false;
            }
            f++;
        };

        for (f = 0; f < 9 && Salida == true; f += 3)
        {
            for (c = 0; c < 9 && Salida == true; c += 3)
            {
                if (BuscarPorBloque(f, c, Valor) != 1)
                {
                    Salida = false;
                }
            }
        }
        Valor++;
    }
    return Salida;
}

void Ayuda(int pFil, int pCol, Cadena pAyu) {
    char Valor;
    int Pos=0;
    strcpy(pAyu,"");
    char v = ObtenerValor(pFil, pCol);
    if (v == ' ')
    {
        Valor = '1';
        while (Valor <= '9')
        {
            PonerValor(pFil, pCol, Valor);
            if (ComprobarValor(pFil, pCol, Valor) == true)
            {
                pAyu[Pos++]=Valor;
                pAyu[Pos++]=' ';
            }
            Valor++;
        }
        PonerValor(pFil, pCol, ' ');
        pAyu[Pos++]='\0';
    }
}

void GetSudoku(Cadena pSudo) {
    Cadena Numero;
    strcpy(pSudo,"Dificultad: ");
    switch (Tablero.Dificultad)
    {
    case MUY_FACIL:
        strcat(pSudo,"Muy Fácil");
        break;
    case FACIL:
        strcat(pSudo,"Fácil");
        break;
    case MEDIA:
        strcat(pSudo,"Media");
        break;
    case DIFICIL:
        strcat(pSudo,"Difícil");
        break;
    case MUY_DIFICIL:
        strcat(pSudo,"Muy Difícil");
        break;
    default:
        strcat(pSudo,"** Sudoku vacío **");
    }

    sprintf(Numero,"%d",NumeroHuecos());
    strcat(pSudo, "\tHuecos: ");
    strcat(pSudo,Numero);
    strcat(pSudo,"\n  123 456 789\n");
    for (int f = 0; f < 9; f++)
    {
        if (f % 3 == 0)
            strcat(pSudo," +---+---+---+\n");

        sprintf(Numero,"%d",f+1);
        strcat(pSudo,Numero);
        for (int c = 0; c < 9; c++)
        {
            if (c % 3 == 0)
                strcat(pSudo,"|");
            sprintf(Numero,"%c",ObtenerValor(f, c));
            strcat(pSudo,Numero);
        };
        strcat(pSudo,"|\n");
    };
    strcat(pSudo," +---+---+---+\n");
}

int MenuPrincipal(bool pInicio)
{
    int valor;

    if (pInicio)
    {
        printf("1.- Juego Nuevo\n");
        printf("2.- -----------\n");
        printf("3.- -----------\n");
        printf("4.- -----------\n");
        printf("5.- -----------\n");
    }
    else
    {
        printf("1.- -----------\n");
        printf("2.- Borrar Juego\n");
        printf("3.- Poner Valor\n");
        printf("4.- Borrar Valor\n");
        printf("5.- Ayuda\n");
    }
    printf("6.- Salir\n");
    printf("Elige Opción: ");
    scanf("%d",valor);

    return valor;
}

TDificultad MenuDificultad()
{
    int valor;
    do
    {
        printf("Eligen la Dificultad:\n");
        printf("Muy Fácil(1) Fácil(2) Medio(3) Difícil(4) Muy Difícil(5)\n");
        printf("Elige Opción: ");
        scanf("%d",valor);
        if (valor<1 || valor>5)
            printf("** Error, elija una dificultad correcta.\n");
    }
    while(valor<1 || valor>5);
    return (Tablero.TDificultad)valor;
}



int main()
{
    int Menu;
    //Sudoku  Juego;
    bool Inicio=true;
    int F,C, Aviso=0;
    char V,sn;
    Cadena SudoActual, Ayuda;

    do
    {
        cls;
        GetSudoku(SudoActual);
        printf("%d\n",SudoActual);
        if (Aviso>0)
        {
            printf("*** \n");
            switch (Aviso)
            {
            case 1:
                printf("La opción: %d no está en el menú.", Menu);
                break;
            case 2:
                printf("La posición F= C= introducida es incorrecta.%d\n", F,C);
                break;
            case 3:
                printf("La posición F= C= está ocupada.%d\n", F, C);
                break;
            case 4:
                printf("El valor: no se puede poner en la posición F= C=%d\n", V,F,C);
                break;
            case 5:
                printf("El valor: es incorrecto para el juego%d\n", V);
                break;
            case 6:
                printf("Los posibles valores en la posición F= C= son: %d\n", F,C,Ayuda);
                break;
            }
            printf(" ***\n");
            Aviso=0;
        }
        if (NumeroHuecos()==0)
        {
            printf("*** SUDOKU COMPLETO\n");
            if (Correcto()==false)
                printf("PERO IN\n");
            printf("CORRECTO ***\n");
        }

        printf("");

        Menu=MenuPrincipal(Inicio);
        switch(Menu)
        {
        case 1:
            if  (Inicio==true)
            {
                cls;
                Nuevo(MenuDificultad());
                Inicio=false;
            }
            else Aviso=1;
            break;
        case 2:
            if (Inicio==false)
            {
                printf("¿ Está seguro de borrar el juego (s/n):\n");
                scanf("%c",sn);
                if (sn=='s' || sn=='S')
                {
                    Borrar();
                    Inicio=true;
                }
            }
            else Aviso=1;
            break;
        case 3:
            if (Inicio==false)
            {
                printf("Introduce Fila, Columna y Valor: ");
                scanf("%c",F,C,V);
                if (V<'1' || V>'9')
                    Aviso=5;
                else if (F<1 || F>9 || C<1 || C>9 )
                    Aviso=2;
                else if (ObtenerValor(F-1,C-1)!=' ')
                    Aviso=3;
                else
                {
                    PonerValor(F-1,C-1,V);
                    if (ComprobarValor(F-1,C-1,V)==false)
                        Aviso=4;
                    else
                        Aviso=0;
                }
            }
            else Aviso=1;
            break;
        case 4:
            if (Inicio==false)
            {
                printf("Introduce Fila, y Columna: ");
                scanf("%c",F,C);
                if (F<1 || F>9 || C<1 || C>9 )
                    Aviso=2;
                else
                    PonerValor(F-1,C-1,' ');
            }
            else Aviso=1;
            break;
        case 5:
            if (Inicio==false)
            {
                printf("Introduce Fila y Columna a obtener ayuda: ");
                scanf("%c",F,C);
                if (F<1 || F>9 || C<1 || C>9 || ObtenerValor(F-1,C-1)!=' ')
                    Aviso=2;
                else
                {
                    Ayuda(F-1,C-1,Ayuda);
                    Aviso=6;
                }
            }
            else Aviso=1;
        case 6:
            break;
        default:
            Aviso=1;
        };

    }
    while (Menu!=6);

    return 0;
}