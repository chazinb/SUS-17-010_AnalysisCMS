const float   zmin =  76;  // [GeV]
const float   zmax = 106;  // [GeV]

int bin_zmin;
int bin_zmax;

int bin_ele_ptmin;
int bin_ele_ptmax;

int bin_muon_ptmin;
int bin_muon_ptmax;

void getLumiEff()
{

  gInterpreter->ExecuteMacro("../test/PaperStyle.C");

  TFile*  data  = new TFile ("../rootfiles/nominal/FR/01_Data.root","read");
  //  TFile*  tt = new TFile ("../rootfiles/nominal/FR/06_TT.root","read");
  TFile*  zjets = new TFile ("../rootfiles/nominal/FR/07_ZJets.root","read");
  TFile*  wjets  = new TFile ("../rootfiles/nominal/FR/08_WJets.root","read");

  float muonjetet = 20.;
  float elejetet = 35.;

  TString muonsuffix = Form("_%.0fGev", muonjetet);
  TString elesuffix = Form("_%.0fGev", elejetet);

  // DATA

  TH2D* h2_Ele_loose_pt_m2l_ZRegion  = (TH2D*) data -> Get("FR/03_ZRegion/h_Ele_loose_pt_m2l"  + elesuffix);
  TH2D* h2_Ele_tight_pt_m2l_ZRegion  = (TH2D*) data -> Get("FR/03_ZRegion/h_Ele_tight_pt_m2l"  + elesuffix);
  TH2D* h2_Muon_loose_pt_m2l_ZRegion = (TH2D*) data -> Get("FR/03_ZRegion/h_Muon_loose_pt_m2l" + muonsuffix);
  TH2D* h2_Muon_tight_pt_m2l_ZRegion = (TH2D*) data -> Get("FR/03_ZRegion/h_Muon_tight_pt_m2l" + muonsuffix);

  /*
  bin_ele_ptmin = -1;
  bin_ele_ptmax = h2_Ele_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(25.) - 1;
  */
       
  bin_ele_ptmin = h2_Ele_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(25.);
  bin_ele_ptmax = -1;
  
  /*
  bin_muon_ptmin = -1;  
  bin_muon_ptmax = h2_Muon_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(20.) - 1;
  */
  
  bin_muon_ptmin = h2_Muon_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(20.);
  bin_muon_ptmax = -1;
    

  TH1D* h_Ele_loose_m2l_ZRegion  = (TH1D*) h2_Ele_loose_pt_m2l_ZRegion  -> ProjectionX("Ele loose m2l data",  bin_ele_ptmin,  bin_ele_ptmax);
  TH1D* h_Ele_tight_m2l_ZRegion  = (TH1D*) h2_Ele_tight_pt_m2l_ZRegion  -> ProjectionX("Ele tight m2l data",  bin_ele_ptmin,  bin_ele_ptmax);
  TH1D* h_Muon_loose_m2l_ZRegion = (TH1D*) h2_Muon_loose_pt_m2l_ZRegion -> ProjectionX("Muon loose m2l data", bin_muon_ptmin, bin_muon_ptmax);
  TH1D* h_Muon_tight_m2l_ZRegion = (TH1D*) h2_Muon_tight_pt_m2l_ZRegion -> ProjectionX("Muon tight m2l data", bin_muon_ptmin, bin_muon_ptmax);
 
  // ZJETS

  TH2D* h2_Ele_loose_pt_m2l_ZRegion_zjets  = (TH2D*) zjets -> Get("FR/03_ZRegion/h_Ele_loose_pt_m2l"  + elesuffix);
  TH2D* h2_Ele_tight_pt_m2l_ZRegion_zjets  = (TH2D*) zjets -> Get("FR/03_ZRegion/h_Ele_tight_pt_m2l"  + elesuffix);
  TH2D* h2_Muon_loose_pt_m2l_ZRegion_zjets = (TH2D*) zjets -> Get("FR/03_ZRegion/h_Muon_loose_pt_m2l" + muonsuffix);
  TH2D* h2_Muon_tight_pt_m2l_ZRegion_zjets = (TH2D*) zjets -> Get("FR/03_ZRegion/h_Muon_tight_pt_m2l" + muonsuffix);
  
  /*
  bin_ele_ptmin = -1;
  bin_ele_ptmax = h2_Ele_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(25.) - 1;
  */
  
  bin_ele_ptmin = h2_Ele_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(25.);
  bin_ele_ptmax = -1;
  
  /*
  bin_muon_ptmin = -1;
  bin_muon_ptmax = h2_Muon_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(20.) - 1;
  */
  
  bin_muon_ptmin = h2_Muon_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(20.);
  bin_muon_ptmax = -1;
  

  TH1D* h_Ele_loose_m2l_ZRegion_zjets  = (TH1D*) h2_Ele_loose_pt_m2l_ZRegion_zjets  -> ProjectionX("Ele loose m2l zjets",  bin_ele_ptmin,  bin_ele_ptmax);
  TH1D* h_Ele_tight_m2l_ZRegion_zjets  = (TH1D*) h2_Ele_tight_pt_m2l_ZRegion_zjets  -> ProjectionX("Ele tight m2l zjets",  bin_ele_ptmin,  bin_ele_ptmax);
  TH1D* h_Muon_loose_m2l_ZRegion_zjets = (TH1D*) h2_Muon_loose_pt_m2l_ZRegion_zjets -> ProjectionX("Muon loose m2l zjets", bin_muon_ptmin, bin_muon_ptmax);
  TH1D* h_Muon_tight_m2l_ZRegion_zjets = (TH1D*) h2_Muon_tight_pt_m2l_ZRegion_zjets -> ProjectionX("Muon tight m2l zjets", bin_muon_ptmin, bin_muon_ptmax);

  // WJETS

  TH2D* h2_Ele_loose_pt_m2l_ZRegion_wjets  = (TH2D*) wjets -> Get("FR/03_ZRegion/h_Ele_loose_pt_m2l"  + elesuffix);
  TH2D* h2_Ele_tight_pt_m2l_ZRegion_wjets  = (TH2D*) wjets -> Get("FR/03_ZRegion/h_Ele_tight_pt_m2l"  + elesuffix);
  TH2D* h2_Muon_loose_pt_m2l_ZRegion_wjets = (TH2D*) wjets -> Get("FR/03_ZRegion/h_Muon_loose_pt_m2l" + muonsuffix);
  TH2D* h2_Muon_tight_pt_m2l_ZRegion_wjets = (TH2D*) wjets -> Get("FR/03_ZRegion/h_Muon_tight_pt_m2l" + muonsuffix);

  /*
  bin_ele_ptmin = -1;
  bin_ele_ptmax = h2_Ele_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(25.) - 1;
  */
  
  bin_ele_ptmin = h2_Ele_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(25.);
  bin_ele_ptmax = -1;
  
  /*   
  bin_muon_ptmin = -1; 
  bin_muon_ptmax = h2_Muon_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(20.) - 1;
  */
  
  bin_muon_ptmin = h2_Muon_tight_pt_m2l_ZRegion -> ProjectionY() -> FindBin(20.);
  bin_muon_ptmax = -1;
  
  TH1D* h_Ele_loose_m2l_ZRegion_wjets  = (TH1D*) h2_Ele_loose_pt_m2l_ZRegion_wjets  -> ProjectionX("Ele loose m2l wjets",  bin_ele_ptmin,  bin_ele_ptmax);
  TH1D* h_Ele_tight_m2l_ZRegion_wjets  = (TH1D*) h2_Ele_tight_pt_m2l_ZRegion_wjets  -> ProjectionX("Ele tight m2l wjets",  bin_ele_ptmin,  bin_ele_ptmax);
  TH1D* h_Muon_loose_m2l_ZRegion_wjets = (TH1D*) h2_Muon_loose_pt_m2l_ZRegion_wjets -> ProjectionX("Muon loose m2l wjets", bin_muon_ptmin, bin_muon_ptmax);
  TH1D* h_Muon_tight_m2l_ZRegion_wjets = (TH1D*) h2_Muon_tight_pt_m2l_ZRegion_wjets -> ProjectionX("Muon tight m2l wjets", bin_muon_ptmin, bin_muon_ptmax);

  bin_zmin = h_Ele_loose_m2l_ZRegion->FindBin(zmin);
  bin_zmax = h_Ele_loose_m2l_ZRegion->FindBin(zmax);

  // Effective luminosity calculation

  printf("============ Datos ============ \n \n");

  float ele_loose_data =  h_Ele_loose_m2l_ZRegion -> Integral(bin_zmin, bin_zmax);
  float ele_tight_data = h_Ele_tight_m2l_ZRegion -> Integral(bin_zmin, bin_zmax);
  float muon_loose_data = h_Muon_loose_m2l_ZRegion -> Integral(bin_zmin, bin_zmax);
  float muon_tight_data = h_Muon_tight_m2l_ZRegion -> Integral(bin_zmin, bin_zmax);

  printf("Loose electrons in the Z window = %.0f \n", ele_loose_data);
  printf("Tight electrons in the Z window = %.0f \n", ele_tight_data);
  printf("Loose muons in the Z window = %.0f \n", muon_loose_data);
  printf("Tight muons in the Z window = %.0f \n \n", muon_tight_data);
  
  printf("============ TT ============ \n \n");

  float ele_loose_tt = 0.;
  float ele_tight_tt = 0.;
  float muon_loose_tt = 0.;
  float muon_tight_tt = 0.;
  /*
  float ele_loose_tt = h_Ele_loose_m2l_ZRegion_tt -> Integral(bin_zmin, bin_zmax);
  float ele_tight_tt = h_Ele_tight_m2l_ZRegion_tt -> Integral(bin_zmin, bin_zmax);
  float muon_loose_tt = h_Muon_loose_m2l_ZRegion_tt -> Integral(bin_zmin, bin_zmax);
  float muon_tight_tt = h_Muon_tight_m2l_ZRegion_tt -> Integral(bin_zmin, bin_zmax);

  printf("Loose electrons in the Z window = %.0f \n", ele_loose_tt);
  printf("Tight electrons in the Z window = %.0f \n", ele_tight_tt);
  printf("Loose muons in the Z window = %.0f \n", muon_loose_tt);
  printf("Tight muons in the Z window = %.0f \n \n", muon_tight_tt);
  */
  printf("============ ZJets ============ \n \n");

  float ele_loose_zjets =  h_Ele_loose_m2l_ZRegion_zjets -> Integral(bin_zmin, bin_zmax);
  float ele_tight_zjets = h_Ele_tight_m2l_ZRegion_zjets -> Integral(bin_zmin, bin_zmax);
  float muon_loose_zjets = h_Muon_loose_m2l_ZRegion_zjets -> Integral(bin_zmin, bin_zmax);
  float muon_tight_zjets = h_Muon_tight_m2l_ZRegion_zjets -> Integral(bin_zmin, bin_zmax);

  printf("Loose electrons in the Z window = %.0f \n", ele_loose_zjets);
  printf("Tight electrons in the Z window = %.0f \n", ele_tight_zjets);
  printf("Loose muons in the Z window = %.0f \n", muon_loose_zjets);
  printf("Tight muons in the Z window = %.0f \n \n", muon_tight_zjets);
  
  printf("============ WJets ============ \n \n");

  float ele_loose_wjets = h_Ele_loose_m2l_ZRegion_wjets -> Integral(bin_zmin, bin_zmax);
  float ele_tight_wjets = h_Ele_tight_m2l_ZRegion_wjets -> Integral(bin_zmin, bin_zmax);
  float muon_loose_wjets = h_Muon_loose_m2l_ZRegion_wjets -> Integral(bin_zmin, bin_zmax);
  float muon_tight_wjets = h_Muon_tight_m2l_ZRegion_wjets -> Integral(bin_zmin, bin_zmax);

  printf("Loose electrons in the Z window = %.0f \n", ele_loose_wjets);
  printf("Tight electrons in the Z window = %.0f \n", ele_tight_wjets);
  printf("Loose muons in the Z window = %.0f \n", muon_loose_wjets);
  printf("Tight muons in the Z window = %.0f \n \n", muon_tight_wjets);

  float lum_ele_loose = 0.;
  float lum_ele_tight = 0.;
  float lum_muon_loose = 0.;
  float lum_muon_tight = 0.;

  lum_ele_loose = 1000. * ele_loose_data / (ele_loose_tt + ele_loose_zjets + ele_loose_wjets);
  lum_ele_tight = 1000. * ele_tight_data / (ele_tight_tt + ele_tight_zjets + ele_tight_wjets);
  lum_muon_loose = 1000. * muon_loose_data / (muon_loose_tt + muon_loose_zjets + muon_loose_wjets);
  lum_muon_tight = 1000. * muon_tight_data / (muon_tight_tt + muon_tight_zjets + muon_tight_wjets);

  printf("===================== Effective luminosity ===================== \n \n");
	
  printf("Effective luminosity in electrons loose = %f pb \n", lum_ele_loose);
  printf("Effective luminosity in electrons tight = %f pb \n \n", lum_ele_tight);
  printf("Effective luminosity in muons loose = %f pb \n", lum_muon_loose);
  printf("Effective luminosity in muons tight = %f pb \n \n", lum_muon_tight);

}






