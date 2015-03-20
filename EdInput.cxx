#include "EdInput.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "TString.h"

EdInput::EdInput(const char *file){
    printf("Reading %s for input\n", file);

    char command[100];
    char tmp[100];
    ifstream inputfile;
    inputfile.open(file, ifstream::in);
    if( !inputfile ) {
      printf("%s cannot be opened\n", file); 
      exit(1);
    }
    char c1;
    char delim = ';';
    TString valcommand;
    TString valc2;
    double factor;
    int poscomma;
    int atvertex = 0;
    
    while( !inputfile.eof() ){      //      c1 = inputfile.peek(); // read the first character , if it is a #, skip the line
      inputfile.getline(command,100,delim);
      // printf("read command %s\n",command);
      valcommand = command;
      valc2 = valcommand(0,1);
      if (valc2.Contains("#")==false) {
	
	//	printf("%s \n",valcommand.Data());
	if (valcommand.Contains("nevt:")) {
	  valcommand.ReplaceAll("nevt:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.nevt = valcommand.Atoi();
	  printf("Total Number of events %d\n",fData.nevt);
	}
	if (valcommand.Contains("nprint:")) {
	  valcommand.ReplaceAll("nprint:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.nprnt = valcommand.Atoi();
	  printf("Print feedback every %d events\n",fData.nprnt);
	}
	if (valcommand.Contains("model:")) {
	  valcommand.ReplaceAll("model:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.model = valcommand.Atoi();
	  printf("Model for the generator %d\n",fData.model);
	}
	if (valcommand.Contains("M_mode:")) {
	  valcommand.ReplaceAll("M_mode:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.mass_model = valcommand.Atoi();
	  printf("Mass Model for the decaying particle %d\n",fData.mass_model);
	}
	if (valcommand.Contains("ifile:")) {
	  valcommand.ReplaceAll("ifile:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("\n","");
	  valcommand.ReplaceAll("\t","");
	  fData.ifile = valcommand.Strip();
	  printf("Input file spectra from %s\n",fData.ifile.Data());
	}
	if (valcommand.Contains("beam:")) {
	  valcommand.ReplaceAll("beam:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.beam_pid = valcommand.Atoi();
	  printf("Beam Particle PID=%d\n",fData.beam_pid);
	}
	if (valcommand.Contains("en:")) {
	  valcommand.ReplaceAll("en:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains("MeV")) factor = 0.001;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("GeV","");
	  valcommand.ReplaceAll("MeV","");
	  fData.e_energy = factor*valcommand.Atof();
	  printf("Beam energy of %.4f\n",fData.e_energy);
	}
	if (valcommand.Contains("tg_Z:")) {
	  valcommand.ReplaceAll("tg_Z:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.tg_Z = valcommand.Atoi();
	  printf("Target Z: %d\n",fData.tg_Z);
	}
	if (valcommand.Contains("tg_N:")) {
	  valcommand.ReplaceAll("tg_N:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.tg_N = valcommand.Atoi();
	  printf("Target N: %d\n",fData.tg_N);
	}
	if (valcommand.Contains("tg_mass:")) {
	  valcommand.ReplaceAll("tg_mass:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  if (valcommand.Contains("MeV")) factor = 0.001;
	  else factor = 1;
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("GeV","");
	  valcommand.ReplaceAll("MeV","");
	  fData.tg_mass = factor*valcommand.Atof();
	  printf("Target Mass: %.4e\n",fData.tg_mass);
	}
	if (valcommand.Contains("length:")) {
	  valcommand.ReplaceAll("length:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  fData.length = factor*valcommand.Atof();
	  printf("Target length: %.4f cm\n",fData.length);	  
	}
	if (valcommand.Contains("ras_x:")) {
	  valcommand.ReplaceAll("ras_x:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  fData.lenx = factor*valcommand.Atof();
	  printf("Raster X: %.4f cm\n",fData.lenx);	  
	}
	if (valcommand.Contains("ras_y:")) {
	  valcommand.ReplaceAll("ras_y:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  fData.leny = factor*valcommand.Atof();
	  printf("Raster Y: %.4f cm\n",fData.leny);	  
	}
	if (valcommand.Contains("theta:")) {
	  valcommand.ReplaceAll("theta:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" deg")) factor = 3.14/180;
	  else factor = 1; //rad
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll("deg","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("rad","");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.theta_min = factor*valc2.Atof();
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.theta_max = factor*valc2.Atof();
	  printf("Theta_min=%.2f ;  Theta_max=%.2f\n",fData.theta_min,fData.theta_max);	  
	}
	if (valcommand.Contains("offset:")) {
	  valcommand.ReplaceAll("offset:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1; //rad
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.off_x = factor*valc2.Atof();
	  valcommand.Replace(0,valc2.Length()+1,"");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.off_y = factor*valc2.Atof();
	  valcommand.Replace(0,valc2.Length()+1,"");
	  fData.off_z = factor*valcommand.Atof();
	  printf("Offset_X=%.2f ;  Offset_Y=%.2f ; Offset_Z=%.2f\n",fData.off_x,fData.off_y,fData.off_z);
	}
	if (valcommand.Contains("npart:")) {
	  valcommand.ReplaceAll("npart:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.npart = valcommand.Atoi();
	  printf("Number of particle in final state: %d\n",fData.npart);
	}
	if (valcommand.Contains("pid:")) {
	  valcommand.ReplaceAll("pid:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  printf("Particle ID for final states particles: ");
	  for (int i=0; i<fData.npart -1; i++) {
	    poscomma = valcommand.First(",");
	    valc2 = valcommand(0,poscomma);
	    fData.pid[i] = valc2.Atoi();
	    valcommand.Replace(0,poscomma+1,"");
	    printf(" %d",fData.pid[i]);
	  }
	  fData.pid[fData.npart -1] = valcommand.Atoi();
	   printf(" %d \n",fData.pid[fData.npart -1]);
	}
	if (valcommand.Contains("nvertex:")) {
	  valcommand.ReplaceAll("nvertex:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.nvertex = valcommand.Atoi();
	  printf("Number of vertexes: %d\n",fData.nvertex);
	}
	if (valcommand.Contains("vertex")) {
	  valcommand.ReplaceAll("vertex:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.overt[atvertex] = valc2.Atoi();
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.npvert[atvertex] = valc2.Atoi();
	  printf("Origin vertex particle n.: %d    Number of particles at this vertex: %d \n",fData.overt[atvertex],fData.npvert[atvertex]);
	  
	  
	}
	if (valcommand.Contains("v_type:")) {
	  valcommand.ReplaceAll("v_type:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.v_type[atvertex] = valc2.Atoi();
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.v_ratio[atvertex] = valc2.Atof();
	  printf("Vertex type=%i , Vertex ratio=%.2f \n",fData.v_type[atvertex],fData.v_ratio[atvertex]);
	  if (fData.v_type[atvertex] != 1) {
	    printf("vertex n. %i type not supported \n",atvertex+1);
	    exit(1);
	  }
	  atvertex++;
	}
	if (valcommand.Contains("output:")) {
	  valcommand.ReplaceAll("output:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.out_fmt = valcommand.Atoi();
	  printf("Output format n.: %d\n",fData.out_fmt);
	}
	if (valcommand.Contains("END")) {
	  break;
	}
      }
    }
    if (atvertex!=fData.nvertex) printf("Number of reqeusted vertexes is %i, but format written for just %i vertexes\n",fData.npart, atvertex);
    inputfile.close();
    printf("Finhed reading input file\n");
}

EdInput::~EdInput(){
}
