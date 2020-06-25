#include "THDM.h"
#include "Constraints.h"
#include "DecayTable.h"
#include "HBHS.h"
#include <iostream>
#include "SM.h"
#include "Util.h"
//#include "THDM.h"
#include <complex>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_integration.h>
//#include "Constraints.h"
//#include "DecayTable.h"
//#include "THDM.h"
#include "Util.h"
#include <fstream>
//#include <iostream>
//#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>
#include <cfloat>
#include <cstring>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {

  if (argc < 11) {
    cout << "Usage: ./CalcPhys mh mH mA mHp sin(beta-alpha) lambda_6 lambda_7 m_12^2 tan_beta yukawas_type output_filename\n";
    return -1;
  }

  double mh_in = (double)atof(argv[1]);
  double mH_in = (double)atof(argv[2]);
  double mA_in = (double)atof(argv[3]);
  double mHp_in = (double)atof(argv[4]);
  double sba_in = (double)atof(argv[5]);
  double l6_in = (double)atof(argv[6]);
  double l7_in = (double)atof(argv[7]);
  double m12_2_in = (double)atof(argv[8]); 
  double tb_in = (double)atof(argv[9]);
  int yt_in = (int)atof(argv[10]);
  char* file = argv[11];
  
  //double cba_in = sqrt(1. - pow(sba_in,2));
  THDM model;

  SM sm; 
  model.set_SM(sm);

  bool pset = model.set_param_phys(mh_in,mH_in,mA_in,mHp_in,sba_in,l6_in,l7_in,m12_2_in,tb_in);

  if (!pset) {
	cerr << "The parameters you have specified were not valid\n";
	return -1;
  }

/*#if defined HiggsBounds
  HB_init();
  HS_init();
#endif
*/

  model.set_yukawas_type(yt_in);

  // Reference SM Higgs mass for EW precision observables
  double mh_ref = 125.;  

  // Write model information to the screen
  //model.print_param_phys();
  //model.print_param_hybrid();
  //model.print_param_gen();	  
  Constraints constr(model);
  //Constraints check(model);
  //check.print_all(mh_ref);
  double S,T,U,V,W,X;   
  //double mh,mH,cba,tb,Z4,Z5,Z7;  
  //get_param_hybrid(mh,mH,cba,Z4,Z5,Z7,tb);
  constr.oblique_param(mh_ref,S,T,U,V,W,X);
  
  //double cba_wo_sgn = sqrt(1 - pow(sba_in,2));
  //double cba_in = copysign(cba_wo_sgn,sba_in);
  //printf(" Oblique V: %12.5e\n", V);
  //printf(" Oblique W: %12.5e\n", W);  
  //printf(" Oblique X: %12.5e\n", X);
  //printf(" Delta_rho: %12.5e\n", constr.delta_rho(mh_ref));
  //printf("\n");
  //printf(" Delta_amu: %12.5e\n\n", constr.delta_amu());





/*#if defined HiggsBounds

// See HiggsSignals manual for more information
  int mass_pdf = 2;
  HS_set_pdf(mass_pdf);
  HS_setup_assignment_range_massobservables(2.);
  HS_set_output_level(0);

// Share couplings of 2HDM model with HiggsBounds/HiggsSignals
  HB_set_input_effC(model);
  
  // Arrays hold the HiggsBounds results 
  int hbres[6];
  double hbobs[6];
  int hbchan[6];
  int hbcomb[6];  */

