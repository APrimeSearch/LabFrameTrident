//
//  ParticleType.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-17.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_ParticleType_h
#define LabFrameTrident_ParticleType_h

#include <string>

class ParticleType
{
    std::string name_;
    int pid_;
    int charge3_;
    double mass_;
    
    
public:
    ParticleType(std::string name,int pid,int charge3,double mass);
    
    ParticleType antiparticle(const std::string newname) const;
    
public:
    double mass() const {return mass_;};
    int charge3() const { return charge3_;};
    int pid() const { return pid_;};
    std::string name() const { return name_;};
    
    double p(double E) const;
    double E(double p) const;
    
};

bool operator==(const ParticleType& pt1, const ParticleType& pt2);

/********** Standard Particle Types ******************/

const ParticleType eminus("electron",-11,-3,0.000511);
const ParticleType eplus=eminus.antiparticle("positron");

const ParticleType muminus("muon",-11,-3,0.104);
const ParticleType muplus=muminus.antiparticle("antimuon");

#endif
