// Recebe n > 0 e v e devolve o máximo
// dentre os inteiros no intervalo v[0..n-1].

//extern int NOP;

int maximo_ (int n, int v[]) {
    int k, m = v[0];
//    NOP = 0;
    for(k = 1; k < n; k++) {
//        NOP++;
        if(v[k] > m)
            m = v[k];
    }
    return k;
}
