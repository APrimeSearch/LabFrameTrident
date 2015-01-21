//
//  PhaseSpaceSelector.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-25.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include "PhaseSpaceSelector.h"
#include "FourVector.h"
//#include "DebugLevel.h"
#include <random>
#include <cmath>
#include "constants.h"

PhaseSpaceSelector::PhaseSpaceSelector(double pmax):
gen_(), unitRandom_(0,1), pmax_(pmax)
{
}

double PhaseSpaceSelector::scaledRandom(double min, double max) const
{
    return unitRandom_(gen_)*(max-min)+min;
}

void PhaseSpaceSelector::randomUnitVectorAnywhere (double& theta, double& phi, double& selectionWeight) const
{
    double costheta = scaledRandom(-1,1);
    phi = scaledRandom(0, 2*PI);
    theta=acos(costheta);
    
    selectionWeight=4*PI;
}


void PhaseSpaceSelector::randomFourVectorAnywhere (double mass, FourVector& v, double& selectionWeight) const
{
    double theta, phi, momentum;
    double angularWeight=1;
    randomUnitVectorAnywhere(theta,phi,angularWeight);
    momentum=pow(scaledRandom(0,pow(pmax_,3)),1/3.); // sample as p^2 dp
    
    v.setSphericalLength(mass, momentum, theta, phi);
    selectionWeight=angularWeight*pow(pmax_,3)/3.;
}