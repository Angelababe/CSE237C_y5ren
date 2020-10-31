
typedef float DTYPE;
#define SIZE 256 		/* SIZE OF DFT */
void dft(DTYPE input_real[SIZE], DTYPE input_imag[SIZE], DTYPE XX_R[SIZE], DTYPE XX_I[SIZE]);
void mvp (int i, int j,DTYPE real, DTYPE imag, DTYPE input_real[SIZE], DTYPE input_imag[SIZE],DTYPE real_sample[SIZE], DTYPE imag_sample[SIZE]);
void split1 (DTYPE *real, DTYPE *imag, DTYPE real_sample, DTYPE imag_sample);
