//
//  SimplifiedAPEXPhaseSpaceSelector.cc
//  LabFrameTrident
//
//  Created by Natalia Toro on 2014-12-25.
//  Copyright (c) 2014 Natalia Toro. All rights reserved.
//

#include "SimplifiedAPEXPhaseSpaceSelector.h"

#include <random>
#include <vector>
#include "Particle.h"
#include "constants.h"

SimplifiedAPEXPhaseSpaceSelector::SimplifiedAPEXPhaseSpaceSelector(double pmax, double thetaxmin,double thetaxmax, double thetaymax, double deltapoverp, double p0):
thetaxmin_(thetaxmin),
thetaxmax_(thetaxmax),
thetaymax_(thetaymax),
p0_(p0),
deltap_(p0*0.045),
PhaseSpaceSelector(pmax)
{
}


/* randomUnitVectorWithinAngularAcceptance 
 
 Produces a unit vector (theta, phi) within an appropriate angular acceptance -- same prescription as randomFourVectorWithinAngularAcceptance.
 
 Following conventions of PhaseSpaceSelector::randomUnitVectorAnywhere, weighted events sample the integrand d(omega).  This is achieved by sampling uniformly in the planar angles thetax and thetay (angles from the z axis in the x-z and y-z planes, respectively) within the spectrometer window (or all solid angles) and weighting by the product of ranges in (thetax) and (thetay) times a Jacobian.
 For example, the sum of N events' weights should approach the total solid angle Omega.
 
 First two arguments (ptype, e) are input arguments used to determine acceptance.
 Last three arguments (theta, phi, selectionweight) are outputs.
 */
void SimplifiedAPEXPhaseSpaceSelector::randomUnitVectorWithinAngularAcceptance
    (const ParticleType &ptype,  // Input: particle type of the new particle
     const Event &e,             // Input: event to which one would add particle
     double &theta,              // Output: randomly generated particle's theta (angle from z)
     double &phi,                // Output: randomly generated particle's phi (polar angle in xy plane)
     double &dOmegaWeight)    // Output: weight (to sample dOmega)
const
{
    // Pick a point in solid-angle acceptance.  For the first positron and electron in event, we impose the spectrometer cuts.  For all other particles, we let the particle land anywhere.
    
    if(ptype == eplus && e.finalStateMultiplicity(eplus)==0)
        randomUnitVectorInSpectrometer(false, theta, phi, dOmegaWeight);
    else if(ptype == eminus && e.finalStateMultiplicity(eminus)==0)
        randomUnitVectorInSpectrometer(true, theta, phi, dOmegaWeight);
    else
        randomUnitVectorAnywhere(theta, phi, dOmegaWeight);
    return;
}

/* randomFourVectorWithinAngularAcceptance
 
 Produces a four-vector within an appropriate angular acceptance.
 
 The acceptance imposed depends on the particle type ptype and the existing content of the event e.
 
 - For positron, if e contains no positrons: Right spectrometer (calls randomFourVectorInSpectrometer)
 – For electron, if e contains no electrons: Left spectrometer (calls randomFourVectorInSpectrometer)
 – Otherwise: no acceptance imposed  (calls randomFourVectorAnywhere)

 This guarantees that, if electrons and positrons are randomly generated then added to the event, selector only requires the FIRST of each type to be in spectrometer  acceptance.
 
 Following conventions of PhaseSpaceSelector::randomFourVectorAnywhere, weighted events sample the integrand d(omega) p^2 dp.  
 This is achieved by sampling uniformly in the planar angles thetax and thetay (angles from the z axis in the x-z and y-z planes, respectively) within the spectrometer window (or all solid angles) and in d(p^3), weighting by the product of ranges in (thetax), (thetay), and (p^3) times a Jacobian.
 
 First two arguments (ptype, e) are input arguments used to determine acceptance.
 Last two arguments (v, selectionweight) are outputs.
 */
