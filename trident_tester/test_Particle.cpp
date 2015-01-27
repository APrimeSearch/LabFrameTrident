//
//  test_Particle.cpp
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include "Particle.h"
#include <cmath>

using namespace std;

int test_Particle()
{
    Particle testebeam(eminus, eminus.p(10.0), 0,0);
    FourVector eAtRest(eminus.mass(), 0,0,0);
    
    Particle testerest(eminus,eAtRest);
    
    cout << "beam p" << testebeam.p() << endl;
    cout << "beam v" << testebeam.vtx() << endl;
    
    cout << "rest p" << testerest.p() << endl;
    
    cout << " beam mass - rest mass "
         << testebeam.p().len()-testerest.p().len()
         << endl;
    
    cout << " E-|p|" <<testebeam.E() - testebeam.pabs()
         << " vs. ultrarelativistic "
         << pow(eminus.mass(),2)/(2*testebeam.E()) << endl;
    
    FourVector electronMomentum=testebeam.p();
    FourVector almostCollinearPhoton;
    almostCollinearPhoton.setCartesianLength(0.,0.0001,0.00004,5.0);
    
    Particle offShell(eminus, electronMomentum+almostCollinearPhoton);
    cout << "!! On-shell failure messages above are GOOD !!" << endl;
    
    cout << " Mass difference" << offShell.p().len()-eminus.mass() << endl;
    
    return 0;
}
