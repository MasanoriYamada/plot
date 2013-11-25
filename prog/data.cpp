#include "../include/data.h"
#include <fstream>
#include <iostream>
#include <sstream>

//using namespace namespace_gnuplot;
using namespace std;

void DATA::in_file(string* fname)
{
  for (int id = 0 ; id < datasize_ ;id ++)
    {
      fName_[id] = fname[id];
    }
}
void DATA::in_exp(double** a,double (*func)(double x, double* a), int x_in, int x_fi, int dx)
{
  x_data_ = new double[x_fi-x_in + 1 ]();
  y_data_ = new double[x_fi-x_in + 1 ]();
  for (int ifile = 0 ; ifile < datasize_ ; ifile++)
    {
      for (int id = x_in ; id < x_fi+1 ; id++)
	{
	  x_data_[id] = id*dx;
	  y_data_[id] = (*func)(x_data_[id],a[ifile]);
	}
      makefile(x_in,x_fi,ifile);
    }
  delete [] x_data_;
  delete [] y_data_;
}
void DATA::makefile(int x_in, int x_fi, int ifile)
{
  stringstream ss;
  
  ss << ifile <<".tmpForDrowing.dat";
  fName_[ifile] = ss.str();
  fstream ofs;

  ofs.setf(std::ios::scientific);
  ofs.open(fName_[ifile].c_str(),std::ios::out);
  if (!ofs.is_open()) {
    std::cerr << "ERROR output file can't open (no exist)::"<<fName_[ifile]<<std::endl;
    exit(1);
   }
  for(int id = x_in ; id < x_fi; id++){
    ofs<<x_data_[id]<<" "<<y_data_[id]<<endl;
  }
  ofs.close();

}

string DATA::getName()
{
  return dataName_;
}
string* DATA::getfName()
{
  return fName_;
}
int DATA::get_datasize()
{
   return datasize_;
}
