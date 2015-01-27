//
//  test_TridentEventGenerator.cpp
//  LabFrameTrident
//
//  Created by Natalia Toro on 2015-01-26.
//  Copyright (c) 2015 Natalia Toro. All rights reserved.
//

#include <stdio.h>
#include "TridentEventGenerator.h"
#include "SimplifiedAPEXPhaseSpaceSelector.h"
#include "Event.h"

int test_TridentEventGenerator(int ntry)
{
    double Ebeam=2.0;
    PhaseSpaceSelector* apex=SimplifiedAPEXPhaseSpaceSelector::apexOldReachSelector(Ebeam, Ebeam/2.);
    
    TridentEventGenerator tri(*apex, 0.01, 1.0);
    
    int ngood=0;
    double minweight=99., maxweight=0.;
    for(int i=0; i<ntry ; i++)
    {
        Event ev;
        if(tri.tryEvent(Ebeam, Wpoint , ev))
        {
            ngood++;
            if(ev.weight() > maxweight)
                maxweight = ev.weight();
            if(ev.weight() < minweight)
                minweight = ev.weight();
            
/*            cout << " =========== < GOOD EVENT > ==============" << std::endl;
            cout << ev << std::endl;
            cout << " ----------- </good event > --------------" << std::endl;
*/
        }
        else
        {
/*
                cout << "*********** < BAD EVENT > **************" << std::endl;
                cout << ev << std::endl;
                cout << " ----------- </bad event > --------------" << std::endl;

 */
        }
    }
    cout << ngood << " out of " << ntry << " good events!" << std::endl;
    cout << " weight range " << minweight << " to " << maxweight << std::endl;
    return ngood;
}