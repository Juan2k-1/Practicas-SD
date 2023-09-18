/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Modelo;

import Modelo.GestorJuegosIntf;
import static Modelo.GestorJuegosIntf.TipoDificultad.VACIO;
import java.rmi.RemoteException;
import java.util.Random;

/**
 *
 * @author juald
 */
public class GestorJuegos_Impl2 implements GestorJuegosIntf {

    private GestorJuegosIntf.TipoDificultad dificultad;
    private char tablero[][];
    private int pCod;
    private int pFil;
    private int pCol;
    private char pVal;

    public GestorJuegos_Impl2() throws RemoteException {
        super();
        inicializar(VACIO);
        codigoAleatorio();
    }

    public void inicializar(GestorJuegosIntf.TipoDificultad pDifi) {
        this.dificultad = pDifi;
        this.tablero = new char[9][9];
        for (int f = 0; f < 9; f++) {
            for (int c = 0; c < 9; c++) {
                this.tablero[f][c] = ' ';
            }
        }
    }

    public void codigoAleatorio() {
        Random random = new Random();
        random.setSeed(System.currentTimeMillis());
        this.pCod = random.nextInt(100000);
    }

    @Override
    public int NuevoJuego(TipoDificultad pDifi) throws RemoteException {
        int f, c;
        char Valor;
        this.inicializar(pDifi);

        Random random = new Random();
        random.setSeed(System.nanoTime());

        char[] valoresActuales = new char[81];
        for (int i = 0; i < 81; i++) {
            valoresActuales[i] = ' ';
        }

        int Pos;
        for (char v = '1'; v <= '9'; v++) {
            Pos = random.nextInt(9);
            while (valoresActuales[Pos] != ' ') {
                Pos++;
                if (Pos == 9) {
                    Pos = 0;
                }
            }
            valoresActuales[Pos] = v;
            PonerValor(getpCod(), 0, Pos, v);
        }

        Pos = 9;
        while (Pos < 81) {
            f = Pos / 9;
            c = Pos % 9;
            Valor = valoresActuales[Pos] != ' ' ? valoresActuales[Pos] : '0';

            boolean EsCorrecto = false;
            while (EsCorrecto == false && Valor < '9') {
                Valor++;
                PonerValor(getpCod(), f, c, Valor);
                EsCorrecto = ComprobarValor(getpCod(), f, c, Valor);
            }
            if (EsCorrecto == true) {
                valoresActuales[Pos] = Valor;
                Pos++;
            } else {
                valoresActuales[Pos] = ' ';
                PonerValor(getpCod(), f, c, ' ');
                Pos--;
                if (Pos < 0) {
                    break;
                }
            }
        }

        int NHuecos = 0;
        switch (pDifi) {
            case MUY_FACIL: {
                NHuecos = 10;
                break;
            }
            case FACIL: {
                NHuecos = 30;
                break;
            }
            case DIFICIL: {
                NHuecos = 60;
                break;
            }
            case MUY_DIFICIL: {
                NHuecos = 70;
                break;
            }
            default: {
                NHuecos = 40;
            }
        }

        for (int i = 0; i < NHuecos; i++) {
            do {
                f = random.nextInt(9);
                c = random.nextInt(9);
            } while (ObtenerValor(getpCod(), f, c) == ' ');
            PonerValor(this.getpCod(), f, c, ' ');
        }

        System.out.println("Su código es: " + getpCod());
        return getpCod();
    }

    @Override
    public boolean BorrarJuego(int pCodJuego) throws RemoteException {
        boolean resultado = false;
        inicializar(VACIO);
        resultado = true;
        return resultado;
    }

    @Override
    public boolean PonerValor(int pCodJuego, int pFila, int pColumna, char pValor) throws RemoteException {
        boolean resultado = false;
        this.getTablero()[pFila][pColumna] = pValor;
        resultado = true;
        return resultado;
    }

    @Override
    public char ObtenerValor(int pCodJuego, int pFila, int pColumna) throws RemoteException {
        char resultado;
        resultado = this.getTablero()[pFila][pColumna];
        return resultado;
    }

    @Override
    public boolean ComprobarValor(int pCodJuego, int pFila, int pColumna, char pValor) throws RemoteException {
        boolean resultado = true;
        if (this.buscarPorFila(pFila, pValor) != 1 || this.buscarPorColumna(pColumna, pValor) != 1 || this.buscarPorBloque(pFila, pColumna, pValor) != 1) {
            resultado = false;
        }
        return resultado;
    }

    @Override
    public int NumeroHuecos(int pCodJuego) throws RemoteException {
        int cuantos = 0;
        for (int f = 0; f < 9; f++) {
            for (int c = 0; c < 9; c++) {
                if (this.getTablero()[f][c] == ' ') {
                    cuantos++;
                }
            }
        }
        return cuantos;
    }

