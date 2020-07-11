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

// https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
static inline float sqrt1(const float x)
{
  union {
    int i;
    float x;
  } u;
  u.x = x;
  u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

  // Two Babylonian Steps (simplified from:)
  // u.x = 0.5f * (u.x + x/u.x);
  // u.x = 0.5f * (u.x + x/u.x);
  u.x =         u.x + x / u.x;
  u.x = 0.25f * u.x + x / u.x;

  return u.x;
}

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
    }
  }
  

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

// Hanning window
// https://www.mathworks.com/help/signal/ref/hann.html
// https://community.sw.siemens.com/s/article/window-types-hanning-flattop-uniform-tukey-and-exponential
static const uint8_t HANNING[128] = {
  20,  20,  21,  21,  21,  21,  22,  22,  23,  23,  24,  25,  25,  26,  27,  28,
  29,  31,  32,  33,  34,  36,  37,  39,  40,  42,  44,  45,  47,  49,  51,  53,
  55,  57,  59,  61,  64,  66,  68,  71,  73,  75,  78,  80,  83,  85,  88,  91,
  93,  96,  99, 101, 104, 107, 110, 113, 115, 118, 121, 124, 127, 130, 133, 136,
 138, 141, 144, 147, 150, 153, 156, 159, 161, 164, 167, 170, 173, 175, 178, 181,
 183, 186, 189, 191, 194, 196, 199, 201, 204, 206, 208, 211, 213, 215, 217, 219,
 221, 223, 225, 227, 229, 231, 233, 234, 236, 237, 239, 240, 242, 243, 244, 245,
 247, 248, 249, 249, 250, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255, 255
};

void fft_fast(int16_t *xre, int16_t *xim) {
  // apply Hanning window
  for (uint32_t i=0; i<N/2; i++) {
    xre[i] = ((int32_t)xre[i]) * HANNING[i] / 255;
    xre[N-1-i] = ((int32_t)xre[N-1-i]) * HANNING[i] / 255;
  }

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

  // compute spectral power
  for (uint32_t i=0; i<N/4; i++) {
    int32_t re = xre[i];
    int32_t im = xim[i];
    int32_t power_sq = (re * re + im * im) >> 7;
    xre[i] = sqrt1(power_sq) + 0.5f;
  }
}
