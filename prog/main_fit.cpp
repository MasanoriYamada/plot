#include "../include/gnuplot.h"
#include "../include/io.h"
#include "../include/analys.h"

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


double g1yy1(double x, double* a)
{
  if ( x == 0 )
    {
    return a[0];
    }
  else if ( x > 0)
    {
      return  a[0]*exp(-a[1]*x*x)+ a[2]*((1 - exp(-a[3]*x*x)))*((1 - exp(-a[3]*x*x)))*(exp(-a[4]*x)/x)*(exp(-a[4]*x)/x);
    }
}
double g1y1(double x, double* a)
{
  if ( x == 0 )
    {
    return a[0];
    }
  else if ( x > 0)
    {
      return  a[0]*exp(-a[1]*x*x)+ a[2]*((1 - exp(-a[3]*x*x))/x)*exp(-a[4]*x);
    }
}

int main(){
  cout<<"program start"<<endl;

    // raw data (average & error)
    string	inPath_raw	  = "/data1/yamada/OmgOmg/results/set1/ts22/spin00.bin1/Potential/jack_error/r/";
    string	inStaticsInfo_raw = "OmgOmgPot";

    // for fit parametor at each bin sample
    string		inPath  = "/data1/yamada/OmgOmg/results/set1/ts22/spin00.bin1/fitPot/bin";
    string		outPath = "/data1/yamada/OmgOmg/results/set1/ts22/spin00.bin1/fit_vs_raw/";
    root_mkdir(outPath.c_str());
    vector <string>	inStaticsInfo;
    inStaticsInfo.push_back("1g1y1D");
    inStaticsInfo.push_back("1g1yy1D");
    inStaticsInfo.push_back("1g1y3D");
    inStaticsInfo.push_back("1g1yy3D");
    vector <string>	outStaticsInfo;
    outStaticsInfo.push_back("1g1y1D");
    outStaticsInfo.push_back("1g1yy1D");
    outStaticsInfo.push_back("1g1y3D");
    outStaticsInfo.push_back("1g1yy3D");

    // for ave (parametor from average potential data)
    string		inPath_ave  = "/data1/yamada/OmgOmg/results/set1/ts22/ave/fitPot";
    string		outPath_ave = "/data1/yamada/OmgOmg/results/set1/ts22/ave/fitPot/fit_vs_raw";
    root_mkdir(outPath_ave.c_str());
    vector<string>	inStaticsInfo_ave;
    inStaticsInfo_ave.push_back("ave_1g1y1D");
    inStaticsInfo_ave.push_back("ave_1g1yy1D");
    inStaticsInfo_ave.push_back("ave_1g1y3D");
    inStaticsInfo_ave.push_back("ave_1g1yy3D");
    vector<string>	outStaticsInfo_ave;
    outStaticsInfo_ave.push_back("ave_1g1y1D");
    outStaticsInfo_ave.push_back("ave_1g1yy1D");
    outStaticsInfo_ave.push_back("ave_1g1y3D");
    outStaticsInfo_ave.push_back("ave_1g1yy3D");
  std::string     physInfo = "RC16x32_B1830Kud013760Ks013710C1761";



 
  const int	Npara = 5;

    for (int ifunc = 0; ifunc < outStaticsInfo_ave.size() ;ifunc++)
  //for (int ifunc = 0; ifunc < 1 ;ifunc++)
    {   
      DATA	data_bin(inStaticsInfo[ifunc] +" fit each sample",binnumber);
      DATA	data_raw("raw",1);
      DATA	data_ave(inStaticsInfo[ifunc] +" fit from potential ave",1);
       
       
      IODATA	iod;
      iod.setReadBinaryMode(false);
      iod.setWriteBinaryMode(false);
      iod.setConfSize(binnumber);
      iod.setOutAve(false);
      iod.setD("1D");
       
      std::string*	datafile = new string[1];
       
      for (int it = T_in; it <T_fi +1; it++){
	stringstream	iraw;
	stringstream	out_bin;
	stringstream	out_ave;

	// make raw dat name 
	iraw <<inPath_raw<<"/"<<inStaticsInfo_raw<<"000700"<<"."
	     <<physInfo<<".it"<<std::setw(2) << std::setfill('0')<<it;
	datafile[0] = iraw.str();
	 
	// read fit parametor at each bin sample
	double **a_j_p = new double* [binnumber];
	double *b_p;
	 
	for (int j= 0; j <binnumber; j++) 
	  {
	    b_p = new double[Npara+1]();
	    iod.callData(b_p,2,inPath,inStaticsInfo[ifunc],physInfo,j,it);
	    a_j_p[j]= b_p;
	  }

	//read fit paramtor at ave
	double **ave_param_a_j_p = new double *[1];
	double *ave_param_b_p;
	 
	 
	for (int j= 0; j <1; j++) {
	  ave_param_b_p = new double[Npara+1]();
	  iod.callData(ave_param_b_p,2,inPath,inStaticsInfo[ifunc],physInfo,j,it);
	  ave_param_a_j_p[j]= ave_param_b_p;
	}
	 
	/*  
	    for (int j= 0; j <binnumber; j++) {
	    for (int i=0;i<5;i++)cout << a[j][i]<<endl;
	    }
	*/
	 
	//===================== make data =======================
	// raw data
	data_raw.in_file(datafile);
	data_raw.set_scale(0.1209, 197.3/0.1209, 197.3/0.1209);
  
	// fit data (each bin)
	if(ifunc == 0 || ifunc == 2){
	data_bin.in_exp(a_j_p,g1y1, 0, 2, 0.01);
	}
	else if (ifunc == 1 || ifunc ==3){
	data_bin.in_exp(a_j_p,g1yy1, 0, 2, 0.01);
	}

	//fit data (ave)
	if(ifunc == 0 || ifunc == 2){
	data_ave.in_exp(ave_param_a_j_p,g1y1, 0, 2, 0.01);
	}
	else if (ifunc == 1 || ifunc ==3){
	data_ave.in_exp(ave_param_a_j_p,g1yy1, 0, 2, 0.01);
	}

	//===================== plot =======================

	// bin + raw
	GNUPLOT gp_bin;

	gp_bin.set("set grid");
	gp_bin.set_flg_w(true);
	gp_bin.set_flg_up(true);

	DATA data_bin_raw("",data_bin.get_datasize() + data_raw.get_datasize());
	data_bin_raw.add(data_bin,data_raw);
	//gp_bin.plot(data_bin_raw);

	out_bin<<"set output \""<<outPath<<"/"<<outStaticsInfo[ifunc]<<".it"<<std::setw(2) << std::setfill('0')<<it<<".eps\"";

	gp_bin.set("set term postscript enhanced color solid lw 3");
	gp_bin.set(out_bin.str());
	out_bin.clear();
	gp_bin.plot(data_bin_raw);


	//ave + raw
	GNUPLOT gp_ave;
	gp_ave.set("set grid");
	gp_ave.set_flg_w(true);	
	gp_ave.set_flg_up(true);

	DATA data_ave_raw("",data_ave.get_datasize() + data_raw.get_datasize());
	data_ave_raw.add(data_ave,data_raw);
	gp_ave.plot(data_ave_raw);

	out_ave<<"set output \""<< outPath_ave<<"/"<<outStaticsInfo_ave[ifunc]<<".it"<<std::setw(2) << std::setfill('0')<<it<<".eps\"";
	gp_ave.set("set term postscript enhanced color solid lw 3");
	gp_ave.set(out_ave.str());
	out_ave.clear();
	gp_ave.plot(data_ave_raw);



	//for check
	//DATA data_all("",data_ave.get_datasize() + data_bin_raw.get_datasize());
	//data_all.add(data_ave,data_bin_raw);
	//gp1.plot(data_raw);
	//gp1.plot(data_bin);
	//gp1.plot(data_ave);
	//gp1.plot(data_all);



	delete []a_j_p;
	delete []b_p;
	delete []ave_param_a_j_p;
	delete []ave_param_b_p;
   
      }//it
    }//ifunc
  return 0;
}
