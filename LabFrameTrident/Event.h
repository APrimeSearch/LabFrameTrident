//
//  Event.h
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-16.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#ifndef LabFrameTrident_Event_h
#define LabFrameTrident_Event_h

#include <iostream>
#include <vector>
#include "Particle.h"

//#include "GlobalEventData.h"

class Event {
    
public:
    Event();
    ~Event();
    Event(const Event& e); // copies kinematics but not weight.
    
    void print(std::ostream& os) const;
    void print() const { print(std::cout);};

    double weight() const;
    double scaleWeight(double scale);
    double setWeight(double weight);
    
    int finalStateMultiplicity(const ParticleType& p) const;
    int initialStateMultiplicity(const ParticleType& p) const;
   
    void addIncomingParticle(const Particle& p);
    void addOutgoingParticle(const Particle& p);
    
    bool valid() const;
    
    FourVector incomingMomentum() const;
    FourVector outgoingMomentum() const;
    bool conservesMomentum() const;
    FourVector residualMomentum() const;
    
    std::string write() const;
    
    const std::vector<Particle>& incomingParticles() const
        {return incomingParticles_;};
    const std::vector<Particle>& outgoingParticles() const
        {return outgoingParticles_;};
    
    
private:
    double* weight_;   // Pointer allows for events to have unassigned weight
    
    std::vector<Particle> incomingParticles_;
    std::vector<Particle> outgoingParticles_;
    
    bool writeGroup(std::ostream& outs, const std::string& begintag, const std::string& endtag, const std::vector<Particle>& writeFrom) const;

    
    // Can't remember what I wanted to put here...
    // I think part of the idea was that it would
    // be used to calculate whether particle is in acceptance.
    // GlobalEventData eventData_;
    
    constexpr static const double MOMENTUM_CONSERVATION_TOLERANCE=1E-8;

};

std::ostream& operator<< (std::ostream& s, const Event& e);

#endif