    @Override
    public String Ayuda(int pCodJuego, int pFila, int pColumna) throws RemoteException {
        char valor;
        String resultado = " ";
        int pos = 0;
        char v = ObtenerValor(pCodJuego, pFila, pColumna);
        if (v == ' ') {
            valor = '1';
            while (valor <= '9') {
                PonerValor(pCodJuego, pFila, pColumna, valor);
                if (ComprobarValor(pCodJuego, pFila, pColumna, valor) == true) {
                    //resultado.toCharArray()[pos++] = valor;
                    //resultado.toCharArray()[pos++] = ' ';
                    resultado += valor;
                    resultado += ' ';
                }
                valor++;
            }
            PonerValor(pCodJuego, pFila, pColumna, ' ');
            resultado.toCharArray()[pos++] = '\0';
        }
        return resultado;
    }

    @Override
    public boolean Correcto(int pCodJuego) throws RemoteException {
        boolean resultado = true;
        char valor = '1';
        int f, c;
        while (valor <= '9' && resultado) {
            c = 0;
            while (c < 9 && resultado) {
                if (this.buscarPorColumna(c, valor) != 1) {
                    resultado = false;
                }
                c++;
            }
            f = 0;
            while (f < 9 && resultado) {
                if (this.buscarPorFila(f, valor) != 1) {
                    resultado = false;
                }
                f++;
            }
            for (f = 0; f < 9 && resultado; f += 3) {
                for (c = 0; c < 9 && resultado; c += 3) {
                    if (this.buscarPorBloque(f, c, valor) != 1) {
                        resultado = false;
                    }
                }
            }
            valor++;
        }

        return resultado;
    }

    @Override
    public String GetSudoku(int pCodJuego) throws RemoteException {
        String numero = null;
        String pSudo;

        pSudo = "Dificultad:";
        switch (this.getDificultad()) {
            case MUY_FACIL: {
                pSudo += " Muy Fácil";
                break;
            }
            case FACIL: {
                pSudo += " Fácil";
                break;
            }
            case MEDIA: {
                pSudo += " Media";
                break;
            }
            case DIFICIL: {
                pSudo += " Difícil";
                break;
            }
            case MUY_DIFICIL: {
                pSudo += " Muy Difícil";
                break;
            }
            default: {
                pSudo = "** Sudoku vacío **";
            }
        }
        numero = Integer.toString(NumeroHuecos(pCodJuego));
        pSudo += "\tHuecos: ";
        pSudo += numero;
        pSudo += "\n  123 456 789\n";
        for (int f = 0; f < 9; f++) {
            if (f % 3 == 0) {
                pSudo += "+---+---+---+\n";
            }
            numero = Integer.toString(f + 1);
            pSudo += numero;
            for (int c = 0; c < 9; c++) {
                if (c % 3 == 0) {
                    pSudo += "|";
                }
                numero = Character.toString(ObtenerValor(pCodJuego, f, c));
                pSudo += numero;
            }
            pSudo += "|\n";
        }
        pSudo += "+---+---+---+\n";

        return pSudo;
    }

    public int buscarPorFila(int pFil, char pVal) {
        int cuantos = 0;
        for (int c = 0; c < 9 && cuantos < 2; c++) {
            if (this.tablero[pFil][c] == pVal) {
                cuantos++;
            }
        }
        return cuantos;
    }

    public int buscarPorColumna(int pCol, char pVal) {
        int cuantos = 0;
        for (int f = 0; f < 9 && cuantos < 2; f++) {
            if (this.tablero[f][pCol] == pVal) {
                cuantos++;
            }
        }
        return cuantos;
    }

    public int buscarPorBloque(int pFil, int pCol, char pVal) {
        int minF = (pFil / 3) * 3;
        int minC = (pCol / 3) * 3;
        int maxF = minF + 3;
        int maxC = minC + 3;

        int cuantos = 0;
        for (int f = minF; f < maxF && cuantos < 2; f++) {
            for (int c = minC; c < maxC && cuantos < 2; c++) {
                if (this.tablero[f][c] == pVal) {
                    cuantos++;
                }
            }
        }
        return cuantos;
    }

    public int getpCod() {
        return this.pCod;
    }

    public int getpFil() {
        return pFil;
    }

    public int getpCol() {
        return pCol;
    }

    public char getpVal() {
        return pVal;
    }

    public char[][] getTablero() {
        return tablero;
    }

    public GestorJuegosIntf.TipoDificultad getDificultad() {
        return dificultad;
    }
}
