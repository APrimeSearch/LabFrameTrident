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


class PhaseSpaceSelector {
   
public:
    
    PhaseSpaceSelector();

    /* Note: Acceptance for particle P within event can depend on other particles in event. */

    virtual void randomFourVectorWithinAcceptance
        (const ParticleType& ptype,
         const Event& e,
         FourVector& v,
         double& selectionWeight) const;
    virtual void randomUnitVectorWithinAngularAcceptance(const ParticleType& ptype,
         const Event& gd,
         double& theta, double& phi,
         double& selectionWeight) const;
    
    virtual bool passAcceptance(const Event& e) const;

    
private:
    
    DebugLevel _debugLevel;
    
};

#endif
