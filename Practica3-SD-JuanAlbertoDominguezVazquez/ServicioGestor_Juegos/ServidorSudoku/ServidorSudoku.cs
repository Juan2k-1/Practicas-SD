using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;
using System.Text;
using System.Threading.Tasks;

namespace ServicioGestor_Juegos
{
    class ServidorSudoku
    {
        static void Main(string[] args)
        {
            ChannelServices.RegisterChannel(new TcpChannel(12345), false);
            Console.WriteLine("Registrando el servicio del Sudoku Remoto en modo Singleton...");
            RemotingConfiguration.RegisterWellKnownServiceType(typeof(ServicioGestor_Juegos), "ServicioGestor_Juegos",
            WellKnownObjectMode.Singleton);
            Console.WriteLine("Esperando llamadas Remotas...");
            Console.WriteLine("Pulsa Enter para Salir..");
            Console.ReadLine();
        }
    }
}
