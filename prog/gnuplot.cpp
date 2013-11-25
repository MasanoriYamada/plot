#include <iostream>
#include <stdio.h>
#include "../include/gnuplot.h"

//using namespace namespace_gnuplot;
using namespace std;

void GNUPLOT::plot(DATA data)
{
  fprintf(gp_, "set title \" %s \"\n", data.getName().c_str());

  string  plot_string;
  for(int i = 0 ; i < data.get_datasize() ; i ++)
    {
      if (!flg_w_){
	plot_string = "\"" +  (data.getfName())[i] + "\"" + plot_string ;

      }
      else {
	plot_string = "\"" +  (data.getfName())[i] + "\" w e " + plot_string;
      }
      if ( i != data.get_datasize() - 1) plot_string = " , " + plot_string ;
    }
      cout<<plot_string<<endl;

  fprintf(gp_, "plot %s\n", plot_string.c_str());
  /*  if(flg_rm_){
  for(int i = 0 ; i < data.get_datasize() ; i ++)  rm_file((data.getfName())[i] );
  }*/
}

void GNUPLOT::set_flg_w(bool flg_w)
{
  flg_w_ = flg_w;
}
void GNUPLOT::set(string param)
{
 fprintf(gp_, "%s\n", param.c_str());
}
void GNUPLOT::set_flg_rm(bool flg_rm)
{
  flg_rm_ = flg_rm;
}
void GNUPLOT::rm_file(string fname)
{
  if( remove(fname.c_str()) )
    {
      cout<<"ERR can't remove "<<fname<<endl;
    }
}
