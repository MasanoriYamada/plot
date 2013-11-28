#ifndef DATA_2013_11_22
#define DATA_2013_11_22
#include <string>
#include <iostream>
//namespace namespace_gnuplot{
  class DATA{
  public:
    DATA(std::string dataName,int dataSize)
    {
      datasize_	 = dataSize;
      dataName_	 = dataName;
      fName_	 = new std::string[datasize_]();
      x_scale_	 = new std::string[datasize_]();
      y_scale_	 = new std::string[datasize_]();
      err_scale_ = new std::string[datasize_]();
      for (int i =0 ;i <datasize_ ; i++)
	{
	  x_scale_[i]	= "1";
	  y_scale_[i]	= "1";
	  err_scale_[i] = "1";
	}
    }
    DATA(const DATA &other); //copy constract
    ~DATA()
    {
      delete [] fName_; fName_ = NULL;
      delete [] x_scale_; x_scale_ = NULL;
      delete [] y_scale_; y_scale_ = NULL;
      delete [] err_scale_; err_scale_ = NULL;
      
    }
    void setName(std::string name);
    void in_file(std::string* file_name);
    void in_exp(double** a,double (*func)(double x, double* a), double x_in, double x_fi, double dx);
    void set_scale(double x_scale, double y_scale, double err_scale);
    int get_datasize();
    void add(DATA &data1, DATA &data2);
    std::string getName();
    std::string* getfName();
    std::string* get_x_scale();
    std::string* get_y_scale();
    std::string* get_err_scale();
  private:
    double * x_data_;
    double * y_data_;
    int datasize_;
    int datasize_in_file_;
    static int global_ifile_;
    std::string* fName_;
    std::string dataName_;
    std::string* x_scale_;
    std::string* y_scale_;
    std::string* err_scale_;
    void makefile(int NumberOfDataInFile, int ifile);
  };




//}
#endif


