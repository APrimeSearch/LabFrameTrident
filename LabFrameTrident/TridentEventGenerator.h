//
//  PhysicsProcess.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

//  Responsible for creating trident events, given
//  acceptance.
//

#ifndef LabFrameTrident_TridentEventGenerator_h
#define LabFrameTrident_TridentEventGenerator_h

#include "EventGenerator.h"

class TridentEventGenerator: public EventGenerator {
    
public:
    TridentEventGenerator(PhaseSpaceSelector& ps, double mMin, double mMax);

    bool tryEvent(
                  double incidentEnergy,  // INPUT
                  const Nucleus& nucleus, // INPUT
                  Event& e) const; // OUTPUT

private:
    double matrixElement(const Event& e) const;
    
    double mMin_, mMax_;
    
};

#endif