// Run HiggsBounds 'full', i.e. with each Higgs result separately  
  /*HB_run_full(hbres, hbchan, hbobs, hbcomb);
 FILE *fHB;
 fHB = fopen("mH300mA450_tyI_HBAllowed.txt","app");
 if(hbobs[0]<1){
 fprintf(fHB, " %f\t%f\t%f\n", sba_in, cba_in, tb_in); }
 fclose(fHB); */
 //printf("\nHiggsBounds results (full):\n");
  //printf("  Higgs  res  chan       ratio        ncomb\n");
  //for (int i=1;i<=4;i++) {
    //printf("%5d %5d %6d %16.8E %5d   %s\n", i, hbres[i],hbchan[i],hbobs[i],hbcomb[i],hbobs[i]<1 ? "Allowed" : "Excluded");
  //}
  //printf("------------------------------------------------------------\n");
  //printf("  TOT %5d %6d %16.8E %5d   %s\n", hbres[0],hbchan[0],hbobs[0],hbcomb[0],hbobs[0]<1 ? "ALLOWED" : "EXCLUDED");
 /* FILE *fpp;
  fpp=fopen("huberbp_tyI_150_300_sba_cba_tb_csqmu_csqmh_csqtot.txt","app");
*/ 
/*  double csqmu;
  double csqmh;
  double csqtot;
  int nobs;
  double pval;
  */
 // double dMh[3]={0., 0., 0.,};
 // HS_set_mass_uncertainties(dMh);
 
 // HS_run(&csqmu, &csqmh, &csqtot, &nobs, &pval);
 // fprintf(fpp,"%f\t%f\t%f\t%f\t%f\t%f\t",sba_in, cba_in, tb_in, csqmu, csqmh, csqtot);
 // fclose(fpp);
  //printf("\nHiggsSignals results:\n");
  //printf(" Chi^2 from rates: %16.8E\n", csqmu);
  //printf("  Chi^2 from mass: %16.8E\n", csqmh);
  //printf("      Total chi^2: %16.8E\n", csqtot);
  //printf("    # observables: %16d\n\n", nobs);
