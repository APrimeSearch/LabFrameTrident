//
//  Nucleus.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2015-01-21.
//  Copyright (c) 2015 Natalia Toro. All rights reserved.
//

#include <cmath>
#include <cassert>
#include "Nucleus.h"
#include "constants.h"

Nucleus::Nucleus(std::string name, double atomicMass, int atomicNumber, FormFactorModel formFactor) :
formFactor_(formFactor),
ParticleType(name, 999, atomicNumber, atomicMass*amuInGeV)
{}

double Nucleus::atomicMass() const
{
    return mass()/amuInGeV;
}

// Currently, only implemented point form factor.  Will add others later...
double Nucleus::formFactor(double q2) const
{
    if(formFactor_==FormFactorModel::Point) {
        return pow(atomicNumber(),2);
    }
    else
        assert(false);
}