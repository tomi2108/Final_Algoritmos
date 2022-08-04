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
};
struct nodo_lista
{
  info_lista info;
  nodo_lista *sgte;
  nodo_sublista *sublista;
};

nodo_lista *add(nodo_lista *&p, info_lista e)
{
  nodo_lista *aux = p;
  if (p == NULL)
  {
    p = new nodo_lista;
    p->info = e;
    p->sgte = NULL;
    aux = p;
  }
  else
  {

    while (aux->sgte != NULL)
    {
      aux = aux->sgte;
    }
    aux->sgte = new nodo_lista;
    aux = aux->sgte;
    aux->info = e;
    aux->sgte = NULL;
  }
  return aux;
}
nodo_sublista *add(nodo_sublista *&p, info_sublista e)
{
  nodo_sublista *aux = p;
  if (p == NULL)
  {
    p = new nodo_sublista;
    p->info = e;
    p->sgte = NULL;
    aux = p;
  }
  else
  {
    while (aux->sgte != NULL)
    {
      aux = aux->sgte;
    }
    aux->sgte = new nodo_sublista;
    aux = aux->sgte;
    aux->info = e;
    aux->sgte = NULL;
  }
  return aux;
}

nodo_lista *addFirst(nodo_lista *&p, info_lista e)
{
  nodo_lista *aux = NULL;
  if (p == NULL)
  {
    add(p, e);
    aux = p;
  }
  else
  {
    aux = new nodo_lista;
    aux->info = e;
    aux->sgte = p;
    p = aux;
  }
  return aux;
}
nodo_sublista *addFirst(nodo_sublista *&p, info_sublista e)
{
  nodo_sublista *aux = NULL;
  if (p == NULL)
  {
    add(p, e);
    aux = p;
  }
  else
  {
    aux = new nodo_sublista;
    aux->info = e;
    aux->sgte = p;
    p = aux;
  }
  return aux;
}

info_lista pop(nodo_lista *&);
info_sublista pop(nodo_sublista *&);

info_lista_dato removeFirst(nodo_lista_dato *&p)
{
  info_lista_dato t;
  nodo_lista_dato *aux = p;
  if (aux->sgte != NULL)
  {
    p = aux->sgte;
  }
  else
  {
    p = NULL;
  }
  t = aux->info;
  delete aux;
  return t;
};

info_lista_dato pop(nodo_lista_dato *&p)
{
  info_lista_dato t = removeFirst(p);
  return t;
}

nodo_lista *insertar_ordenado(nodo_lista *&p, info_lista e)
{
  nodo_lista *aux = p;
  nodo_lista *aux2 = p;
  if (p == NULL)
  {
    addFirst(p, e);
    aux = p;
    return aux;
  }
  if (e.campo1 - aux2->info.campo1 > 0)
  {
    addFirst(p, e);
    aux = p;
    return aux;
  }
  while (aux2 != NULL && e.campo1 - aux2->info.campo1 < 0)
  {
    if (aux2 == p)
    {
      aux2 = aux2->sgte;
    }
    else
    {
      aux2 = aux2->sgte;
      aux = aux->sgte;
    }
  }
  addFirst(aux->sgte, e);
  return aux->sgte;
}
nodo_sublista *insertar_ordenado(nodo_sublista *&p, info_sublista e)
{
  nodo_sublista *aux = p;
  nodo_sublista *aux2 = p;
  if (p == NULL)
  {
    addFirst(p, e);
    aux = p;
    return aux;
  }
  if (e.campo4 - aux2->info.campo4 > 0)
  {
    addFirst(p, e);
    aux = p;
    return aux;
  }
  while (aux2 != NULL && e.campo4 - aux2->info.campo4 < 0)
  {
    if (aux2 == p)
    {
      aux2 = aux2->sgte;
    }
    else
    {
      aux2 = aux2->sgte;
      aux = aux->sgte;
    }
  }
  addFirst(aux->sgte, e);
  return aux->sgte;
}

