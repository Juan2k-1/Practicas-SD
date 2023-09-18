using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;
using System.Text;
using System.Threading.Tasks;

namespace ServicioGestor_Juegos
{
    class ClienteSudoku
    {
        public static TipoDificultad menuDificultad()
        {
            TipoDificultad dificultad = TipoDificultad.VACIO;
            int pDifi;

            do
            {
                Console.WriteLine("---- Elija la Dificultad ----");
                Console.WriteLine("1.- Muy Fácil.");
                Console.WriteLine("2.- Fácil.");
                Console.WriteLine("3.- Medio.");
                Console.WriteLine("4.- Difícil.");
                Console.WriteLine("5.- Muy Difícil");
                Console.WriteLine("Elige opción: ");
                int.TryParse(Console.ReadLine(), out pDifi);

                if (pDifi < 1 || pDifi > 5)
                {
                    Console.WriteLine("** Error, elija una dificultad correcta **");
                }

                switch (pDifi)
                {
                    case 1:
                        {
                            dificultad = TipoDificultad.MUY_FACIL;
                            break;
                        }
                    case 2:
                        {
                            dificultad = TipoDificultad.FACIL;
                            break;
                        }
                    case 3:
                        {
                            dificultad = TipoDificultad.MEDIA;
                            break;
                        }
                    case 4:
                        {
                            dificultad = TipoDificultad.DIFICIL;
                            break;
                        }
                    case 5:
                        {
                            dificultad = TipoDificultad.MUY_DIFICIL;
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Opción inválida");
                            break;
                        }
                }
            } while (pDifi < 1 || pDifi > 5);
            return dificultad;
        }

