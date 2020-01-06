#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
  // El prefix al construir el easy_dial es indefinit
  indefinit = true;
  R.dump(_phones);
  for(int i = 0; i < _phones.size(); i++){
    insereix(_phones[i].nom(), i);
  }
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){
  indefinit = D.indefinit;
  _prefix = D._prefix;
  if (D._arrel != NULL) {
    esborra(D._arrel);
  }
  _phones = D._phones;
  _historial = D._historial;
  _visitats = D._visitats;
  pos = D.pos;
  ultim_resultat = D.ultim_resultat;
  _arrel = copia_tst(D._arrel);
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
  if(this != &D) {
    easy_dial aux(D);
  }
  return *this;
}

easy_dial::~easy_dial() throw(){
  esborra(_arrel);
}

/* Inicialitza el prefix en curs a buit. Retorna el nom de F(S, '');
si F (S, '') no existeix llavors retorna l'string buit. */
string easy_dial::inici() throw(){
  string res = "";
  _prefix = "";
  indefinit = false;
  // NUEVO
  node_tst *aux = new node_tst;
  aux->_esq = aux->_cen = aux->_dret = NULL;
  aux->_x = 0;
  aux->_visitat = false;
  aux->_valor = phone::ENDPREF;
  // ACABA LO NUEVO
  // Si el vector esta buit easy_dial també per tant retornara el string buit.
  if(_phones.size() != 0){
    // Actualitzem l'ultim resultat;
    res = _phones[0].nom();
    ultim_resultat = res;
    _historial.push_back(res);
    // cout << ultim_resultat << endl;
    _visitats.push_back(aux);
  } else pos = -1;
  return res;
}

/* Retorna el nom de F(S, p') on p' és el prefix resultant d'afegir
el caràcter c al final del prefix en curs p i
fa que el nou prefix en curs sigui p'.
Si F(S, p) existeix però F(S, p') no existeix llavors retorna
l'string buit.
Si no existeix F(S, p) (i per tant tampoc pot existir F(S, p'))
llavors es produeix un error i el prefix en curs queda indefinit.
Naturalment, es produeix un error si el prefix en curs inicial p
fos indefinit. */
string easy_dial::seguent(char c) throw(error){
  if(indefinit) throw error(ErrPrefixIndef);
  // if(pos == -1) {
  //   indefinit = true;
  //   throw error(ErrPrefixIndef);
  // }
  _prefix = _prefix + c;
  string nom_resultat = "";
  // cout << "ultim_resultat: " <<ultim_resultat << endl;
  node_tst *n = obte_nom_max_freq(_arrel, 0, _prefix, nom_resultat);

  // Actualitzem _historial
  if(nom_resultat != ""){
    // it = _historial.begin();
    _historial.push_back(nom_resultat);
    // _historial.insert(it, nom_resultat);
    ultim_resultat = nom_resultat;
    // ++contador_historial;
    // for(int i = 0; i < _historial.size(); i++){
    //   cout << _historial[i] << endl;
    // }
    _visitats.push_back(n);
  } else {
    pos = -1;
    ultim_resultat = "";
    _historial.push_back(nom_resultat);
  }
  return nom_resultat;
}

/* Elimina l'últim caràcter del prefix en curs p = p' · a
(a és el caràcter eliminat). Retorna el nom F(S, p')
i fa que el nou prefix en curs sigui p'.
Es produeix un error si p fos buida i si es fa que el prefix en curs
quedi indefinit. Òbviament, també es produeix un error
si p fos indefinit. */
string easy_dial::anterior() throw(error){
  string nom_resultat;
  if(indefinit) throw error(ErrPrefixIndef);
  // Eliminem l'ultim caracter del prefix en curs
  if(_prefix.length() != 0){
    _prefix.erase(_prefix.end()-1);
    _historial.pop_back();
    nom_resultat = _historial[_historial.size()-1];
    _visitats[_visitats.size()-1]->_visitat = false;
    _visitats.pop_back();
    pos = _visitats[_visitats.size()-1]->_x;
  } else throw error(ErrNoHiHaAnterior);
  return nom_resultat;
}

/* Retorna el número de telèfon de F(S, p), sent p
el prefix en curs. Es produeix un error si p és indefinit o si
no existeix F(S, p). */
nat easy_dial::num_telf() const throw(error){
  if(indefinit) throw error(ErrPrefixIndef);
  if(pos == -1) throw error(ErrNoExisteixTelefon);
  return _phones[pos].numero();
}

