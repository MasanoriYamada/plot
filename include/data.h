#ifndef DATA_2013_11_22
#define DATA_2013_11_22
#include <string>

//namespace namespace_gnuplot{
  class DATA{
  public:
    DATA(std::string dataName,int dataSize)
    {
      datasize_ = dataSize;
      dataName_ = dataName;
      x_data_ = new double[datasize_]();
      y_data_ = new double[datasize_]();
      fName_ = new std::string[datasize_]();
    }
    ~DATA()
    {
      delete [] x_data_;
      delete [] y_data_;
      delete [] fName_;
    }
    void setName(std::string name);
    void in_file(std::string* file_name);
    void in_exp(double* x, double* a, double (*func)(double &x, double* a));

    int get_datasize();
    double* getX();
    double* getY();
    std::string getName();
    std::string* getfName();
  private:
    double * x_data_;
    double * y_data_;
    int datasize_;
    std::string* fName_;
    std::string dataName_;
  };




//}
#endif


