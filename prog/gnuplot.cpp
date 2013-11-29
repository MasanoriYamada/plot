#include <iostream>
#include <stdio.h>
#include <sstream>
#include "../include/gnuplot.h"

//using namespace namespace_gnuplot;
using namespace std;

void GNUPLOT::plot(DATA &data)
{
  fprintf(gp_, "set title \" %s \"\n", data.getName().c_str());

  string  plot_string;
  for(int i = 0 ; i < data.get_datasize() ; i ++)
    {
      if (!flg_w_){
	plot_string = "\"" +  (data.getfName())[i] + 
	  "\" using ($1*" + (data.get_x_scale())[i] + "):($2*" + (data.get_y_scale())[i] + ")" 
	  + plot_string ;
      }
      else {
	plot_string = "\"" +  (data.getfName())[i] + 
	  "\" using ($1*" + data.get_x_scale()[i] + "):($2*" + data.get_y_scale()[i] + "):($3*"+ data.get_err_scale()[i] + ") w e " 
	  + plot_string;
      }
      if ( i != data.get_datasize() - 1) plot_string = " , " + plot_string ;
    }
  cout<<"plot==>> "<<plot_string<<endl;
  if(!flg_up_){
  fprintf(gp_, "plot %s\n", plot_string.c_str());
  fprintf(gp_, "reset %s\n", plot_string.c_str());
  }
  else {
    fprintf(gp_, "set multiplot\n", plot_string.c_str());
    fprintf(gp_, "set key left top\n");
    fprintf(gp_, "set xzeroaxis lt 7\n");
    fprintf(gp_, "plot %s\n", plot_string.c_str());
    fprintf(gp_, "unset grid\n"); 
    fprintf(gp_, "set title \"enlarged view\"\n"); 
    fprintf(gp_, "set size 0.5,0.5\n"); 
    fprintf(gp_, "set origin 0.50,0.43\n"); 
    fprintf(gp_, "unset key\n"); 
    fprintf(gp_, "set yr[-150:50]\n"); 
    fprintf(gp_, "unset xl\n"); 
    fprintf(gp_, "unset yl\n"); 
    fprintf(gp_, "replot\n"); 
    fprintf(gp_, "unset multiplot\n"); 
    fprintf(gp_, "reset\n"); 
      
      }
}

void GNUPLOT::set_flg_w(bool flg_w)
{
  flg_w_ = flg_w;
}
void GNUPLOT::set(string param)
{
 fprintf(gp_, "%s\n", param.c_str());
}
void GNUPLOT::set_flg_up(bool flg_up)
{
  flg_up_ = flg_up;
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
