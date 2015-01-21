//
//  PhaseSpaceSelector.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_PhaseSpaceSelector_h
#define LabFrameTrident_PhaseSpaceSelector_h

#include "FourVector.h"
#include "Event.h"
#include "FourVector.h"
#include "ParticleType.h"
#include "DebugLevel.h"

#include <random>

class PhaseSpaceSelector {
   
public:
    
    PhaseSpaceSelector(double pmax);

    /* Note: Acceptance for particle P within event can depend on other particles in event. */

    virtual void randomFourVectorWithinAcceptance
        (const ParticleType& ptype,
         const Event& e,
         FourVector& v,
         double& selectionWeight) const = 0;
    virtual void randomUnitVectorWithinAngularAcceptance(const ParticleType& ptype,
         const Event& gd,
         double& theta, double& phi,
         double& selectionWeight) const = 0;
    
    virtual bool passAcceptance(const Event& e, bool debug) const = 0;
    bool passAcceptance(const Event& e) const { return passAcceptance(e, false); }


protected:
    double scaledRandom(double min, double max) const;
    void randomUnitVectorAnywhere
    (double& theta, double& phi,
     double& selectionWeight) const;
    void randomFourVectorAnywhere
    (double mass, FourVector& v,
     double& selectionWeight) const;
    
private:
    
//    DebugLevel _debugLevel;
    double pmax_;  // Maximum momentum needed for phase-space selection
    
    mutable std::default_random_engine gen_;
    mutable std::uniform_real_distribution<double> unitRandom_;
};

#endif