//#endif 

  // Write LesHouches-style output
  model.write_LesHouches(file,true,true,true,true);

  // Print Higgs decays to the screen
  DecayTable table(model);
  THDM tabbble(model);

  double BrHhh = table.get_gamma_hhh(2,1,1)/table.get_gammatot_h(2);
  double BrHbb = table.get_gamma_hdd(2,3,3)/table.get_gammatot_h(2);
  double BrHtata = table.get_gamma_hll(2,3,3)/table.get_gammatot_h(2);
  double BrHzz = table.get_gamma_hvv(2,2)/table.get_gammatot_h(2); 
  double BrHww = table.get_gamma_hvv(2,3)/table.get_gammatot_h(2);
  double BrHgaga = table.get_gamma_hgaga(2)/table.get_gammatot_h(2);
  double BrHtt = table.get_gamma_huu(2,3,3)/table.get_gammatot_h(2);
  double BrHgg = table.get_gamma_hgg(2)/table.get_gammatot_h(2);
  double BrAZh = table.get_gamma_hvh(3,2,1)/table.get_gammatot_h(3);
  double BrAZH = table.get_gamma_hvh(3,2,2)/table.get_gammatot_h(3);
  double BrAgaga = table.get_gamma_hgaga(3)/table.get_gammatot_h(3);
  double BrAtautau = table.get_gamma_hll(3,3,3)/table.get_gammatot_h(3);
  double Brhbb = table.get_gamma_hdd(1,3,3)/table.get_gammatot_h(1);
  double Brhtautau = table.get_gamma_hll(1,3,3)/table.get_gammatot_h(1);
  double Brhww = table.get_gamma_hvv(1,3)/table.get_gammatot_h(1);
  double Brhgaga = table.get_gamma_hgaga(1)/table.get_gammatot_h(1);
  double Brhgg = table.get_gamma_hgg(1)/table.get_gammatot_h(1);
  double BrAgg = table.get_gamma_hgg(3)/table.get_gammatot_h(3);
  double Brhzz = table.get_gamma_hvv(1,2)/table.get_gammatot_h(1);
  double Gammah = table.get_gammatot_h(1);
  double GammaH = table.get_gammatot_h(2);
  double GammaA = table.get_gammatot_h(3);
  double gammatomassA = table.get_gammatot_h(3)/mA_in;
  //double testsbap = tabbble.get_sbap();
  double Gammahww = table.get_gamma_hvv(1,3);
  double Gammahzz = table.get_gamma_hvv(1,2);
  double Gammahbb = table.get_gamma_hdd(1,3,3);
  double Gamhgg = table.get_gamma_hgg(1);
  double testcba = tabbble.get_cba();
  double testsba = tabbble.get_sba();
  double testsbap = tabbble.get_sbap();
  double testcbap = tabbble.get_cbap();
  complex<double> khvvsq = table.hvv_coup_sq(3,1);
  double M = model.get_hmass(1);
  //double hww_all = table.hvv_allp(1,3);
  double mult_hvv = tabbble.mult_hvv(1);
  double mult_Hvv = tabbble.mult_hvv(2);
  double xx1 = tabbble.get_XX1();
  double xx2 = tabbble.get_XX2();
  double yy = tabbble.get_YY();
  double qkii11 = tabbble.qkii11();
  double qkii21 = tabbble.qkii21();
  double coupling_hww = tabbble.get_coupling_hww();
  complex <double> testhwwscale = tabbble.get_hwwscale();
  table.print_decays(1);
  //table.print_decays(2);
  //table.print_decays(3);
  //table.print_decays(4);
  //DecayTable table(model);
 // FILE *fp;
 // fp=fopen("tyII_stab_unit_pert_150_485_485_mustar_theo_sba_cba_tb_S_T_U_stab_unit_pert_vivid.txt","app");
  //fpp=fopen("huberbp_tyII_410_475_485_sba_cba_tb_BrHhh_BrHbb_BrHtautau_BrHzz_BrHww_BrHgaga_BrAzh_Agaga_Atata_hbb_htata_hww_hzz_hgaga_mod_n133_1000.txt","app");
 

  //printf("\n");
  //printf(" Oblique S: %12.5e\n", S);  
  //printf(" Oblique T: %12.5e\n", T);
  //printf(" Oblique U: %12.5e\n", U); 
  //printf("%d\n",(constr.check_stability() ? 1 : 0) );

 // if((constr.check_perturbativity() ? 1 : 0) == 0 || (constr.check_stability() ? 1 : 0) == 0 || (constr.check_unitarity() ? 1 : 0) == 0){
  //if((constr.check_stability() ? 1 : 0) == 0 || (constr.check_unitarity() ? 1 : 0) == 0){
 // fprintf(fp,"%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\t%d\n", testsba, testcba, tb_in, S, T, U, (constr.check_stability() ? 1 : 0), (constr.check_unitarity() ? 1 : 0), (constr.check_perturbativity() ? 1 : 0));}
   //printf("%f\t%f\t%f\t%d\t%d\t%d\n",sba_in, cba_in ,tb_in,(constr.check_stability() ? 1 : 0), (constr.check_unitarity() ? 1 : 0),    (constr.check_perturbativity() ? 1 : 0));}
 // fclose(fp);



 // printf("%f\t%f\t%f\t%f\t%f\t%f",BrHww,BrHzz,BrHhh,BrHtata,BrHbb,BrHgaga);
  //printf("%f\t%f\n",testcba,testsba);
  //printf("%f\t%f\t%f\t%f\n",testhwwscale,Gamhww,Brhww,Gammah);
  /*complex <double> qk11 = tabbble.get_qki(1,1);
  complex <double> qk12 = tabbble.get_qki(1,2);
  complex <double> qk21 = tabbble.get_qki(2,1);
  complex <double> qk22 = tabbble.get_qki(2,2);
  double testcba = tabbble.get_cba();
  double testsba = tabbble.get_sba();
  double testsbap = tabbble.get_sbap();
  double testcbap = tabbble.get_cbap();
  printf("%f\t%f\n",testcba,testsba);
  printf("%f\t%f\n",testsbap,testcbap);
  printf("%f\t%f\t%f\t%f\n",qk11,qk12,qk21,qk22);*/
  //printf("%f\t%f\t%f\t%f\t%f\t%f\n", table.get_gamma_hdd(1,3,3), table.get_gamma_hll(1,3,3), table.get_gamma_hvv(1,3), table.get_gamma_hvv(1,2), table.get_gamma_hgaga(1),table.get_gammatot_h(1));
  //FILE *fp ;
  
  //fp=fopen("huberbp_theo_tyI_150_300_tyI_theo_sba_cba_tb_S_T_U_stab_unit_pert_mod.txt","app");
  //fpp=fopen("huberbp_tyI_150_300_sba_cba_tb_BrHhh_BrHbb_BrHtautau_BrHzz_BrHww_BrHgaga_BrAzh_Agaga_Atata_hbb_htata_hww_hzz_hgaga_mod_n133_1000.txt","app");
 

  //printf("\n");
  //printf(" Oblique S: %12.5e\n", S);  
  //printf(" Oblique T: %12.5e\n", T);
  //printf(" Oblique U: %12.5e\n", U); 
  //printf("%d\n",(constr.check_stability() ? 1 : 0) );

  //if((constr.check_perturbativity() ? 1 : 0) == 0 || (constr.check_stability() ? 1 : 0) == 0 || (constr.check_unitarity() ? 1 : 0) == 0){
   //fprintf(fp,"%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\t%d\n", sba_in, cba_in, tb_in, S, T, U, (constr.check_stability() ? 1 : 0), (constr.check_unitarity() ? 1 : 0),    (constr.check_perturbativity() ? 1 : 0));
   //printf("%f\t%f\t%f\t%d\t%d\t%d\n",sba_in, cba_in ,tb_in,(constr.check_stability() ? 1 : 0), (constr.check_unitarity() ? 1 : 0),    (constr.check_perturbativity() ? 1 : 0));}
  //fclose(fp);
  
 /* FILE *fpp1;
  fpp1=fopen("huberbp_tyI_150_300_sba_cba_tb_BrAzh_Agaga_Atata_hbb_htata_hww_hzz_hgaga_ch2_m1_750.txt","app");
  fprintf(fpp1,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", sba_in,cba_in, tb_in,BrAZh, BrAgaga, BrAtautau, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga);
  printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",sba_in,cba_in, tb_in, BrAZh, BrAgaga, BrAtautau, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga);
  fclose(fpp1);
*/
 //printf("%f\n",)
 //printf("%f\t%f\n",testcbap, testsbap);
  //printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",sba_in,cba_in, tb_in, BrAZh, BrAgaga, BrAtautau, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga,Gammah,Gamhww);
  /*FILE *fpp1;
  fpp1=fopen("BP2_1tev_redef_sba_cba_tb_Azh_Agaga_Atata_hbb_htata_hww_hzz_hgaga_hgg_Gammah_XX1_XX2_YY_sbap.txt","app");
  fprintf(fpp1,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", sba_in, cba_in, tb_in, BrAZh, BrAgaga, BrAtautau, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga, Brhgg, Gammah, xx1, xx2, yy, testsbap);
  printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",sba_in,cba_in, tb_in, BrAZh, BrAgaga, BrAtautau, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga);
  fclose(fpp1);*/
 //printf("%f\t%f\t%f\t%f\t%f\n",sba_in,cba_in, tb_in,Gamhgg,Brhgg);
