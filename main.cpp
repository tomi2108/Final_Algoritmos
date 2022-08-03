#include <iostream>

using namespace std;

struct info_lista_dato
{
  int campo1;
  string campo2;
  float campo3;
  int campo4;
};
struct nodo_lista_dato
{
  info_lista_dato info;
  nodo_lista_dato *sgte;
};

struct info_sublista
{
  float campo3;
  int campo4;
};

struct nodo_sublista
{
  info_sublista info;
  nodo_sublista *sgte;
};

struct info_lista
{
  int campo1;
  string campo2;
  nodo_sublista *sublista;
};
struct nodo_lista
{
  info_lista info;
  nodo_lista *sgte;
};

info_lista pop(nodo_lista *&);
info_sublista pop(nodo_sublista *&);
info_lista_dato pop(nodo_lista_dato *&);
nodo_lista *insertar_ordenado(nodo_lista *&, info_lista);
nodo_sublista *insertar_ordenado(nodo_sublista *&, info_sublista);
nodo_lista_dato *insertar_ordenado(nodo_lista_dato *&, info_lista_dato);
nodo_lista *insertar_sin_repetir(nodo_lista *&, info_lista);
nodo_sublista *insertar_sin_repetir(nodo_sublista *&, info_sublista);
nodo_lista_dato *insertar_sin_repetir(nodo_lista_dato *&, info_lista_dato);

bool no_esta_en(nodo_lista *p, int a)
{
  if (p == NULL)
  {
    return true;
  }
  nodo_lista *aux = p;
  while (aux != NULL)
  {
    if (aux->info.campo1 == a)
    {
      return false;
    }
  }
  return true;
}

nodo_lista *cargar_lista_de_listas(nodo_lista_dato *&p)
{
  nodo_lista_dato *aux = p;
  nodo_lista *listaFinal = NULL;
  while (aux->sgte != NULL)
  {
    info_lista_dato infoDato = pop(aux);
    if (no_esta_en(listaFinal, infoDato.campo1))
    {
      info_lista nuevo;
      nuevo.campo1 = infoDato.campo1;
      nuevo.campo2 = infoDato.campo2;
      info_sublista nuevoSub;
      nuevoSub.campo3 = infoDato.campo3;
      nuevoSub.campo4 = infoDato.campo4;
      nodo_lista *list = insertar_ordenado(listaFinal, nuevo);
      insertar_ordenado(list->info.sublista, nuevoSub);
    };
  }

  return listaFinal;
}

int main()
{

  return 0;
}