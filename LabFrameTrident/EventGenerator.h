//
//  EventGenerator.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_EventGenerator_h
#define LabFrameTrident_EventGenerator_h

#include "PhaseSpaceSelector.h"
#include "GenerationStatistics.h"
#include "Event.h"
#include "DebugLevel.h"

class EventGenerator
{
public:
    // Constructor
    EventGenerator(PhaseSpaceSelector& ps);
    makeEvent(Event& e) const;
    
    void displayStatisics() const;
    bool stopped() const { return stopped_};
    
    void setDebugLevel(const bool deep);
//    void addStopCondition(StopCondition*);
   
/*
 Should these just be specific to the derived classes?
protected:
    // Members
    bool tryEvent(Event& e) const;
    double weight(Event& e) const;
 */
    
private:
    virtual bool tryEvent(Event& e, bool& goodEvent) const;
    
private:
    // Data
    const PhaseSpaceSelector& _allowedPhaseSpace;
    
    mutable GenerationStatistics _myStatistics;
//    int _stopConditionCheckFrequency;
//    bool _stopped;
//    sdk::vector<StopCondition*> _stopConditions;
    
    DebugLevel _debugLevel;
    
};

#endif
