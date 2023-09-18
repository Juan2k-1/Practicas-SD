using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ClienteJuegos
{   
    public class Sudoku
    {
        private ServicioJuegos.TipoDificultad dificultad;
        private char[,] tablero;
        private int pCod;

        public ServicioJuegos.TipoDificultad getDificultad
        {
            get
            {
                return this.dificultad;
            }
        }


        private char[,] getTablero
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
            inicializar(ServicioJuegos.TipoDificultad.VACIO);
            codigoAleatorio();
        }

        public Sudoku(int pCod, ServicioJuegos.TipoDificultad pDif)
        {
            this.dificultad = pDif;
            this.pCod = pCod;
        }

        private void inicializar(ServicioJuegos.TipoDificultad dificultad)
        {
            this.dificultad = dificultad;
            tablero = new char[9, 9];
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
    }
}
