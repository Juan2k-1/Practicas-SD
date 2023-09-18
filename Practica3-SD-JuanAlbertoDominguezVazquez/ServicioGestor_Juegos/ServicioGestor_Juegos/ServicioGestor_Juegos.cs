using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace ServicioGestor_Juegos
{
    public class ServicioGestor_Juegos : MarshalByRefObject, IGestorJuegos
    {
        private List<Sudoku> sudokus;

        public ServicioGestor_Juegos()
        {
            this.sudokus = new List<Sudoku>();
        }

        private int buscarSudoku(int pCod)
        {
            Boolean encontrado = false;
            int i = 0;

            while (i < this.sudokus.Count && !encontrado)
            {
                if (this.sudokus[i].getpCod == pCod)
                {
                    encontrado = true;
                }
                else
                {
                    i++;
                }
            }
            if (encontrado)
            {
                return i;
            }
            else
            {
                return -1;
            }
        }

        public string Ayuda(int pCodJuego, int pFila, int pColumna)
        {
            char valor;
            String resultado = " ";
            int pos = 0;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                resultado = " ";
            }
            else
            {
                char v = ObtenerValor(pCodJuego, pFila, pColumna);
                if (v == ' ')
                {
                    valor = '1';
                    while (valor <= '9')
                    {
                        PonerValor(pCodJuego, pFila, pColumna, valor);
                        if (ComprobarValor(pCodJuego, pFila, pColumna, valor) == true)
                        {
                            resultado += valor;
                            resultado += ' ';
                        }
                        valor++;
                    }
                    PonerValor(pCodJuego, pFila, pColumna, ' ');
                    resultado.ToCharArray()[pos++] = '\0';
                }
            }
            return resultado;
        }

        public bool BorrarJuego(int pCodJuego)
        {
            Boolean resultado = false;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                resultado = false;
            }
            else
            {
                this.sudokus[posicion].inicializar(TipoDificultad.VACIO);
                resultado = true;
            }
            return resultado;
        }

        public bool ComprobarValor(int pCodJuego, int pFila, int pColumna, char pValor)
        {
            Boolean resultado = true;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                resultado = false;
            }
            else
            {
                if (this.sudokus[posicion].buscarPorFila(pFila, pValor) != 1 || this.sudokus[posicion].buscarPorColumna(pColumna, pValor) != 1 || this.sudokus[posicion].buscarPorBloque(pFila, pColumna, pValor) != 1)
                {
                    resultado = false;
                }
            }
            return resultado;
        }

        public bool Correcto(int pCodJuego)
        {
            Boolean resultado = true;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                resultado = false;
            }
            else
            {
                char valor = '1';
                int f, c;
                while (valor <= '9' && resultado)
                {
                    c = 0;
                    while (c < 9 && resultado)
                    {
                        if (this.sudokus[posicion].buscarPorColumna(c, valor) != 1)
                        {
                            resultado = false;
                        }
                        c++;
                    }
                    f = 0;
                    while (f < 9 && resultado)
                    {
                        if (this.sudokus[posicion].buscarPorFila(f, valor) != 1)
                        {
                            resultado = false;
                        }
                        f++;
                    }
                    for (f = 0; f < 9 && resultado; f += 3)
                    {
                        for (c = 0; c < 9 && resultado; c += 3)
                        {
                            if (this.sudokus[posicion].buscarPorBloque(f, c, valor) != 1)
                            {
                                resultado = false;
                            }
                        }
                    }
                    valor++;
                }
            }
            return resultado;
        }

        public string GetSudoku(int pCodJuego)
        {
            String numero = null;
            String pSudo = null;
            Sudoku aux = null;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                pSudo = "** Sudoku Vacío **";
            }
            else
            {
                aux = this.sudokus[posicion];
                pSudo = "Dificultad:";
                switch (aux.getDificultad)
                {
                    case TipoDificultad.MUY_FACIL:
                        {
                            pSudo += " Muy Fácil";
                            break;
                        }
                    case TipoDificultad.FACIL:
                        {
                            pSudo += " Fácil";
                            break;
                        }
                    case TipoDificultad.MEDIA:
                        {
                            pSudo += " Media";
                            break;
                        }
                    case TipoDificultad.DIFICIL:
                        {
                            pSudo += " Difícil";
                            break;
                        }
                    case TipoDificultad.MUY_DIFICIL:
                        {
                            pSudo += " Muy Difícil";
                            break;
                        }
                    default:
                        {
                            pSudo = "** Sudoku vacío **";
                            break;
                        }
                }
            }
            numero = Convert.ToString(NumeroHuecos(pCodJuego));
            pSudo += "\tHuecos: ";
            pSudo += numero;
            pSudo += "\n  123 456 789\n";
            for (int f = 0; f < 9; f++)
            {
                if (f % 3 == 0)
                {
                    pSudo += "+---+---+---+\n";
                }
                numero = Convert.ToString(f + 1);
                pSudo += numero;
                for (int c = 0; c < 9; c++)
                {
                    if (c % 3 == 0)
                    {
                        pSudo += "|";
                    }
                    numero = Convert.ToString(ObtenerValor(pCodJuego, f, c));
                    pSudo += numero;
                }
                pSudo += "|\n";
            }
            pSudo += "+---+---+---+\n";
            return pSudo;
        }

        public int NuevoJuego(TipoDificultad pDifi)
        {
            int f, c;
            char Valor;
            Sudoku sudoku = new Sudoku();
            sudoku.inicializar(pDifi);

            this.sudokus.Add(sudoku);

            Random random = new Random(DateTime.Now.Millisecond);

            char[] valoresActuales = new char[81];
            for (int i = 0; i < 81; i++)
            {
                valoresActuales[i] = ' ';
            }

            int Pos;
            for (char v = '1'; v <= '9'; v++)
            {
                Pos = random.Next(9);
                while (valoresActuales[Pos] != ' ')
                {
                    Pos++;
                    if (Pos == 9)
                    {
                        Pos = 0;
                    }
                }
                valoresActuales[Pos] = v;
                PonerValor(sudoku.getpCod, 0, Pos, v);
            }

            Pos = 9;
            while (Pos < 81)
            {
                f = Pos / 9;
                c = Pos % 9;
                Valor = valoresActuales[Pos] != ' ' ? valoresActuales[Pos] : '0';

                Boolean EsCorrecto = false;
                while (EsCorrecto == false && Valor < '9')
                {
                    Valor++;
                    PonerValor(sudoku.getpCod, f, c, Valor);
                    EsCorrecto = ComprobarValor(sudoku.getpCod, f, c, Valor);
                }
                if (EsCorrecto == true)
                {
                    valoresActuales[Pos] = Valor;
                    Pos++;
                }
                else
                {
                    valoresActuales[Pos] = ' ';
                    PonerValor(sudoku.getpCod, f, c, ' ');
                    Pos--;
                    if (Pos < 0)
                    {
                        break;
                    }
                }
            }

            int NHuecos = 0;
            switch (pDifi)
            {
                case TipoDificultad.MUY_FACIL:
                    {
                        NHuecos = 10;
                        break;
                    }
                case TipoDificultad.FACIL:
                    {
                        NHuecos = 30;
                        break;
                    }
                case TipoDificultad.DIFICIL:
                    {
                        NHuecos = 60;
                        break;
                    }
                case TipoDificultad.MUY_DIFICIL:
                    {
                        NHuecos = 70;
                        break;
                    }
                default:
                    {
                        NHuecos = 40;
                        break;
                    }
            }

            for (int i = 0; i < NHuecos; i++)
            {
                do
                {
                    f = random.Next(9);
                    c = random.Next(9);
                } while (ObtenerValor(sudoku.getpCod, f, c) == ' ');
                PonerValor(sudoku.getpCod, f, c, ' ');
            }
            //Console.WriteLine("Su código es: " + sudoku.getpCod);
            return sudoku.getpCod;
        }

        public int NumeroHuecos(int pCodJuego)
        {
            int cuantos = 0;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                cuantos = 81;
            }
            else
            {
                for (int f = 0; f < 9; f++)
                {
                    for (int c = 0; c < 9; c++)
                    {
                        if (this.sudokus[posicion].getTablero[f, c] == ' ')
                        {
                            cuantos++;
                        }
                    }
                }
            }
            return cuantos;
        }

        public char ObtenerValor(int pCodJuego, int pFila, int pColumna)
        {
            char resultado;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                resultado = ' ';
            }
            else
            {
                resultado = this.sudokus[posicion].getTablero[pFila, pColumna];
            }
            return resultado;
        }

        public bool PonerValor(int pCodJuego, int pFila, int pColumna, char pValor)
        {
            Boolean resultado = false;
            int posicion = buscarSudoku(pCodJuego);
            if (posicion == -1)
            {
                resultado = false;
            }
            else
            {
                this.sudokus[posicion].getTablero[pFila, pColumna] = pValor;
                resultado = true;
            }
            return resultado;
        }

        public float Completo(int Codigo)
        {
            float resultado = 0;
            char valor = ' ';
            int buscar = buscarSudoku(Codigo);
            if (buscar == -1)
            {
                resultado = 0;
            } 
            else
            {
                for (int f = 0; f < 9; f++)
                {
                    for (int c = 0; c < 9; c++)
                    {
                        if (this.sudokus[buscar].getTablero[f, c] != ' ')
                        {
                            valor = ObtenerValor(Codigo, f, c);
                            if (valor == '1')
                            {
                                resultado += 1;
                            }
                            else if (valor == '2')
                            {
                                resultado += 2;
                            }
                            else if (valor == '3')
                            {
                                resultado += 3;
                            }
                            else if (valor == '4')
                            {
                                resultado += 4;
                            }
                            else if (valor == '5')
                            {
                                resultado += 5;
                            }
                            else if (valor == '6')
                            {
                                resultado += 6;
                            }
                            else if (valor == '7')
                            {
                                resultado += 7;
                            }
                            else if (valor == '8')
                            {
                                resultado += 8;
                            }
                            else 
                            {
                                resultado += 9;
                            }
                            //Console.WriteLine(resultado);
                        }
                    }
                }
                resultado = (resultado / 81) * 20;
            }
            return resultado;
        }
    }
}
