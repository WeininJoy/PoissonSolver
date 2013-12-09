#include "classes.h"

LowerMatrix::LowerMatrix(int m) {
	n=m;
	dim=n*n;
	diagonal.assign(dim,1);
	tridiagonal.assign(dim-1,0);
	identity.assign(dim-n,0);
}

LowerMatrix::~LowerMatrix() {
	vector<double>().swap(diagonal);
	vector<double>().swap(tridiagonal);
	vector<double>().swap(identity);
}

int LowerMatrix::Size() {
	return dim;
}

void LowerMatrix::Set(int i,int j,double value) {
	if(i==j) {
		diagonal[i]=value;
	} else if(j==(i-1)) {
		tridiagonal[j]=value;
	} else if(j==(i-n)) {
		identity[j]=value;
	}
}

double LowerMatrix::Get(int i,int j) {
	if(i==j) {
		return diagonal[i];
	} else if(j==(i-1)) {
		return tridiagonal[j];
	} else if(j==(i-n)) {
		return identity[j];
	} else {
		return 0.0;
	}
}