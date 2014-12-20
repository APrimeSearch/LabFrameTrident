
//
//  FourVector.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-17.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_FourVector_h
#define LabFrameTrident_FourVector_h

#include <iostream>
//#include "Particle.h"
#include <array>

using std::cout;

class FourVector {
    
    double v_[4];

public:

    FourVector();
    FourVector(double v0,double v1,double v2,double v3);
    FourVector(double v[4]);
    FourVector(const FourVector& v1);

    void setCartesianT(double t,double x, double y, double z);
    void setSphericalT(double t, double rho, double theta, double phi);
    
    void setCartesianLength(double len,double x, double y, double z);
    
    void setSphericalLength(double len, double rho, double theta, double phi);
    
    double sq() const; // Invariant length-squared
    double len() const;  // Invariant length
    double len3() const; // 3-vector length
    
//    FourVector* operator+ (const FourVector& v1, const FourVector& v2);
    void operator+=(const FourVector& v1);
 
    
    double T() const { return v_[0]; }
    double X() const { return v_[1]; }
    double Y() const { return v_[2]; }
    double Z() const { return v_[3]; }
    
    void print(std::ostream& s) const;
    void print() const { print(cout); return; };
    
/*  Do we need these?
    void setT(double t)  { v_[0]=t; }
    void setX(double x)  { v_[1]=x; }
    void setY(double y)  { v_[2]=y; }
    void setZ(double z)  { v_[3]=z; }
 */

};

FourVector operator+ (const FourVector& v1, const FourVector& v2);
double operator* (const FourVector& v1, const FourVector& v2);

std::ostream& operator<< (std::ostream& s, const FourVector& v1);


#endif
