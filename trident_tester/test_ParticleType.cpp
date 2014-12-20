//
//  test_ParticleType.cpp
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include <iostream>
#include "ParticleType.h"

using namespace std;

int test_ParticleType()
{
    cout << eplus.charge3()/3 << endl;
    cout << eplus.name() << endl;
    
    cout << eplus.antiparticle("slew").name() << endl;
    cout << eplus.antiparticle("slew").charge3() << endl;
    
    return 0;
    
}