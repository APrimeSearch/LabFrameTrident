//
//  SimplifiedAPEXPhaseSpaceSelector.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-17.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_SimplifiedAPEXPhaseSpaceSelector_h
#define LabFrameTrident_SimplifiedAPEXPhaseSpaceSelector_h


class SimplifiedAPEXPhaseSpaceSelector: PhaseSpaceSelector {
    
public:
    
    SimplifiedAPEXPhaseSpaceSelector(); 
    
    bool checkAcceptance(const Particle& p, const EventGlobalData& gd) const;
    bool checkAngularAcceptance(const Particle& p, const EventGlobalData& gd) const;
    
    randomFourVectorWithinAcceptance(ParticleType& ptype, Particle& p, const EventGlobalData& gd, double& selectionWeight) const;
    randomUnitVectorWithinAngularAcceptance(ParticleType& ptype, Particle& p, const EventGlobalData& gd, double& selectionWeight) const;
    
    bool passAcceptance(const Event& e) const;
    
    
private:
    
    double thetaxmin_;
    double thetaxmax_;
    double thetaymax_;
    double deltap_;
    double p0_;
    
};

#endif

#endif
