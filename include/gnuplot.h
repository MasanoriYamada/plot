#ifndef GNUPLOT_2013_11_19
#define GNUPLOT_2013_11_19
#include "data.h"

//namespace namespace_gnuplot{
  class GNUPLOT{
  public:
    GNUPLOT()
    {
      gp_ = popen("gnuplot -persist","w");
      flg_w_ = false;
      flg_rm_ = false;
    }
    ~GNUPLOT()
    {
      pclose(gp_);
    }

    void plot(DATA data);
    void set(std::string param);
    void set_flg_w(bool flg_w_);
    void set_flg_rm(bool flg_rm_);

    private:
    void rm_file(std::string fname);
    FILE *gp_;
    bool flg_w_;
    bool flg_rm_;
  };




//}
#endif
