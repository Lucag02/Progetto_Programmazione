//
// Created by luca on 16/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_SUBJECT_H
#define PROGETTO_PROGRAMMAZIONE_SUBJECT_H
#include "Observer.h"

class Subject {
public:
    virtual void registerObserver(Observer* o)=0;
    virtual void notifyObserver(const float &dt) =0;
    virtual void removeObservers(Observer* o)=0;
    virtual ~Subject()=default;
};


#endif //PROGETTO_PROGRAMMAZIONE_SUBJECT_H
