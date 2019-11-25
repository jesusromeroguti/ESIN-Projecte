#include "call_registry.hpp"

/* !!!!!!! -Hem de trobar una bona funcio de hash per que no totes funcionen be.
            -L'he cambiat el nom a la funcio de hash perque en la classe
            nat que utilitzem pels naturals ja hi havia una funcio de igual nom
            has i creaba conflictes !!!!!!!!!!!!!!*/

// Cost lineal
call_registry::call_registry() throw(error): _quants(0){
  _size = 50;
  _taula = new node_hash*[_size];
  for(int i = 0; i < _size; i++){
    _taula[i] = NULL;
  }
}

call_registry::call_registry(const call_registry& R) throw(error): _quants(R._quants), _size(R._size){
  _taula = new node_hash*[R._size];
  for(int i = 0; i < R._size; i++){
    node_hash *origen = R._taula[i];
    node_hash *desti;
    // En cas de que el contingut de _taula[i] == NULL
    if(origen == NULL){
      _taula[i] = NULL;
      continue; // continua en la seguent posicio de la _taula
    }

    desti = new node_hash(origen->_k, origen->_tel, NULL);
    // desti = new node_hash;
    // desti->_k = origen->_k;
    // desti->_tel = origen->_tel;
    // desti->seg = NULL;
    _taula[i] = desti;
    origen = origen->seg;

    while(origen != NULL){
      node_hash *nou = new node_hash(origen->_k, origen->_tel, NULL);
      // node_hash *nou = new node_hash;
      // nou->_k = origen->_k;
      // nou->_tel = origen->_tel;
      desti->seg = nou;
      desti = nou;
      origen = origen->seg;
    }
    // seg ultim node apunta a NULL
    desti->seg = NULL;
  }
}

call_registry::~call_registry() throw(){
  node_hash *p;
  // node que apunta al element segunt de la llista
  node_hash *pseg;
  // Recorrerem tota la taula i eliminarem tots els elements
  // de la llista contenida en cada posicio de la taula
  for(int i = 0; i < _size; i++){
    p = _taula[i];
    while(p != NULL){
      pseg = p->seg;
      delete p;
      p = pseg;
    }
  }
  // eliminem la _taula
  delete[] _taula;
}

void call_registry::registra_trucada(nat num) throw(error){
  nat i = funcio_hash(num);
  node_hash *p = _taula[i];
  if(conte(num)){
    // Posicio de la llista (node) on esta el num que ens interesa
    p->_tel++;
  } else {
    // Creu el nou phone
    phone t(num,"",1);
    // Creu el nou node a la _taula
    _taula[i] = new node_hash(num,t,_taula[i]);
    ++_quants;
  }
}

void call_registry::assigna_nom(nat num, const string& name) throw(error){
  nat i = funcio_hash(num);
  node_hash *n = pos_element(num);
  if (n != NULL) {
    phone t(num, name, n->_tel.frequencia());
    n->_tel = t;
  }
  else {
    phone t(num, name, 0);
    _taula[i] = new node_hash(num, t, _taula[i]);
    ++_quants;
  }
}

void call_registry::elimina(nat num) throw(error){
  nat i = funcio_hash(num);
  node_hash *ant = NULL;
  node_hash *p = _taula[i];
  bool trobat = false;
  while(p != NULL && !trobat){
    if(p->_k == num){
      trobat = true;
    } else {
      ant = p;
      p = p->seg;
    }
  }
  if(trobat){
    // Es el primer node/element de la llista
    if(ant == NULL){
      _taula[i] = p->seg;
    } else {
      ant->seg = p->seg;
    }
    delete p;
    --_quants;
  } else throw error(ErrNumeroInexistent);

}

bool call_registry::conte(nat num) const throw(){
  node_hash *n = pos_element(num);
  return (n != NULL);
}

string call_registry::nom(nat num) const throw(error){
  string resultat;
  node_hash *p = pos_element(num);
  if(p == NULL){
    throw error(ErrNumeroInexistent);
  }else {
    resultat = p->_tel.nom();
  }
  return resultat;
}

nat call_registry::num_trucades(nat num) const throw(error){
  nat freq;
  node_hash *p = pos_element(num);
  if(p == NULL){
    throw error(ErrNumeroInexistent);
  } else {
    freq = p->_tel.frequencia();
  }
  return freq;
}

bool call_registry::es_buit() const throw(){
  return _quants == 0;
}

nat call_registry::num_entrades() const throw(){
  return _quants;
}

void call_registry::dump(vector<phone>& V) const throw(error){

}

call_registry::node_hash::node_hash(const nat &k, const phone &tel, node_hash *seg) throw(error) : _k(k), _tel(tel), seg(seg){}

nat call_registry::funcio_hash(nat x) const throw(){
    // nat suma = 0;
    // int y;
    // while(x > 0){
    //   y = x % 1000;
    //   x = x / 1000;
    //   suma += y;
    // }
    // return suma % _size;
    nat i = x % _size;
    return i;
}

call_registry::node_hash* call_registry::pos_element(nat num) const throw(){
  nat i = funcio_hash(num);
  // p conte el primer punter de la posición on hauria d'estar el num
  node_hash *p = _taula[i];
  bool trobat = false;
  while(p != NULL && !trobat){
    if(p->_k == num) trobat = true;
    else if (p == NULL) return p;
    else p = p->seg;
  }
  return p;
}

// Constructor per defecte
call_registry::node_hash::node_hash(){}

// bool call_registry::diferents() const throw(error){
//   bool iguals = false;
//   nat i = 0;
//   // Bucle per a recorrer tota la _taula
//   while(i < _size && !iguals){
//     // Agafo el nom del primer phone de la _taula
//     string nom = _taula[i]->_tel.nom();
//     node_hash *p = _taula[i]->seg;
//     // Comparo tots els noms amb el que tinc guardat
//     while(p != NULL && !iguals){
//       if(p->_tel.nom() == nom) iguals = true;
//       else p = p->seg;
//     }
//     // Seguent posicio de la _taula
//     i++
//   }
// }
