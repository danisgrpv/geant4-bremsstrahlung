//#define OuterSpectra
#define SingleEnergy

#ifndef TEMPLATE_PRIMARYGEN_HH
#define TEMPLATE_PRIMARYGEN_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4UniformRandPool.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4Electron.hh"
#include "G4Neutron.hh"
#include "G4Deuteron.hh"
#include "G4Alpha.hh"
#include "G4Triton.hh"
#include "map"
#include "vector"
#include "fstream"
#include "iostream"
#include "CommandMessenger.hh"
#include "DetGeometry.hh"
#include "math.h"


class DetGeometry;
using namespace std;

class G4ParticleGun;
class G4Event;
class PrimaryGenMessenger;

class PrimaryGen : public G4VUserPrimaryGeneratorAction
{
private:

   G4ParticleGun*  gun;

   G4GeneralParticleSource* GPSgun;

   PrimaryGenMessenger * primarygenmessenger;
   DetGeometry*fDetector;

#ifdef OuterSpectra
   map<G4double, G4double> *ew;
#endif

    public:
    PrimaryGen(DetGeometry*det);
    virtual ~PrimaryGen();
    virtual void GeneratePrimaries(G4Event*);

    void SetNewPatEn(G4double newValue)
    {
        U = newValue;
        gun->SetParticleEnergy(U*MeV);
    }

    G4double U = 14;

    G4String outerspectrapath = "../TestSpectra.txt";

};

#endif //TEMPLATE_PRIMARYGEN_HH
