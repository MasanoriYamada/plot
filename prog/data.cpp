#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "../include/data.h"

//using namespace namespace_gnuplot;
using namespace std;

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
  for(int id = 0 ; id < ND; id++){
    ofs<<x_data_[id]<<" "<<y_data_[id]<<endl;
  }
  ofs.close();

}

DATA DATA::add(DATA &data1, DATA &data2)
{
  DATA data3(data1.getName() + "+" + data2.getName() ,data1.datasize_ + data2.datasize_);
  string* array = new string[data3.datasize_];

  for (int id = 0 ; id < data1.datasize_ ; id ++)
    {
      array[id] = (data1.getfName())[id];
      cout<<"data1"<<(data1.getfName())[id]<<endl;
    }
  for (int id = data1.datasize_ ; id < data3.datasize_ ; id ++)
    {
      array[id] = (data2.getfName())[id - data1.datasize_];
      cout<<"data2 "<<(data2.getfName())[id - data1.datasize_]<<endl;
    }
  data3.in_file(array);

  for (int i =0; i<data3.datasize_ ;i++){
      cout<<"data3"<<(data3.getfName())[i]<<endl;
    }

  delete [] array;
  return data3;
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
