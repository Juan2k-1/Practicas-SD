using System;
using System.ServiceModel;

namespace Gestor_Juegos
{
    class ServidorJuegos
    {
        static void Main(string[] args)
        {
            Console.WriteLine("****** Host del servicio Gestor de Juegos de WCF ***************");
            using (ServiceHost host = new ServiceHost(typeof(Gestor_Juegos.ServicioJuegos)))
            {
                host.Open();
                Console.WriteLine("Servidor GestorJuegos funcionando............");
                Console.WriteLine("Pulse intro para continuar...");
                Console.ReadLine();
                host.Close();
            }
        }
    }
}
