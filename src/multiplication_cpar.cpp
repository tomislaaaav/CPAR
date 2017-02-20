#include "multiplication_cpar.h"
using namespace std;

void OnMultLineCPAR(int m_ar, int m_br)
{
    SYSTEMTIME Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);



    Time1 = clock();

	// CHANGE
	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_br; j++)
		{	temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

    Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	cout << "Result matrix: " << endl;
	for(i=0; i<1; i++) {
		for(j=0; j<min(10,m_br); j++) {
			cout << phc[j] << " ";
		}
	}
	cout << endl;

    free(pha);
    free(phb);
    free(phc);
}

void OnMultCPAR(int m_ar, int m_br) 
{
	
	double Time1, Time2;
	
	char st[100];
	double temp = 0;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++) {
			phb[i*m_br + j] = (double)(i+1);
		}

    Time1 = omp_get_wtime();

	for(i=0; i<m_ar; i++) {
		for( j=0; j<m_br; j++) {
			temp = 0;
			#pragma omp parallel for
			for( k=0; k<m_ar; k++) {	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j];
			}
		}
	}


    Time2 = omp_get_wtime();
	sprintf(st, "Time: %3.3f seconds\n", (Time2 - Time1));
	cout << st;

	cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;

    free(pha);
    free(phb);
    free(phc);
	
	
}