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

call_registry::~call_registry() throw(){}

void call_registry::registra_trucada(nat num) throw(error){
  nat i = funcio_hash(num);
  // // nat i = num % _size;
  node_hash *p = _taula[i];
  // bool trobat = false;
  // while(p != NULL && !trobat){
  //   if(p->_k == num) trobat = true;
  //   else p = p->seg;
  // }
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

bool call_registry::conte(nat num) const throw(){
  // bool trobat;
  // // Obtenim la posició a la _taula
  // nat i = funcio_hash(num);
  // // nat i = num % _size;
  // cout << "i = " << i << endl;
  // // p conte el primer punter de la posición on hauria d'estar el num
  // node_hash *p = _taula[i];
  // trobat = false;
  // while(p != NULL && !trobat){
  //   if(p->_k == num) trobat = true;
  //   else p->seg;
  // }
  //return trobat;
  node_hash *n = pos_element(num);
  return (n != NULL);
}

string call_registry::nom(nat num) const throw(error){
  string resultat;
  if(!conte(num)){
    throw error(ErrNumeroInexistent);
  }else {
    bool trobat = false;
    nat i = num % _size;
    node_hash *p = _taula[i];
    while(p != NULL && !trobat){
      if(p->_k == num) {
        resultat = p->_tel.nom();
        trobat = true;
      } else p = p->seg;
    }
  }
  return resultat;
}

nat call_registry::num_trucades(nat num) const throw(error){
  nat freq;
  if(!conte(num)){
    throw error(ErrNumeroInexistent);
  } else {
    nat i = num % _size;
    node_hash *p = _taula[i];
    bool trobat = false;
    while(p != NULL && !trobat){
      if(p->_k == num){
        freq = p->_tel.frequencia();
        trobat = true;
      } else p = p->seg;
    }
  }
  return freq;
}

bool call_registry::es_buit() const throw(){
  return _quants == 0;
}

nat call_registry::num_entrades() const throw(){
  return _quants;
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
  while(!trobat){
    if(p->_k == num) trobat = true;
    else if (p == NULL) return p;
    else p = p->seg;
  }
  return p;
}
