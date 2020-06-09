/* ********************************************************************
* maxqfft.h
* July 01 , 2005
* Paul Holden (Paul Holden@maximhq.com)
* Maxim Integrated Products
 
* NOTE: All fft input/outputs are signed and in Q8.7 notation
* Copyright (C) 2005 Maxim/Dallas Semiconductor Corporation,
* All Rights Reserved .
[... copyright de la note d’application de maxim]
*/

#ifndef     __MAXQ_FFT_H__
#define     __MAXQ_FFT_H__


void main_fft(short *x_n_re, short *x_n_im);

void fft_fast(short *xre,short *xim);

#endif