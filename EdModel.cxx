#include "EdModel.h"

EdModel::EdModel(EdInput *inp){

    if( inp ){
      int tot_part = 100;
      ifile = inp->GetIfile();
	length = inp->Get_length();
	len_x = inp->Get_lenx();
	len_y = inp->Get_leny();
	ph_model = inp->GetModel();
	m_model = inp->GetMassModel();
	beam_pid = inp->GetBeamPID();
	if (ph_model == 2) {
	  Float_t Energy_1, Energy_2, E_counts;
	  TTree *Input_spectrum = new TTree("Hin", "HG Monte Carlo input");
	  Input_spectrum->Branch("Energy_1",&Energy_1,"Energy_1/F");
	  Input_spectrum->Branch("Energy_2",&Energy_2,"Energy_2/F");
	  Input_spectrum->Branch("E_counts",&E_counts,"E_counts/F");
	  printf("Reading input file %s\n",ifile.Data());
	  Input_spectrum->ReadFile(ifile.Data(), "Energy_1:Energy_2:E_counts");
	  H1_spec = new TH1F("H1_spec","H1_spec",Input_spectrum->GetEntries(),Input_spectrum->GetMinimum("Energy_1"),Input_spectrum->GetMaximum("Energy_2"));
	  Axis_t *new_bins = new Axis_t[Input_spectrum->GetEntries() + 1];	    
	  TAxis *axis = H1_spec->GetXaxis(); 
	  for (int i=0; i< Input_spectrum->GetEntries(); i++) {
	    Input_spectrum->GetEntry(i);
	    new_bins[i] = Energy_1;
	    H1_spec->SetBinContent(i+1,E_counts);
	    if (i+1 == Input_spectrum->GetEntries()) new_bins[i+1] = Energy_2; 
	  }
	  axis->Set(Input_spectrum->GetEntries(), new_bins); 
	  delete new_bins; 
	  delete Input_spectrum;
	}
	tg_Z = inp->Get_tg_Z();
	tg_N = inp->Get_tg_N();
	tg_mass = inp->Get_tg_mass();
	energy = inp->Get_eEnergy();
	theta_min = inp->Get_thetaMin();
	theta_max = inp->Get_thetaMax();
	npart = inp->GetNpart();
	tot_part = npart;
	for (int i=0; i<tot_part; i++) pid[i] = inp->GetPid(i);
	nvertex = inp->GetNvertex();
	tot_part = nvertex;
	for (int i=0; i<tot_part; i++) {
	  npvert[i] = inp->GetNpvert(i);
	  overt[i] = inp->GetOvert(i);
	  v_ratio[i] = inp->GetV_ratio(i);
	  v_type[i] = inp->GetV_type(i);
	}
	offset.SetXYZ( inp->GetTgtXoff(),
		       inp->GetTgtYoff(),
		       inp->GetTgtZoff() );

    }

    length = length / 100. ; // conversion distances in m
    len_x = len_x / 100. ; 
    len_y = len_y / 100. ; 
    offset *= 1e-2; // conversion distances in cm to m

    return;
}

EdModel::~EdModel(){
    return;
}


double EdModel::GetEnergy(){
  double e_out = 0.;
  if (ph_model == 1) { // PhaseSpace Single Energy
    e_out = energy;

  }
  else if (ph_model == 2) { // PhaseSpace Multiple Energy
    while (isnan(e_out) || e_out ==0) e_out = H1_spec->GetRandom();
  }

  return e_out;
}

char * EdModel::GetMassModelString(){
  if (m_model == 1) return "Breit-Wigner";
  else if (m_model == 2) return "Flat";
  else if (m_model == 3) return "m=mass";
  else return "Sorry: No mass model supported. Check your input file";

}
