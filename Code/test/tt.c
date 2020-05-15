#include<stdio.h>
#include<string.h>
int mod(int mod_a, int mod_b){
  return mod_a - (mod_a/mod_b)*mod_b;
}

int times(int times_a, int times_b, int times_mod){
  int times_ret = 0;
  while(times_b != 0){
    if(mod(times_b, 2)){
      times_ret = times_ret + times_a;
      if(times_ret >= times_mod) times_ret = times_ret - times_mod;
    }
    times_a = times_a + times_a;
    if(times_a >= times_mod) times_a = times_a - times_mod;
    times_b = times_b / 2;
  }
  return times_ret;
}

int prf(int prf_x, int prf_y){
  int prf_z = times(prf_x, prf_y, 1000000007);
  prf_z = prf_z + 2987;
  if(prf_z >= 1000000007) prf_z = prf_z - 1000000007;
  prf_z = times(prf_z, prf_z, 1000000007);

  prf_z = prf_z + prf_x;
  if(prf_z >= 1000000007) prf_z = prf_z - 1000000007;
  prf_z = prf_z + prf_y;
  if(prf_z >= 1000000007) prf_z = prf_z - 1000000007;
  prf_z = prf_z + prf_y;
  if(prf_z >= 1000000007) prf_z = prf_z - 1000000007;

  return prf_z;
}

int modify_array(int ma_a[5]){
  int ma_p = prf(ma_a[0], ma_a[4]), ma_q = prf(ma_a[2], ma_a[3]);
  ma_a[0] = prf(ma_p, ma_q);
  ma_a[1] = prf(ma_p, ma_a[0]);
  ma_a[2] = prf(ma_q, ma_a[1]);
  ma_a[3] = prf(ma_p, ma_a[2]);
  ma_a[4] = prf(ma_q, ma_a[3]);
  return 0;
}

struct ST{
  int st_a, st_b[5][5][5];
};

int modify_struct(struct ST ms_a){
  int ms_i = 0, ms_j = 0, ms_k = 1;
  ms_a.st_a = prf(ms_a.st_b[0][0][0], ms_a.st_b[2][3][3]);
  while(ms_i < 5){
    while(ms_j < 5){
      while(ms_k < 5){
        if(ms_k > 0){
          ms_a.st_b[ms_i][ms_j][ms_k] = prf(ms_a.st_a, ms_a.st_b[ms_i][ms_j][ms_k-1]);
        }else if(ms_j > 0){
          ms_a.st_b[ms_i][ms_j][ms_k] = prf(ms_a.st_a, ms_a.st_b[ms_i][ms_j - 1][4]);
        }else{
          ms_a.st_b[ms_i][ms_j][ms_k] = prf(ms_a.st_a, ms_a.st_b[ms_i - 1][4][4]);
        }
        ms_k = ms_k + 1;
      }
      ms_j = ms_j + 1;
      ms_k = 0;
    }
    ms_i = ms_i + 1;
    ms_j = ms_k = 0;
  }
  return 0;
}

int main(){
  int n = 4074, m, array[5][5][5], i, j, k;
  struct ST st;

  i = 0;
  while(i < 5){
    j = 0;
    while(j < 5){
      k = 0;
      while(k < 5){
        array[i][j][k] = st.st_b[i][j][k] = 0;
        k = k + 1;
      }
      j = j + 1;
    }
    i = i + 1;
  }
  st.st_a = 0;

  if(mod(n, 3) == 0) m = 108;
  else if(mod(n, 3) == 1) m = 505;
  else m = 983;

  while(mod(n, 947) != 6){
    n = prf(n, m);
    m = prf(n, m);
  }

  m = mod(m, 1009);

  while(m){
	printf("%d\n",m);
    int p, q;
    m = m - 1;
    n = times(n, n, 1000000007);

    n = q = prf(n, m);
    n = prf(q, n);

    if(mod(n = prf(q, n), 2) && mod(q = prf(q, n), 2)){
      n = prf(q, n);
    }else{
      n = prf(m, n);
    }

    if(mod(n = prf(q, n), 2) || mod(q = prf(q, n), 2)){
      n = prf(q, n);
    }else{
      n = prf(m, n);
    }

    p = 0;

    if(n > q) p = p + 1;
    if(n < q) p = p + 2;
    if(mod(n, 10) >= mod(q, 10)) p = p + 4;
    if(mod(n, 10) <= mod(q, 10)) p = p + 8;
    if(mod(n, 2) == mod(q, 2)) p = p + 16;
    if(mod(prf(n, m), 2) != mod(q, 2)) p = p + 32;

    n = prf(p, n);
    n = prf(p, q);

    p = mod(p, 100);
    q = mod(q, 100);
    p = ((p + q) * (p + 2 * q) + 13) * (997 + p);
    n = prf(p, n);

    q = -q;
    while(q < 0) q = q + 10007;
    n = prf(q, n);

    if(mod(q = prf(p, q), 2) || !(mod(n = prf(p, q), 2) && mod(p = prf(n, q), 2))){
      n = prf(p, q);
    }else{
      n = prf(q, p);
    }

    p = array[mod(prf(p, q), 5)][mod(prf(n, p), 5)][mod(prf(q, n), 5)];
    p = p + 233;
    if(p >= 1000000007) p = p - 1000000007;
    array[mod(prf(p, q), 5)][mod(prf(n, p), 5)][mod(prf(q, n), 5)] = prf(p, p);

    modify_array(array[mod(prf(p, q), 5)][mod(prf(n, p), 5)]);

    modify_struct(st);
  }

  i = 0;
  while(i < 5){
    j = 0;
    while(j < 5){
      k = 0;
      while(k < 5){
        n = prf(n, array[i][j][k]);
        n = prf(n, st.st_b[i][j][k]);
        k = k + 1;
      }
      j = j + 1;
    }
    i = i + 1;
  }

  n = prf(n, st.st_a);

  printf("answer: %d\n", n);

  return 0;
}
