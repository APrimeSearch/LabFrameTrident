//
//  Nucleus.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2015-01-21.
//  Copyright (c) 2015 Natalia Toro. All rights reserved.
//

#ifndef __LabFrameTrident__Nucleus__
#define __LabFrameTrident__Nucleus__

#include <stdio.h>
#include "Particle.h"
#include <string>

enum class FormFactorModel { Point , Tsai, Fermi2p };

class Nucleus : public ParticleType {
  
    FormFactorModel formFactor_;

public:
    Nucleus(std::string name, double atomicMass, int atomicNumber, FormFactorModel formFactor);
    
    double atomicMass() const;
    int atomicNumber() const { return charge(); }
    double formFactor(double q2) const;
};

/********** Standard Nuclei ******************/

const Nucleus Wpoint("Wpoint",184.0,74,FormFactorModel::Point);

#endif /* defined(__LabFrameTrident__Nucleus__) */
