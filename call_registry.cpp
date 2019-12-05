#include "call_registry.hpp"

#define FACTOR_CARREGA .9

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


call_registry& call_registry::operator=(const call_registry& R) throw(error){
  if(this != &R){
    call_registry aux(R);
    // Potser abans borrar lo que conte el parametre implicit?
    swap(aux);
  }
  return *this;
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
  _quants = 0;
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
    // Si el factor_carrega > 90% es realitza redispersio a la taula
    factor_carrega();
    // cout << _quants << endl;
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
    // Si el factor_carrega > 90% es realitza redispersio a la taula
    factor_carrega();
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


// Revisar ordenació mes eficient (quicksort, mergesort)
void call_registry::dump(vector<phone>& V) const throw(error){
  // boolea que indica si hi ha dos noms repetits
  bool iguals = false;
  // Fem el volcat dels phones
  for(int i = 0; i < _size; i++){
    node_hash *p = _taula[i];
    while(p != NULL){
      // V[i] = p->_tel;
      if(p->_tel.nom() != ""){
        V.push_back(p->_tel);
      }
      p = p->seg;
    }
  }

  // Mirar si hi han noms repetits
  for(int j = 0; j <V.size(); j++){
    string name = V[j].nom();
    for(int k = j + 1; k < V.size(); k++){
      // Comprarar noms no phones
      if(V[j].nom() == V[k].nom()){
        // iguals = true;
        throw error(ErrNomRepetit);
      }
    }
  }

}

call_registry::node_hash::node_hash(const nat &k, const phone &tel, node_hash *seg) throw(error) : _k(k), _tel(tel), seg(seg){}

nat call_registry::funcio_hash(nat x) const throw(){
    return util::hash(x) % _size;
}

call_registry::node_hash* call_registry::pos_element(nat num) const throw(){
  nat i = funcio_hash(num);
  // p conte el primer punter de la posición on hauria d'estar el num
  node_hash *p = _taula[i];
  bool trobat = false;
  while(p != NULL && !trobat){
    if(p->_k == num) trobat = true;
    else p = p->seg;
  }
  return p;
}

void call_registry::swap(call_registry &R) throw(){
  node_hash **aux = _taula;
  _taula = R._taula;
  R._taula = aux;
  nat auxs = _size;
  _size = R._size;
  R._size = auxs;
  auxs = _quants;
  _quants = R._quants;
  R._quants = auxs;
}


// Constructor per defecte
call_registry::node_hash::node_hash(){}

void call_registry::redispersio(){
  // nat mida_abans = _size;
  nat mida_abans = _size;
  _size = _size * 2 + 1;
  node_hash **nova_taula = new node_hash*[_size]();

  for(int i = 0; i < mida_abans; i++){
    node_hash *p = _taula[i];
    while(p != NULL){
      node_hash *aux = p;
      p = p->seg;
      node_hash *&nou = nova_taula[funcio_hash(aux->_k)];
      aux->seg = nou;
      nou = aux;
    }
  }
  // eliminem la _taula
  delete[] _taula;
  _taula = nova_taula;
}

// Funcio per saber si es sobrepasa el factor de carrega
void call_registry::factor_carrega(){
  float f = static_cast<float>(_quants) / static_cast<float>(_size);
  if(f >= FACTOR_CARREGA){
    redispersio();
  }
}
