#include "call_registry.hpp"

call_registry::call_registry() throw(error) : _prim(NULL), _size(0){}

call_registry::call_registry(const call_registry& R) throw(error) : _prim(R._prim), _size(R._size){
}


void call_registry::registra_trucada(nat num) throw(error){
  // Si hi ha una entrada amb el num corresponent incrementem compt
  if(conte(num)) {
    node *n = _prim;
    while(n != NULL){
      if(n->tel.numero() == num) n->tel++;
      else n = n->seg;
    }
    // Si no hi ha cap entrada amb aquest num la creem
  } else {
    node *ant = NULL;
    //Creem el phone
    phone t(num,"",1);
    //Creem el nou node
    node *n = new node();
    n->tel = t;
    n->seg = NULL;
    // Inserim el node al call_registry
    if(es_buit()){
      _prim = n;
    } else{
      ant->seg = n;
    }
    ant = n;
    _size++;
  }
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
  if(conte(num)){
    node *n = _prim;
    while(n != NULL){
      if(n->tel.numero() == num){
        // No tenim acces al atribut privat _name
        // per tant creo un phone nou i li assigno al actual
        phone p(num, name, n->tel.frequencia());
        n->tel = p;
      } else n = n->seg;
    }
    // El numero no esta en el call_registry
  } else {
    node *ant = NULL;
    phone t(num, name, 0);
    node *n = new node;
    n->tel = t;
    n->seg = NULL;
    if(es_buit()){
      _prim = n;
    } else {
      ant->seg = n;
    }
    ant = n;
    _size++;
  }
}


void call_registry::elimina(nat num) throw(error){
  // Si no conte el numero que volem eliminar
  // llancem excepcio
  if(!conte(num)){
    throw error(ErrNumeroInexistent);
  } else {
    // Quan si que hi es busquem on esta
    node *aux = _prim;
    while(aux != NULL){
      // Variable per saber quin es l'element anterior al que vull borrar
      node *ant = NULL;
      // Una vegada trobat el volem eliminar
      if(aux->tel.numero() == num){
        // Si l'element que volem eliminar es el primer
        if(aux == _prim){
          node *elim = aux;
          _prim = aux->seg;
          aux = aux->seg;
          delete elim;
          // Si volem el un element que no es el primer
        } else {
          node *elim = aux;
          ant->seg = aux->seg;
          aux = aux->seg;
          delete elim;
          ant = aux;
        }
      } else {
        ant = aux;
        aux = aux->seg;
      }
    }
  }
}

bool call_registry::conte(nat num) const throw() {
  node *aux = _prim;
  bool t = false;
  while(aux != NULL && !t){
    if(aux->tel.numero() == num) t = true;
    else aux = aux->seg;
  }
  return t;
}

string call_registry::nom(nat num) const throw(error){
  if(!conte(num)){
    throw error(ErrNumeroInexistent);
  } else {
    node *aux = _prim;
    while(aux != NULL){
      if(aux->tel.numero() == num) return aux->tel.nom();
      else aux = aux->seg;
    }
  }
}

nat call_registry::num_trucades(nat num) const throw(error){
  if(!conte(num)) throw error(ErrNumeroInexistent);
  else {
    node *aux = _prim;
    while(aux != NULL){
      if(aux->tel.numero() == num) return aux->tel.frequencia();
      else aux = aux->seg;
    }
  }
}

bool call_registry::es_buit() const throw(){
  return _size == 0;
}

nat call_registry::num_entrades() const throw(){
  return _size;
}
