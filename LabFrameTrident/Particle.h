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
    ParticleType ptype_;
    FourVector p_;  // momentum
    FourVector vertex_;  // vertex
    
    static const ON_SHELL_TOLERANCE=1E-8;
    
public:
    Particle(const ParticleType& ptype, const FourVector& v );
    Particle(const ParticleType& ptype, double p, double theta, double phi);
    
    bool onShell();
    
    double E() const { return p_.T();};
    double pabs() const { return p_.len3();};
    double pt() const { return p_.X()*p_.X()+p_.Y()*p_.Y();};
    const FourVector& p() const { return p_;};
    
};


#endif
