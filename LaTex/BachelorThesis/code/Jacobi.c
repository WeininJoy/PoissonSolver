void Algorithms::JacobiMethod(Matrix& A,vector<double>& x,const vector<double>& b) {
    vector<double> r(dim,1),solved(dim);

    for(int i=1,k=0;i<=N;i++) {
        for(int j=1;j<=N;j++,k++) {
            solved[k]=g(j*h,i*h);
        }
    }

    double TOL=pow(10,-3)*((x-solved)|(x-solved));
    while(TOL<=(r|r)) {
        r=b-A*x;
        x+=1.0/4.0*r;
    }
}