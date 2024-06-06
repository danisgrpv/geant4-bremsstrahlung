#ifndef TEMPLATE_DETGEOMETRY_HH
#define TEMPLATE_DETGEOMETRY_HH

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VUserDetectorConstruction.hh"
#include "PrimaryGen.hh"
#include "CommandMessenger.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class GeometryMessenger;

class DetGeometry  : public G4VUserDetectorConstruction
{
private:

    virtual G4VPhysicalVolume*  Construct();
    G4VPhysicalVolume*          physWorld;
    GeometryMessenger *geometryMessenger;

public:
    DetGeometry();
    virtual ~DetGeometry();
    void SetNewMat(G4String newName);
    void SetNewSize(G4double newSize);
    G4String material_name = "G4_C";
    G4double R_size = 5;
};

#endif //TEMPLATE_DETGEOMETRY_HH


