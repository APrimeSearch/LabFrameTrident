//
//  Particle.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_Particle_h
#define LabFrameTrident_Particle_h

#include <ostream>
#include <string>
#include "FourVector.h"
#include "ParticleType.h"

class Particle {
    ParticleType ptype_;
    FourVector p_;  // momentum
    FourVector vertex_;  // vertex
    
    constexpr static const double ON_SHELL_TOLERANCE=1E-8;
    
public:
    Particle(const ParticleType& ptype, const FourVector p, const FourVector& v );
    
    Particle(const ParticleType& ptype, const FourVector p);
    Particle(const ParticleType& ptype, double p, double theta, double phi);
    Particle(const Particle& pold);
    
    bool onShell() const;
    void offShellDiagnostics(std::ostream& s) const;
    
    std::string printP() const;
    std::string printPV() const;
    
    // Basic inline kinematics functions
    double E() const { return p_.T();};
    double pabs() const { return p_.len3();};
    double pt() const { return p_.X()*p_.X()+p_.Y()*p_.Y();};
    const FourVector& p() const { return p_;};
    const FourVector& vtx() const { return vertex_;};
    
    void setVertex(const FourVector& v) { vertex_=v;};
    void displaceVertex(const FourVector& dv) { vertex_=dv;};
    
    const ParticleType& ptype() const {return ptype_;};
};

std::ostream& operator<< (std::ostream& s, const Particle& p);


#endif
