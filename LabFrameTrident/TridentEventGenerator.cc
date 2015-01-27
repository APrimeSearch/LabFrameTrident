//
//  TridentEventGenerator.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2015-01-21.
//  Copyright (c) 2015 Natalia Toro. All rights reserved.
//

#include "TridentEventGenerator.h"
#include "constants.h"
#include <cassert>

//--------------- Constructor ----------------//
TridentEventGenerator::TridentEventGenerator(PhaseSpaceSelector& ps,
                                             double mMin, double mMax):
EventGenerator(ps), mMin_(mMin), mMax_(mMax) {}


// Phase-Space Workhorse
bool TridentEventGenerator::tryEvent(
              double incidentEnergy,  // INPUT
              const Nucleus& nucleus, // INPUT
              Event& e) const // OUTPUT
{
    bool goodEvent;
    
    // Incoming particles: electron of momentum p(incidentEnergy) and  nucleus at rest.
    //Particle(const ParticleType &ptype, double p, double theta, double phi)
    Particle eIn(eminus, eminus.p(incidentEnergy), 0, 0);
    Particle nucIn(Particle(nucleus, 0, 0, 0));
    
    e.addIncomingParticle(eIn);
    e.addIncomingParticle(nucIn);
    e.setWeight(1);
    
    // Now build up the particles' kinematics:
    // 1. choose lplus (four-vector in acceptance), add to event
    // 2. choose ^lminus (unit-vector in acceptance)
    // 3. choose q2 (inv mass^2 in range)
    // 4. solve for lminus length, add to event, check acceptance
    // 5. Choose ^precoil (for APEX/HPS, unit-vector anywhere)
    // 6. solve for precoil 4-vector, add to event
    // 7. use momentum conservation to get nucleus momentum -- check
    //      on-shell and positive energy; add to event
    // At this point, we will have a weight (from selections alone) of
    // l+^2 dl+ dOmega+ dOmega- dOmega_r dq^2
    // 8. Scale by remaining Jacobian factors
    
    double weightFactor;

    // 1. choose lplus (four-vector in acceptance), add to event
    FourVector lplus;
    goodEvent=phaseSpace().randomFourVectorWithinAcceptance(eplus, e, lplus, weightFactor);
    if(!goodEvent) return false;
    Particle plus(eplus, lplus);
    e.addOutgoingParticle(plus);
    e.scaleWeight(weightFactor);     // l+^2 dl+ dOmega+ weight

    // 2. choose ^lminus (unit-vector in acceptance)
    double thetaMinus, phiMinus, lminusMin, lminusMax;
    goodEvent = phaseSpace().randomUnitVectorWithinAngularAcceptance(eminus, e, thetaMinus, phiMinus, weightFactor, lminusMin,lminusMax);
    if(!goodEvent) return false;
    e.scaleWeight(weightFactor);   // dOmega- weight
    
    // 3. choose q2 (inv mass^2 in range)
    if(lminusMax > incidentEnergy-lplus.T())
        lminusMax = incidentEnergy-lplus.T();
    
    double q2min=(lplus+Particle(eminus, lminusMin, thetaMinus, phiMinus).p()).sq();
    double q2max=(lplus+Particle(eminus, lminusMax, thetaMinus, phiMinus).p()).sq();
    if(q2max > mMax_* mMax_)
        q2max = mMax_* mMax_;
    if(q2min < mMin_* mMin_)
        q2min = mMin_* mMin_;
    
    assert(q2max>q2min);
                    
    double q2=phaseSpace().scaledRandom(q2min, q2max);
    e.scaleWeight(q2max-q2min); // dq^2 weight
    
    // 4. solve for lminus length, add to event, check acceptance
    // note my nA is actually "-A" from Beranek, which is positive,
    // and I've done some manipulations
    double nA=q2/2-pow(eminus.mass(),2);
    double B=lplus.dotUnit3Vector(thetaMinus,phiMinus);
    double me=eplus.mass();
    double ep=lplus.T();
    
    double disc1=nA*nA-me*me*(ep*ep-B*B);
    if(disc1<0) return false;
    
    double modlminus=(nA*B + ep * sqrt(disc1))/(ep*ep-B*B);
    
    Particle minus(eminus, modlminus, thetaMinus, phiMinus);
    FourVector qpair=lplus+minus.p();
    
    if(fabs(qpair.sq() - q2) > 1e-8)
    {
        std::cerr << "BAD Q CALCULATION: q=" <<qpair << "sq = " << qpair.sq()
                  << " q2 = " << q2 <<  " diff " << q2-qpair.sq() << std::endl;
        assert(false);
    }
    
    // 4A : Noticed that all "bad" events in Mathematica trial can be
    // identified by having D < 0, which is unphysical, more precisely
    // 4-momentum conservation implies k+Mnuc=q0 + k'e+p'nuc.  In physical
    // region, should have mass >M+m
    //
    // In principle, this can be achieved at generation level by setting appropriate bounds on q2 , we'll just do a quick check here.
    
    double recoilm2=(eIn.p() + nucIn.p() - qpair).sq();
    double mNuc =nucleus.mass();
    
    if(recoilm2 < pow(me+mNuc,2))
        return false;
    
    e.addOutgoingParticle(minus);

    goodEvent=phaseSpace().passAcceptance(e);
    if(!goodEvent) return false;
    
    // 5. Choose ^precoil (for APEX/HPS, unit-vector anywhere)
    double thetaR, phiR;
    double lRmin, lRmax;  /// DUMMY VARIABLES, NEVER ACTUALY USED
    goodEvent = phaseSpace().randomUnitVectorWithinAngularAcceptance(eminus, e, thetaR, phiR, weightFactor, lRmin, lRmax);
    if(!goodEvent) return false;
    e.scaleWeight(weightFactor);   // dOmegaR weight
    
    // 6. solve for precoil 4-vector, add to event
    double D = recoilm2 + pow(me,2) - pow(mNuc,2);
    double F = 2*(eIn.E()+mNuc-qpair.T());
    double G = 2* (eIn.p()-qpair).dotUnit3Vector(thetaR,phiR);
    
    if(F<mNuc+me || fabs(G)>F) /// some basic kinematic checks.
        return false;
    
    double disc2=D*D-me*me*(F*F-G*G);
    if(disc2<0) return false;

    double modkprime = (D*G + F*sqrt(disc2))/(F*F-G*G);
    Particle erecoil(eminus, modkprime, thetaR, phiR);
    
    if(fabs(D-F*erecoil.E()+G*erecoil.pabs())>1e-8)
    {
        std::cerr << "BAD erecoil EQUATION: D=" << D << "vs. F*E = " << F*erecoil.E() <<  " - G*p  = " << G*erecoil.pabs() << std:: endl;
    }
    
    e.addOutgoingParticle(erecoil);

    // 7. use momentum conservation to get nucleus momentum -- check
    //      on-shell and positive energy; add to event
    // At this point, we will have a weight (from selections alone) of
    // l+^2 dl+ dOmega+ dOmega- dOmega_r dq^2
    
    Particle nucRecoil(nucleus, eIn.p()+nucIn.p() - qpair - erecoil.p());

    double debugm2= (erecoil.p() +nucRecoil.p()).sq();
    if(fabs(debugm2 - recoilm2) > 1e-8 )
    {
        std::cerr << "BAD erecoil CALCULATION: debugm2=" << debugm2 << "vs. recoilm2 = " << recoilm2 << std:: endl;
    }
    
    if(! nucRecoil.onShell()) return false;
    
    e.addOutgoingParticle(nucRecoil);
    
    
    goodEvent=phaseSpace().passAcceptance(e);
    
    // Additional Jacobian factor
    double delta1Derivative = - modkprime/erecoil.E() - (modkprime -G/2)/nucRecoil.E();
    double delta2Derivative = - modlminus/minus.E() + (modlminus + B)/qpair.T();
    
    double overallJacobian = 1/(128*eIn.pabs()*nucleus.mass()*pow(2*PI,8)) *
                        pow(modkprime * modlminus,2)
                        /(nucRecoil.E()*erecoil.E()* qpair.T() * plus.E() * minus.E())
                        / fabs(delta1Derivative * delta2Derivative);
    
    e.scaleWeight(overallJacobian);
    
//    e.scaleWeight(matrixElement(e));
    
    return goodEvent;

}