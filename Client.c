#include "include.h"

int main(int argc, char const *argv[])
{
	Village *v = new Village(1, 100);
  Village *res = new Village(2, 100);
  int stat = callrpc(
    /* host */ "localhost",
    /* prognum */ PROGNUM,
    /* versnum */ VERSNUM,
    /* procnum */ PROCNUM,
    /* encodage argument */ (xdrproc_t)xdr_village,
    /* argument */ (char *)v,
    /* decodage retour */ (xdrproc_t)xdr_village,
    /* retour de la fonction distante */(char *)&res
  );
	return 0;
}