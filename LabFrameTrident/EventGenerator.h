//
//  EventGenerator.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_EventGenerator_h
#define LabFrameTrident_EventGenerator_h

class EventGenerator
{
public:
    // Constructor
    EventGenerator(PhaseSpaceSelector& ps, PhysicsProcess);
    Event& makeEvent() const;
    
    
// Local data
   
protected:
    // Members
    bool inPhaseSpace(Event& e) const;
    double weight(Event& e) const;
    
private:
    const PhaseSpaceSelector& _allowedPhaseSpace;
    const PhysicsProcess& _processToGenerate;
    
    GenerationStatistics
    
};

#endif
