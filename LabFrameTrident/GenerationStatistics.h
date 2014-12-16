//
//  GenerationStatistics.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_GenerationStatistics_h
#define LabFrameTrident_GenerationStatistics_h

class GenerationStatistics {
    friend class EventGenerator;
    
    int unphysicalEventCount_;
    int rejectedEventCount_;
    int goodEventCount_;
    double sumOfWeights_;
    double maxWeight_;
    double minWeight_;
    int maxTries_;
    
protected:
    
public:
    void printStatistics();
    double goodEventEfficiency();
    
};

#endif
