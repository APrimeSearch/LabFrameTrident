//
//  Event.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-20.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include "Event.h"
#include <vector>
#include <sstream>
using namespace std;

/**************  Constructors/Destructor ****************/
Event::Event():
incomingParticles_(), outgoingParticles_(), weight_(NULL)
{};

Event::Event(const Event& e):
incomingParticles_(e.incomingParticles_), outgoingParticles_(e.outgoingParticles_), weight_(NULL)
{};

Event::~Event()
{
    delete weight_;
    incomingParticles_.clear();
    outgoingParticles_.clear();
}

/*************** I/O Functions ****************/
// NOT YET IMPLEMENTED

bool Event::writeGroup(ostream& outs, const string& begintag, const string& endtag, const std::vector<Particle>& writeFrom) const
{
    outs << begintag << endl;
    for(vector<Particle>::const_iterator p=writeFrom.begin();
        p!= writeFrom.end(); ++p){
        outs << *p;
    }
    outs << endtag << endl;
    return true;
}

std::string Event::write() const
{
    std::ostringstream s;
    s<< "<event>" << std::endl;
    writeGroup(s,"<incoming>","</incoming>",incomingParticles_);
    writeGroup(s,"<outgoing>","</outgoing>",outgoingParticles_);
    s<< "</event>" << std::endl;
    return s.str();
}

std::ostream& operator<< (std::ostream& s, const Event& e)
{
    s<<e.write();
    return s;
}

/*************** Particle & kinematic manipulation ************/

// TODO: Need to un
void Event::addIncomingParticle(const Particle &p)
{
    incomingParticles_.push_back(p);
    return;
}

void Event::addOutgoingParticle(const Particle &p)
{
    outgoingParticles_.push_back(p);
    return;
}

int Event::finalStateMultiplicity(const ParticleType& pt) const
{
    int count=0;
    for(vector<Particle>::const_iterator p=outgoingParticles_.begin();
        p!= outgoingParticles_.end(); ++p){
        if(p->ptype() == pt) ++count;
    }
    return count;
}

int Event::initialStateMultiplicity(const ParticleType& pt) const
{
    int count=0;
    for(vector<Particle>::const_iterator p=incomingParticles_.begin();
        p!= incomingParticles_.end(); ++p){
        if(p->ptype() == pt) ++count;
    }
    return count;
}

FourVector Event::incomingMomentum() const
{
    FourVector pIn;
    for(vector<Particle>::const_iterator p=incomingParticles_.begin();
        p!= incomingParticles_.end(); ++p){
        pIn += p->p();
    }
    return pIn;
}

FourVector Event::outgoingMomentum() const
{
    FourVector pOut;
    for(vector<Particle>::const_iterator p=outgoingParticles_.begin();
        p!= outgoingParticles_.end(); ++p){
        pOut += p->p();
    }
    return pOut;
}

bool Event::conservesMomentum() const
{
    return outgoingMomentum()==incomingMomentum();
}

FourVector Event::residualMomentum() const
{
    return incomingMomentum()-outgoingMomentum();
}

bool Event::valid() const
{
    bool valid=conservesMomentum();
    
    for(vector<Particle>::const_iterator p=outgoingParticles_.begin();
        p!= outgoingParticles_.end() && valid; ++p){
        
        valid = valid && p->onShell();
    }
    return valid;
}

/*************** Weight manipulation **************/
double Event::weight() const
{
    if(weight_==NULL) {
        cerr << " WARNING: ATTEMPTED TO RETRIEVE WEIGHT FOR EVENT WITH NO WEIGHT ASSIGNED.  Returning 1/0." << std::endl;
        return 1/0.;
    }
    else return *weight_;
}

double Event::scaleWeight(double scale)
{
    if(weight_==NULL) {
        cerr << " WARNING: ATTEMPTED TO RETRIEVE WEIGHT FOR EVENT WITH NO WEIGHT ASSIGNED.  Returning Zero." << std::endl;
        return 1/0.;
    }
    else *weight_ *=scale;
    return *weight_;
}

double Event::setWeight(double weight)
{
    if(weight_==NULL)
        weight_ = new double(weight);
    else *weight_ = weight;
    return *weight_;
}