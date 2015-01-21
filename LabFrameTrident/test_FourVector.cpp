//
//  trident_tester.cpp
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include <iostream>
#include "FourVector.h"
#include <cmath>

using namespace std;

int test_FourVector()
{
    
    // Test Four-vector
    FourVector v;
    FourVector v2(1,0,1,0);
    FourVector v3({2,0,-1,0});
    
    cout << " v0 = " << v.print() << endl;
    
    cout << " v2 = " << v2.print() << endl;
    cout << " v3 = " << v3.print() << endl;
    
    cout << " v2.v3 = " << v2*v3 << endl;

    cout << "v2+v3 = "<< v2+v3 << endl;
    
    v.setSphericalLength(0.000511,10.000,acos(-0.99),0.0);
 
    v2.setCartesianLength(0.000511,5.000,1.0,1.0);

    cout << " Mass difference" << v.len() - v2.len() << endl;
   
    cout << " closure test " << (v+v2).sq()-v.sq()-v2.sq()-2*(v*v2) << endl;
    
    return 0;
};