// BACKUP

  /*
  TH1D* h_Muon_loose_m2l_ZRegion = (TH1D*) data -> Get("FR/03_ZRegion/h_Muon_loose_m2l" + muonsuffix);
  TH1D* h_Muon_tight_m2l_ZRegion = (TH1D*) data -> Get("FR/03_ZRegion/h_Muon_tight_m2l" + muonsuffix);
  TH1D* h_Ele_loose_m2l_ZRegion = (TH1D*) data -> Get("FR/03_ZRegion/h_Ele_loose_m2l" + elesuffix);
  TH1D* h_Ele_tight_m2l_ZRegion = (TH1D*) data -> Get("FR/03_ZRegion/h_Ele_tight_m2l" + elesuffix);
  

  TH1D* h_Muon_loose_m2l_ZRegion_tt = (TH1D*) tt -> Get("FR/03_ZRegion/h_Muon_loose_m2l" + muonsuffix);
  TH1D* h_Muon_tight_m2l_ZRegion_tt = (TH1D*) tt -> Get("FR/03_ZRegion/h_Muon_tight_m2l" + muonsuffix);
  TH1D* h_Ele_loose_m2l_ZRegion_tt = (TH1D*) tt -> Get("FR/03_ZRegion/h_Ele_loose_m2l" + elesuffix);
  TH1D* h_Ele_tight_m2l_ZRegion_tt = (TH1D*) tt -> Get("FR/03_ZRegion/h_Ele_tight_m2l" + elesuffix);
  
  TH1D* h_Muon_loose_m2l_ZRegion_zjets = (TH1D*) zjets -> Get("FR/03_ZRegion/h_Muon_loose_m2l" + muonsuffix);
  TH1D* h_Muon_tight_m2l_ZRegion_zjets = (TH1D*) zjets -> Get("FR/03_ZRegion/h_Muon_tight_m2l" + muonsuffix);
  TH1D* h_Ele_loose_m2l_ZRegion_zjets = (TH1D*) zjets -> Get("FR/03_ZRegion/h_Ele_loose_m2l" + elesuffix);
  TH1D* h_Ele_tight_m2l_ZRegion_zjets = (TH1D*) zjets -> Get("FR/03_ZRegion/h_Ele_tight_m2l" + elesuffix);

  TH1D* h_Muon_loose_m2l_ZRegion_wjets = (TH1D*) wjets -> Get("FR/03_ZRegion/h_Muon_loose_m2l" + muonsuffix);
  TH1D* h_Muon_tight_m2l_ZRegion_wjets = (TH1D*) wjets -> Get("FR/03_ZRegion/h_Muon_tight_m2l" + muonsuffix);
  TH1D* h_Ele_loose_m2l_ZRegion_wjets = (TH1D*) wjets -> Get("FR/03_ZRegion/h_Ele_loose_m2l" + elesuffix);
  TH1D* h_Ele_tight_m2l_ZRegion_wjets = (TH1D*) wjets -> Get("FR/03_ZRegion/h_Ele_tight_m2l" + elesuffix);
  */
