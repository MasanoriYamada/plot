#ifndef DATA_2013_11_22
#define DATA_2013_11_22
#include <string>
#include <iostream>
//namespace namespace_gnuplot{
  class DATA{
  public:
    DATA(std::string dataName,int dataSize)
    {
      datasize_ = dataSize;
      dataName_ = dataName;
      fName_ = new std::string[datasize_]();
    }
    DATA(const DATA &other); //copy constract
    ~DATA()
    {
	  delete [] fName_; fName_ = NULL;
    }
    void setName(std::string name);
    void in_file(std::string* file_name);
    void in_exp(double** a,double (*func)(double x, double* a), double x_in, double x_fi, double dx);
    int get_datasize();
    void add(DATA &data1, DATA &data2);
    std::string getName();
    std::string* getfName();
  private:
    double * x_data_;
    double * y_data_;
    int datasize_;
    int datasize_in_file_;
    std::string* fName_;
    std::string dataName_;
    void makefile(int NumberOfDataInFile, int ifile);
  };




//}
#endif


