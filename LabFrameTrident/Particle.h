//
//  Particle.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_Particle_h
#define LabFrameTrident_Particle_h

#include "FourVector.h"
#include "ParticleType.h"

class Particle {
    ParticleType ptype;
    FourVector p;  // momentum
    FourVector vertex;  // vertex
    
    
    
public:
    Particle(ParticleType& ptype, FourVector);
    
    bool onShell();
    double E() const { return p.T();};
    double p() const { return p.len3();};
    double pt() const { return pow(p.X(),2)+pow(p.Y(),2);};
};


#endif
