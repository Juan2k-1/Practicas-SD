#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

//Declaración del tipo enumerado cuyos elementos son los distintos tipos de dificultad
enum TDificultad {VACIO, MUY_FACIL, FACIL, MEDIA, DIFICIL, MUY_DIFICIL};

//Declaración del tipo Cadena
typedef char Cadena[300];


#define cls system("clear")
#define pause system("read -p 'Pulsa return para continuar...  '  a")

class Sudoku
{
    char Tablero[9][9];

    //Cuanto mayor sea la dificultad el sudoku tendrá más casillas vacías.
    TDificultad Dificultad;

    //Método que devuelve el número de ocurrencias del carácter pVal en la fila pFil.
    //La salida podrá ser 0 = Ninguna ocurrencia, 1=Una ocurrencia, 2=dos o más ocurrencias.
    int BuscarPorFila(int pFil, char pVal);

    //Método que devuelve el número de ocurrencias del caracter pval, en la columna pCol.
    int BuscarPorColumna(int pCol, char pVal);

    //Método que devuelve el número de ocurrencias del caracter pval, en bloque del juego que
    //contiene la fila pfil y la columna pCol.
    int BuscarPorBloque(int pFil, int pCol, char pVal);

    //Método que inicializa el atributo Dificultad con pDifi y el Tablero con el carácter ' '
    void Inicializar(TDificultad pDifi);
public:
    //Constructor que inicializa el objeto con un sudoku vacio
    Sudoku();

    //Método que genera un sudoku aleatorio con una dificultad indicada en pDifi
    void Nuevo(TDificultad pDifi);

    //Inicializa el objeto con un sudoku vacio
    void Borrar();

    //Método que almacena el carácter pVal en la fila pFil y la columna pCol
    void PonerValor(int pFil, int pCol, char pVal);

    //Método que devuelve el carácter almacenado en la fila pFil y la columna pCol
    char ObtenerValor(int pFil, int pCol);

    //Método que devuleve true si solo hay un caracter pVal en la fila pFil,
    //en la columna pCol y en el bloque que contiene la fila pFil y la columna pCol.
    bool ComprobarValor(int pFil, int pCol, char pVal);

    int NumeroHuecos();
    bool Correcto();
    void Ayuda(int pFil, int pCol, Cadena pAyu);
    void GetSudoku(Cadena pSudo);
};


int Sudoku::BuscarPorFila(int pFil, char pVal)
{
    int Cuantos = 0;
    for (int c = 0; c < 9 && Cuantos < 2; c++)
        if (Tablero[pFil][c] == pVal)
            Cuantos++;
    return Cuantos;
}

int Sudoku::BuscarPorColumna(int pCol, char pVal)
{
    int Cuantos = 0;
    for (int f = 0; f < 9 && Cuantos < 2; f++)
        if (Tablero[f][pCol] == pVal)
            Cuantos++;
    return Cuantos;
}

int Sudoku::BuscarPorBloque(int pFil, int pCol, char pVal)
{
    int minF = (pFil / 3) * 3;
    int minC = (pCol / 3) * 3;
    int maxF = minF + 3;
    int maxC = minC + 3;

    int Cuantos = 0;
    for (int f = minF; f < maxF && Cuantos < 2; f++)
        for (int c = minC; c < maxC && Cuantos < 2; c++)
            if (Tablero[f][c] == pVal)
                Cuantos++;
    return Cuantos;
}

void Sudoku::Inicializar(TDificultad pDifi)
{
    Dificultad=pDifi;
    for (int f = 0; f < 9; f++)
        for (int c = 0; c < 9; c++)
            Tablero[f][c] = ' ';
}

Sudoku::Sudoku()
{
   Inicializar(VACIO);
}

void Sudoku::Borrar()
{
    Inicializar(VACIO);
}

