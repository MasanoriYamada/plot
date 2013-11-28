#include "../include/gnuplot.h"
#include "../include/io.h"
#include "../include/analys.h"

#include <iostream>
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

std::string             inPath        = "/home/sinyamada/results/set1/Spin0-0Bin50/fitPot";
std::string             physInfo       = "RC16x32_B1830Kud013760Ks013710C1761";
//std::string             inStaticsInfo  = "1g1y1D";
//std::string             inStaticsInfo  = "1g1yy1D";
std::string             inStaticsInfo  = "1g1y3D";
//std::string             inStaticsInfo  = "1g1yy3D";

int main(){
  cout<<"program start"<<endl;

  const int Npara = 5;
  
  DATA data_exp("potential from parametor",binnumber);
  DATA data_file("jack",1);
  

  IODATA iod;
  iod.setReadBinaryMode(false);
  iod.setWriteBinaryMode(false);
  iod.setConfSize(binnumber);
  iod.setOutAve(false);
  iod.setD("1D");

  std::string* datafile = new string[1];

  for (int it = T_in; it <T_fi +1; it++){
    stringstream ss;
    ss <<"/home/sinyamada/Spin0-0Bin50/Potential/jack_error/r/OmgOmgPot000014.RC16x32_B1830Kud013760Ks013710C1761.it"<<std::setw(2) << std::setfill('0')<<it;
    datafile[0] = ss.str();

  
  double **a = new double* [binnumber];
  double *b;
    
    GNUPLOT gp1;
    
    for (int j= 0; j <binnumber; j++) {
      b = new double[Npara+1]();
    iod.callData(b,2,inPath,inStaticsInfo,physInfo,j,it);
    a[j]= b;
    }
    
  for (int j= 0; j <binnumber; j++) {
    for (int i=0;i<5;i++)cout << a[j][i]<<endl;
  }
  
  //data_exp.in_exp(a,g1yy1, 0, 2, 0.002);
  data_exp.in_exp(a,g1y1, 0, 2, 0.002);
  data_file.in_file(datafile);
  data_file.set_scale(0.1209, 197.3/0.1209, 197.3/0.1209);

  DATA data_all("",data_file.get_datasize() + data_exp.get_datasize());
  data_all.add(data_exp,data_file);
  //gp1.set("set yr[-50:100]");
  gp1.set_flg_w(true);
  gp1.plot(data_all);
  //gp1.set("set term postscript enhanced color solid lw 3");
  //gp1.set("set output \"/home/sinyamada/Spin0-0Bin50/fitPot/fit_vs_raw/1D/1gy1D.it09.eps\"");
  //gp1.set("set output \"/home/sinyamada/Spin0-0Bin50/fitPot/fit_vs_raw/1D/1gyy1D.it07.eps\"");
  //gp1.set("set output \"/home/sinyamada/Spin0-0Bin50/fitPot/fit_vs_raw/3D/1gy1D.it07.eps\"");
  //gp1.set("set output \"/home/sinyamada/Spin0-0Bin50/fitPot/fit_vs_raw/3D/1gyy1D.it07.eps\"");
  //gp1.plot(data_all);
   delete []a;
   delete []b;

  }
  return 0;
}
