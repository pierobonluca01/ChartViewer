#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controller {
private:
    Model* model;
    View* view;
public:
    Controller();

    void setModel(Model*);
    void setView(View*);
};

#endif // CONTROLLER_H
