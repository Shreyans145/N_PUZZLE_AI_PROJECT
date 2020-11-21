#include <bits/stdc++.h>
using namespace std;

 
#include <cstdio>
#include <cstdlib>
  


#define TEST 1000
#define S 10000


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

inline void swap_these(int &a, int &b) {
    a = a+b;
    b = a-b;
    a = a-b;  
}


void N_dig_Generation() {
    FILE *fp = fopen("Test.txt", "w");
    int testcase = TEST, direc, posi, steps;
    while (testcase--) {
        int state[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        steps = S;
        posi = 9;
        while (steps--) 
        {

            direc = rand() % 4;
            switch (direc) 
            {
                case UP:
                    if (posi <= 3)
                        break;
                    else 
                    {
                        swap_these(state[posi - 1], state[posi - 4]), posi -= 3;
                        break;
                    }
                case DOWN:
                    if (posi >= 7)
                        break;
                    else 
                    {
                        swap_these(state[posi - 1], state[posi + 2]), posi += 3;
                        break;
                    }
                case LEFT:
                    if (posi % 3 == 1)
                        break;
                    else 
                    {
                        swap_these(state[posi - 1], state[posi - 2]), posi--;
                        break;
                    }
                case RIGHT:
                    if (posi % 3 == 0)
                        break;
                    else 
                    {
                        swap_these(state[posi - 1], state[posi]), posi++;
                        break;
                    }
            }
        }
        fprintf(fp, "%d %d %d %d %d %d %d %d %d\n", state[0], state[1], state[2], state[3], state[4], state[5], state[6], state[7], state[8]);
    }
    fclose(fp);
}







int main() {
    N_dig_Generation();
    return 0;
}