// Print parameters than can be used as input for HDECAY
// model.print_hdecay();
  /*FILE *fpp1;
  fpp1=fopen("Ty2newbp_mH150_mA485_Hp485_tyII_sba_cba_tb_Hzz_Hww_Hhh_Hbb_Htata_Hgaga_Azh_AZH_Agaga_Atata_Agg_hbb_htata_hww_hzz_hgaga_hgg_Gammah_GammaH_GammaA_gammaAtoMA.txt","app");
  fprintf(fpp1,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",testsba, testcba, tb_in, BrHzz, BrHww, BrHhh, BrHbb, BrHtata, BrHgaga, BrAZh, BrAZH, BrAgaga, BrAtautau, BrAgg, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga, Brhgg, Gammah, GammaH,GammaA,gammatomassA);
  printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",testsba,testcba, tb_in, BrAZh, BrAgaga, BrAtautau, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga);
  fclose(fpp1);*/
/*#if defined HiggsBounds
  HB_finish();
  HS_finish();
#endif*/
  //FILE *fpp1;
  //fpp1=fopen("BP1_tyI_1tev_ReDo_sba_cba_tb_Hzz_Hww_Hhh_Hbb_Htata_Hgaga_Htt_Hgg_Azh_AZH_Agaga_Atata_Agg_hbb_htata_hww_hzz_hgaga_hgg_Gammah_GammaH_GammaA_gammaAtoMA.txt","app");
  //fprintf(fpp1,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",testsba, testcba, tb_in, BrHzz, BrHww, BrHhh, BrHbb, BrHtata, BrHgaga,BrHtt,BrHgg, BrAZh, BrAZH, BrAgaga, BrAtautau, BrAgg, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga, Brhgg, Gammah, GammaH,GammaA,gammatomassA);
  printf("sba = %f\t cba= %f\t khvvp=%f\t kHvvp=%f\t mult_hvv = %f\t, mult_Hvv = %f\t qkii11=%f\t qkii21=%f\t coupling_hww = %f\t khvvsq=(%f,%f)\t  tb =%f\t brhbb=%f\t brhtata =%f\t brhww = %f\t brhzz = %f\t brhgaga = %f\t gammahbb=%f\t gammahww= %f\t  gammah= %f\n", testsba, testcba, testsbap, testcbap, mult_hvv, mult_Hvv, qkii11, qkii21, coupling_hww, khvvsq, tb_in, Brhbb, Brhtautau, Brhww, Brhzz, Brhgaga, Gammahbb, Gammahww, Gammah);
  //fclose(fpp1);
}
