#include "../../inc/types.h"
#include "../../inc/ME.h"
#include "../../inc/coder.h"

int fullSearch(MEPARM *meparm, unsigned int meRange) {
	printf("entrou \n");
    int half = meRange / 2;
    int h, w;

    int SAD, bestSAD = MAX;

    int operations = 0;

    int truncFLAG = 0;

    gsl_matrix_uchar *candBlock;
    gsl_matrix_uchar *targetBlock = meparm->targetBlock;
    gsl_matrix_uchar_view tempV;

    for (h = half; h >= -half; h--) {
		printf("Passou 1 FS\n");        
		for (w = -half; w <= half; w++) {
            if (isInsideFrame(h, w)) {
				printf("Passou 2 FS\n");                
				extractCandBlock(h, w);
				printf("Passou 3 FS\n");
                truncFLAG = SADCalc(targetBlock, candBlock, &SAD, bestSAD, meparm->PEL, &operations);
				printf("Passou 4 FS\n");
				
                if (!truncFLAG) {
                    meparm->vh = h;
                    meparm->vw = w;
                    bestSAD = SAD;
                }
                operations++;
            }
        }
    }
    return operations;
}
