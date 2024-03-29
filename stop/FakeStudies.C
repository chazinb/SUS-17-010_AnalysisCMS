#include "TInterpreter.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TPaletteAxis.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TDirectory.h"
#include <fstream>
#include <iostream>


void FakeStudies(TString Selection, TString channel) {

  const int nChannels = 4, nVariables = 1, nMetCuts = 1, nBtagCuts = 1;
  TString Channel[nChannels] = {"_ee", "_mm", "_em", "_ll"};
  TString Variable[nVariables] = {"MT2ll"};
  //TString MetCut[nMetCuts] = {"02_VR1", "02_SR1", "02_SR2", "02_SR3"};
  TString MetCut[nMetCuts] = {"02_SR1_Tag"};
  TString BtagCut[nBtagCuts] = {"_Veto"};

  gSystem->mkdir("FakesPlots", kTRUE); 
 // gSystem->Exec("cp  ./index.php ./FakesPlots/; done");
//  gSystem->Exec("for dir in $(find ./FakesPlots/ -type d); do cp -n ./index.php $dir/; done");
 
  TString RootFileName = "";
  if (Selection=="ttbar") RootFileName = "../minitrees/rootfiles/nominal/Stop/04_TTTo2L2Nu.root";
  if (Selection=="WW")    RootFileName = "../minitrees/rootfiles/nominal/Stop/06_WW.root";
  if (Selection=="ST")    RootFileName = "../minitrees/rootfiles/nominal/Stop/05_ST.root";
  if (Selection=="ZJets") RootFileName = "../minitrees/rootfiles/nominal/Stop/07_ZJetsHT.root";

  if (RootFileName=="") return;

  TFile *RootFile = TFile::Open(RootFileName);
  //TFile *RootFile = TFile::Open(RootFileName);

  TCanvas *CC = new TCanvas("CC", "", 900, 600); 
  CC->Divide(2, 2);

  TCanvas *CL = new TCanvas("CL", "", 900, 800); 
  CL->Divide(1, 2);
  
  TPad *PadC1 = (TPad*)CC->GetPad(1);
  //TPad *PadC2 = (TPad*)CC->GetPad(2);
  //TPad *PadC4 = (TPad*)CC->GetPad(3);
  //TPad *PadC3 = (TPad*)CC->GetPad(4);
  
  //TPad *PadL1 = (TPad*)CL->GetPad(1); 
  TPad *PadL1 = new TPad("PadL1", "", 0.02, 0.27, 0.98, 0.98, 21);
  PadL1->SetLogy(); 
  TPad *PadL2 = new TPad("PadL2", "", 0.02, 0.09, 0.98, 0.33, 21);
  //TPad *PadL2 = (TPad*)CL->GetPad(2); PadL2->SetLogy();
  //TPad *PadL3 = (TPad*)CL->GetPad(3); PadL3->SetLogy();
  //TPad *PadL4 = (TPad*)CL->GetPad(4); PadL4->SetLogy();

    // Run2015B Setting
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    CC->Range(0,0,1,1);
    CC->SetFillColor(10);
    CC->SetBorderMode(0);
    CC->SetBorderSize(2);
    CC->SetTickx(1);
    CC->SetTicky(1);
    CC->SetLeftMargin(0.16);
    CC->SetRightMargin(0.02);
    CC->SetTopMargin(0.05);
    CC->SetBottomMargin(0.13);
    CC->SetFrameFillColor(0);
    CC->SetFrameFillStyle(0);
    CC->SetFrameBorderMode(0);

    PadL1->SetFillColor(0);
    PadL1->SetBorderMode(0);
    PadL1->SetBorderSize(2);
    //PadL1->SetGridy();
    //PadL1->SetLogx();
    PadL1->SetTickx(1);
    PadL1->SetTicky(1);
    PadL1->SetLeftMargin(0.16);
    PadL1->SetRightMargin(0.02);
    //PadL1->SetTopMargin(0.05);
    //PadL1->SetBottomMargin(0.31);
    PadL1->SetTopMargin(0.065);
    PadL1->SetBottomMargin(0.13);
    PadL1->SetFrameFillStyle(0);
    PadL1->SetFrameBorderMode(0);
    PadL1->SetFrameFillStyle(0);
    PadL1->SetFrameBorderMode(0);
    PadL1->Draw();


    PadL2->SetFillColor(0);
    PadL2->SetBorderMode(0);
    PadL2->SetBorderSize(2);
    //PadL2->SetGridy();
    //PadL2->SetLogx();
    PadL2->SetTickx(1);
    PadL2->SetTicky(1);
    PadL2->SetLeftMargin(0.16);
    PadL2->SetRightMargin(0.02);
    //PadL2->SetTopMargin(0.05);
    //PadL2->SetBottomMargin(0.31);
    PadL2->SetTopMargin(0.065);
    PadL2->SetBottomMargin(0.13);
    PadL2->SetFrameFillStyle(0);
    PadL2->SetFrameBorderMode(0);
    PadL2->SetFrameFillStyle(0);
    PadL2->SetFrameBorderMode(0);
    PadL2->Draw();
    // End Run2015B Setting 

    float lumi = 35.867;
    TString Lumi = "35.867";// Lumi += lumi;      
    
    TLatex *text1 = new TLatex(0.96,0.95125, Lumi + " fb^{-1} (13 Tev)"); 
    text1->SetNDC();                                              
    text1->SetTextAlign(31);                          
    text1->SetTextFont(42);    
    text1->SetTextSize(0.04);   
    text1->SetLineWidth(2);    
    text1->Draw();  

  for (int v = 0; v<nVariables; v++) 
    for (int m = 0; m<nMetCuts; m++) {

      if (Variable[v]=="MET" && MetCut[m]!="01") continue;

      for (int b = 0; b<nBtagCuts; b++) {
      
	TLegend  *leg = new TLegend(0.23, 0.2, 0.39, 0.3);
	leg->SetFillColor(kWhite); leg->SetBorderSize(0.);
	leg->SetTextColor(1); leg->SetTextSize(0.035);
	leg->SetTextFont(62); 
	leg->SetHeader("t#bar{t} dilepton events");
	if (Selection=="WW") leg->SetHeader("WW dilepton events");
	if (Selection=="ST") leg->SetHeader("tW dilepton events");
	if (Selection=="ZJets") leg->SetHeader("ZJets dilepton events");
       
	//for (int c = 3; c<nChannels; c++) {

          TH1F* Fake; TH1F* Truth;  

          if (BtagCut[b].Contains("Veto"))
           {
             TH1F* Fake0;  TH1F* Truth0;
             TH1F* Fake1;  TH1F* Truth1;

              std::cout <<  MetCut[m] <<std::endl; 
             Fake0   = (TH1F*) RootFile->Get("Stop/" + MetCut[m] + "_NoTag/h_" + Variable[v] + "_fake"  + channel);
            // Fake1->SetDirectory(0);
             Fake1  = (TH1F*) RootFile->Get("Stop/" + MetCut[m] + "_NoJet/h_" + Variable[v] + "_fake"  + channel);
             Fake0  -> Add (Fake1);
             Fake = (TH1F*) Fake0 ->Clone(); 
             //Fake->SetDirectory(0);

	     Truth0  = (TH1F*) RootFile->Get("Stop/" + MetCut[m] + "_NoTag/h_" + Variable[v] + "_truth" + channel);
             //Truth1->SetDirectory(0);
	     Truth1 = (TH1F*) RootFile->Get("Stop/" + MetCut[m] + "_NoJet/h_" + Variable[v] + "_truth" + channel);
             Truth0 -> Add (Truth1);            
             //Truth->SetDirectory(0);
             Truth = (TH1F*) Truth0 ->Clone(); 
             std::cout << "done Veto" <<std::endl;
 
             Fake0 ->Reset(); Fake1 ->Reset(); Truth0 ->Reset(); Truth1 ->Reset(); 
           }
          else
           {
             Fake  = (TH1F*) RootFile->Get("Stop/" + MetCut[m] + BtagCut[b] + "/h_" + Variable[v] + "_fake"  + channel);
	     Truth = (TH1F*) RootFile->Get("Stop/" + MetCut[m] + BtagCut[b] + "/h_" + Variable[v] + "_truth" + channel);
	   }

          Fake->Scale(lumi);
	  Truth->Scale(lumi);
	  
         //if (!BtagCut[b].Contains("Veto")) 
         //   {
         //    Fake->Scale(lumi);
	 //    Truth->Scale(lumi);
         //  }
 
             std::cout << "Fake  ->GetMinimum()  " << Fake->GetMinimum() <<std::endl; 
             std::cout << "Truth ->GetMinimum()  " << Truth->GetMinimum() <<std::endl; 
	  float fakemin = Fake->GetMinimum();
	  float truthmin = Truth->GetMinimum();
	  if (fakemin < truthmin) { Truth->SetMinimum(fakemin + 0.0001);} 
	//float fmin = Fake->GetMinimum();
	//  if (fmin>0.)
	//    Truth->SetMinimum(fmin*0.9);
	// else  Truth->SetMinimum(0.1);


         // Truth->SetMinimum(0.1);
	  //Truth->SetXTitle("M_{T2}(ll) [GeV]");
	  Truth->SetYTitle("Events / 20 GeV");
	      
	  Truth->GetXaxis()->SetLabelFont(42);
	  Truth->GetYaxis()->SetLabelFont(42);
	  Truth->GetXaxis()->SetTitleFont(42);
	  Truth->GetYaxis()->SetTitleFont(42);
	  
	  Truth->GetYaxis()->SetTitleSize(0.06);
	  Truth->GetYaxis()->SetLabelSize(0.05);
	  Truth->GetXaxis()->SetTitleSize(0.06);
	  Truth->GetXaxis()->SetLabelSize(0.); //0.05);
	  Truth->GetXaxis()->SetTitleOffset(0.95);
	  Truth->GetYaxis()->SetTitleOffset(1.25);

	  Truth->SetLineWidth(2);
	  Fake->SetLineWidth(2);

	  Fake->SetLineColor(2);

          PadC1->cd();
	  //if (c==0) PadC1->cd();
	  //if (c==1) PadC2->cd();
	  //if (c==2) PadC3->cd();
	  //if (c==3) PadC4->cd();

	  Truth->DrawCopy();
	  Fake->DrawCopy("same");

             std::cout << "2" <<std::endl; 
	  PadL1->cd();
          //if (c==3) PadL1->cd();
	  //if (c==1) PadL2->cd();
	  //if (c==2) PadL3->cd();
	  //if (c==3) PadL4->cd();

	  Truth->DrawCopy();
	  Fake->DrawCopy("same");

	  leg->AddEntry(Truth, "Two leptons matched", "l");
	  leg->AddEntry(Fake,  "At least one no matched lepton",   "l");

	  leg->Draw();

	  PadL2->cd();

	  Fake->Divide(Truth);

	  Fake->SetXTitle("M_{T2}(ll) [GeV]");
	  Fake->SetYTitle("Fake/Truth");
	      
	  Fake->GetXaxis()->SetLabelFont(42);
	  Fake->GetYaxis()->SetLabelFont(42);
	  Fake->GetXaxis()->SetTitleFont(42);
	  Fake->GetYaxis()->SetTitleFont(42);
	  
	  Fake->GetYaxis()->SetTitleSize(0.17);
	  Fake->GetYaxis()->SetLabelSize(0.15);
	  Fake->GetXaxis()->SetTitleSize(0.17);
	  Fake->GetXaxis()->SetLabelSize(0.15);
	  Fake->GetXaxis()->SetTitleOffset(1.20);
	  Fake->GetYaxis()->SetTitleOffset(0.44);

	  Fake->DrawCopy("p");
             std::cout << "3" <<std::endl; 

	//}

	TString PlotName = Selection + "_" + Variable[v] + "_" + MetCut[m] + BtagCut[b] + channel ;
	//CC->Print("../Plots/FakeStudies/" + PlotName + ".png");
	CL->Print("FakesPlots/" + PlotName + "_log.png");

      Truth->Reset();
      Fake ->Reset();
      }
             std::cout << "end " << MetCut[m] << std::endl; 

    }

}

