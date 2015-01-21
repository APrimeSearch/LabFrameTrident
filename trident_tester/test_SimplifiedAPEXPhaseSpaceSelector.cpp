//
//  test_SimplifiedAPEXPhaseSpaceSelector.cpp
//  LabFrameTrident
//
//  Created by Natalia Toro on 2015-01-15.
//  Copyright (c) 2015 Natalia Toro. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include "SimplifiedAPEXPhaseSpaceSelector.h"
#include "constants.h"

using namespace std;

int test_SimplifiedAPEXPhaseSpaceSelector()
{
    
    ofstream angles;
    angles.open("/Users/Natalia/angles.dat");
    
    double Ebeam=2.0;
    int nev=200000;
    PhaseSpaceSelector* apex=SimplifiedAPEXPhaseSpaceSelector::apexOldReachSelector(Ebeam, Ebeam/2.);
    
    PhaseSpaceSelector* twopi=SimplifiedAPEXPhaseSpaceSelector::trivialAPEXstyleSelector(Ebeam);

    // Test average solid-angle weight of electrons as expected -- use empty event.
    double sumweightAPEXe=0; // Should average to about 0.004
    double sumweightAPEXe2=0; // 2nd electron: Should average to 2pi
    double sumweightAPEXmu=0; // Should average to 2pi
    double sumweightAPEXeFV=0; // Should average to sumweightAPEXe*(1.045^3-0.955^3)/3
    double sumweightAPEXmuFV=0; // Should average to 2pi
    double sumweightTWOPI; // Should average to 4pi
    double theta,phi,weight;
    FourVector myvector;
    
    Event e;
    FourVector ptest;
    apex->randomFourVectorWithinAcceptance(eminus, e, ptest, weight);
    e.addOutgoingParticle(Particle(eminus,ptest));
    
    cout << "Event e has " << e.finalStateMultiplicity(eminus) << " electrons" << endl;
    
    for(int iev=0;iev<nev; ++iev)
    {
        apex->randomUnitVectorWithinAngularAcceptance(eplus, e, theta, phi, weight);
        sumweightAPEXe+= weight;
        apex->randomFourVectorWithinAcceptance(eplus, e, myvector, weight);
        sumweightAPEXeFV+= weight;
        
        apex->randomUnitVectorWithinAngularAcceptance(eminus, e, theta, phi, weight);
        sumweightAPEXe2+= weight;
        
        twopi->randomUnitVectorWithinAngularAcceptance(eplus, e, theta, phi, weight);
        sumweightTWOPI+=weight;
        angles << theta << " " << weight << endl;
        
        apex->randomUnitVectorWithinAngularAcceptance(muplus, e, theta, phi, weight);
        sumweightAPEXmu+= weight;
        apex->randomFourVectorWithinAcceptance(muplus, e, myvector, weight);
        sumweightAPEXmuFV+= weight;
        
    }

    cout << " PI = " << PI << endl;
    
    cout << " APEX e omega/expected: " << sumweightAPEXe/nev/(0.017*0.037*4) << " (linearized) " << endl;

    cout << " APEX e2 omega/expected: " << sumweightAPEXe2/nev/(4*PI) << endl;
    cout << " APEX mu omega/expected: " << sumweightAPEXmu/nev/(4*PI) << endl;
    cout << " TWOPI omega/expected: " << sumweightTWOPI/nev/(2*PI) << endl;
    
    cout << " APEX e momentum/expected: " << sumweightAPEXeFV/sumweightAPEXe/((pow(1.045,3)-pow(0.955,3))/3) << endl;
    

    
    cout << " APEX mu momentum/expected: " << sumweightAPEXmuFV/sumweightAPEXmu/(pow(2.0,3)/3) << endl;
    
    
    // Test efficiency for events constructed to be within acceptance (Should be 100%)
    
    cout << " -- Now testing that events constructed to be within acceptance pass, and evaluating phase-space volume by MC -- " << endl;
 
    
    int fail=0, bfail=0, cfail=0;
    double maxweight=0, minweight=1000;
    double totalAA=0, totalAB=0, totalAC=0, totalBB=0, totalBC=0, totalCC=0;
    int statsAA=0, statsAB=0, statsAC=0, statsBB=0, statsBC=0, statsCC=0;
    
    
    // First check just the APEX acceptance.
    for(int iev=0;iev<nev; ++iev)
    {
        Event e1;
        FourVector pele1;
        FourVector ppos1;
        FourVector pele2;
        double weight;
        
        e1.setWeight(1);
        
        apex->randomFourVectorWithinAcceptance(eminus, e1, pele1, weight);
        
        e1.addOutgoingParticle(Particle(eminus,pele1));
        e1.scaleWeight(weight);
        
        apex->randomFourVectorWithinAcceptance(eplus, e1, ppos1, weight);
        e1.addOutgoingParticle(Particle(eplus,ppos1));
        e1.scaleWeight(weight);
        
        apex->randomFourVectorWithinAcceptance(eplus, e1, pele1, weight);
        e1.addOutgoingParticle(Particle(eminus,pele1));
        e1.scaleWeight(weight);
        
        if(apex->passAcceptance(e1)){
            totalAA += e1.weight()/nev;
            statsAA++;
        }
        else
        {
            fail++;
            cout  << " Failed Event " << endl << e1 << endl;
            apex->passAcceptance(e1,true);
        }
        
        if(e1.weight()<minweight) minweight=e1.weight();
        if(e1.weight()>maxweight) maxweight=e1.weight();
    }
 
    if(fail>0)
        cout << fail << " / " << nev << "APEX events rejected by APEX cuts (should be 0) " << endl;
    
    
//    Now look at wider acceptances
    PhaseSpaceSelector* b= new SimplifiedAPEXPhaseSpaceSelector(Ebeam, 0.01,0.2,0.1,0.06,Ebeam/2.);
    PhaseSpaceSelector* c= new SimplifiedAPEXPhaseSpaceSelector(Ebeam, 0.01,0.7,0.3,0.06,Ebeam/2.);
    
    // Now generate events in "b" acceptance...
    for(int iev=0;iev<nev; ++iev)
    {
        Event e1;
        FourVector pele1;
        FourVector ppos1;
        FourVector pele2;
        double weight;
        
        e1.setWeight(1);
        
        b->randomFourVectorWithinAcceptance(eminus, e1, pele1, weight);
        
        e1.addOutgoingParticle(Particle(eminus,pele1));
        e1.scaleWeight(weight);
        
        b->randomFourVectorWithinAcceptance(eplus, e1, ppos1, weight);
        e1.addOutgoingParticle(Particle(eplus,ppos1));
        e1.scaleWeight(weight);
        
        b->randomFourVectorWithinAcceptance(eplus, e1, pele1, weight);
        e1.addOutgoingParticle(Particle(eminus,pele1));
        e1.scaleWeight(weight);
        
        if(apex->passAcceptance(e1)){
            totalAB += e1.weight()/nev;
            statsAB++;
        }
        if(b->passAcceptance(e1)){
            totalBB += e1.weight()/nev;
            statsBB++;
        }
        else
        {
            bfail++;
        }
    }
    
    if(bfail>0) {
        cout << bfail << " / " << nev << "B events rejected by B cuts (should be 0) " << endl;
        return -1;
    }

    nev=2e8;
    // Now generate events in "c" acceptance...
    for(int iev=0;iev<nev; ++iev)
    {
        Event e1;
        FourVector pele1;
        FourVector ppos1;
        FourVector pele2;
        double weight;
        
        e1.setWeight(1);
        
        c->randomFourVectorWithinAcceptance(eminus, e1, pele1, weight);
        
        e1.addOutgoingParticle(Particle(eminus,pele1));
        e1.scaleWeight(weight);
        
        c->randomFourVectorWithinAcceptance(eplus, e1, ppos1, weight);
        e1.addOutgoingParticle(Particle(eplus,ppos1));
        e1.scaleWeight(weight);
        
        c->randomFourVectorWithinAcceptance(eplus, e1, pele1, weight);
        e1.addOutgoingParticle(Particle(eminus,pele1));
        e1.scaleWeight(weight);
        
        if(apex->passAcceptance(e1)){
            totalAC += e1.weight()/nev;
            statsAC++;
        }
        if(b->passAcceptance(e1)){
            totalBC += e1.weight()/nev;
            statsBC++;
        }
        if(c->passAcceptance(e1)){
            totalCC += e1.weight()/nev;
            statsCC++;
        }
        else
        {
            cfail++;
        }
    }
    
    if(cfail>0) {
        cout << cfail << " / " << nev << "C events rejected by C cuts (should be 0) " << endl;
        return -1;
    }

    // Volume results:
    cout << " A volume (stats) = A: " << totalAA << " (" << statsAA << ") " <<
                                "B: " << totalAB << " (" << statsAB << ") " <<
                                "C: " << totalAC << " (" << statsAC << ") " << endl;
    cout << " B volume (stats) = B: " << totalBB << " (" << statsBB << ") " <<
                                "C: " << totalBC << " (" << statsBC << ") " << endl;
    
    angles.close();
    
    return 0;
    
}