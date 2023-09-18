/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _GESTORJUEGOS_H_RPCGEN
#define _GESTORJUEGOS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef char Cadena[300];

enum TDificultad {
	VACIO = 0,
	MUY_FACIL = 1,
	FACIL = 2,
	MEDIA = 3,
	DIFICIL = 4,
	MUY_DIFICIL = 5,
};
typedef enum TDificultad TDificultad;

struct RCadena {
	bool_t Salida;
	Cadena Contenido;
};
typedef struct RCadena RCadena;

struct TFCV {
	int pCod;
	int pFil;
	int pCol;
	char pVal;
};
typedef struct TFCV TFCV;

struct TFC {
	int pCod;
	int pFil;
	int pCol;
};
typedef struct TFC TFC;

#define GESTORJUEGOS 0x30000001
#define GESTORJUEGOS_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define Nuevo 1
extern  int * nuevo_1(TDificultad *, CLIENT *);
extern  int * nuevo_1_svc(TDificultad *, struct svc_req *);
#define Borrar 2
extern  bool_t * borrar_1(int *, CLIENT *);
extern  bool_t * borrar_1_svc(int *, struct svc_req *);
#define PonerValor 3
extern  bool_t * ponervalor_1(TFCV *, CLIENT *);
extern  bool_t * ponervalor_1_svc(TFCV *, struct svc_req *);
#define ObtenerValor 4
extern  char * obtenervalor_1(TFC *, CLIENT *);
extern  char * obtenervalor_1_svc(TFC *, struct svc_req *);
#define ComprobarValor 5
extern  bool_t * comprobarvalor_1(TFCV *, CLIENT *);
extern  bool_t * comprobarvalor_1_svc(TFCV *, struct svc_req *);
#define NumeroHuecos 6
extern  int * numerohuecos_1(int *, CLIENT *);
extern  int * numerohuecos_1_svc(int *, struct svc_req *);
#define Correcto 7
extern  bool_t * correcto_1(int *, CLIENT *);
extern  bool_t * correcto_1_svc(int *, struct svc_req *);
#define Ayuda 8
extern  RCadena * ayuda_1(TFC *, CLIENT *);
extern  RCadena * ayuda_1_svc(TFC *, struct svc_req *);
#define GetSudoku 9
extern  RCadena * getsudoku_1(int *, CLIENT *);
extern  RCadena * getsudoku_1_svc(int *, struct svc_req *);
extern int gestorjuegos_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define Nuevo 1
extern  int * nuevo_1();
extern  int * nuevo_1_svc();
#define Borrar 2
extern  bool_t * borrar_1();
extern  bool_t * borrar_1_svc();
#define PonerValor 3
extern  bool_t * ponervalor_1();
extern  bool_t * ponervalor_1_svc();
#define ObtenerValor 4
extern  char * obtenervalor_1();
extern  char * obtenervalor_1_svc();
#define ComprobarValor 5
extern  bool_t * comprobarvalor_1();
extern  bool_t * comprobarvalor_1_svc();
#define NumeroHuecos 6
extern  int * numerohuecos_1();
extern  int * numerohuecos_1_svc();
#define Correcto 7
extern  bool_t * correcto_1();
extern  bool_t * correcto_1_svc();
#define Ayuda 8
extern  RCadena * ayuda_1();
extern  RCadena * ayuda_1_svc();
#define GetSudoku 9
extern  RCadena * getsudoku_1();
extern  RCadena * getsudoku_1_svc();
extern int gestorjuegos_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Cadena (XDR *, Cadena);
extern  bool_t xdr_TDificultad (XDR *, TDificultad*);
extern  bool_t xdr_RCadena (XDR *, RCadena*);
extern  bool_t xdr_TFCV (XDR *, TFCV*);
extern  bool_t xdr_TFC (XDR *, TFC*);

#else /* K&R C */
extern bool_t xdr_Cadena ();
extern bool_t xdr_TDificultad ();
extern bool_t xdr_RCadena ();
extern bool_t xdr_TFCV ();
extern bool_t xdr_TFC ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_GESTORJUEGOS_H_RPCGEN */