nodo_lista_dato *insertar_ordenado(nodo_lista_dato *&, info_lista_dato);
nodo_lista *insertar_sin_repetir(nodo_lista *&, info_lista);
nodo_sublista *insertar_sin_repetir(nodo_sublista *&, info_sublista);
nodo_lista_dato *insertar_sin_repetir(nodo_lista_dato *&, info_lista_dato);

nodo_lista *cargar_lista_de_listas(nodo_lista_dato *&p)
{
  int cache = 0;
  nodo_lista *listaFinal = NULL;
  while (p != NULL)
  {
    info_lista_dato infoDato = pop(p);
    if (cache != infoDato.campo1 || listaFinal == NULL)
    {
      cache = infoDato.campo1;
      info_lista nuevo;
      nuevo.campo1 = infoDato.campo1;
      nuevo.campo2 = infoDato.campo2;
      nodo_lista *newNodo = insertar_ordenado(listaFinal, nuevo);
      newNodo->sublista = NULL;
      info_sublista nuevoSub;
      nuevoSub.campo3 = infoDato.campo3;
      nuevoSub.campo4 = infoDato.campo4;
      insertar_ordenado(newNodo->sublista, nuevoSub);
    }
    else
    {
      info_sublista nuevoSub;
      nuevoSub.campo3 = infoDato.campo3;
      nuevoSub.campo4 = infoDato.campo4;
      nodo_lista *aux = listaFinal;
      if (aux->info.campo1 != cache)
      {
        while (aux->sgte->info.campo1 != cache)
        {
          aux = aux->sgte;
        }
      }
      insertar_ordenado(aux->sublista, nuevoSub);
    }
  }
  return listaFinal;
}

void agregar_lista_final(info_lista_dato &a, nodo_lista_dato *&lista)
{
  nodo_lista_dato *nuevo = new nodo_lista_dato;
  nuevo->info = a;
  nuevo->sgte = NULL;

  if (lista == NULL)
  {
    lista = nuevo;
  }
  else
  {
    nodo_lista_dato *aux = lista;
    while (aux->sgte != NULL)
    {
      aux = aux->sgte;
    }
    aux->sgte = nuevo;
  }
}
info_lista_dato crear_info_dato(int campo1, string campo2, float campo3, int campo4)
{
  return {campo1,
          campo2,
          campo3,
          campo4};
};

nodo_lista_dato *generar_lista_dato()
{
  nodo_lista_dato *p = NULL;
  info_lista_dato a = crear_info_dato(1, "hola", 2.7, 6);
  info_lista_dato b = crear_info_dato(1, "hola", 1.8, 9);
  info_lista_dato c = crear_info_dato(2, "chau", 7.8, 96);
  info_lista_dato d = crear_info_dato(3, "hey", 3.33, 86);
  info_lista_dato e = crear_info_dato(3, "hey", 5.55, 57);
  info_lista_dato f = crear_info_dato(3, "hey", 6, 100);
  agregar_lista_final(a, p);
  agregar_lista_final(b, p);
  agregar_lista_final(c, p);
  agregar_lista_final(d, p);
  agregar_lista_final(e, p);
  agregar_lista_final(f, p);
  return p;
};

void mostrar_nodo_sublista(info_sublista n)
{
  cout << n.campo3 << endl;
  cout << n.campo4 << endl;
}

void mostrar_sublista(nodo_sublista *lista)
{
  nodo_sublista *aux = lista;
  while (aux != NULL)
  {
    mostrar_nodo_sublista(aux->info);
    aux = aux->sgte;
  }
}

void mostrar_nodo_lista(nodo_lista *n)
{
  cout << n->info.campo1 << endl;
  cout << n->info.campo2 << endl;
  cout << "Sublista" << endl;
  mostrar_sublista(n->sublista);
}

void mostrar_lista_de_listas(nodo_lista *lista)
{
  nodo_lista *aux = lista;
  while (aux != NULL)
  {
    mostrar_nodo_lista(aux);
    aux = aux->sgte;
  }
};

int main()
{

  nodo_lista_dato *p = generar_lista_dato();

  nodo_lista *lista_de_listas = cargar_lista_de_listas(p);

  mostrar_lista_de_listas(lista_de_listas);

  return 0;
}