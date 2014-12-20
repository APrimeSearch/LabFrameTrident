//
//  Event.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_Event_h
#define LabFrameTrident_Event_h

#include <ostream.h>
#include <vector.h>

#include "GlobalEventData.h"

class Event {
    
public:
    void print(ostream& os) const;
    void print(ostream& os) const { print(cout)};

    
    int finalStateMultiplicity(const ParticleType& p);
    int initialStateMultiplicity(const ParticleType& p);
    
private:
    double* weight_;   // Pointer allows for events to have unassigned weight
    
    stl::vector<Particle*> incomingParticles_;
    stl::vector<Particle*> outgoingParticles_;
    
    GlobalEventData eventData_;

};

#endif
