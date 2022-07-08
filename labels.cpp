#include "labels.h"

Labels::Labels(size_t n): l(vector<string>(n, "label")) {
    for(size_t i=0; i<n; i++) {
        l[i]=std::to_string(i+1);
    }
}

Labels::Labels(const Labels& lc): l(lc.l) {}

string Labels::getLabel(size_t i) const {
    return l[i];
}

string& Labels::setLabel(size_t i) {
    return l[i];
}

void Labels::newLabels(size_t n) {
    for(size_t i=0; i<n; i++)
        l.push_back("nuova"+std::to_string(i+1));
}

void Labels::insertLabel(size_t i) {
    l.insert(l.begin()+i, "nuova");
}

void Labels::removeLabel(size_t i) {
    l.erase(l.begin()+i);
}

string& Labels::operator [](size_t i) {
    try {
        if(i>l.size())
            throw 0;
        return l[i];
    } catch(int err) {
        switch(err) {
        case 0:
            std::cerr<<"\n [!] Indice fuori range.\n     Ritornato l'ultimo elemento.\n";
            return l[0];
            break;
        default:
            std::cerr<<"\n [!] Errore generico. \n";
            abort();
        }
    }
}


