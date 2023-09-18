/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Modelo;

import java.net.MalformedURLException;
import java.util.Random;
import java.util.Scanner;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author juald
 */
public class GestorJuegos_Cliente {

    public static GestorJuegosIntf.TipoDificultad menuDificultad() {
        Scanner sc = new Scanner(System.in);
        int pDifi;

        do {
            System.out.println("---- Elija la Dificultad ----");
            System.out.println("1.- Muy Fácil.");
            System.out.println("2.- Fácil.");
            System.out.println("3.- Medio.");
            System.out.println("4.- Difícil.");
            System.out.println("5.- Muy Difícil");
            System.out.println("Elige opción: ");
            pDifi = sc.nextInt();

            if (pDifi < 1 || pDifi > 5) {
                System.out.println("** Error, elija una dificultad correcta **");
            }

            switch (pDifi) {
                case 1: {
                    return GestorJuegosIntf.TipoDificultad.MUY_FACIL;
                }
                case 2: {
                    return GestorJuegosIntf.TipoDificultad.FACIL;
                }
                case 3: {
                    return GestorJuegosIntf.TipoDificultad.MEDIA;
                }
                case 4: {
                    return GestorJuegosIntf.TipoDificultad.DIFICIL;
                }
                case 5: {
                    return GestorJuegosIntf.TipoDificultad.MUY_DIFICIL;
                }
                default: {
                    System.out.println("Opción inválida");
                    return menuDificultad();
                }
            }
        } while (pDifi < 1 || pDifi > 5);
    }

    public static int buscarJuego(ArrayList<GestorJuegos_Impl2> juegos, int codigo) {
        boolean encontrado = false;
        int i = 0;

        while (i < juegos.size() && !encontrado) {
            if (codigo == juegos.get(i).getpCod()) {
                encontrado = true;
            } else {
                i++;
            }
        }
        if (encontrado) {
            return i;
        } else {
            return -1;
        }
    }

