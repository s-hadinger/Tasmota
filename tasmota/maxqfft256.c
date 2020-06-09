#include <stdlib.h>
 
// 23 secondes de TF devient 5 par FFT et 4 par FFT fast
//
// on a deux tableaux de N donnees , pour R et iR
// mais les donnees initiales sont reelles => X(N-n)=X(n)ˆ* ou‘ X // est la transformee de Fourier de x (X1=TF(x1), X2=TF(x2))
// si on concatene x1 (dans R) et x2 (dans iR), alors on retrouve X1 et X2 par // Re(X1)= (ReX(n)+ReX(N-n))/2
// Im(X1)= (ImX(n)-ImX(N-n))/2 // Re(X2)= (ImX(n)+ImX(N-n))/2
// Im(X2)=-(ReX(n)-ReX(N-n))/2

/* ********************************************************************
 * maxqfft . c
 *
 * July 01 , 2005
 *
 * Paul Holden (Paul Holden@maximhq.com)
 * Maxim Integrated Products
 * NOTE: All fft input/outputs are signed and in Q8.7 notation
 * Copyright (C) 2005 Maxim/Dallas Semiconductor Corporation , * All Rights Reserved .
 [... copyright dans la note d’application de Maxim]
*/

#include "maxqfft256.h"
#include <stdint.h>

/* DEFINE STATEMENTS */
#define N       256
#define N_DIV_2 128
#define LOG_2_N 8
#define N_MINUS_1 ((N)-1)

