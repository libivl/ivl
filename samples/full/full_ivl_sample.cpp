#include <ivl/array_2d.hpp>
#include <ivl/lina.hpp>
#include <cv.h>
#include <vector>

using namespace std;
using namespace ivl;

int main()
{

}



int fitEllip(vector<double> X, vector<double> Y, double *ellparam, IplImage *img)
//int* fitEllip()
{
	/*vector<double> X, Y;
	double tempx[20],tempy[30];

	X.push_back(152);X.push_back(152);X.push_back(153);X.push_back(153);X.push_back(154);X.push_back(154);X.push_back(155);X.push_back(155);X.push_back(156);X.push_back(156);X.push_back(157);X.push_back(157);
	X.push_back(158); X.push_back(158);X.push_back(159);X.push_back(159);X.push_back(160);X.push_back(160);X.push_back(161);

	Y.push_back(3);Y.push_back(4);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);
	Y.push_back(2); Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(4);Y.push_back(3);*/

	int flag=0;

	ivl::array<double> X_arr(X.size(), &(X[0]));
	ivl::array<double> Y_arr(Y.size(), &(Y[0]));

	double mx = ivl::mean(X_arr);
	double my = ivl::mean(Y_arr);
	double sx = (ivl::max(X_arr)-ivl::min(X_arr))/2;
    double sy = (ivl::max(Y_arr)-ivl::min(Y_arr))/2;
	double *x;// = (X-mx)/sx;
    double *y;// = (Y-my)/sy;
	CvMat *D, *Dtransp, *S;//*C
	//double **D, **Dtransp;
	//double C[6][6];

	x=new double[X.size()];
	y=new double[Y.size()];

	if (sx==0 || sy==0)
		return -1;

	for (int i=0; i<X.size(); i++)
	{
		x[i] = (X[i]-mx)/sx;
		y[i] = (Y[i]-my)/sy;
	}

	D=cvCreateMat(X.size(),6,CV_32FC1);
	Dtransp=cvCreateMat(6,X.size(),CV_32FC1);
	//C=cvCreateMat(6,6,CV_32FC1);
	S=cvCreateMat(6,6,CV_32FC1);
//	cvSetZero( C );
	cvSetZero( D );

	//	D = [ x.*x  x.*y  y.*y  x  y  ones(size(x)) ];
	for (int i=0; i<X.size(); i++)
	{
		CV_MAT_ELEM( *D, double, i, 0 )=x[i]*x[i];
		CV_MAT_ELEM( *D, double, i, 1 )=x[i]*y[i];
		CV_MAT_ELEM( *D, double, i, 2 )=y[i]*y[i];
		CV_MAT_ELEM( *D, double, i, 3 )=x[i];
		CV_MAT_ELEM( *D, double, i, 4 )=y[i];
		CV_MAT_ELEM( *D, double, i, 5 )=1.0;
	}

	cvTranspose(D, Dtransp);

	// S = D'*D;
	cvMatMul(Dtransp, D, S);

	//C(6,6) = 0; C(1,3) = -2; C(2,2) = 1; C(3,1) = -2;

//-------------------------------------------- MATLAB ENGINE ------------------------------
	double doubleS[6][6];
	double C[6][6]={0};

	for (int i=0; i<6; i++)
	{
		for (int j=0; j<6; j++)
		{
			doubleS[i][j]=CV_MAT_ELEM( *S, double, i, j );
			if (ivl::isnan(doubleS[i][j]) || ivl::isinf(doubleS[i][j]) )
				return -1;
			C[i][j]=0.0;
		}
	}
	C[5][5] = 0; C[0][2] = -2; C[1][1] = 1; C[2][0] = -2;

#if 0
	mxArray *m_S, *m_C, *m_gevec, *m_geval ;

	m_S=mxCreateDoubleMatrix(6, 6, mxREAL);
	m_C=mxCreateDoubleMatrix(6, 6, mxREAL);
	m_gevec=mxCreateDoubleMatrix(6, 6, mxREAL);
	m_geval=mxCreateDoubleMatrix(6, 6, mxREAL);

	memcpy((void *)mxGetPr(m_S), (void *)doubleS, sizeof(double)*36);
	memcpy((void *)mxGetPr(m_C), (void *)C, sizeof(double)*36);
	engPutVariable(m_pEngine, "S", m_S);
	engPutVariable(m_pEngine, "C", m_C);
	engPutVariable(m_pEngine, "gevec", m_gevec);
	engPutVariable(m_pEngine, "geval", m_geval);

	engEvalString(m_pEngine, "[gevec, geval] = eig(S,C);" );

	/*double *buffer= '\0';
	engOutputBuffer(m_geval, buffer, 36);*/

	m_geval = engGetVariable(m_pEngine, "geval");
	m_gevec = engGetVariable(m_pEngine, "gevec");

	double *temp=(double*)mxGetData(m_geval);
#endif


	ivl::array_2d<std::complex<double> > geval; // geval
	ivl::array_2d<std::complex<double> > gevec;

	ivl::lvalue(geval, gevec) =

		ivl::eig++(
			ivl::array_2d<double>(ivl::idx(6, 6), (double*)doubleS),
			ivl::array_2d<double>(ivl::idx(6, 6), (double*)C));



	int negEigPos=-1;
	for (int i=0; i<36; i++)
	{
		if (ivl::lt(geval[i],std::complex<double>(0.0, 0.0))  && !isinf(geval[i])) //&& _isnan(temp[i])
		{
			negEigPos=i;
			break;
		}
	}

	if (negEigPos!=-1)
	{
		double A[6];//,outa[6];
		//temp=(double*)mxGetData(m_gevec);
		for (int i=0; i<6; i++)
		{
			A[i]=gevec[negEigPos+i].real();
		}

		ellparam[0] = A[0]*sy*sy;
		ellparam[1] = A[1]*sx*sy;
		ellparam[2] = A[2]*sx*sx;
		ellparam[3] = -2*A[0]*sy*sy*mx - A[1]*sx*sy*my + A[3]*sx*sy*sy;
		ellparam[4] = -A[1]*sx*sy*mx - 2*A[2]*sx*sx*my + A[4]*sx*sx*sy;
		ellparam[5] = A[0]*sy*sy*mx*mx + A[1]*sx*sy*mx*my + A[2]*sx*sx*my*my-A[3]*sx*sy*sy*mx - A[4]*sx*sx*sy*my+ A[5]*sx*sx*sy*sy;
		ellparam[6] = floor(mx);
		ellparam[7] = floor(my);

		/*int flag=0;
		for (int i=0; i<6; i++)
		{
			if (ellparam[i]<DBL_EPSILON)
			//if (ellparam[i]==nan_num)
			{
				flag=-1;
			}
		}*/
	}
	else
	{
		flag=-1;
	}

/*
	mxDestroyArray(m_S);
	mxDestroyArray(m_C);
	mxDestroyArray(m_gevec);
	mxDestroyArray(m_geval);*/
	return flag;
}