void SimplifiedAPEXPhaseSpaceSelector::randomFourVectorWithinAcceptance
(const ParticleType& ptype,          // Input: particle type
 const Event& e,                     // Input: event to which one would add particle
 FourVector& v,                      // Output: randomly selected four-vector
 double& dOmegaP2dPWeight) const     // Output: weight (to sample dOmega p^2 dp)
{

    if(ptype == eplus && e.finalStateMultiplicity(eplus)==0)
        randomFourVectorInSpectrometer(false, ptype.mass(), v, dOmegaP2dPWeight);
    else if(ptype == eminus && e.finalStateMultiplicity(eminus)==0)
        randomFourVectorInSpectrometer(true, ptype.mass(), v, dOmegaP2dPWeight);
    else
        randomFourVectorAnywhere(ptype.mass(), v, dOmegaP2dPWeight);
    return;
}


/* randomUnitVectorInSpectrometer
 
 Produces a unit vector (theta, phi) within a square angular acceptance box in thetax, thetay (the simplified spectrometer acceptance); the sign of thetax is determined by the Left argument.
 
 Following conventions of PhaseSpaceSelector::randomUnitVectorAnywhere, weighted events sample the integrand d(omega).  
 
 This is achieved by sampling uniformly in the planar angles thetax and thetay (angles from the z axis in the x-z and y-z planes, respectively) within the spectrometer window (or all solid angles) and weighting by the product of ranges in (thetax) and (thetay) times a Jacobian.
 For example, the sum of N events' weights should approach the total solid angle Omega.
 
 First argument (Left) is input arguments used to determine which spectrometer to use.
 Last three arguments (theta, phi, selectionweight) are outputs.
 */
void SimplifiedAPEXPhaseSpaceSelector::randomUnitVectorInSpectrometer
(bool Left,
 double& theta, double& phi,
 double& dOmegaWeight) const
{
    double thetay=scaledRandom(- thetaymax_, thetaymax_);
    
    double thetax=0;
    if(Left)
        thetax = scaledRandom(-thetaxmax_, -thetaxmin_);
    else
        thetax = scaledRandom(thetaxmin_, thetaxmax_);

    theta=atan2(sqrt(pow(tan(thetax),2)+pow(tan(thetay),2)),1);
    phi=atan2(tan(thetay), tan(thetax));

    // Jacobian:
    //      sintheta dtheta dphi = sintheta * |d(theta,phi)/d(thetax,thetay)| dthetax dthetay
    
    double Jacobian = pow(cos(theta),3)/(pow(cos(thetax),2)*pow(cos(thetay),2));
    
    dOmegaWeight = (2*thetaymax_) *               // y range
                      (thetaxmax_-thetaxmin_) *   // x range
                      Jacobian;           // jacobian to spherical coords
    

    return;
}

/* randomFourVectorInSpectrometer
 
 Produces a four-vector in the angular acceptance of randomUnitVectorInSpectrometer, with momentum in the range p0 +/- deltap.
 
 Following conventions of PhaseSpaceSelector::randomFourVectorAnywhere, weighted events sample the integrand d(omega) p^2 dp.
 This is achieved by sampling uniformly in the planar angles thetax and thetay (angles from the z axis in the x-z and y-z planes, respectively) within the spectrometer window (or all solid angles) and in d(p^3), weighting by the product of ranges in (thetax), (thetay), and (p^3) times a Jacobian.
 */
void SimplifiedAPEXPhaseSpaceSelector::randomFourVectorInSpectrometer
(bool Left,                 // Input: left spectrometer or right?
 double mass,               // Input: particle mass (to make 4-vector)
 FourVector& v,             // Output: randomly selected four-vector
 double& dOmegaP2dPWeight)  // Output: weight (to sample dOmega p^2 dp)
