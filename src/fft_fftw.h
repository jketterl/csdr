#pragma once

#ifdef USE_FFTW
//http://www.fftw.org/doc/Complex-One_002dDimensional-DFTs.html
//http://www.fftw.org/doc/Precision.html

#include <fftw3.h>
#define FFT_LIBRARY_USED "fftw3"

#define fft_malloc fftwf_malloc
#define fft_free fftwf_free

typedef struct fft_plan_s
{
	int size;
	void* input;
	void* output;
	fftwf_plan plan;
} fft_plan_t;

#include "libcsdr.h"

fft_plan_t* make_fft_c2c(int size, complexf* input, complexf* output, int forward, int benchmark);
fft_plan_t* make_fft_r2c(int size, float* input, complexf* output, int benchmark);
fft_plan_t* make_fft_c2r(int size, complexf* input, float* output, int benchmark);
void fft_execute(fft_plan_t* plan);
void fft_destroy(fft_plan_t* plan);

/*
 * FFTW_MEASURE is inacceptably slow when there is no hardware cycle counter
 * available. Unfortunately, there's no way to detect this at compile- or
 * runtime.
 *
 * this is a problem on ARM CPUs, so we disable FFTW_MEASURE for those.
 *
 * additional information: http://www.fftw.org/fftw3_doc/Cycle-Counters.html
 *
 * https://github.com/simonyiszk/openwebrx/issues/139
 */
#if defined __arm__ || __aarch64__
#define CSDR_FFTW_MEASURE FFTW_ESTIMATE
#else
#define CSDR_FFTW_MEASURE FFTW_MEASURE
#endif

#endif