#if 0
int LAPACK_fitEllip(vector<double> X, vector<double> Y, double *ellparam, IplImage *img)
{
	//X.push_back(152);X.push_back(152);X.push_back(153);X.push_back(153);X.push_back(154);X.push_back(154);X.push_back(155);X.push_back(155);X.push_back(156);X.push_back(156);X.push_back(157);X.push_back(157);
	//X.push_back(158); X.push_back(158);X.push_back(159);X.push_back(159);X.push_back(160);X.push_back(160);X.push_back(161);
	//Y.push_back(3);Y.push_back(4);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(5);
	//Y.push_back(2); Y.push_back(5);Y.push_back(2);Y.push_back(5);Y.push_back(2);Y.push_back(4);Y.push_back(3);
	doublereal pA[36], pB[36];

	int flag=0;
	double mx = meanvec(X);
	double my = meanvec(Y);
	double sx = (maxvec(X)-minvec(X))/2;
    double sy = (maxvec(Y)-minvec(Y))/2;
	double *x;// = (X-mx)/sx;
    double *y;// = (Y-my)/sy;
	CvMat *D, *Dtransp, *S;//*C
	//double **D, **Dtransp;
	//double C[6][6];

	x=new double[X.size()];
	y=new double[Y.size()];

	if (sx==0 || sy==0)
		return -1;

	for (int i=0; i<X.size(); i++)
	{
		x[i] = (X[i]-mx)/sx;
		y[i] = (Y[i]-my)/sy;
	}

	D=cvCreateMat(X.size(),6,CV_32FC1);
	Dtransp=cvCreateMat(6,X.size(),CV_32FC1);
	//C=cvCreateMat(6,6,CV_32FC1);
	S=cvCreateMat(6,6,CV_32FC1);
//	cvSetZero( C );
	cvSetZero( D );

	//	D = [ x.*x  x.*y  y.*y  x  y  ones(size(x)) ];
	for (int i=0; i<X.size(); i++)
	{
		CV_MAT_ELEM( *D, double, i, 0 )=x[i]*x[i];
		CV_MAT_ELEM( *D, double, i, 1 )=x[i]*y[i];
		CV_MAT_ELEM( *D, double, i, 2 )=y[i]*y[i];
		CV_MAT_ELEM( *D, double, i, 3 )=x[i];
		CV_MAT_ELEM( *D, double, i, 4 )=y[i];
		CV_MAT_ELEM( *D, double, i, 5 )=1.0;
	}

	cvTranspose(D, Dtransp);

	// S = D'*D;
	cvMatMul(Dtransp, D, S);

	//C(6,6) = 0; C(1,3) = -2; C(2,2) = 1; C(3,1) = -2;

	double doubleS[6][6];
	double C[6][6]={0};

	for (int i=0; i<6; i++)
	{
		for (int j=0; j<6; j++)
		{
			doubleS[i][j]=CV_MAT_ELEM( *S, double, i, j );
			if (_isnan(doubleS[i][j]) || !_finite(doubleS[i][j]) )
				return -1;
			C[i][j]=0.0;
		}
	}
	C[5][5] = 0; C[0][2] = -2; C[1][1] = 1; C[2][0] = -2;

	int num=0;
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<6; j++)
		{
			pA[num]=CV_MAT_ELEM( *S, float, i, j );
			pB[num]=CV_MAT_ELEM( *C, float, i, j );
			//cout << pA[num] << "  ";
		}
		//cout <<endl;
	}


	int i, j;
	char jobvl = 'N', jobvr = 'N';
	integer nn = 6, one = 1, lwork, info;
	doublereal tmp, *work;
	doublereal VR, VL, alphar[6], alphai[6], beta[6];

	lwork = -1;
	dggev_(&jobvl, &jobvr, &nn, pA, &nn, pB, &nn, alphar, alphai, beta, &VL, &one, &VR, &one,&tmp, &lwork, &info);

	lwork = (integer) tmp;
	printf("\ndggev: lwork = %ld\n", lwork);
	work = (doublereal *) malloc(sizeof(doublereal)*lwork);

	dggev_(&jobvl, &jobvr, &nn, pA, &nn, pB, &nn, alphar, alphai, beta, &VL, &one, &VR, &one, work, &lwork, &info);

    if(info>=0)
	{
		printf("The eigenvalues are: \n");
			for (int j=0; j<6; j++)
			{
				//cout << alphar[j]/beta[j] <<endl;
				printf("%lf\n",beta[j]);
			}
	}
    else
		fprintf(stderr, "dgesv_ fails %d\n", info);

	return 0;
}


#endif