const
{
    double theta,phi,momentum, dOmegaWeight;
    randomUnitVectorInSpectrometer(Left, theta, phi, dOmegaWeight);
    
    double p3min,p3max;
    p3min=pow(p0_-deltap_,3);
    p3max=pow(p0_+deltap_,3);
    
    momentum=pow(scaledRandom(p3min,p3max), 1/3.);
    
    // int(p^2 dp) = p^3/3
    dOmegaP2dPWeight = dOmegaWeight * (p3max-p3min)/3.;
    
    v.setSphericalLength(mass, momentum, theta, phi);
    return;
}

/* passAcceptance
 
 Determines whether an event is within acceptance.
 Pass requires 
 - At least one electron and one positron in event.
 - First electron in its spectrometer acceptance
 - First positron in its spectrometer acceptance
 
 Called without second argument => debug = false
  */
bool SimplifiedAPEXPhaseSpaceSelector::passAcceptance(const Event &e, bool debug) const
{
    bool firstElectron=true, firstPositron=true, goodSoFar=true;
    bool foundBoth=false;
    
    for (std::vector<Particle>::const_iterator i=e.outgoingParticles().begin();
         i!=e.outgoingParticles().end() && goodSoFar && !foundBoth;
         ++i)
    {
        if(debug){
            cout << " @ particle " << i-e.outgoingParticles().begin()
        << " firstElectron=" << firstElectron <<  " firstPositron=" << firstPositron << std::endl;
        }
        
        if(i->ptype() == eplus && firstPositron)
        {
            goodSoFar = goodSoFar && inSpectrometer(false, i->p());
            firstPositron=false;
        }
        else if(i->ptype() == eminus && firstElectron)
        {
            goodSoFar = goodSoFar && inSpectrometer(true, i->p());
            firstElectron=false;
        }
        foundBoth= (firstElectron==false && firstPositron==false);
    }
   
    if(debug)
    {
        cout <<  "goodSoFar " << goodSoFar << " foundBoth " << foundBoth << std::endl;
    }
    
    return goodSoFar && foundBoth;
}


/* inSpectrometer
 
Helper function for passAcceptance -- checks whether individual momentum-vector is inside spectrometer acceptance.
 */
bool SimplifiedAPEXPhaseSpaceSelector::inSpectrometer(bool Left, const FourVector &p) const
{
    double thetax=atan2(p.X(), p.Z());
    double thetay=atan2(p.Y(), p.Z());
    
    //cout << " thetax " << thetax << " thetay " << thetay << " P " << p.len3() << std::endl;
    
    
    // Check horizontal angle
    if(Left) {
        if(thetax < - thetaxmax_ ||  thetax > - thetaxmin_) return false;
    }
    else {
        if(thetax < thetaxmin_ ||  thetax > thetaxmax_) return false;
    }

    // Check vertical angle
    if(thetay< - thetaymax_ || thetay > thetaymax_) return false;
    
    // Check momentum
    if(p.len3()<p0_ - deltap_ || p.len3()> p0_ + deltap_) return false;
    
    // If we got here, it passes!
    return true;
}


/////////////  Static Functions: Defining useful special cases /////////////


// "5degHRS" settings from LHEtoPGScut
SimplifiedAPEXPhaseSpaceSelector* SimplifiedAPEXPhaseSpaceSelector::apexOldReachSelector(double pmax, double p0)
{
    return new SimplifiedAPEXPhaseSpaceSelector(pmax, 0.089-0.017, 0.089+0.017, 0.037,  0.045, p0);
}

// Requires only that electron & positron be in left/right forward quadrants
SimplifiedAPEXPhaseSpaceSelector* SimplifiedAPEXPhaseSpaceSelector::hemisphereSelector(double pmax)
{
    return new SimplifiedAPEXPhaseSpaceSelector(pmax, 0, PI/2, PI/2, 1.0, pmax/2.);
}

// Trivial (forward hemisphere) selector
SimplifiedAPEXPhaseSpaceSelector* SimplifiedAPEXPhaseSpaceSelector::trivialAPEXstyleSelector(double pmax)
{
    return new SimplifiedAPEXPhaseSpaceSelector(pmax, -PI/2, PI/2, PI/2, 1.0, pmax/2.);
}



