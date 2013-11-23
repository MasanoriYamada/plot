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
void DATA::in_exp(double* x, double* a,double (*func)(double &x, double* a))
{
  for (int id = 0 ; id < datasize_ ;id ++)
    {
      x_data_[id] = x[id];
      y_data_[id] = (*func)(x[id],a);
    }
}
double * DATA::getX()
{
  return x_data_;
}
double * DATA::getY()
{
  return y_data_;
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
