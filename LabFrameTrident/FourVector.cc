//
//  FourVector.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include "FourVector.h"
#include <cmath>
#include <iomanip>

/**************** Constructors (public) ************/
FourVector::FourVector()
{
    v_[0]=0;
    v_[1]=0;
    v_[2]=0;
    v_[3]=0;
}

FourVector::FourVector(double v0,double v1,double v2,double v3)
{
    v_[0]=v0;
    v_[1]=v1;
    v_[2]=v2;
    v_[3]=v3;
}

FourVector::FourVector(double v[4])
{
    for(int i=0;i<4;++i){
        v_[i]=v[i];
    }
};

FourVector::FourVector(const FourVector& v1)
{
    for(int i=0;i<4;++i){
        this->v_[i]=v1.v_[i];
    };
};

/**************** Assignment methods (public) ************/

void FourVector::setCartesianT(double t,double x, double y, double z)
{
    v_[0]=t;
    v_[1]=x;
    v_[2]=y;
    v_[3]=z;
    return;
}

void FourVector::setSphericalT(double t, double rho, double theta, double phi)
{
    v_[0]=t;
    v_[1]=rho*sin(theta)*cos(phi);
    v_[2]=rho*sin(theta)*sin(phi);
    v_[3]=rho*cos(theta);
    return;
}

void FourVector::setCartesianLength(double len,double x, double y, double z)
{
    v_[0]=sqrt(len*len+x*x+y*y+z*z);
    v_[1]=x;
    v_[2]=y;
    v_[3]=z;
    return;
}

void FourVector::setSphericalLength(double len, double rho, double theta, double phi)
{
    v_[0]=sqrt(len*len+rho*rho);
    v_[1]=rho*sin(theta)*cos(phi);
    v_[2]=rho*sin(theta)*sin(phi);
    v_[3]=rho*cos(theta);
    return;
}


/**************** Math methods (public) ************/

double FourVector::sq() const
{
    return (v_[0]*v_[0] -
            v_[1]*v_[1] -
            v_[2]*v_[2] -
            v_[3]*v_[3]);
}

double FourVector::len() const
{
    return sqrt(sq());
}

double FourVector::len3() const
{
    return sqrt(v_[1]*v_[1] +
            v_[2]*v_[2] +
            v_[3]*v_[3]);
}


/**************** Operators ************/

void FourVector::operator+= (const FourVector& v1)
{
    for(int i=0;i<4;++i){
        this->v_[i]+= v1.v_[i];
    };
}

FourVector operator+ (const FourVector& v1, const FourVector& v2)
{
    return FourVector(v1.T()+v2.T(),
                      v1.X()+v2.X(),
                      v1.Y()+v2.Y(),
                      v1.Z()+v2.Z());
}

double operator*(const FourVector&v1, const FourVector& v2)
{
    return (v1.T()*v2.T() -
            v1.X()*v2.X() -
            v1.Y()*v2.Y() -
            v1.Z()*v2.Z());
}


/*************** IO Methods ******************/
void FourVector::print(std::ostream& s) const
{
    s << std::setw(12) << std::setprecision(6) << T()
      << std::setw(12) << std::setprecision(6) << X()
      << std::setw(12) << std::setprecision(6) << Y()
      << std::setw(12) << std::setprecision(6) << Z()
      << std::endl;
}


std::ostream& operator<< (std::ostream& s, const FourVector& v1)
{
    
    s << std::setw(12) << std::setprecision(6) << v1.T()
      << std::setw(12) << std::setprecision(6) << v1.X()
      << std::setw(12) << std::setprecision(6) << v1.Y()
      << std::setw(12) << std::setprecision(6) << v1.Z();
    return s;
}