//
//  test_ParticleType.cpp
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include <iostream>
#include "ParticleType.h"
#include "Nucleus.h"
#include <cmath>

using namespace std;

int test_ParticleType()
{
    cout << eplus.charge() << endl;
    cout << eplus.name() << endl;
    
    cout << eplus.antiparticle("slew").name() << endl;
    cout << eplus.antiparticle("slew").charge() << endl;
    
    Nucleus Wsimple("W",184.0,74,FormFactorModel::Point);
    
    cout << " NUCLEUS: " << Wsimple.name() << " " << Wsimple.pid() << " " << Wsimple.formFactor(0.01)/pow(Wsimple.atomicNumber(),2) << endl;
    
    
    return 0;
    
}