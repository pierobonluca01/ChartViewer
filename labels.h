#ifndef LABELS_H
#define LABELS_H

#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;


class Labels {
    friend class Graph;
private:
    vector<string> l;

    Labels(size_t);
    Labels(const Labels&);

    void newLabels(size_t);
    void insertLabel(size_t);
    void removeLabel(size_t);

public:
    string& operator [](size_t);
};

#endif // LABELS_H
