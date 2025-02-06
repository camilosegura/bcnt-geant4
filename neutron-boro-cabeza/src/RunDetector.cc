#include "RunDetector.hh"

RunDetector::RunDetector(/* args */)
{
}

RunDetector::~RunDetector()
{
}

void RunDetector::BeginOfRunAction(const G4Run *)
{
    // G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // analysisManager->Reset();

    // analysisManager->OpenFile("bio-3-project.root");

    // analysisManager->CreateNtuple("Hits", "Hits");
    // analysisManager->CreateNtupleIColumn("fEvent");
    // analysisManager->CreateNtupleDColumn("fX");
    // analysisManager->CreateNtupleDColumn("fY");
    // analysisManager->CreateNtupleDColumn("fZ");
    // // analysisManager->CreateNtupleDColumn("fEnergy");
    // analysisManager->FinishNtuple(0);
    // analysisManager->CreateH1("EnergyDeposit", "Energía depositada (keV)", 100, 0., 10.); // 100 bins, rango de 0 a 10 keV
    // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // // Crear histogramas para cada tejido
    // analysisManager->CreateH1("Tejido1", "Energía depositada en Tejido 1", 100, 0., 1000.); // keV
    // analysisManager->CreateH1("Tejido2", "Energía depositada en Tejido 2", 100, 0., 1000.); // keV
    // analysisManager->CreateH1("Tejido3", "Energía depositada en Tejido 3", 100, 0., 1000.); // keV
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    
    // analysisManager->Reset();
    // Abrir el archivo de salida
    if (analysisManager) {
        analysisManager->Reset();
        // Abrir el archivo de salida
        analysisManager->OpenFile("bio-3-project.root");

        // Crear histogramas para cada tejido
        analysisManager->CreateH1("Brain", "Energía depositada en Cerebro", 100, 0., 1000.); // keV
        analysisManager->CreateH1("Skull", "Energía depositada en Cráneo", 100, 0., 1000.); // keV
        analysisManager->CreateH1("Skin", "Energía depositada en Piel", 100, 0., 1000.); // keV
    }
    
}

void RunDetector::EndOfRunAction(const G4Run *)
{
    // G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // analysisManager->Write();
    // analysisManager->CloseFile(false);
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
   // Add error checking
    if (analysisManager) {
        analysisManager->Write();
        analysisManager->CloseFile(false);
    }
}