//
//  ParticleType.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include <stdio.h>
#include "ParticleType.h"
#include <cmath>

ParticleType::ParticleType(std::string name,int pid,int charge,double mass):
name_(name),pid_(pid),charge_(charge),mass_(mass)
{};

ParticleType ParticleType::antiparticle(const std::string newname) const
{
    return ParticleType(newname,-pid_,-charge_,mass_);
}

double ParticleType::p(double E) const
{
    return sqrt(E*E-mass_*mass_);
}

double ParticleType::E(double p) const
{
    return sqrt(p*p+mass_*mass_);
}

/// DOESN'T CHECK NAME, DOES CHECK PID
bool operator==(const ParticleType& pt1, const ParticleType& pt2){
    return (pt1.pid()==pt2.pid() && pt1.charge()==pt2.charge() && pt1.mass()==pt2.mass());
}