        public static int buscarJuego(List<Sudoku> juegos, int codigo)
        {
            Boolean encontrado = false;
            int i = 0;

            while (i < juegos.Count && !encontrado)
            {
                if (codigo == juegos[i].getpCod)
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

        public static int buscarPorPosicion(List<Sudoku> juegos, int posicion)
        {
            Boolean encontrado = false;
            int posicionActual = 0;

            while (posicionActual < juegos.Count && !encontrado)
            {
                if (posicion == posicionActual)
                {
                    encontrado = true;
                }
                else
                {
                    posicionActual++;
                }
            }
            if (encontrado)
            {
                return juegos[posicionActual].getpCod;
            }
            else
            {
                return -1;
            }
        }

        public static void Menu(ServicioGestor_Juegos gestor)
        {
            List<Sudoku> Juegos = new List<Sudoku>();
            int opcion, opcionGestion, resultado = 0, borrar;
            int codSudoActual = 0;
            String sn;

            do
            {
                Console.Clear();               
                String sudoActual = gestor.GetSudoku(codSudoActual);
                Console.WriteLine(sudoActual);
                Console.WriteLine("---- Servidor de Juegos ----");
                Console.WriteLine("1.- Gestión de juegos.");
                Console.WriteLine("2.- Jugar.");
                Console.WriteLine("0.- Salir.");
                Console.WriteLine("Elige opción: ");
                int.TryParse(Console.ReadLine(), out opcion);

                switch (opcion)
                {
                    case 1:
                        {
                            do
                            {
                                Console.Clear();
                                Console.WriteLine("---- Gestión de juegos ----");
                                Console.WriteLine("1.- Crear Juego.");
                                Console.WriteLine("2.- Borrar Juego.");
                                Console.WriteLine("3.- Seleccionar Juego.");
                                Console.WriteLine("0.- Salir.");
                                Console.WriteLine("Elige opción: ");
                                int.TryParse(Console.ReadLine(), out opcionGestion);

                                switch (opcionGestion)
                                {
                                    case 1:
                                        {
                                            TipoDificultad dificultad = menuDificultad();
                                            codSudoActual = gestor.NuevoJuego(dificultad);
                                            Sudoku sudokuNuevo = new Sudoku(codSudoActual, dificultad);
                                            Juegos.Add(sudokuNuevo);
                                            Console.WriteLine("¡Juego creado con éxito!");
                                            Console.WriteLine("Pulse intro para continuar...");
                                            Console.ReadLine();
                                            break;
                                        }
                                    case 2:
                                        {
                                            Console.Clear();
                                            Console.WriteLine("Posición" + "\t" + "Código" + "\t\t" + "Dificultad");
                                            Console.WriteLine("------------------------------------------");
                                            for (int i = 0; i < Juegos.Count; i++)
                                            {
                                                Console.WriteLine(Juegos.IndexOf(Juegos[i]) + 1 + "\t\t" + Juegos[i].getpCod + "\t\t" + Juegos[i].getDificultad);
                                            }

                                            Console.WriteLine("Indique la posicion del sudoku que desea eliminar: ");
                                            int.TryParse(Console.ReadLine(), out borrar);

                                            resultado = buscarPorPosicion(Juegos, borrar - 1);
                                            if (resultado != -1)
                                            {
                                                Console.WriteLine("Está seguro de borrar el juego: " + borrar + " (s/n)?");
                                                sn = Console.ReadLine();
                                                if (sn.ToUpper().Equals("S"))
                                                {
                                                    gestor.BorrarJuego(resultado);
                                                    Juegos.RemoveAt(borrar - 1);
                                                    Console.WriteLine("¡Juego borrado con éxito!");
                                                    Console.WriteLine("Pulse intro para continuar...");
                                                    Console.ReadLine();
                                                }
                                                else
                                                {
                                                    Console.WriteLine("Volviendo a atrás, no se eliminará ningún juego");
                                                    Console.WriteLine("Pulse intro para continuar...");
                                                    Console.ReadLine();
                                                }
                                            }
                                            else
                                            {
                                                Console.WriteLine("La posición del juego que ha introducido no existe, vuelva a intentarlo");
                                                Console.WriteLine("Pulse intro para continuar...");
                                                Console.ReadLine();
                                            }
                                            break;
                                        }

                                    case 3:
                                        
                                        float media = 0;
                                        Console.Clear();
                                        Console.WriteLine("Posición" + "\t" + "Código" + "\t\t" + "Dificultad" + "\t" + "Completado");
                                        Console.WriteLine("----------------------------------------------------------------------");
                                        for (int i = 0; i < Juegos.Count; i++)
                                        {
                                            Console.WriteLine(Juegos.IndexOf(Juegos[i]) + 1 + "\t\t" + Juegos[i].getpCod + "\t\t" + Juegos[i].getDificultad + "\t\t" + gestor.Completo(Juegos[i].getpCod) + " %");
                                        }
                                        for (int i = 0; i < Juegos.Count; i++)
                                        {
                                            media += gestor.Completo(Juegos[i].getpCod);
                                        }
                                        Console.WriteLine("La media de completitud es: " + media / Juegos.Count + " %");
                                          
                                        Console.WriteLine("Seleccione la posición del sudoku que desea jugar: ");
                                        int.TryParse(Console.ReadLine(), out int pos);
                                        int busquedaAux = buscarPorPosicion(Juegos, pos - 1);
                                        if (busquedaAux == -1)
                                        {
                                            Console.WriteLine("La posición introducida no existe, vuelva a intentarlo");
                                            Console.WriteLine("Pulse intro para continuar...");
                                            Console.ReadLine();
                                        }
                                        else
                                        {
                                            codSudoActual = busquedaAux;
                                            Console.WriteLine("Ha seleccionado jugar al sudoku con código: " + codSudoActual + " a partir de ahora se le mostrará dicho sudoku");
                                            Console.WriteLine("Pulse intro para continuar...");
                                            Console.ReadLine();
                                        }
                                        break;
                                    case 0:
                                        Console.WriteLine("Volviendo al menu principal...");
                                        Console.WriteLine("Pulse intro para continuar...");
                                        Console.ReadLine();
                                        break;
                                    default:
                                        Console.WriteLine("Opcion inválida, inténtelo de nuevo.");
                                        Console.WriteLine("Pulse intro para continuar...");
                                        Console.ReadLine();
                                        break;
                                }
                            } while (opcionGestion != 0);
                            break;
                        }

                    case 2:
                        {
                            Console.Clear();
                            int opcionJugar = 0;
                            int Aviso = 0, f = 0, c = 0;
                            String Ayuda = null;
                            char v = ' ';
                            //resultado = buscarJuego(Juegos, codSudoActual);

                            do
                            {
                                String sudoActual2 = gestor.GetSudoku(codSudoActual);
                                Console.WriteLine(sudoActual2);

                                if (Aviso > 0)
                                {
                                    Console.WriteLine("***");
                                    switch (Aviso)
                                    {
                                        case 1:
                                            Console.WriteLine("La opción " + opcionJugar + " no está en el menú.");
                                            break;
                                        case 2:
                                            Console.WriteLine("La posición F= " + f + " C=" + c + " introducida es incorrecta.");
                                            break;
                                        case 3:
                                            Console.WriteLine("La posición F= " + f + " C=" + c + " está ocupada");
                                            break;
                                        case 4:
                                            Console.WriteLine("El valor " + v + " no se puede poner en la posición F=" + f + " C=" + c);
                                            break;
                                        case 5:
                                            Console.WriteLine("El valor " + v + " es incorrecto para el juego");
                                            break;
                                        case 6:
                                            Console.WriteLine("Los posibles valores en la posición F=" + f + " C=" + c + " son: " + Ayuda);
                                            break;
                                    }
                                    Console.WriteLine("***");
                                    Aviso = 0;
                                }
                                if (gestor.NumeroHuecos(codSudoActual) == 0)
                                {
                                    Console.WriteLine("*** SUDOKU COMPLETO ***");
                                    if (gestor.Correcto(codSudoActual) == false)
                                    {
                                        Console.WriteLine("SUDOKU MAL COMPLETADO, MALA SUERTE");
                                    }
                                    else
                                    {
                                        Console.WriteLine("¡SUDOKU CORRECTO, FELICIDADES!");
                                    }
                                }

                                Console.WriteLine("---- Menú de Juegos ----");
                                Console.WriteLine("1.- Poner Valor.");
                                Console.WriteLine("2.- Borrar Valor.");
                                Console.WriteLine("3.- Ayuda.");
                                Console.WriteLine("0.- Salir.");
                                Console.WriteLine("Elige opción: ");
                                int.TryParse(Console.ReadLine(), out opcionJugar);

                                switch (opcionJugar)
                                {
                                    case 1:
                                        Console.WriteLine("Introduce fila: ");
                                        int.TryParse(Console.ReadLine(), out f);
                                        Console.WriteLine("Introduce columna: ");
                                        int.TryParse(Console.ReadLine(), out c);
                                        Console.WriteLine("Introduce valor: ");
                                        char.TryParse(Console.ReadLine(), out v);

                                        if (v < '1' || v > '9')
                                        {
                                            Aviso = 5;
                                        }
                                        else if (f < 1 || f > 9 || c < 1 || c > 9)
                                        {
                                            Aviso = 2;
                                        }
                                        else if (gestor.ObtenerValor(codSudoActual, f - 1, c - 1) != ' ')
                                        {
                                            Aviso = 3;
                                        }
                                        else
                                        {
                                            gestor.PonerValor(codSudoActual, f - 1, c - 1, v);
                                            if (gestor.ComprobarValor(codSudoActual, f - 1, c - 1, v) == false)
                                            {
                                                Aviso = 4;
                                            }
                                            else
                                            {
                                                Aviso = 0;
                                            }
                                            Console.WriteLine("Valor: " + v + " introducido en fila: " + f + " columna: " + c + " correctamente");
                                        }
                                        break;
                                    case 2:
                                        Console.WriteLine("Introduce fila: ");
                                        int.TryParse(Console.ReadLine(), out f);
                                        Console.WriteLine("Introduce columna: ");
                                        int.TryParse(Console.ReadLine(), out c);

                                        if (f < 1 || f > 9 || c < 1 || c > 9)
                                        {
                                            Aviso = 2;
                                        }
                                        else
                                        {
                                            gestor.PonerValor(codSudoActual, f - 1, c - 1, ' ');
                                            Console.WriteLine("Valor: " + v + " borrado en fila: " + f + " columna: " + c + " correctamente");
                                        }
                                        break;
                                    case 3:
                                        Console.WriteLine("Introduce fila: ");
                                        int.TryParse(Console.ReadLine(), out f);
                                        Console.WriteLine("Introduce columna: ");
                                        int.TryParse(Console.ReadLine(), out c);

                                        if (f < 1 || f > 9 || c < 1 || c > 9 || gestor.ObtenerValor(codSudoActual, f - 1, c - 1) != ' ')
                                        {
                                            Aviso = 2;
                                        }
                                        else
                                        {
                                            Ayuda = gestor.Ayuda(codSudoActual, f - 1, c - 1);
                                            Aviso = 6;
                                        }
                                        break;
                                    case 0:
                                        Console.WriteLine("Volviendo al menu principal...");
                                        break;
                                    default:
                                        Console.WriteLine("Opción inválida, inténtelo de nuevo.");
                                        break;
                                }
                            } while (opcionJugar != 0);
                            break;
                        }
                    case 0:
                        Console.WriteLine("Saliendo del programa...");
                        break;
                    default:
                        Console.WriteLine("Opción inválida, inténtelo de nuevo.");
                        break;
                }
            } while (opcion != 0);
        }
        static void Main(string[] args)
        {
            ChannelServices.RegisterChannel(new TcpChannel(), false);
            ServicioGestor_Juegos gestor = (ServicioGestor_Juegos)Activator.GetObject(typeof(ServicioGestor_Juegos),
            "tcp://localhost:12345/ServicioGestor_Juegos");
            Console.WriteLine("Tengo conexión con el servidor, comenzamos...\n");
            Menu(gestor);
        }
    }
}
