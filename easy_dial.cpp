#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
  _prefix = "";
  crea_tst(R);
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){}
easy_dial::~easy_dial() throw(){}

/* Inicialitza el prefix en curs a buit. Retorna el nom de F(S, '');
si F (S, '') no existeix llavors retorna l'string buit. */
string easy_dial::inici() throw(){}

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
  if ( c != "\0" ) {
  	_prefix = _prefix + c;
  }
  else throw(phone::ENDPREF);
}

/* Elimina l'últim caràcter del prefix en curs p = p' · a
(a és el caràcter eliminat). Retorna el nom F(S, p')
i fa que el nou prefix en curs sigui p'.
Es produeix un error si p fos buida i si es fa que el prefix en curs
quedi indefinit. Òbviament, també es produeix un error
si p fos indefinit. */
string easy_dial::anterior() throw(error){}

/* Retorna el número de telèfon de F(S, p), sent p
el prefix en curs. Es produeix un error si p és indefinit o si
no existeix F(S, p). */
nat easy_dial::num_telf() const throw(error){}

/* Retorna en el vector result tots els noms dels contactes de
telèfon que comencen amb el prefix pref, en ordre lexicogràfic creixent. */
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){}

/* Retorna el número mitjà de pulsacions necessàries para obtenir un
telèfon. Formalment, si X és el conjunt de noms emmagatzemats en
el easy_dial i t(s) és el número de pulsacions mínimes
necessàries (= número de crides a l'operació seguent) per
obtenir el telèfon el nom del qual és s. La funció retorna la suma
    Pr(s) · t(s)
per tots els telèfons s del conjunt X, sent Pr(s) la probabilitat de
telefonar a s. La probabilitat s'obté dividint la freqüència de s per
la suma de totes les freqüències. */
double easy_dial::longitud_mitjana() const throw(){}


//Funció que crea el tst amb tots els registres
void crea_tst(const call_registry& R) throw(error){}

//Funció que insereix la string al easy_dial
void insereix(const string& s) throw(error){}

//Funció que insereix cada caràcter de la string a els nodes del tst
void insereix_r(node_tst *n, nat pos, string s, bool& repetit){}





//.rep
//Opcions tst, Tries
struct node_tst {
  char _valor;
  node_tst* _esq;
  node_tst* _dret;
  node_tst* _cen;
};
node_tst *_arrel;
string _prefix;

//Funció que crea el tst amb tots els registres
void crea_tst(const call_registry& R) throw(error);

//Funció que insereix la string al easy_dial
void insereix(const string& s) throw(error);

//Funció que insereix cada caràcter de la string a els nodes del tst
void insereix_r(node_tst *n, nat pos, string s, bool& repetit);




//////////////
void diccionari::insereix(const string& p) throw(error) {
  /**
   * Pre:  Cert.
   * Post: Afegeix la paraula p al diccionari; si la paraula p ja formava
   *       part del diccionari, l'operació no té cap efecte.
   * Cost: O(l*log s) sent l la longitud mitja i s el numero promig de simbols.
  */
  string s = p + _especial; //--> \0
  bool repetit = false;
  _arrel = insereix(_arrel, 0, s, repetit);
  if (!repetit) _n_paraules++;
}

//////////////
typename diccionari::node* diccionari::insereix(node *n, nat posicio, string s, bool& repetit) {
  /**
   * Pre:  Cert.
   * Post: Afegeix la lletra del string s allotjada a la posicio del nat posicio.
   * Cost: O(l*log s) sent l el número de simbols que hem queden per visitar i s el número
   *       promig de simbols.
  */
  if (n == NULL) {
    if (posicio > s.length()-1) {
      repetit = true;
    } else {
      try {
        n = new node;
        n->esq = n->dret = n->cent = NULL;
        n->valor = s[posicio];
        if (posicio < s.length()-1) {
          n->cent = insereix(n->cent, posicio+1, s, repetit);
        }
      }
      catch (...) {
        delete n;
        throw;
      }
    }
  } else {
    if (n->valor > s[posicio]) {
        n->esq = insereix(n->esq, posicio, s, repetit);
      } else if (n->valor < s[posicio]) {
        n->dret = insereix(n->dret, posicio, s, repetit);
    } else {   // (n->valor == s[posicio])
      n->cent = insereix(n->cent, posicio+1, s, repetit);
    }
  }
  return n;
}
