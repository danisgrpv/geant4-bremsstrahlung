#include "PrimaryGen.hh"
#include "G4RandomTools.hh"
#include "G4SystemOfUnits.hh"
#include "G4NuclideTable.hh"
#include "vector"

using namespace std;

class PrimaryGenMessenger;


PrimaryGen::PrimaryGen(DetGeometry*det):fDetector(det)
{
    primarygenmessenger = new PrimaryGenMessenger(this);

    gun = new G4ParticleGun();
    gun->SetParticleDefinition(G4Electron::Electron());

    gun->SetNumberOfParticles(1);

//   GPSgun = new G4GeneralParticleSource();

#ifdef SingleEnergy
    //    gun->SetParticleEnergy(U*MeV);
      gun->SetParticleEnergy(0.8*MeV);
#endif

#ifdef OuterSpectra
    ew = new map <G4double, G4double>;

    G4int FileSize=0;
    ifstream file;
    file.open(outerspectrapath);
    string line;
    while (getline(file, line))
    {
        FileSize++;
    }
    file.close();

    G4double P;
    G4double E;
    G4double **Spectr = new G4double*[FileSize];
    for(G4int count =0; count <FileSize; count++)
    {
        Spectr[count] = new G4double [2];
    }
    G4double  K=0;
    G4double  * Pspectr = new G4double[FileSize];
    G4double * Pnorm = new G4double [FileSize];

    ifstream file1;
    file1.open(outerspectrapath);
    for (int i = 0; i < FileSize; i++)
    {
        file1 >> E >> P;
        Spectr[i][1] = E;
        Spectr[i][2] = P;
    }
    file1.close();

    for (int i=0; i<FileSize; i++)
    {
        K = K+Spectr[i][2];
        Pspectr[i] = K;
    }

    for (int i = 0; i < FileSize; i++)
    {
        Pnorm[i] = Pspectr[i]/K;
        ew->insert(std::pair<G4double, G4double> (Pnorm[i], Spectr[i][1]));
    }

    for (int count=0; count<FileSize;count++)
    { delete [] Spectr[count];}

    delete [] Pnorm;
    delete [] Pspectr;
#endif
}

PrimaryGen::~PrimaryGen()
{
#ifdef OuterSpectra
    delete ew;
#endif

    delete gun;
//delete GPSgun;
    delete primarygenmessenger;
}

void PrimaryGen::GeneratePrimaries(G4Event* anEvent)
{

#ifdef OuterSpectra
    G4double rand = G4UniformRand();

    map<G4double, G4double>::iterator it=ew->lower_bound(rand);

    gun->SetParticleEnergy(it->second*MeV);
#endif

//    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(92,235,0);
//    gun->SetParticleDefinition(ion);

    gun->SetParticlePosition(G4ThreeVector(0,0,1*cm));

    double dX, dY, dZ;
    G4double cosTheta;
    G4double sinTheta;
    G4double phi;

    cosTheta = 0.125*G4UniformRand()-1, phi = twopi*G4UniformRand();
    sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    dX = sinTheta*std::cos(phi),
    dY = sinTheta*std::sin(phi),
    dZ = cosTheta;
    gun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1));

    gun->GeneratePrimaryVertex(anEvent);

//    GPSgun->GeneratePrimaryVertex(anEvent);
}