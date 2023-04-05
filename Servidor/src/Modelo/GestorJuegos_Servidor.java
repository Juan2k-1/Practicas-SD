/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Modelo;

import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;
import java.rmi.server.*;
import java.rmi.registry.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author juald
 */
public class GestorJuegos_Servidor {

    public static void main(String[] args) {

        try {
            int puerto = 0;
            Scanner sc = new Scanner(System.in);
            System.out.println("Introduce el nº de puerto para comunicarse: ");
            puerto = sc.nextInt();

            Registry registry = LocateRegistry.createRegistry(puerto);
            GestorJuegos_Impl2 obj = new GestorJuegos_Impl2();

            GestorJuegosIntf stub = (GestorJuegosIntf) UnicastRemoteObject.exportObject(obj, puerto);

            registry = LocateRegistry.getRegistry(puerto);
            registry.bind("GestorJuegos", stub);

            System.out.println("Servidor GestorJuegos esperando peticiones...");
        } catch (RemoteException ex) {
            Logger.getLogger(GestorJuegos_Servidor.class.getName()).log(Level.SEVERE, null, ex);
        } catch (AlreadyBoundException ex) {
            Logger.getLogger(GestorJuegos_Servidor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
