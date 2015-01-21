//
//  SimplifiedAPEXPhaseSpaceSelector.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-17.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_SimplifiedAPEXPhaseSpaceSelector_h
#define LabFrameTrident_SimplifiedAPEXPhaseSpaceSelector_h

#include "PhaseSpaceSelector.h"
#include "Particle.h"
#include "Event.h"
#include "FourVector.h"

class SimplifiedAPEXPhaseSpaceSelector: public PhaseSpaceSelector {
    
public:
    
    SimplifiedAPEXPhaseSpaceSelector(double pmax, double thetaxmin, double thetaxmax, double thetaymax, double deltapoverp, double p0);

    
    void randomFourVectorWithinAcceptance
        (const ParticleType& ptype,
         const Event& e,
         FourVector& v,
         double& selectionWeight) const;
    void randomUnitVectorWithinAngularAcceptance
        (const ParticleType& ptype,
         const Event& e,
         double& theta, double& phi,
         double& selectionWeight) const;

    bool passAcceptance(const Event& e, bool debug) const;

    // Defined in base class already
//    bool passAcceptance(const Event& e) const { return passAcceptance(e,false);}
    
    
    // Useful predefined phase-space selections
    
    // The settings used in LHEtoPGScut
    static SimplifiedAPEXPhaseSpaceSelector* apexOldReachSelector(double pmax, double p0);
    
    // Requires only that electron & positron be in left/right hemispheres
    static SimplifiedAPEXPhaseSpaceSelector* hemisphereSelector(double pmax);

    // Trivial selector
    static SimplifiedAPEXPhaseSpaceSelector* trivialAPEXstyleSelector(double pmax);
    
    
private:
    void randomUnitVectorInSpectrometer
    (bool Left,
     double& theta, double& phi,
     double& selectionWeight) const;
    void randomFourVectorInSpectrometer
    (bool Left, double mass,
     FourVector& v,
     double& selectionWeight) const;
    
    bool inSpectrometer(bool Left, const FourVector& p) const;

    
    double thetaxmin_;
    double thetaxmax_;
    double thetaymax_;
    double deltap_;
    double p0_;
    
};



#endif
