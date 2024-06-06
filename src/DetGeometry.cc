#include "DetGeometry.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "CommandMessenger.hh"
#include "G4GeometryManager.hh"
#include "CADMesh.hh"


DetGeometry::DetGeometry()
{
    geometryMessenger = new GeometryMessenger(this);
}

DetGeometry::~DetGeometry()
{
    delete geometryMessenger;
}

G4VPhysicalVolume* DetGeometry::Construct(){

    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4NistManager* nist = G4NistManager::Instance();

    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");


    G4Box* solidWorld = new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume*logicWorld = new G4LogicalVolume(solidWorld, world_mat,"World");
    G4VisAttributes*nva = new G4VisAttributes();
    nva->SetVisibility(false);
    logicWorld->SetVisAttributes(nva);
    G4VPhysicalVolume* physWorld =
            new G4PVPlacement(0,
                              G4ThreeVector(),
                              logicWorld,
                              "World",
                              0,
                              false,
                              0);

    //define materials

    G4Material*mat_1 = nist->FindOrBuildMaterial("G4_Ta");
    G4Material*mat_2 = nist->FindOrBuildMaterial("G4_Galactic");

    //define distances

    G4double tube_R = R_size;

    //define body number 1
    G4ThreeVector Body_No_1_pos = G4ThreeVector(0, 0, 0);
    G4Tubs*Body_No_1 = new G4Tubs("Body_No_1", 0*cm, 2*cm, 0.01*cm, 0*deg, 360*deg);
    G4LogicalVolume*logicBody_No_1 = new G4LogicalVolume(Body_No_1, mat_1, "Body_No_1");

    new G4PVPlacement(0,
                      Body_No_1_pos,
                      logicBody_No_1,
                      "Body_No_1",
                      logicWorld,
                      false,
                      0);

    //define body number 2
    G4RotationMatrix*myRotation = new G4RotationMatrix();
    myRotation->rotateX(0*deg);
    myRotation->rotateY(45*deg);
    myRotation->rotateZ(45*deg);

    G4ThreeVector Body_No_2_pos = G4ThreeVector(0, 0, 0);
    G4Sphere*Body_No_2 = new G4Sphere("Body_No_2", 6*cm, 6.5*cm, 0*deg, 360*deg, 0*deg, 180*deg);
    G4LogicalVolume*logicBody_No_2 = new G4LogicalVolume(Body_No_2, mat_2, "Body_No_2");

    new G4PVPlacement(myRotation,
                      Body_No_2_pos,
                      logicBody_No_2,
                      "Body_No_2",
                      logicWorld,
                      false,
                      0);

    return physWorld;
}

void DetGeometry::SetNewMat(G4String newName) {
    material_name = newName;
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void DetGeometry::SetNewSize(G4double newSize) {
    R_size = newSize;
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}
