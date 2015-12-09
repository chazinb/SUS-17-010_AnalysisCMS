#define AnalysisWW_cxx
#include "../include/AnalysisWW.h"


//------------------------------------------------------------------------------
// AnalysisWW
//------------------------------------------------------------------------------
AnalysisWW::AnalysisWW(TTree* tree) : AnalysisCMS(tree) {}


//------------------------------------------------------------------------------
// Loop
//------------------------------------------------------------------------------
void AnalysisWW::Loop(TString analysis, TString filename, float luminosity)
{
  if (fChain == 0) return;

  Setup(analysis, filename, luminosity);


  // Define histograms
  //----------------------------------------------------------------------------
  TH1::SetDefaultSumw2();

  for (int j=0; j<ncut; j++) {

    if (scut[j].Contains("Top/"))  continue;
    if (scut[j].Contains("TTDM/")) continue;
    if (scut[j].Contains("WZ/"))   continue;

    for (int k=0; k<=njetbin; k++) {

      TString sbin = (k < njetbin) ? Form("/%djet", k) : "";

      TString directory = scut[j] + sbin;

      root_output->cd();

      if (k < njetbin) gDirectory->mkdir(directory);

      root_output->cd(directory);

      for (int i=ee; i<=ll; i++) {

	TString suffix = "_" + schannel[i];

	DefineHistograms(i, j, k, suffix);

	h_metvar_m2l[i][j][k] = new TH2D("h_metvar_m2l" + suffix, "", 4, metvar_bins, 2000, 0, 200);
	h_jetpt1[i][j][k]     = new TH1D("h_jetpt1"     + suffix, "", 1000, 0., 1000.);
      }
    }
  }
  

  // Loop over events
  //----------------------------------------------------------------------------
  for (Long64_t jentry=0; jentry<_nentries;jentry++) {

    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;

    fChain->GetEntry(jentry);

    PrintProgress(jentry, _nentries);

    EventSetup();


    // Analysis
    //--------------------------------------------------------------------------
    if (!trigger) continue;

    if (Lepton1.flavour * Lepton2.flavour > 0) continue;

    if (Lepton1.v.Pt() < 20.) continue;
    if (Lepton2.v.Pt() < 20.) continue;

    _nlepton   = 2;  // Redefine _nlepton
    _nelectron = 0;  // Redefine _nelectron

    if (abs(Lepton1.flavour) == ELECTRON_FLAVOUR) _nelectron++;
    if (abs(Lepton2.flavour) == ELECTRON_FLAVOUR) _nelectron++;

    if      (_nelectron == 2) _channel = ee;
    else if (_nelectron == 1) _channel = em;
    else if (_nelectron == 0) _channel = mm;
    
    _m2l  = mll;
    _pt2l = ptll;


    // Fill histograms
    //--------------------------------------------------------------------------
    bool pass = true;

    FillLevelHistograms(WW_00_Has2Leptons, pass);

    pass &= (mll > 12.);
    FillLevelHistograms(WW_01_Mll, pass);

    pass &= (MET.Et() > 20.);
    FillLevelHistograms(WW_02_PfMet, pass);

    bool pass_zveto = (_nelectron == 1 || _nelectron != 1 && _metvar > 45. && fabs(mll - Z_MASS) > 15.);

    FillLevelHistograms(WW_03_ZVeto, pass && pass_zveto);

    pass &= (_mpmet > 20.);
    FillLevelHistograms(WW_04_MpMet, pass && pass_zveto);

    //pass &= (_passdphiveto);
    FillLevelHistograms(WW_05_DPhiVeto, pass && pass_zveto);

    bool pass_ptll = (_nelectron == 1 && ptll > 30. || _nelectron != 1 && ptll > 45.);

    pass &= pass_ptll;
    FillLevelHistograms(WW_06_Ptll, pass && pass_zveto);

    pass &= (_nbjet15 == 0);
    FillLevelHistograms(WW_07_BVeto, pass && pass_zveto);

    pass &= (!_foundsoftmuon);
    FillLevelHistograms(WW_08_SoftMu, pass && pass_zveto);

    bool pass_ht = (_ht < 250.);
    FillLevelHistograms(WW_09_Ht, pass && pass_zveto && pass_ht);
    
    FillLevelHistograms(WW_10_DY, pass);  // Data-driven DY

    bool passZwindow = (fabs(mll - Z_MASS) < 15.);  // Z window at 2 leptons level
    FillLevelHistograms(WW_11_ZWindow, passZwindow);

    passZwindow &= (MET.Et() > 20.);
    FillLevelHistograms(WW_12_ZWindowPfMet, passZwindow);

    passZwindow &= (_mpmet > 20.);
    FillLevelHistograms(WW_13_ZWindowMpMet, passZwindow);

    passZwindow &= (pass_ptll);
    FillLevelHistograms(WW_14_ZWindowPtll, passZwindow);

    bool Jet[12];
    
    for (UInt_t j=0; j<12; ++j)
      {
	Jet[j] = (std_vector_jet_pt->at(0) < 25 + j);
	FillLevelHistograms(WW_18_ZWindow25 + j, passZwindow && pass_ptll && Jet[j]);
      }

    passZwindow &= (_nbjet15 == 0);
    FillLevelHistograms(WW_15_ZWindowBVeto, passZwindow);

    passZwindow &= (!_foundsoftmuon);
    FillLevelHistograms(WW_16_ZWindowSoftMu, passZwindow);
    
    FillLevelHistograms(WW_17_ZCR, pass && pass_ht && passZwindow);  // Z control region - orthogonal to WW one


    // monoH selection - on top of WW excluding Ht selection
    //----------------------------------------------------------------------------
    bool pass_monoh = (pass && pass_zveto);
    bool pass_drll  = (Lepton1.v.DeltaR(Lepton2.v) < 1.5);

    FillLevelHistograms(monoH_80_CR, pass_monoh && !pass_drll);
    
    pass_monoh &= (_mc < 100);
    FillLevelHistograms(monoH_00_Mc, pass_monoh);
    
    pass_monoh &= pass_drll;
    FillLevelHistograms(monoH_01_DRll, pass_monoh);
    
    pass_monoh &= (_mpmet > 60);
    FillLevelHistograms(monoH_02_MpMet, pass_monoh);
  }


  EndJob();
}


//------------------------------------------------------------------------------
// FillAnalysisHistograms
//------------------------------------------------------------------------------
void AnalysisWW::FillAnalysisHistograms(int ichannel,
					int icut,
					int ijet)
{
  h_metvar_m2l[ichannel][icut][ijet]->Fill(_metvar, _m2l,            _event_weight);
  h_jetpt1[ichannel][icut][ijet]    ->Fill(std_vector_jet_pt->at(0), _event_weight);

  if (ichannel != ll) FillAnalysisHistograms(ll, icut, ijet);
}


//------------------------------------------------------------------------------
// FillLevelHistograms
//------------------------------------------------------------------------------
void AnalysisWW::FillLevelHistograms(int  icut,
				     bool pass)
{
  if (!pass) return;

  FillHistograms(_channel, icut, _jetbin);
  FillHistograms(_channel, icut, njetbin);

  FillAnalysisHistograms(_channel, icut, _jetbin);
  FillAnalysisHistograms(_channel, icut, njetbin);
}