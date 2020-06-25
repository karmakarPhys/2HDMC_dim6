#include <iostream>
#include <fstream>
using namespace std;

void exec() {
  ofstream myfile;
  int i,j,i1,j1,m = 80, n = 45;
  float mh= 125.7, mH = 150 , mA= 400 , mC = 400, lam6 = 0, lam7 = 0 ; 
  myfile.open ("mH150_mAHp400_algn_tyI.txt");
  for(i=0;i<m;i++){
    for(j = 0; j<n; j++) {
       //float mA =300;
       //float tb = 0.001 + 0.5*j, sba = 1.0 - 0.004*i;
    float tb = 0.001+0.33*j; 
    float sba = sqrt(1.0-0.0001*pow(i,2));
       float m12sq = (625*(36 + 25*pow(tb,2) + 11*(pow(sba,2)*(-1 + pow(tb,2)) - 2*tb*sqrt((pow(sba,2) - pow(sba,4))/pow(1 + pow(tb,2),2))*(1 + pow(tb,2)))))/(tb + pow(tb,3))- 50.0;
       //float m12sq =  pow(mH,2)*tb/(1+pow(tb,2)) - (pow(mH,2)-pow(mh,2))*((1-pow(sbain,2))*(pow(tb,2)-1)- 2*tb*sbain*sqrt(1 - pow(sbain,2)))/(tb*(1+pow(tb,2)));
       //float m12sq = pow(mh,2)/(tb*(1+pow(tb,2))) + pow(mH,2)*tb/(1+pow(tb,2)) - (pow(mH,2)-pow(mh,2))*((1-pow(sbain,2))*(pow(tb,2)-1)- 2*tb*sbain*sqrt(1 - pow(sbain,2)))/(tb*(1+pow(tb,2)));
       //float m12sq = pow(mH,2)*tb/(1 + pow(tb,2));
      //myfile << "./CalcPhys\t"<< "125.\t" << "300.\t" << "500.\t" << "500.\t" << 1-i*0.007 << "\t"<< "0.\t" << "0.\t" << "-100.\t"<< 0+j*0.5 <<"\t" << "2.\t" << "dkk.dat\n";
       myfile << "./CalcPhys\t"<< "125.7\t" << mH << "\t" << mA << "\t"<< mC  <<"\t" << sba << "\t"<< "0.\t" << "0.\t" << m12sq  << "\t" << tb  << "\t" << "1.\t" << "huberbp_2HDMC_out.dat\n";
      //myfile << "./CalcHybrid\t"<< "125.\t" << "300.\t" << -0.995+i*0.004975 << "\t"<< "-2.\t" << "-2.\t" << "0.\t"<< 0.01+j*0.4 <<"\t" << "1.\t" << "LH_hybrid_type1"<< (i*50+2+2*j)<<".dat\n";
  } }

  for(i1=0;i1<m;i1++){
    for(j1 = 0; j1<n; j1++) {
       //float mA =300;
           float tb1 = 0.001+0.33*j1; 
    float sba1 = sqrt(1.0-0.0001*pow(i1,2));
       //float mh= 125.7, mH = 300. , mA= 300. , mC = 300., lam6 = 0., lam7 = 0. ; 
       //float m12sq1 = pow(mh,2)/(tb1*(1+pow(tb1,2))) + pow(mH,2)*tb1/(1+pow(tb1,2)) - (pow(mH,2)-pow(mh,2))*((1-pow(sbain1,2))*(pow(tb1,2)-1)- 2*tb1*sbain1*sqrt(1 - pow(sbain1,2)))/(tb1*(1+pow(tb1,2)));
       float m12sq1 = (625*(36 + 25*pow(tb1,2) + 11*(pow(sba1,2)*(-1 + pow(tb1,2)) - 2*tb1*sqrt((pow(sba1,2) - pow(sba1,4))/pow(1 + pow(tb1,2),2))*(1 + pow(tb1,2)))))/(tb1 + pow(tb1,3)) - 50.0;
       //float m12sq1 = pow(mH,2)*tb1/(1+pow(tb1,2)) - (pow(mH,2)-pow(mh,2))*((1-pow(sbain1,2))*(pow(tb1,2)-1)- 2*tb1*sbain1*sqrt(1 - pow(sbain1,2)))/(tb1*(1+pow(tb1,2)));
       myfile << "./CalcPhys\t"<< "125.7\t" << mH << "\t" << mA << "\t"<< mC  <<"\t" << -sba1 << "\t"<< "0.\t" << "0.\t" << m12sq1 << "\t" << tb1  << "\t" << "1.\t" << "huberbp_2HDMC_out.dat\n";
  } }
myfile.close();
}
