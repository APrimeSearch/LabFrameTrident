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
#include "Nucleus.h"

class EventGenerator
{
public:
    // Constructor
    EventGenerator(PhaseSpaceSelector& ps);
    
//    void displayStatisics() const;
    
    virtual bool tryEvent(
                        double incidentEnergy,  // INPUT
                        const Nucleus& nucleus, // INPUT
                        Event& e) // OUTPUT
            const = 0;

protected:
    const PhaseSpaceSelector& phaseSpace() const { return _allowedPhaseSpace; };
    
//bool stopped() const { return stopped_};
    
//    void setDebugLevel(const bool deep);
//    void addStopCondition(StopCondition*);
   
/*
 Should these just be specific to the derived classes?  I think so.
protected:
 // Members
 private:
 virtual double matrixElement(Event& e) const = 0;

 */
    
private:
    // Data
    const PhaseSpaceSelector& _allowedPhaseSpace;
    
    
// For functionality I may want to add later...
//    mutable GenerationStatistics _myStatistics;

//    int _stopConditionCheckFrequency;
//    bool _stopped;
//    sdk::vector<StopCondition*> _stopConditions;
//    DebugLevel _debugLevel;
    
};

#endif
