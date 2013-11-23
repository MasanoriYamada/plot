#include <iostream>
#include "../include/gnuplot.h"
//#include "../include/io.h"

//using namespace namespace_gnuplot;
using namespace std;

void GNUPLOT::plot(DATA data)
{

  string  plot_string;
  for(int i = 0 ; i < data.get_datasize() ; i ++)
    {
      if (!flg_w_){
      plot_string = "\"" +  (data.getfName())[i] + "\"" + plot_string;
      }
      else {
	plot_string = "\"" +  (data.getfName())[i] + "\" w e " + plot_string;
      }
      if ( i != data.get_datasize() - 1) plot_string = " , " + plot_string;
    }
      cout<<plot_string<<endl;

  /*
  IODATA tmp;
  tmp.setWriteBinaryMode(false);
  tmp.outData(data.getX,outPath,outStaticsInfo,physInfo,iconf,iT,fit1g1y3D->getDofA()+1);
  */
  //fprintf(terminal, "plot sin(x)\n");
  fprintf(gp_, "plot %s\n", plot_string.c_str());

}
void GNUPLOT:: set_flg_w(bool flg_w){
  flg_w_ =flg_w;
}
