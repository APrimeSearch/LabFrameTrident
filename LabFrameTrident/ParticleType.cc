//
//  ParticleType.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include <stdio.h>
#include "ParticleType.h"

ParticleType::ParticleType(std::string name,int pid,int charge3,double mass):
name_(name),pid_(pid),charge3_(charge3),mass_(mass)
{};

ParticleType ParticleType::antiparticle(const std::string newname) const
{
    return ParticleType(newname,-pid_,-charge3_,mass_);
}
