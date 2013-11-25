#include "../include/gnuplot.h"
#include <iostream>
#include <math.h>
using namespace std;

double gauss(double x, double* a)
{
  return a[0]+a[1]*x;
}

int main(){
  cout<<"program start"<<endl;

  const int Nfile = 3; 
  const int Npara = 2; 
  GNUPLOT gp1;
  GNUPLOT gp2;

    string input[3] = {"../debug/OmgOmgPot000002.RC16x32_B1830Kud013760Ks013710C1761.it07",
		     "../debug/OmgOmgPot000002.RC16x32_B1830Kud013760Ks013710C1761.it08",
		     "../debug/OmgOmgPot000002.RC16x32_B1830Kud013760Ks013710C1761.it09"};
  

  DATA data_file("file",Nfile);
  data_file.in_file(input);
  gp1.set_flg_w(true);
  gp1.plot(data_file);

  DATA data_exp("exp",Nfile);
  double b[Npara] ={1,1};
  double **a = new double* [Nfile];
  
  for (int i =0 ;i<Nfile;i++){ 
    a[i]=b; 
  }

  data_exp.in_exp(a,gauss, 0, 100, 1);
  gp2.set_flg_rm(true);
  gp2.plot(data_exp);
  
  delete []a;

  return 0;
}
