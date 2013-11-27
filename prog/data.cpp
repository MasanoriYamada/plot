#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../include/data.h"

//using namespace namespace_gnuplot;
using namespace std;

DATA::DATA(const DATA &other)
{
  datasize_ = other.datasize_;
  dataName_ = other.dataName_;
  fName_ = new std::string[datasize_]();
  copy(other.fName_, other.fName_ + sizeof(string)*datasize_, fName_);
}

void DATA::in_file(string* fname)
{
  for (int id = 0 ; id < datasize_ ;id ++)
    {
      fName_[id] = fname[id];
    }
}
void DATA::in_exp(double** a,double (*func)(double x, double* a), double x_in, double x_fi, double dx)
{
  int ND = (int) (x_fi - x_in)/dx + 1;
  x_data_ = new double[ND]();
  y_data_ = new double[ND]();
  for (int ifile = 0 ; ifile < datasize_ ; ifile++)
    {
      for (int id = 0 ; id < ND ;id ++)
	{
	  x_data_[id] = x_in + (double)id * dx;
	  y_data_[id] = (*func)(x_data_[id],a[ifile]);
	}
      makefile(ND,ifile);
    }
  delete [] x_data_;
  delete [] y_data_;
}
void DATA::makefile(int ND, int ifile)
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
  int error = 0;
  for(int id = 0 ; id < ND; id++){
    ofs<<x_data_[id]<<" "<<y_data_[id]<<" "<<error<<endl;
  }
  ofs.close();

}

void DATA::add(DATA &data1, DATA &data2)
{
  this->dataName_ = data1.getName() + " + " + data2.getName();
  this->datasize_ = data1.datasize_ + data2.datasize_;

  for (int id = 0 ; id < data1.datasize_ ; id ++)
    {
      fName_[id] = (data1.getfName())[id];
    }
  for (int id = data1.datasize_ ; id < datasize_ ; id ++)
    {
      fName_[id] = (data2.getfName())[id - data1.datasize_];
    }

  for (int i =0; i<datasize_ ;i++){
    }

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