/* Retorna en el vector result tots els noms dels contactes de
telèfon que comencen amb el prefix pref, en ordre lexicogràfic creixent. */
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
  // Falta ordenar els noms en ordre lexicogràfic creixent
  node_tst *l = obte_noms(_arrel, 0, pref, result);
}

/* Retorna el número mitjà de pulsacions necessàries para obtenir un
telèfon. Formalment, si X és el conjunt de noms emmagatzemats en
el easy_dial i t(s) és el número de pulsacions mínimes
necessàries (= número de crides a l'operació seguent) per
obtenir el telèfon el nom del qual és s. La funció retorna la suma
    Pr(s) · t(s)
per tots els telèfons s del conjunt X, sent Pr(s) la probabilitat de
telefonar a s. La probabilitat s'obté dividint la freqüència de s per
la suma de totes les freqüències. */
double easy_dial::longitud_mitjana() const throw(){
  // A l'hora de construir podem afegir el numero de pulsacions
  // necessaries per que aparegui el nom del telefon
  // Pr(s) = freq(s) / sum(freq(X))
  // t(s) = num crides seguent(s) (he posat s per posar algo, ja se q se li passa un char jajaj)
  double prob = 0.0;
  double sum_freqs = 0.0;

  // prob = calcula_prob(_phones);
  // crides = num_crides(_phones); // S'haurà de comparar la frequencia amb els altres s
}
/*
double easy_dial::calcula_prob(vector<phone> _phones) const throw(){
  //Calculem la suma de totes
  for (int i = 0; i < _phones.size(); ++i) {
    //freqs.insert(phone::frequencia(_phones[i].nom()));
    sum_freqs += phone::frequencia(_phones[i].nom());
  }
  //calculem la probabilitat de cada s
  for (int i = 0; i < _phones.size(); ++i) {
    prob += (phone::frequencia(_phones[i].nom()) / sum_freqs);
  }
  prob = (prob/_phones.size());
}*/

typename easy_dial::node_tst* easy_dial::insereix_r(node_tst *n, nat i, string s, int x){
  if(n == NULL){
    n = new node_tst;
    n->_esq = n->_dret = n->_cen = NULL;
    n->_valor = s[i];
    n->_x = -1;
    n->_visitat = false; // NUEVO
    try{
      if(i < s.length()-1){
        n->_cen = insereix_r(n->_cen, i+1, s, x);
      } else { // i == s.length-1 --> s[i] == ENDPREF
        n->_valor = s[i];   // Realmente no hace falta, ya lo haces arriba.
        n->_x = x;      // Si es el node que conte \0 llavors posem la posicio del vector
      }
    } catch (...){
      delete n;
      throw;
    }
  } else {
    if(n->_valor > s[i]){
      n->_esq = insereix_r(n->_esq, i, s, x);
    } else if(n->_valor < s[i]){
      n->_dret = insereix_r(n->_dret, i, s, x);
    } else {
      n->_cen = insereix_r(n->_cen, i+1, s, x);
    }
  }
  return n;
}

void easy_dial::insereix(const string &n, int x) throw(error){
  string s = n + phone::ENDPREF;
  // cout << s << endl;
  _arrel = insereix_r(_arrel,0, s, x);
}

void easy_dial::obte_tots(node_tst *n, vector<string> &p) const{
  vector<string>::iterator it;
  if(n != NULL){
    if(n->_valor == phone::ENDPREF){
      p.push_back(_phones[n->_x].nom());
    }
    obte_tots(n->_esq, p);
    obte_tots(n->_dret, p);
    obte_tots(n->_cen, p);
  }
}

typename easy_dial::node_tst* easy_dial::obte_noms(node_tst *n, nat i, const string& prefix, vector<string>& p) const{
  node_tst *res = NULL;
  if(n != NULL){
    if(i <= prefix.length()-1){
      if(n->_valor > prefix[i]){
        res = obte_noms(n->_esq, i, prefix, p);
      }
      else if(n->_valor < prefix[i]){
        res = obte_noms(n->_dret, i, prefix, p);
      }
      else if(n->_valor == prefix[i]){
        res = obte_noms(n->_cen, i+1, prefix, p);
      }
    } else { // i == prefix.length() - 1
      res = n;
      // cout << res->_valor << endl;
      obte_tots(res, p);
    }
  }
  return res;
}

