#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../include/data.h"

//using namespace namespace_gnuplot;
using namespace std;

int DATA::global_ifile_;
DATA::DATA(const DATA &other)
{
  datasize_ = other.datasize_;
  dataName_ = other.dataName_;
  fName_ = new std::string[datasize_]();
  copy(other.fName_, other.fName_ + sizeof(string)*datasize_, fName_);
  x_scale_ = new std::string[datasize_]();
  copy(other.x_scale_, other.x_scale_ + sizeof(string)*datasize_, x_scale_);
  y_scale_ = new std::string[datasize_]();
  copy(other.y_scale_, other.y_scale_ + sizeof(string)*datasize_, y_scale_);
  err_scale_ = new std::string[datasize_]();
  copy(other.err_scale_, other.err_scale_ + sizeof(string)*datasize_, err_scale_);
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
      for(int i=0 ;i<5; i++) cout<<"debug"<<ifile<<" "<<i<<" "<<(a[ifile])[i]<<endl;

      for (int id = 0 ; id < ND ;id ++)
	{
	  x_data_[id] = x_in + (double)id * dx;
	  y_data_[id] = (*func)(x_data_[id],a[ifile]);
	}
      makefile(ND,ifile);
    }
  global_ifile_ = global_ifile_ +1;
  delete [] x_data_;
  delete [] y_data_;
}
void DATA::makefile(int ND, int ifile)
{
  stringstream ss;
  
  ss << global_ifile_<<"."<<ifile <<".tmpForDrowing.dat";
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
      x_scale_[id] = (data1.get_x_scale())[id];
      y_scale_[id] = (data1.get_y_scale())[id];
      err_scale_[id] = (data1.get_err_scale())[id];
    }
  for (int id = data1.datasize_ ; id < datasize_ ; id ++)
    {
      fName_[id] = (data2.getfName())[id - data1.datasize_];
      x_scale_[id] = (data2.get_x_scale())[id - data1.datasize_];
      y_scale_[id] = (data2.get_y_scale())[id - data1.datasize_];
      err_scale_[id] = (data2.get_err_scale())[id - data1.datasize_];
    }

}
void DATA::set_scale(double x_scale, double y_scale, double err_scale)
{
  stringstream sx, sy, se;
  sx<< x_scale;
  sy<< y_scale;
  se<< err_scale;
  for(int id = 0; id < datasize_ ; id ++){
    x_scale_[id]   = sx.str();
    y_scale_[id]   = sy.str();
    err_scale_[id] = se.str();
}
  sx.str("");
  sx.clear(stringstream::goodbit);
  sy.str("");
  sy.clear(stringstream::goodbit);
  se.str("");
  se.clear(stringstream::goodbit);
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
string* DATA::get_x_scale()
{
  return x_scale_;
}
string* DATA::get_y_scale()
{
  return y_scale_;
}
string* DATA::get_err_scale()
{
  return err_scale_;
}
