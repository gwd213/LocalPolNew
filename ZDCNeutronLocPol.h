// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef OFFLINESMDTESTING_DST_H
#define OFFLINESMDTESTING_DST_H

#include <fun4all/SubsysReco.h>

#include <string>
#include <cmath>
#include <map>
#include <vector>

class CaloWaveformFitting;
class TowerInfoContainer;
class PHCompositeNode;
class Gl1Packet;
class CaloPacketContainer;
class CaloPacket;
class TH1;
class TH2;
class TTree;

class ZDCNeutronLocPol : public SubsysReco
{
 public:

  ZDCNeutronLocPol(const std::string &name = "ZDCNeutronLocPol");

  ~ZDCNeutronLocPol() override;

  int Init(PHCompositeNode *topNode) override;
  int InitRun(PHCompositeNode *topNode) override;
  int process_event(PHCompositeNode *topNode) override;
  int End(PHCompositeNode *topNode) override;

  void setGainMatch(const std::string &fname);
  void setFileName(const std::string &fname); 

 protected:
  CaloWaveformFitting *WaveformProcessingFast = nullptr;

  TH1 *h_rawADC[32] = {nullptr};
  TH1 *h_pedADC[32] = {nullptr};
  TH1 *h_signalADC[32] = {nullptr};

  TH2 *h_waveformZDC = nullptr;
  TH2 *h_waveformSMD_North = nullptr;
  TH2 *h_waveformSMD_South = nullptr;
  TH2 *h_waveformVeto_North = nullptr;
  TH2 *h_waveformVeto_South = nullptr;
  TH2 *h_waveformAll = nullptr;


  float gain[32] = {0.0f};
  float smd_south_rgain[16] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
  float smd_north_rgain[16] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

  float rawADC[32] = {0.0f};
  float pedADC[32] = {0.0f};
  float signalADC[32] = {0.0f};
  float smd_pos[4] = {0.0f};


  int ZDCTimingMin = 4;
  int ZDCTimingMax = 10;
  int VetoTimingMin = 6;
  int VetoTimingMax = 11;
  int NorthSMDTimingMin = 9;
  int NorthSMDTimingMax = 999; //unused
  int SouthSMDTimingMin = 7;
  int SouthSMDTimingMax = 12;
  
  TTree *smdHits;
  // Branches of TTree 
  ///////////////////////////////////
  // ZDC ADC value 
  // zdc{side}{module}_adc
  // side : S,N , module : 1,2,3
  ///////////////////////////////////
  float zdcS1_adc = 0.;
  float zdcS2_adc = 0.;
  float zdcS3_adc = 0.;
  float zdcN1_adc = 0.;
  float zdcN2_adc = 0.;
  float zdcN3_adc = 0.;

  ///////////////////////////////////
  // Veto ADC value 
  ///////////////////////////////////
  float veto_NF = 0.;
  float veto_NB = 0.;
  float veto_SF = 0.;
  float veto_SB = 0.;

  ///////////////////////////////////
  // Reconstructed SMD hit position
  ///////////////////////////////////
  float n_x = 0;
  float n_y = 0;
  float s_x = 0;
  float s_y = 0;


  //////////////////////////////////////////////
  // boolian to classify Triger type from GL1 
  // isTirg[3] = ZDC North & South Concidence
  // For detail, refer to DAQ log
  //////////////////////////////////////////////
  bool isTrig[64];
  
  int bunchnumber = 0;

  const int kNumberOfHSMD = 8;
  const int kNumberOfVSMD = 7;
  double smdS_h_adc[8];
  double smdS_v_adc[7];
  double smdN_h_adc[8];
  double smdN_v_adc[7];

  // float smdS1_adc = 0.;
  // float smdS2_adc = 0.;
  // float smdS3_adc = 0.;
  // float smdS4_adc = 0.;
  // float smdS5_adc = 0.;
  // float smdS6_adc = 0.;
  // float smdS7_adc = 0.;

  // float smdN1_adc = 0.;
  // float smdN2_adc = 0.;
  // float smdN3_adc = 0.;
  // float smdN4_adc = 0.;
  // float smdN5_adc = 0.;
  // float smdN6_adc = 0.;
  // float smdN7_adc = 0.;

  // float smdS1_v_adc = 0.;
  // float smdS2_v_adc = 0.;
  // float smdS3_v_adc = 0.;
  // float smdS4_v_adc = 0.;
  // float smdS5_v_adc = 0.;
  // float smdS6_v_adc = 0.;
  // float smdS7_v_adc = 0.;
  // float smdS8_v_adc = 0.;

  // float smdN1_v_adc = 0.;
  // float smdN2_v_adc = 0.;
  // float smdN3_v_adc = 0.;
  // float smdN4_v_adc = 0.;
  // float smdN5_v_adc = 0.;
  // float smdN6_v_adc = 0.;
  // float smdN7_v_adc = 0.;
  // float smdN8_v_adc = 0.;
  
  int showerCutN = 0;
  int showerCutS = 0;
  
  // int evtseq_gl1 = 0;

  // int evtseq_zdc = 0;
  // uint64_t BCO_gl1 = 0;
  // uint64_t BCO_zdc = 0;


  
  
  void CompSmdAdc();
  void CompSmdPos();

  Gl1Packet *p_gl1;
  CaloPacketContainer *zdc_cont;


  std::vector<float> anaWaveformFast(CaloPacket *p, const int channel);

  
  std::string outfile  = "";
  
  int evtcnt;


};

#endif // OFFLINESMDTESTING_DST_H
