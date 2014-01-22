#include "classes.h"

UpperMatrix::UpperMatrix(int n) : LowerMatrix(n) {
	this->n=n;
	this->dim=n*n;
	this->diagonal.assign(dim,0);
	this->tridiagonal.assign(dim-1,0);
	this->identity.assign(dim-n,0);
}

UpperMatrix::~UpperMatrix() {
	vector<double>().swap(diagonal);
	vector<double>().swap(tridiagonal);
	vector<double>().swap(identity);
}

double UpperMatrix::Get(int i,int j) {
	return LowerMatrix::Get(j,i);
}

void UpperMatrix::Set(int i,int j,double value) {
	return LowerMatrix::Set(j,i,value);
}

vector<double> UpperMatrix::operator*(const vector<double>& x) {
    vector<double> tmp;
    tmp.assign(x.size(),0);
    for(int i=0;i<dim;i++) {
        tmp[i]+=x[i]*4.0;
        if(i<(dim-n)) {
            tmp[i]+=x[i+n]*-1.0;
            tmp[i+n]+=x[i]*-1.0;
        }
        if(i%n!=0) {
            tmp[i]+=x[i-1]*-1.0;
            tmp[i-1]+=x[i]*-1.0;
        }
    }
    return tmp;
}

LowerMatrix::LowerMatrix(int n) {
    this->n=n;
    this->dim=n*n;
    this->diagonal.assign(dim,1);
    this->tridiagonal.assign(dim-1,0);
    this->identity.assign(dim-n,0);
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

vector<double> LowerMatrix::operator*(const vector<double>& z) {
    int m;
    vector<double> tmp(z.size());
    for(int i=0;i<dim;i++) {
        for(int j=0;j<5;j++) {
            m=HashMatrix[i][j];
            if(m!=-1 && m<i) {
                tmp[i]=z[i]-Get(i,m)*z[m];
            }
        }
        tmp[i]=z[i]/Get(i,i);
    }
    return tmp;
}