// from https://stackoverflow.com/questions/2602823/in-c-c-whats-the-simplest-way-to-reverse-the-order-of-bits-in-a-byte
// First the left four bits are swapped with the right four bits. Then all adjacent pairs are swapped and then all adjacent single bits. This results in a reversed order.
static inline uint8_t reverseBitsInByte(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

/*
cosine Look-Up Table: An LUT for the cosine function in Q8.7. The table was created with the following program:
  #include <stdio .h>
  #include <math.h> #define N 256
  void main(int argc, char* argv[]) {
    printf(”const int cosLUT[%d] =\n{\n”,N/2);
    for(int i=0; i<N/2; i++) {
      printf(”%+4d”,(int)(128*cos(2*M PI*i/N)));
      if (i<(N/2-1)) printf(”,”);
      if ((i+1)%16==0) printf(”\n”);
    }
    printf (”};\n”);
  }
*/

static const int8_t cosLUT[N_DIV_2] = {  
  +127 ,+127 ,+127 ,+127 ,+127 ,+127 ,+126 ,+126 ,+125 ,+124 ,+124 ,+123 ,+122 ,+121 ,+120 ,+119 ,
  +118,+117,+115,+114,+112,+111,+109,+108,+106,+104,+102,+100, +98, +96, +94, +92,
  +90, +88, +85, +83, +81, +78, +76, +73, +71, +68, +65, +63, +60, +57, +54,
  +51, +48, +46, +43, +40, +37, +34, +31, +28, +24, +21, +18, +15, +12, +9, +6, +3,
  +0, -3, -6, -9, -12, -15, -18, -21, -24, -28, -31, -34, -37, -40, -43, -46,
  -48, -51, -54, -57, -60, -63, -65, -68, -71, -73, -76, -78, -81, -83, -85, -88,
  -90, -92, -94, -96, -98,-100,-102,-104,-106,-108,-109,-111,-112,-114,-115,-117,
  -118,-119,-120,-121,-122,-123,-124,-124,-125,-126,-126,-127,-127,-127,-127,-127
};

/*
  sine Look-Up Table: An LUT for the sine function in Q8.7. The table was created with the following program:
  #include <stdio .h>
  #include <math.h>

  #define N 256
  void main(int argc, char* argv[]) {
    printf(”const int sinLUT[%d] =\n{\n”,N/2);
    for(int i=0; i<N/2; i++) {
      printf(”%+4d”,(int)(128*sin(2*M PI*i/N)));
      if (i<(N/2-1)) printf(”,”);
      if ((i+1)%16==0) printf(”\n”);
    }
    printf (”};\n”) ;
  }
*/
static const int8_t sinLUT[N_DIV_2] = {
+0, +3, +6, +9, +12, +15, +18, +21, +24, +28, +31, +34, +37, +40, +43, +46,
+48, +51, +54, +57, +60, +63, +65, +68, +71, +73, +76, +78, +81, +83, +85, +88,
+90, +92, +94, +96, +98,+100,+102,+104,+106,+108,+109,+111,+112,+114,+115,+117,
+118 ,+119 ,+120 ,+121 ,+122 ,+123 ,+124 ,+124 ,+125 ,+126 ,+126 ,+127 ,+127 ,+127 ,+127 ,+127 ,
+127 ,+127 ,+127 ,+127 ,+127 ,+127 ,+126 ,+126 ,+125 ,+124 ,+124 ,+123 ,+122 ,+121 ,+120 ,+119 ,
+118,+117,+115,+114,+112,+111,+109,+108,+106,+104,+102,+100, +98, +96, +94, +92,
+90, +88, +85, +83, +81, +78, +76, +73, +71, +68, +65, +63, +60, +57, +54, +51,
+48, +46, +43, +40, +37, +34, +31, +28, +24, +21, +18, +15, +12, +9, +6, +3
};

void main_fft(int16_t *x_n_re, int16_t *x_n_im) {
  /* 4.0. Variable Declaration and Initialization */
  int16_t i ; // Misc index
  int32_t n_of_b = N_DIV_2; // Number of butterflies
  int32_t s_of_b = 1; // Size of butterflies
        
  int32_t a_index = 0; // fft data index
  int32_t a_index_ref = 0; // fft data index reference
     
  char stage = 0; // Stage of the fft , 0 to (Log2(N)-1)
  int32_t nb_index ; // Number of butterflies index
  int32_t sb_index ; // Size of butterflies index
    
  int32_t resultMulReCos ;
  int32_t resultMulImCos ;
  int32_t resultMulReSin ;
  int32_t resultMulImSin ;
  int32_t b_index; // 2nd fft data index
 
  int32_t tf_index ; // The twiddle factor index

  for (uint8_t i = 1; i < 240; i++) {
    uint8_t i_rev = reverseBitsInByte(i);
    int16_t tmp;
    if (i_rev > i) {
      tmp = x_n_re[i];
      x_n_re[i] = x_n_re[i_rev];
      x_n_re[i_rev] = tmp;

      // tmp = x_n_im[i];
      // x_n_im[i] = x_n_im[i_rev];
      // x_n_im[i_rev] = tmp;
    }
  }
  // unsigned int i ;
  /*
  i=x_n_re[  1]; x_n_re[  1]=x_n_re[128]; x_n_re[128]=i;
  i=x_n_re[  2]; x_n_re[  2]=x_n_re[ 64]; x_n_re[ 64]=i;
  i=x_n_re[  3]; x_n_re[  3]=x_n_re[192]; x_n_re[192]=i;
  i=x_n_re[  4]; x_n_re[  4]=x_n_re[ 32]; x_n_re[ 32]=i;
  i=x_n_re[  5]; x_n_re[  5]=x_n_re[160]; x_n_re[160]=i;
  i=x_n_re[  6]; x_n_re[  6]=x_n_re[ 96]; x_n_re[ 96]=i;
  i=x_n_re[  7]; x_n_re[  7]=x_n_re[224]; x_n_re[224]=i;
  i=x_n_re[  8]; x_n_re[  8]=x_n_re[ 16]; x_n_re[ 16]=i;
  i=x_n_re[  9]; x_n_re[  9]=x_n_re[144]; x_n_re[144]=i;
  i=x_n_re[ 10]; x_n_re[ 10]=x_n_re[ 80]; x_n_re[ 80]=i;
  i=x_n_re[ 11]; x_n_re[ 11]=x_n_re[208]; x_n_re[208]=i;
  i=x_n_re[ 12]; x_n_re[ 12]=x_n_re[ 48]; x_n_re[ 48]=i;
  i=x_n_re[ 13]; x_n_re[ 13]=x_n_re[176]; x_n_re[176]=i;
  i=x_n_re[ 14]; x_n_re[ 14]=x_n_re[112]; x_n_re[112]=i;
  i=x_n_re[ 15]; x_n_re[ 15]=x_n_re[240]; x_n_re[240]=i;
  i=x_n_re[ 17]; x_n_re[ 17]=x_n_re[136]; x_n_re[136]=i;
  i=x_n_re[ 18]; x_n_re[ 18]=x_n_re[ 72]; x_n_re[ 72]=i;
  i=x_n_re[ 19]; x_n_re[ 19]=x_n_re[200]; x_n_re[200]=i;
  i=x_n_re[ 20]; x_n_re[ 20]=x_n_re[ 40]; x_n_re[ 40]=i;
  i=x_n_re[ 21]; x_n_re[ 21]=x_n_re[168]; x_n_re[168]=i;
  i=x_n_re[ 22]; x_n_re[ 22]=x_n_re[104]; x_n_re[104]=i;
  i=x_n_re[ 23]; x_n_re[ 23]=x_n_re[232]; x_n_re[232]=i;
  i=x_n_re[ 25]; x_n_re[ 25]=x_n_re[152]; x_n_re[152]=i;
  i=x_n_re[ 26]; x_n_re[ 26]=x_n_re[ 88]; x_n_re[ 88]=i;
  i=x_n_re[ 27]; x_n_re[ 27]=x_n_re[216]; x_n_re[216]=i;
  i=x_n_re[ 28]; x_n_re[ 28]=x_n_re[ 56]; x_n_re[ 56]=i;
  i=x_n_re[ 29]; x_n_re[ 29]=x_n_re[184]; x_n_re[184]=i;
  i=x_n_re[ 30]; x_n_re[ 30]=x_n_re[120]; x_n_re[120]=i;
  i=x_n_re[ 31]; x_n_re[ 31]=x_n_re[248]; x_n_re[248]=i;
  i=x_n_re[ 33]; x_n_re[ 33]=x_n_re[132]; x_n_re[132]=i;
  i=x_n_re[ 34]; x_n_re[ 34]=x_n_re[ 68]; x_n_re[ 68]=i;
  i=x_n_re[ 35]; x_n_re[ 35]=x_n_re[196]; x_n_re[196]=i;
  i=x_n_re[ 37]; x_n_re[ 37]=x_n_re[164]; x_n_re[164]=i;
  i=x_n_re[ 38]; x_n_re[ 38]=x_n_re[100]; x_n_re[100]=i;
  i=x_n_re[ 39]; x_n_re[ 39]=x_n_re[228]; x_n_re[228]=i;
  i=x_n_re[ 41]; x_n_re[ 41]=x_n_re[148]; x_n_re[148]=i;
  i=x_n_re[ 42]; x_n_re[ 42]=x_n_re[ 84]; x_n_re[ 84]=i;
  i=x_n_re[ 43]; x_n_re[ 43]=x_n_re[212]; x_n_re[212]=i;
  i=x_n_re[ 44]; x_n_re[ 44]=x_n_re[ 52]; x_n_re[ 52]=i;
  i=x_n_re[ 45]; x_n_re[ 45]=x_n_re[180]; x_n_re[180]=i;
  i=x_n_re[ 46]; x_n_re[ 46]=x_n_re[116]; x_n_re[116]=i;
  i=x_n_re[ 47]; x_n_re[ 47]=x_n_re[244]; x_n_re[244]=i;
  i=x_n_re[ 49]; x_n_re[ 49]=x_n_re[140]; x_n_re[140]=i;
  i=x_n_re[ 50]; x_n_re[ 50]=x_n_re[ 76]; x_n_re[ 76]=i;
  i=x_n_re[ 51]; x_n_re[ 51]=x_n_re[204]; x_n_re[204]=i;
  i=x_n_re[ 53]; x_n_re[ 53]=x_n_re[172]; x_n_re[172]=i;
  i=x_n_re[ 54]; x_n_re[ 54]=x_n_re[108]; x_n_re[108]=i;
  i=x_n_re[ 55]; x_n_re[ 55]=x_n_re[236]; x_n_re[236]=i;
  i=x_n_re[ 57]; x_n_re[ 57]=x_n_re[156]; x_n_re[156]=i;
  i=x_n_re[ 58]; x_n_re[ 58]=x_n_re[ 92]; x_n_re[ 92]=i;
  i=x_n_re[ 59]; x_n_re[ 59]=x_n_re[220]; x_n_re[220]=i;
  i=x_n_re[ 61]; x_n_re[ 61]=x_n_re[188]; x_n_re[188]=i;
  i=x_n_re[ 62]; x_n_re[ 62]=x_n_re[124]; x_n_re[124]=i;
  i=x_n_re[ 63]; x_n_re[ 63]=x_n_re[252]; x_n_re[252]=i;
  i=x_n_re[ 65]; x_n_re[ 65]=x_n_re[130]; x_n_re[130]=i;
  i=x_n_re[ 67]; x_n_re[ 67]=x_n_re[194]; x_n_re[194]=i;
  i=x_n_re[ 69]; x_n_re[ 69]=x_n_re[162]; x_n_re[162]=i;
  i=x_n_re[ 70]; x_n_re[ 70]=x_n_re[ 98]; x_n_re[ 98]=i;
  i=x_n_re[ 71]; x_n_re[ 71]=x_n_re[226]; x_n_re[226]=i;
  i=x_n_re[ 73]; x_n_re[ 73]=x_n_re[146]; x_n_re[146]=i;
  i=x_n_re[ 74]; x_n_re[ 74]=x_n_re[ 82]; x_n_re[ 82]=i;
  i=x_n_re[ 75]; x_n_re[ 75]=x_n_re[210]; x_n_re[210]=i;
  i=x_n_re[ 77]; x_n_re[ 77]=x_n_re[178]; x_n_re[178]=i;
  i=x_n_re[ 78]; x_n_re[ 78]=x_n_re[114]; x_n_re[114]=i;
  i=x_n_re[ 79]; x_n_re[ 79]=x_n_re[242]; x_n_re[242]=i;
  i=x_n_re[ 81]; x_n_re[ 81]=x_n_re[138]; x_n_re[138]=i;
  i=x_n_re[ 83]; x_n_re[ 83]=x_n_re[202]; x_n_re[202]=i;
  i=x_n_re[ 85]; x_n_re[ 85]=x_n_re[170]; x_n_re[170]=i;
  i=x_n_re[ 86]; x_n_re[ 86]=x_n_re[106]; x_n_re[106]=i;
  i=x_n_re[ 87]; x_n_re[ 87]=x_n_re[234]; x_n_re[234]=i;
  i=x_n_re[ 89]; x_n_re[ 89]=x_n_re[154]; x_n_re[154]=i;
  i=x_n_re[ 91]; x_n_re[ 91]=x_n_re[218]; x_n_re[218]=i;
  i=x_n_re[ 93]; x_n_re[ 93]=x_n_re[186]; x_n_re[186]=i;
  i=x_n_re[ 94]; x_n_re[ 94]=x_n_re[122]; x_n_re[122]=i;
  i=x_n_re[ 95]; x_n_re[ 95]=x_n_re[250]; x_n_re[250]=i;
  i=x_n_re[ 97]; x_n_re[ 97]=x_n_re[134]; x_n_re[134]=i;
  i=x_n_re[ 99]; x_n_re[ 99]=x_n_re[198]; x_n_re[198]=i;
  i=x_n_re[101]; x_n_re[101]=x_n_re[166]; x_n_re[166]=i;
  i=x_n_re[103]; x_n_re[103]=x_n_re[230]; x_n_re[230]=i;
  i=x_n_re[105]; x_n_re[105]=x_n_re[150]; x_n_re[150]=i;
  i=x_n_re[107]; x_n_re[107]=x_n_re[214]; x_n_re[214]=i;
  i=x_n_re[109]; x_n_re[109]=x_n_re[182]; x_n_re[182]=i;
  i=x_n_re[110]; x_n_re[110]=x_n_re[118]; x_n_re[118]=i;
  i=x_n_re[111]; x_n_re[111]=x_n_re[246]; x_n_re[246]=i;
  i=x_n_re[113]; x_n_re[113]=x_n_re[142]; x_n_re[142]=i;
  i=x_n_re[115]; x_n_re[115]=x_n_re[206]; x_n_re[206]=i;
  i=x_n_re[117]; x_n_re[117]=x_n_re[174]; x_n_re[174]=i;
  i=x_n_re[119]; x_n_re[119]=x_n_re[238]; x_n_re[238]=i;
  i=x_n_re[121]; x_n_re[121]=x_n_re[158]; x_n_re[158]=i;
  i=x_n_re[123]; x_n_re[123]=x_n_re[222]; x_n_re[222]=i;
  i=x_n_re[125]; x_n_re[125]=x_n_re[190]; x_n_re[190]=i;
  i=x_n_re[127]; x_n_re[127]=x_n_re[254]; x_n_re[254]=i;
  i=x_n_re[131]; x_n_re[131]=x_n_re[193]; x_n_re[193]=i;
  i=x_n_re[133]; x_n_re[133]=x_n_re[161]; x_n_re[161]=i;
  i=x_n_re[135]; x_n_re[135]=x_n_re[225]; x_n_re[225]=i;
  i=x_n_re[137]; x_n_re[137]=x_n_re[145]; x_n_re[145]=i;
  i=x_n_re[139]; x_n_re[139]=x_n_re[209]; x_n_re[209]=i;
  i=x_n_re[141]; x_n_re[141]=x_n_re[177]; x_n_re[177]=i;
  i=x_n_re[143]; x_n_re[143]=x_n_re[241]; x_n_re[241]=i;
  i=x_n_re[147]; x_n_re[147]=x_n_re[201]; x_n_re[201]=i;
  i=x_n_re[149]; x_n_re[149]=x_n_re[169]; x_n_re[169]=i;
  i=x_n_re[151]; x_n_re[151]=x_n_re[233]; x_n_re[233]=i;
  i=x_n_re[155]; x_n_re[155]=x_n_re[217]; x_n_re[217]=i;
  i=x_n_re[157]; x_n_re[157]=x_n_re[185]; x_n_re[185]=i;
  i=x_n_re[159]; x_n_re[159]=x_n_re[249]; x_n_re[249]=i;
  i=x_n_re[163]; x_n_re[163]=x_n_re[197]; x_n_re[197]=i;
  i=x_n_re[167]; x_n_re[167]=x_n_re[229]; x_n_re[229]=i;
  i=x_n_re[171]; x_n_re[171]=x_n_re[213]; x_n_re[213]=i;
  i=x_n_re[173]; x_n_re[173]=x_n_re[181]; x_n_re[181]=i;
  i=x_n_re[175]; x_n_re[175]=x_n_re[245]; x_n_re[245]=i;
  i=x_n_re[179]; x_n_re[179]=x_n_re[205]; x_n_re[205]=i;
  i=x_n_re[183]; x_n_re[183]=x_n_re[237]; x_n_re[237]=i;
  i=x_n_re[187]; x_n_re[187]=x_n_re[221]; x_n_re[221]=i;
  i=x_n_re[191]; x_n_re[191]=x_n_re[253]; x_n_re[253]=i;
  i=x_n_re[199]; x_n_re[199]=x_n_re[227]; x_n_re[227]=i;
  i=x_n_re[203]; x_n_re[203]=x_n_re[211]; x_n_re[211]=i;
  i=x_n_re[207]; x_n_re[207]=x_n_re[243]; x_n_re[243]=i;
  i=x_n_re[215]; x_n_re[215]=x_n_re[235]; x_n_re[235]=i;
  i=x_n_re[223]; x_n_re[223]=x_n_re[251]; x_n_re[251]=i;
  i=x_n_re[239]; x_n_re[239]=x_n_re[247]; x_n_re[247]=i;
  */
  /*
  i=x_n_im[  1]; x_n_im[  1]=x_n_im[128]; x_n_im[128]=i;
  i=x_n_im[  2]; x_n_im[  2]=x_n_im[ 64]; x_n_im[ 64]=i;
  i=x_n_im[  3]; x_n_im[  3]=x_n_im[192]; x_n_im[192]=i;
  i=x_n_im[  4]; x_n_im[  4]=x_n_im[ 32]; x_n_im[ 32]=i;
  i=x_n_im[  5]; x_n_im[  5]=x_n_im[160]; x_n_im[160]=i;
  i=x_n_im[  6]; x_n_im[  6]=x_n_im[ 96]; x_n_im[ 96]=i;
  i=x_n_im[  7]; x_n_im[  7]=x_n_im[224]; x_n_im[224]=i;
  i=x_n_im[  8]; x_n_im[  8]=x_n_im[ 16]; x_n_im[ 16]=i;
  i=x_n_im[  9]; x_n_im[  9]=x_n_im[144]; x_n_im[144]=i;
  i=x_n_im[ 10]; x_n_im[ 10]=x_n_im[ 80]; x_n_im[ 80]=i;
  i=x_n_im[ 11]; x_n_im[ 11]=x_n_im[208]; x_n_im[208]=i;
  i=x_n_im[ 12]; x_n_im[ 12]=x_n_im[ 48]; x_n_im[ 48]=i;
  i=x_n_im[ 13]; x_n_im[ 13]=x_n_im[176]; x_n_im[176]=i;
  i=x_n_im[ 14]; x_n_im[ 14]=x_n_im[112]; x_n_im[112]=i;
  i=x_n_im[ 15]; x_n_im[ 15]=x_n_im[240]; x_n_im[240]=i;
  i=x_n_im[ 17]; x_n_im[ 17]=x_n_im[136]; x_n_im[136]=i;
  i=x_n_im[ 18]; x_n_im[ 18]=x_n_im[ 72]; x_n_im[ 72]=i;
  i=x_n_im[ 19]; x_n_im[ 19]=x_n_im[200]; x_n_im[200]=i;
  i=x_n_im[ 20]; x_n_im[ 20]=x_n_im[ 40]; x_n_im[ 40]=i;
  i=x_n_im[ 21]; x_n_im[ 21]=x_n_im[168]; x_n_im[168]=i;
  i=x_n_im[ 22]; x_n_im[ 22]=x_n_im[104]; x_n_im[104]=i;
  i=x_n_im[ 23]; x_n_im[ 23]=x_n_im[232]; x_n_im[232]=i;
  i=x_n_im[ 25]; x_n_im[ 25]=x_n_im[152]; x_n_im[152]=i;
  i=x_n_im[ 26]; x_n_im[ 26]=x_n_im[ 88]; x_n_im[ 88]=i;
  i=x_n_im[ 27]; x_n_im[ 27]=x_n_im[216]; x_n_im[216]=i;
  i=x_n_im[ 28]; x_n_im[ 28]=x_n_im[ 56]; x_n_im[ 56]=i;
  i=x_n_im[ 29]; x_n_im[ 29]=x_n_im[184]; x_n_im[184]=i;
  i=x_n_im[ 30]; x_n_im[ 30]=x_n_im[120]; x_n_im[120]=i;
  i=x_n_im[ 31]; x_n_im[ 31]=x_n_im[248]; x_n_im[248]=i;
  i=x_n_im[ 33]; x_n_im[ 33]=x_n_im[132]; x_n_im[132]=i;
  i=x_n_im[ 34]; x_n_im[ 34]=x_n_im[ 68]; x_n_im[ 68]=i;
  i=x_n_im[ 35]; x_n_im[ 35]=x_n_im[196]; x_n_im[196]=i;
  i=x_n_im[ 37]; x_n_im[ 37]=x_n_im[164]; x_n_im[164]=i;
  i=x_n_im[ 38]; x_n_im[ 38]=x_n_im[100]; x_n_im[100]=i;
  i=x_n_im[ 39]; x_n_im[ 39]=x_n_im[228]; x_n_im[228]=i;
  i=x_n_im[ 41]; x_n_im[ 41]=x_n_im[148]; x_n_im[148]=i;
  i=x_n_im[ 42]; x_n_im[ 42]=x_n_im[ 84]; x_n_im[ 84]=i;
  i=x_n_im[ 43]; x_n_im[ 43]=x_n_im[212]; x_n_im[212]=i;
  i=x_n_im[ 44]; x_n_im[ 44]=x_n_im[ 52]; x_n_im[ 52]=i;
  i=x_n_im[ 45]; x_n_im[ 45]=x_n_im[180]; x_n_im[180]=i;
  i=x_n_im[ 46]; x_n_im[ 46]=x_n_im[116]; x_n_im[116]=i;
  i=x_n_im[ 47]; x_n_im[ 47]=x_n_im[244]; x_n_im[244]=i;
  i=x_n_im[ 49]; x_n_im[ 49]=x_n_im[140]; x_n_im[140]=i;
  i=x_n_im[ 50]; x_n_im[ 50]=x_n_im[ 76]; x_n_im[ 76]=i;
  i=x_n_im[ 51]; x_n_im[ 51]=x_n_im[204]; x_n_im[204]=i;
  i=x_n_im[ 53]; x_n_im[ 53]=x_n_im[172]; x_n_im[172]=i;
  i=x_n_im[ 54]; x_n_im[ 54]=x_n_im[108]; x_n_im[108]=i;
  i=x_n_im[ 55]; x_n_im[ 55]=x_n_im[236]; x_n_im[236]=i;
  i=x_n_im[ 57]; x_n_im[ 57]=x_n_im[156]; x_n_im[156]=i;
  i=x_n_im[ 58]; x_n_im[ 58]=x_n_im[ 92]; x_n_im[ 92]=i;
  i=x_n_im[ 59]; x_n_im[ 59]=x_n_im[220]; x_n_im[220]=i;
  i=x_n_im[ 61]; x_n_im[ 61]=x_n_im[188]; x_n_im[188]=i;
  i=x_n_im[ 62]; x_n_im[ 62]=x_n_im[124]; x_n_im[124]=i;
  i=x_n_im[ 63]; x_n_im[ 63]=x_n_im[252]; x_n_im[252]=i;
  i=x_n_im[ 65]; x_n_im[ 65]=x_n_im[130]; x_n_im[130]=i;
  i=x_n_im[ 67]; x_n_im[ 67]=x_n_im[194]; x_n_im[194]=i;
  i=x_n_im[ 69]; x_n_im[ 69]=x_n_im[162]; x_n_im[162]=i;
  i=x_n_im[ 70]; x_n_im[ 70]=x_n_im[ 98]; x_n_im[ 98]=i;
  i=x_n_im[ 71]; x_n_im[ 71]=x_n_im[226]; x_n_im[226]=i;
  i=x_n_im[ 73]; x_n_im[ 73]=x_n_im[146]; x_n_im[146]=i;
  i=x_n_im[ 74]; x_n_im[ 74]=x_n_im[ 82]; x_n_im[ 82]=i;
  i=x_n_im[ 75]; x_n_im[ 75]=x_n_im[210]; x_n_im[210]=i;
  i=x_n_im[ 77]; x_n_im[ 77]=x_n_im[178]; x_n_im[178]=i;
  i=x_n_im[ 78]; x_n_im[ 78]=x_n_im[114]; x_n_im[114]=i;
  i=x_n_im[ 79]; x_n_im[ 79]=x_n_im[242]; x_n_im[242]=i;
  i=x_n_im[ 81]; x_n_im[ 81]=x_n_im[138]; x_n_im[138]=i;
  i=x_n_im[ 83]; x_n_im[ 83]=x_n_im[202]; x_n_im[202]=i;
  i=x_n_im[ 85]; x_n_im[ 85]=x_n_im[170]; x_n_im[170]=i;
  i=x_n_im[ 86]; x_n_im[ 86]=x_n_im[106]; x_n_im[106]=i;
  i=x_n_im[ 87]; x_n_im[ 87]=x_n_im[234]; x_n_im[234]=i;
  i=x_n_im[ 89]; x_n_im[ 89]=x_n_im[154]; x_n_im[154]=i;
  i=x_n_im[ 91]; x_n_im[ 91]=x_n_im[218]; x_n_im[218]=i;
  i=x_n_im[ 93]; x_n_im[ 93]=x_n_im[186]; x_n_im[186]=i;
  i=x_n_im[ 94]; x_n_im[ 94]=x_n_im[122]; x_n_im[122]=i;
  i=x_n_im[ 95]; x_n_im[ 95]=x_n_im[250]; x_n_im[250]=i;
  i=x_n_im[ 97]; x_n_im[ 97]=x_n_im[134]; x_n_im[134]=i;
  i=x_n_im[ 99]; x_n_im[ 99]=x_n_im[198]; x_n_im[198]=i;
  i=x_n_im[101]; x_n_im[101]=x_n_im[166]; x_n_im[166]=i;
  i=x_n_im[103]; x_n_im[103]=x_n_im[230]; x_n_im[230]=i;
  i=x_n_im[105]; x_n_im[105]=x_n_im[150]; x_n_im[150]=i;
  i=x_n_im[107]; x_n_im[107]=x_n_im[214]; x_n_im[214]=i;
  i=x_n_im[109]; x_n_im[109]=x_n_im[182]; x_n_im[182]=i;
  i=x_n_im[110]; x_n_im[110]=x_n_im[118]; x_n_im[118]=i;
  i=x_n_im[111]; x_n_im[111]=x_n_im[246]; x_n_im[246]=i;
  i=x_n_im[113]; x_n_im[113]=x_n_im[142]; x_n_im[142]=i;
  i=x_n_im[115]; x_n_im[115]=x_n_im[206]; x_n_im[206]=i;
  i=x_n_im[117]; x_n_im[117]=x_n_im[174]; x_n_im[174]=i;
  i=x_n_im[119]; x_n_im[119]=x_n_im[238]; x_n_im[238]=i;
  i=x_n_im[121]; x_n_im[121]=x_n_im[158]; x_n_im[158]=i;
  i=x_n_im[123]; x_n_im[123]=x_n_im[222]; x_n_im[222]=i;
  i=x_n_im[125]; x_n_im[125]=x_n_im[190]; x_n_im[190]=i;
  i=x_n_im[127]; x_n_im[127]=x_n_im[254]; x_n_im[254]=i;
  i=x_n_im[131]; x_n_im[131]=x_n_im[193]; x_n_im[193]=i;
  i=x_n_im[133]; x_n_im[133]=x_n_im[161]; x_n_im[161]=i;
  i=x_n_im[135]; x_n_im[135]=x_n_im[225]; x_n_im[225]=i;
  i=x_n_im[137]; x_n_im[137]=x_n_im[145]; x_n_im[145]=i;
  i=x_n_im[139]; x_n_im[139]=x_n_im[209]; x_n_im[209]=i;
  i=x_n_im[141]; x_n_im[141]=x_n_im[177]; x_n_im[177]=i;
  i=x_n_im[143]; x_n_im[143]=x_n_im[241]; x_n_im[241]=i;
  i=x_n_im[147]; x_n_im[147]=x_n_im[201]; x_n_im[201]=i;
  i=x_n_im[149]; x_n_im[149]=x_n_im[169]; x_n_im[169]=i;
  i=x_n_im[151]; x_n_im[151]=x_n_im[233]; x_n_im[233]=i;
  i=x_n_im[155]; x_n_im[155]=x_n_im[217]; x_n_im[217]=i;
  i=x_n_im[157]; x_n_im[157]=x_n_im[185]; x_n_im[185]=i;
  i=x_n_im[159]; x_n_im[159]=x_n_im[249]; x_n_im[249]=i;
  i=x_n_im[163]; x_n_im[163]=x_n_im[197]; x_n_im[197]=i;
  i=x_n_im[167]; x_n_im[167]=x_n_im[229]; x_n_im[229]=i;
  i=x_n_im[171]; x_n_im[171]=x_n_im[213]; x_n_im[213]=i;
  i=x_n_im[173]; x_n_im[173]=x_n_im[181]; x_n_im[181]=i;
  i=x_n_im[175]; x_n_im[175]=x_n_im[245]; x_n_im[245]=i;
  i=x_n_im[179]; x_n_im[179]=x_n_im[205]; x_n_im[205]=i;
  i=x_n_im[183]; x_n_im[183]=x_n_im[237]; x_n_im[237]=i;
  i=x_n_im[187]; x_n_im[187]=x_n_im[221]; x_n_im[221]=i;
  i=x_n_im[191]; x_n_im[191]=x_n_im[253]; x_n_im[253]=i;
  i=x_n_im[199]; x_n_im[199]=x_n_im[227]; x_n_im[227]=i;
  i=x_n_im[203]; x_n_im[203]=x_n_im[211]; x_n_im[211]=i;
  i=x_n_im[207]; x_n_im[207]=x_n_im[243]; x_n_im[243]=i;
  i=x_n_im[215]; x_n_im[215]=x_n_im[235]; x_n_im[235]=i;
  i=x_n_im[223]; x_n_im[223]=x_n_im[251]; x_n_im[251]=i;
  i=x_n_im[239]; x_n_im[239]=x_n_im[247]; x_n_im[247]=i;
  */

  /* 4.3. FFT: loop through the 0 to log2(N) stages of
    the butterfly computations . When the FFT begins , the input samples (x(n) ) are stored
    in x n re/x n im. When the FFT is done,
    the spectrum (X(n)) has replaced the input stored in xnre/xnim. */
  for (stage=0; stage<LOG_2_N; stage++) {
    for (nb_index=0; nb_index<n_of_b; nb_index++) {
      tf_index = 0; // The twiddle factor index
      for (sb_index=0; sb_index<s_of_b ; sb_index++) {
        b_index = a_index + s_of_b; // 2nd fft data index
        resultMulReCos = (int16_t) (((int32_t)cosLUT[tf_index] * (int32_t)x_n_re[b_index])>>7);
        resultMulReSin = (int16_t) (((int32_t)sinLUT[tf_index] * (int32_t)x_n_re[b_index])>>7);
        resultMulImCos = (int16_t) (((int32_t)cosLUT[tf_index] * (int32_t)x_n_im[b_index])>>7);
        resultMulImSin = (int16_t) (((int32_t)sinLUT[tf_index] * (int32_t)x_n_im[b_index])>>7);
    
        x_n_re[b_index] = x_n_re[a_index] - resultMulReCos + resultMulImSin;
        x_n_im[b_index] = x_n_im[a_index] - resultMulReSin - resultMulImCos;
        x_n_re[a_index] = x_n_re[a_index] + resultMulReCos - resultMulImSin;
        x_n_im[a_index] = x_n_im[a_index] + resultMulReSin + resultMulImCos;

        if (((sb_index+1) & (s_of_b-1)) == 0)
          a_index = a_index_ref;
        else
          a_index++;

        tf_index += n_of_b;
      }
      a_index = ((s_of_b<<1) + a_index) & N_MINUS_1;
      a_index_ref = a_index;
    }
    n_of_b >>= 1;
    s_of_b <<= 1;
  }
}

void fft_fast(int16_t *xre, int16_t *xim) {
  int32_t monxre,monxim,monyre,monyim,i;
  main_fft(xre,xim); // fft(x)
  for (i=0;i<N/2;i++) {
    monxre =  ((int32_t) xre[i] + (int32_t) xre[N-i]) / 2;
    monxim =  ((int32_t) xim[i] - (int32_t) xim[N-i]) / 2;
    monyre =  ((int32_t) xim[i] + (int32_t) xim[N-i]) / 2;
    monyim = -((int32_t) xre[i] + (int32_t) xre[N-i]) / 2;

    xre[i] = monxre;
    xim[i] = monxim;
    xre[N-i]=monyre;
    xim[N-i]=monyim;
  }
}

