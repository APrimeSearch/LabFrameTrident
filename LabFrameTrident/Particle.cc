//
//  Particle.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include "Particle.h"
#include "ParticleType.h"
#include "FourVector.h"
#include <iostream>
#include <cmath>


/************** Constructors *****************/

Particle::Particle(const ParticleType& ptype, const FourVector p, const FourVector& v ) :
ptype_(ptype), p_(p), vertex_(v)
{
    //if(!onShell())  ...  just print diagnostics
    offShellDiagnostics(std::cerr);
    offShellDiagnostics(std::cout);

    return;
}

Particle::Particle(const ParticleType& ptype, const FourVector p) :
ptype_(ptype), p_(p), vertex_(0,0,0,0)
{
    //if(!onShell())  ...  just print diagnostics
    offShellDiagnostics(std::cerr);
    offShellDiagnostics(std::cout);

    return;
}

Particle::Particle(const ParticleType& ptype, double p, double theta, double phi) :
ptype_(ptype), vertex_(0,0,0,0)
{
    p_.setSphericalLength(ptype.mass(), p, theta , phi);
}

Particle::Particle(const Particle& pold) :
ptype_(pold.ptype_), p_(pold.p_), vertex_(pold.vertex_)
{}

/************** On/Off-Shell Checks *****************/

bool Particle::onShell() const
{
    double m0=ptype_.mass();
    double mp=p_.len();
    
    if(mp>0 && fabs(mp-m0)/m0 < ON_SHELL_TOLERANCE) return true;
    else return false;
}



void Particle::offShellDiagnostics(std::ostream &s) const
{
    double m0=ptype_.mass();
    double mp=p_.len();
    if(mp>0 && fabs(mp-m0)/m0 < ON_SHELL_TOLERANCE)        return;
    else
        s << "** ON-SHELL FAILURE: m = " << m0 << " len(p) = " << mp << std::endl;
    
    return;
}
