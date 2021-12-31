#include "labels.h"

Labels::Labels(size_t n): l(vector<string>(n, "label")) {}

Labels::Labels(const Labels& lc): l(lc.l) {}

void Labels::newLabels(size_t n) {
    for(size_t i=0; i<n; i++)
        l.push_back("label");
}

void Labels::insertLabel(size_t i) {
    l.insert(l.begin()+i, "label");
}

void Labels::removeLabel(size_t i) {
    l.erase(l.begin()+i);
}

string& Labels::operator [](size_t i) {
    try {
        if(i>l.size() /*|| i<0 size_t unsigned*/)
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


