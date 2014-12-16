//
//  EventGenerator.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_EventGenerator_h
#define LabFrameTrident_EventGenerator_h

#include "PhysicsProcess.h"
#include "PhaseSpaceSelector.h"
#include "GenerationStatistics.h"

class EventGenerator
{
public:
    // Constructor
    EventGenerator(PhaseSpaceSelector& ps, PhysicsProcess);
    Event& makeEvent() const;
    
    void displayStatisics() const;
    bool stopped() const { return stopped_};
   
protected:
    // Members
    bool inPhaseSpace(Event& e) const;
    double weight(Event& e) const;
    
private:
    // Data
    const PhaseSpaceSelector& _allowedPhaseSpace;
    const PhysicsProcess& _processToGenerate;
    
    mutable GenerationStatistics _myStatistics;
    
    int stopConditionCheckFrequency_;
    bool stopped_;
    sdk::list<StopCondition*> stopConditions_;
    
    
    
};

#endif