    public static void Menu() {
        try {
            Scanner scanner = new Scanner(System.in);
            ArrayList<GestorJuegos_Impl2> Juegos = new ArrayList<>();
            int opcion, resultado = 0, borrar;
            int codSudoActual = 0;
            String sn;

            do {
                System.out.println("---- Servidor de Juegos ----");
                System.out.println("1.- Gestión de juegos.");
                System.out.println("2.- Jugar.");
                System.out.println("0.- Salir.");
                System.out.print("Elige opción: ");
                opcion = scanner.nextInt();

                switch (opcion) {
                    case 1: {
                        int opcionGestion;

                        do {
                            System.out.println("---- Gestión de juegos ----");
                            System.out.println("1.- Crear Juego.");
                            System.out.println("2.- Borrar Juego.");
                            System.out.println("3.- Seleccionar Juego.");
                            System.out.println("0.- Salir.");
                            System.out.print("Elige opción: ");
                            opcionGestion = scanner.nextInt();

                            switch (opcionGestion) {
                                case 1:
                                    GestorJuegosIntf.TipoDificultad dificultad = menuDificultad();
                                    GestorJuegos_Impl2 JuegoActivo = new GestorJuegos_Impl2();
                                    codSudoActual = JuegoActivo.NuevoJuego(dificultad);
                                    Juegos.add(JuegoActivo);
                                    System.out.println("¡Juego creado con éxito!");
                                    int posicion = buscarJuego(Juegos, codSudoActual);
                                    System.out.println("La posicion del sudoku en el array es: " + posicion);
                                    break;
                                case 2:
                                    System.out.println("Posición" + "\t" + "Código" + "\t\t" + "Dificultad");
                                    System.out.println("------------------------------------------");
                                    for (int i = 0; i < Juegos.size(); i++) {
                                        System.out.println(Juegos.indexOf(Juegos.get(i)) + 1 + "\t\t" + Juegos.get(i).getpCod() + "\t\t" + Juegos.get(i).getDificultad());
                                    }

                                    System.out.println("Indique el codigo del sudoku que desea eliminar: ");
                                    borrar = scanner.nextInt();
                                    resultado = buscarJuego(Juegos, borrar);
                                    if (resultado != -1) {
                                        System.out.println("Está seguro de borrar el juego: " + borrar + " (s/n)?");
                                        sn = scanner.next();
                                        if (sn.toUpperCase().equals("S")) {
                                            Juegos.get(resultado).BorrarJuego(borrar);
                                            Juegos.remove(resultado);
                                            System.out.println("¡Juego borrado con éxito!");
                                        } else {
                                            System.out.println("Volviendo a atrás, no se eliminará ningún juego");
                                        }
                                    } else {
                                        System.out.println("El código del juego que ha introducido no existe, vuelva a intentarlo");
                                    }
                                    break;
                                case 3:
                                    System.out.println("Posición" + "\t" + "Código" + "\t\t" + "Dificultad");
                                    System.out.println("------------------------------------------");
                                    for (int i = 0; i < Juegos.size(); i++) {
                                        System.out.println(Juegos.indexOf(Juegos.get(i)) + 1 + "\t\t" + Juegos.get(i).getpCod() + "\t\t" + Juegos.get(i).getDificultad());
                                    }
                                    System.out.println("Seleccione el código del sudoku que desea jugar: ");
                                    int cod = scanner.nextInt();
                                    if (buscarJuego(Juegos, cod) == -1) {
                                        System.out.println("El código introducido no existe, vuelva a intentarlo");
                                    } else {
                                        codSudoActual = cod;
                                        System.out.println("Ha seleccionado jugar al sudoku con código: " + codSudoActual + " a partir de ahora se le mostrará dicho sudoku");
                                    }
                                    break;
                                case 0:
                                    System.out.println("Volviendo al menu principal...");
                                    break;
                                default:
                                    System.out.println("Opcion inválida, inténtelo de nuevo.");
                                    break;
                            }
                        } while (opcionGestion != 0);
                        break;
                    }

                    case 2: {
                        int opcionJugar = 0;
                        int Aviso = 0, f = 0, c = 0;
                        String Ayuda = null;
                        char v = 0;
                        resultado = buscarJuego(Juegos, codSudoActual);
                        if (resultado == -1) {
                            System.out.println("No existe ningún juego creado, por favor cree uno");
                        } else {
                            //String sudoActual = Juego.GetSudoku(codSudoActual);
                            //System.out.println(sudoActual);
                            do {
                                String sudoActual = Juegos.get(resultado).GetSudoku(codSudoActual);
                                System.out.println(sudoActual);

                                if (Aviso > 0) {
                                    System.out.println("***");
                                    switch (Aviso) {
                                        case 1:
                                            System.out.println("La opción " + opcionJugar + " no está en el menú.");
                                            break;
                                        case 2:
                                            System.out.println("La posición F= " + f + " C=" + c + " introducida es incorrecta.");
                                            break;
                                        case 3:
                                            System.out.println("La posición F= " + f + " C=" + c + " está ocupada");
                                            break;
                                        case 4:
                                            System.out.println("El valor " + v + " no se puede poner en la posición F=" + f + " C=" + c);
                                            break;
                                        case 5:
                                            System.out.println("El valor " + v + " es incorrecto para el juego");
                                            break;
                                        case 6:
                                            System.out.println("Los posibles valores en la posición F=" + f + " C=" + c + " son: " + Ayuda);
                                            break;
                                    }
                                    System.out.println("***");
                                    Aviso = 0;
                                }
                                if (Juegos.get(resultado).NumeroHuecos(codSudoActual) == 0) {
                                    System.out.println("*** SUDOKU COMPLETO ***");
                                    if (Juegos.get(resultado).Correcto(codSudoActual) == false) {
                                        System.out.println("SUDOKU MAL COMPLETADO, MALA SUERTE");
                                    } else {
                                        System.out.println("¡SUDOKU CORRECTO, FELICIDADES!");
                                    }
                                }

                                System.out.println("---- Menú de Juegos ----");
                                System.out.println("1.- Poner Valor.");
                                System.out.println("2.- Borrar Valor.");
                                System.out.println("3.- Ayuda.");
                                System.out.println("0.- Salir.");
                                System.out.print("Elige opción: ");
                                opcionJugar = scanner.nextInt();

                                switch (opcionJugar) {
                                    case 1:
                                        System.out.println("Introduce fila: ");
                                        f = scanner.nextInt();
                                        System.out.println("Introduce columna: ");
                                        c = scanner.nextInt();
                                        System.out.println("Introduce valor: ");
                                        v = scanner.next().charAt(0);

                                        if (v < '1' || v > '9') {
                                            Aviso = 5;
                                        } else if (f < 1 || f > 9 || c < 1 || c > 9) {
                                            Aviso = 2;
                                        } else if (Juegos.get(resultado).ObtenerValor(codSudoActual, f - 1, c - 1) != ' ') {
                                            Aviso = 3;
                                        } else {
                                            Juegos.get(resultado).PonerValor(codSudoActual, f - 1, c - 1, v);
                                            if (Juegos.get(resultado).ComprobarValor(codSudoActual, f - 1, c - 1, v) == false) {
                                                Aviso = 4;
                                            } else {
                                                Aviso = 0;
                                            }
                                            System.out.println("Valor: " + v + " introducido en fila: " + f + " columna: " + c + " correctamente");
                                        }
                                        break;
                                    case 2:
                                        System.out.println("Introduce fila: ");
                                        f = scanner.nextInt();
                                        System.out.println("Introduce columna: ");
                                        c = scanner.nextInt();

                                        if (f < 1 || f > 9 || c < 1 || c > 9) {
                                            Aviso = 2;
                                        } else {
                                            Juegos.get(resultado).PonerValor(codSudoActual, f - 1, c - 1, ' ');
                                            System.out.println("Valor: " + v + " borrado en fila: " + f + " columna: " + c + " correctamente");
                                        }
                                        break;
                                    case 3:
                                        System.out.println("Introduce fila: ");
                                        f = scanner.nextInt();
                                        System.out.println("Introduce columna: ");
                                        c = scanner.nextInt();

                                        if (f < 1 || f > 9 || c < 1 || c > 9 || Juegos.get(resultado).ObtenerValor(codSudoActual, f - 1, c - 1) != ' ') {
                                            Aviso = 2;
                                        } else {
                                            Ayuda = Juegos.get(resultado).Ayuda(codSudoActual, f - 1, c - 1);
                                            Aviso = 6;
                                        }
                                        break;
                                    case 0:
                                        System.out.println("Volviendo al menu principal...");
                                        break;
                                    default:
                                        System.out.println("Opción inválida, inténtelo de nuevo.");
                                        break;
                                }
                            } while (opcionJugar != 0);
                        }
                        break;
                    }

                    case 0:
                        System.out.println("Saliendo del programa...");
                        break;
                    default:
                        System.out.println("Opción inválida, inténtelo de nuevo.");
                        break;
                }
            } while (opcion != 0);

            scanner.close();
        } catch (RemoteException ex) {
            Logger.getLogger(GestorJuegos_Cliente.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void main(String[] args) {
        try {
            int puerto = 0;
            String host;
            Scanner Teclado = new Scanner(System.in);
            System.out.println("Introduce el nº de puerto para comunicarse: ");
            puerto = Teclado.nextInt();
            System.out.print("Introduce el nombre del host: ");
            host = Teclado.next();

            //Obtiene el stub del rmiregistry
            Random random = new Random(System.nanoTime());
            GestorJuegosIntf gestorIntfStub = (GestorJuegosIntf) Naming.lookup("rmi://" + host + ":" + puerto + "/GestorJuegos");

            Menu();

        } catch (NotBoundException ex) {
            Logger.getLogger(GestorJuegos_Cliente.class
                    .getName()).log(Level.SEVERE, null, ex);

        } catch (MalformedURLException ex) {
            Logger.getLogger(GestorJuegos_Cliente.class
                    .getName()).log(Level.SEVERE, null, ex);

        } catch (RemoteException ex) {
            Logger.getLogger(GestorJuegos_Cliente.class
                    .getName()).log(Level.SEVERE, null, ex);
        }
    }
}
