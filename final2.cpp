#include <iostream>

using namespace std;

struct cliente
{
  int carrito;
};

struct nodo_cola
{
  cliente info;
  nodo_cola *sgte;
};

struct caja
{
  int numCaja;
  int dineroEfectivoAp;
  int dineroEfectivoCob;
  int importeTotalTC;
  int cuponesTC;
  int importeTotalTD;
  int cuponesTD;
  int tickets;
  int importTotalTickets;
  nodo_cola *cola;
};

cliente insertarOrdenado(cliente, nodo_cola *&);
caja *buscarEnLista(int, caja *&);
cliente insertarSinRepetir(cliente, nodo_cola *&);
caja *push(caja, caja *&);
caja pop(caja *&);
nodo_cola *queue(cliente, nodo_cola *&);
cliente unQueue(nodo_cola *&);

caja *cajasHabilitadas()
{
  caja *arrCajas = NULL;
  FILE *f = fopen("Cajas.dat", "rb");
  int numCaja = fread(f, sizeof(int), 1, 0);
  int dineroEfectivoAp = fread(f, sizeof(int), 1, 0);
  while (!feof(f))
  {
    caja nuevaCaja;
    nuevaCaja.numCaja = numCaja;
    nuevaCaja.cola = NULL;
    nuevaCaja.cuponesTC = 0;
    nuevaCaja.cuponesTD = 0;
    nuevaCaja.dineroEfectivoAp = dineroEfectivoAp;
    nuevaCaja.dineroEfectivoCob = 0;
    nuevaCaja.importeTotalTC = 0;
    nuevaCaja.importeTotalTD = 0;
    nuevaCaja.importTotalTickets = 0;
    nuevaCaja.tickets = 0;
    push(nuevaCaja, arrCajas);
    int numCaja = fread(f, sizeof(int), 1, 0);
    int dineroEfectivoAp = fread(f, sizeof(int), 1, 0);
  }
  fclose(f);
  return arrCajas;
}

void nuevoCliente(nodo_cola *&p, caja *&cajas, int numCaja)
{
  cliente c;
  c = unQueue(p);

  caja *caja = buscarEnLista(numCaja, cajas);

  queue(c, caja->cola);
}

struct importes
{
  int dineroEf;
  int dineroTc;
  int dineroTd;
  int ticket;
  int dineroTicket;
};

importes calcularImportes(int);

void atenderCliente(int numCaja, caja *&cajas)
{
  caja *pcaja = buscarEnLista(numCaja, cajas);
  cliente c = unQueue(pcaja->cola);

  importes i = calcularImportes(c.carrito);

  pcaja->cuponesTC--;
  pcaja->cuponesTD--;
  pcaja->dineroEfectivoCob += i.dineroEf;
  pcaja->importeTotalTC += i.dineroTc;
  pcaja->importeTotalTD += i.dineroTd;
  pcaja->importTotalTickets += i.dineroTicket;
  pcaja->tickets -= i.ticket;
}

void reasignarCaja(int origen, int destino, caja *&cajas)
{
  caja *cajaO = buscarEnLista(origen, cajas);
  caja *cajaD = buscarEnLista(destino, cajas);

  cliente c = unQueue(cajaO->cola);

  queue(c, cajaD->cola);
}

int main()
{
  nodo_cola *clientes;
  caja *cajas = cajasHabilitadas();

  nuevoCliente(clientes, cajas, 1);
  nuevoCliente(clientes, cajas, 2);
  nuevoCliente(clientes, cajas, 1);
  nuevoCliente(clientes, cajas, 1);

  atenderCliente(1, cajas);

  nuevoCliente(clientes, cajas, 2);

  atenderCliente(2, cajas);

  nuevoCliente(clientes, cajas, 1);
  nuevoCliente(clientes, cajas, 3);
  nuevoCliente(clientes, cajas, 3);

  reasignarCaja(1, 2, cajas);

  atenderCliente(2, cajas);

  nuevoCliente(clientes, cajas, 2);

  atenderCliente(3, cajas);
  atenderCliente(2, cajas);
  atenderCliente(1, cajas);
  atenderCliente(1, cajas);
  atenderCliente(3, cajas);
  atenderCliente(2, cajas);
}