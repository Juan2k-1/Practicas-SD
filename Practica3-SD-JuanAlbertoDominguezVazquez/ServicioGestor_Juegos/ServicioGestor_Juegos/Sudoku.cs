using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ServicioGestor_Juegos
{
    [Serializable]
    public class Sudoku 
    {
        private TipoDificultad dificultad;
        private char[,] tablero;
        private int pCod;

        public TipoDificultad getDificultad
        {
            get
            {
                return this.dificultad;
            }
            set
            {
                this.dificultad = value;
            }
        }
     
        public char[,] getTablero
        {
            get
            {
                return this.tablero;
            }
        }
   
        public int getpCod
        {
            get
            {
                return this.pCod;
            }
        }

        public Sudoku()
        {
            inicializar(TipoDificultad.VACIO);
            codigoAleatorio();
        }

        public Sudoku(int pCod, TipoDificultad pDif)
        {
            this.dificultad = pDif;
            this.pCod = pCod;
        }

        public void inicializar(TipoDificultad dificultad)
        {
            this.dificultad = dificultad;
            tablero = new char[9,9];
            for (int f = 0; f < 9; f++)
            {
                for (int c = 0; c < 9; c++)
                {
                    tablero[f, c] = ' ';
                }
            }
        }

        private void codigoAleatorio()
        {
            Random random = new Random(DateTime.Now.Millisecond);
            pCod = random.Next(10000, 99999);
        }

        
        public int buscarPorFila(int pFil, char pVal)
        {
            int cuantos = 0;
            for (int c = 0; c < 9 && cuantos < 2; c++)
            {
                if(this.tablero[pFil,c] == pVal)
                {
                    cuantos++;
                }
            }
            return cuantos;
        }

        public int buscarPorColumna(int pCol, char pVal)
        {
            int cuantos = 0;
            for (int f = 0; f < 9 && cuantos < 2; f++)
            {
                if (this.tablero[f, pCol] == pVal)
                {
                    cuantos++;
                }
            }
            return cuantos;
        }

        public int buscarPorBloque(int pFil, int pCol, char pVal)
        {
            int minF = (pFil / 3) * 3;
            int minC = (pCol / 3) * 3;
            int maxF = minF + 3;
            int maxC = minC + 3;

            int cuantos = 0;
            for (int f = minF; f < maxF && cuantos < 2; f++)
            {
                for (int c = minC; c < maxC && cuantos < 2; c++)
                {
                    if (this.tablero[f, c] == pVal)
                    {
                        cuantos++;
                    }
                }
            }
            return cuantos;
        }
    }
}