void Sudoku::Nuevo(TDificultad pDifi)
{
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


void Sudoku::PonerValor(int Fila, int Columna, char Valor)
{
    Tablero[Fila][Columna] = Valor;
}

char Sudoku::ObtenerValor(int Fila, int Columna)
{
    return Tablero[Fila][Columna];
}

bool Sudoku::ComprobarValor(int Fila, int Columna, char Valor)
{
    bool Salida = true;
    if (BuscarPorFila(Fila, Valor) != 1 || BuscarPorColumna(Columna, Valor) != 1 || BuscarPorBloque(Fila, Columna, Valor) != 1)
        Salida = false;
    return Salida;
}


int Sudoku::NumeroHuecos()
{
    int Cuantos = 0;
    for (int f = 0; f < 9; f++)
        for (int c = 0; c < 9; c++)
            if (Tablero[f][c] == ' ')
                Cuantos++;
    return Cuantos;
}



bool Sudoku::Correcto()
{
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

void Sudoku::Ayuda(int pFil, int pCol, Cadena pAyu)
{

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


void Sudoku::GetSudoku(Cadena pSudo)
{
    Cadena Numero;
    strcpy(pSudo,"Dificultad: ");
    switch (Dificultad)
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



//******************************************************************************************

int MenuPrincipal(bool pInicio)
{
    int valor;

    if (pInicio)
    {
        cout<<"1.- Juego Nuevo\n";
        cout<<"2.- -----------\n";
        cout<<"3.- -----------\n";
        cout<<"4.- -----------\n";
        cout<<"5.- -----------\n";
    }
    else
    {
        cout<<"1.- -----------\n";
        cout<<"2.- Borrar Juego\n";
        cout<<"3.- Poner Valor\n";
        cout<<"4.- Borrar Valor\n";
        cout<<"5.- Ayuda\n";
    }
    cout<<"6.- Salir\n";
    cout<<"Elige Opción: ";
    cin>>valor;

    return valor;
}

TDificultad MenuDificultad()
{
    int valor;
    do
    {
        cout<<"Eligen la Dificultad:\n";
        cout<<"Muy Fácil(1) Fácil(2) Medio(3) Difícil(4) Muy Difícil(5)\n";
        cout<<"Elige Opción: ";
        cin>>valor;
        if (valor<1 || valor>5)
            cout <<"** Error, elija una dificultad correcta.\n";
    }
    while(valor<1 || valor>5);
    return (TDificultad)valor;
}


int main()
{
    int Menu;
    Sudoku  Juego;
    bool Inicio=true;
    int F,C, Aviso=0;
    char V,sn;
    Cadena SudoActual, Ayuda;

    do
    {
        cls;
        Juego.GetSudoku(SudoActual);
        cout<<SudoActual;
        if (Aviso>0)
        {
            cout<<"*** ";
            switch (Aviso)
            {
            case 1:
                cout << "La opción "<<Menu<<" no está en el menú.";
                break;
            case 2:
                cout << "La posición F="<<F<<" C="<<C<<" introducida es incorrecta.";
                break;
            case 3:
                cout << "La posición F="<<F<<" C="<<C<<" está ocupada";
                break;
            case 4:
                cout << "El valor '"<<V<<"' no se puede poner en la posición F="<<F<<" C="<<C;
                break;
            case 5:
                cout << "El valor '"<<V<<"' es incorrecto para el juego";
                break;
            case 6:
                cout << "Los posibles valores en la posición F="<<F<<" C="<<C<<" son: "<<Ayuda;
                break;
            }
            cout <<" ***\n";
            Aviso=0;
        }
        if (Juego.NumeroHuecos()==0)
        {
            cout<<"*** SUDOKU COMPLETO ";
            if (Juego.Correcto()==false)
                cout<<"PERO IN";
            cout <<"CORRECTO ***\n";
        }

        cout<<endl;

        Menu=MenuPrincipal(Inicio);
        switch(Menu)
        {
        case 1:
            if  (Inicio==true)
            {
                cls;
                Juego.Nuevo(MenuDificultad());
                Inicio=false;
            }
            else Aviso=1;
            break;
        case 2:
            if (Inicio==false)
            {
                cout<<"¿ Está seguro de borrar el juego (s/n):";
                cin >> sn;
                if (sn=='s' || sn=='S')
                {
                    Juego.Borrar();
                    Inicio=true;
                }
            }
            else Aviso=1;
            break;
        case 3:
            if (Inicio==false)
            {
                cout<<"Introduce Fila, Columna y Valor: ";
                cin>>F>>C>>V;
                if (V<'1' || V>'9')
                    Aviso=5;
                else if (F<1 || F>9 || C<1 || C>9 )
                    Aviso=2;
                else if (Juego.ObtenerValor(F-1,C-1)!=' ')
                    Aviso=3;
                else
                {
                    Juego.PonerValor(F-1,C-1,V);
                    if (Juego.ComprobarValor(F-1,C-1,V)==false)
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
                cout<<"Introduce Fila, y Columna: ";
                cin>>F>>C;
                if (F<1 || F>9 || C<1 || C>9 )
                    Aviso=2;
                else
                    Juego.PonerValor(F-1,C-1,' ');
            }
            else Aviso=1;
            break;
        case 5:
            if (Inicio==false)
            {
                cout<<"Introduce Fila y Columna a obtener ayuda: ";
                cin>>F>>C;
                if (F<1 || F>9 || C<1 || C>9 || Juego.ObtenerValor(F-1,C-1)!=' ')
                    Aviso=2;
                else
                {
                    Juego.Ayuda(F-1,C-1,Ayuda);
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
