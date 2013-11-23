#include "../include/gnuplot.h"
#include <iostream>
using namespace std;

int main(){

  cout<<"program start"<<endl;
  string input[3] = {"../debug/OmgOmgPot000002.RC16x32_B1830Kud013760Ks013710C1761.it07",
		     "../debug/OmgOmgPot000002.RC16x32_B1830Kud013760Ks013710C1761.it08",
		     "../debug/OmgOmgPot000002.RC16x32_B1830Kud013760Ks013710C1761.it09"};
  DATA data("Potenttial",3);
  data.in_file(input);

  GNUPLOT gp;
  gp.set_flg_w(true);
  gp.plot(data);

  return 0;
}
