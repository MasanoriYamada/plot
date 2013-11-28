#ifndef ANALYS_H_
#define ANALYS_H_
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <complex>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


static const int T_in=7;
static const int T_fi=8;
static const int XnodeSites =16;
static const int YnodeSites =16;
static const int ZnodeSites =16;
static const int TnodeSites =32/2;
static const int binsize=50;
static const int Confsize=700;
static const int Tshiftsize=9;
int tshift[Tshiftsize]={0,2,4,8,12,16,20,24,28};   //time shift
//int tshift[Tshiftsize]={0};   //time shift
static const double effectivemass=1.3023;
//--------------------------------------------------//
static const int LargeConf=Tshiftsize*Confsize;
static const int binnumber=(Confsize/binsize);
static const int XYZnodeSites =XnodeSites*XnodeSites*XnodeSites;
static const int r_sq_max=((XnodeSites)*(XnodeSites) + (YnodeSites)*(YnodeSites) + (ZnodeSites)*(ZnodeSites));
std::string dir_path;
std::string in_dir_path;
std::string out_dir_path;
std::string r_out_dir_path;
std::string xyz_out_dir_path;
std::string SrcSpin;
std::string SinkSpin;




inline void root_mkdir(const char* str){
if(mkdir(str,0775)!=0){std::cout<<"Warning	cat't make dir	already exist::"<<str<<std::endl;}
}
#endif