void easy_dial::obte_nom_max_freq(node_tst *n, int &max_freq, string &nom_resultat, node_tst* &vis){
  if(n != NULL){
    if(n->_valor == phone::ENDPREF and !n->_visitat){
      if(_phones[n->_x].nom() != ultim_resultat){
        if(max_freq <= _phones[n->_x].frequencia()){
          vis = n;
          // SI max_freq == a la freq del phone phone.nom()>phone2.nom()
          if(max_freq == _phones[n->_x].frequencia()){
            nom_resultat = (nom_resultat >= _phones[n->_x].nom() ? nom_resultat : _phones[n->_x].nom());
          } else {
            max_freq = _phones[n->_x].frequencia();
            nom_resultat = _phones[n->_x].nom();
            pos = n->_x;
          }
        }
      }
    }

    obte_nom_max_freq(n->_esq, max_freq, nom_resultat, vis);
    obte_nom_max_freq(n->_dret, max_freq, nom_resultat, vis);
    obte_nom_max_freq(n->_cen, max_freq, nom_resultat, vis);
  }
}


typename easy_dial::node_tst* easy_dial::obte_nom_max_freq(node_tst *n, nat i, const string& prefix, string &nom_resultat){
  // Variable que guarda a frequencia mes alta actual
  int max_freq = 0;
  // NUEVO
  node_tst *vis = NULL;
  node_tst *res = NULL;
  if(n != NULL){
    if(i <= prefix.length()-1){
      if(n->_valor > prefix[i]){
        res = obte_nom_max_freq(n->_esq, i, prefix, nom_resultat);
      }
      else if(n->_valor < prefix[i]){
        res = obte_nom_max_freq(n->_dret, i, prefix, nom_resultat);
      }
      else if(n->_valor == prefix[i]){
        res = obte_nom_max_freq(n->_cen, i+1, prefix, nom_resultat);
      }
    } else {
      res = n;
      obte_nom_max_freq(res, max_freq, nom_resultat, vis);
      vis->_visitat = true;
      if(vis != NULL) res = vis;
    }
  }
  return res;
}

void easy_dial::esborra(node_tst *n) {
  if(n != NULL){
    esborra(n->_esq);
    esborra(n->_dret);
    esborra(n->_cen);
    delete n;
  }
}

typename easy_dial::node_tst* easy_dial::copia_tst(node_tst *m){
  node_tst *n;
  if (m == NULL) {
    n = NULL;
  } else {
    n = new node_tst;
    n->_valor = m->_valor;
    n->_x = m->_x;
    n->_esq = copia_tst(m->_esq);
    n->_dret = copia_tst(m->_dret);
    n->_cen = copia_tst(m->_cen);
  }
  return n;
}



/*version
void easy_dial::obte_nom_max_freq(node_tst *n, int &max_freq, string &nom_resultat){
  if(n != NULL){
    if(n->_valor == phone::ENDPREF){
      if(max_freq <= _phones[n->_x].frequencia()){
        if(_phones[n->_x].nom() != ultim_resultat){
          // SI max_freq == a la freq del phone phone.nom()>phone2.nom()
          if(max_freq == _phones[n->_x].frequencia()){
            nom_resultat = (nom_resultat >= _phones[n->_x].nom() ? nom_resultat : _phones[n->_x].nom());
          } else {
            max_freq = _phones[n->_x].frequencia();
            nom_resultat = _phones[n->_x].nom();
            pos = n->_x;
          }
        }
      }
    }
    obte_nom_max_freq(n->_esq, max_freq, nom_resultat);
    obte_nom_max_freq(n->_dret, max_freq, nom_resultat);
    obte_nom_max_freq(n->_cen, max_freq, nom_resultat);
  }
}*/

//Versio 1 amb Historial
/*string easy_dial::anterior() throw(error){
  string nom_resultat;
  if(indefinit) throw error(ErrPrefixIndef);
  // Eliminem l'ultim caracter del prefix en curs
  if(_prefix.length() != 0){
    _prefix.erase(_prefix.end()-1);
    cout << "_prefix actual: " << _prefix << endl;
    nom_resultat = _historial[0];
  } else throw error(ErrNoHiHaAnterior);
  return nom_resultat;
}*/
