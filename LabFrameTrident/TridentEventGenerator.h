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

class TridentEventGenerator: EventGenerator {
    
public:
    TridentEventGenerator(PhaseSpaceSelector& ps);

private:
    
    bool tryEvent(Event& e, bool& goodEvent) const;
    
    double tridentMatrixElement(const Event& e);
};

#endif
