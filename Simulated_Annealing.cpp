#include <bits/stdc++.h>
using namespace std;

# ifndef CLK_TCK
# define CLK_TCK CLOCKS_PER_SEC
# endif

#include <cstdio>
#include <ctime>
#include <cmath>

#include <cstdlib>
#include <vector>
#include <algorithm>


#define TEST 1000

#define N_PUZZLE_OG_TEMP 10
#define N_PUZZLE_ATTEMPTS 300
#define STOP_TEPM 0.000000001
#define COOL_DOWN 0.8

//



#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
double Problem_time_ndigits;
int Failure_count_ndigits;
double temperature;

inline void swap_these(int &a, int &b) {
    a = a+b;
    b = a-b;
    a = a-b;  
}

inline int manhat_dist(int num, int posi) {
      int dest_x = ceil(num / 3), dest_y = (num - 1) % 3 + 1, posi_x = ceil(posi / 3), posi_y = (posi - 1) % 3 + 1;
     return abs(dest_x - posi_x) + abs(dest_y - posi_y);
  }



inline bool solved(int *state) {
      for (int i = 0; i < 8; i++)
          if (state[i] != i + 1)
              return false;
      return true;
}





 bool n_digit(int *state, int posi, int direc) {
      int dis;
    switch (direc) {
          case UP:
             if (posi <= 3)
                  return false;
             else {
                  dis = manhat_dist(state[posi - 4], posi - 3) - manhat_dist(state[posi - 4], posi);
                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
          case DOWN:
              if (posi >= 7)
                  return false;
             else {
                  dis = manhat_dist(state[posi + 2], posi + 3) - manhat_dist(state[posi + 2], posi);
                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
          case LEFT:
             if (posi % 3 == 1)
                  return false;
              else {
                  dis = manhat_dist(state[posi - 2], posi - 1) - manhat_dist(state[posi - 2], posi);
                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
          case RIGHT:
              if (posi % 3 == 0)
                  return false;
             else {
                  dis = manhat_dist(state[posi], posi + 1) - manhat_dist(state[posi], posi);
                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
      }
      return false;
  }

  void One_case(int *state) {
      clock_t start_time = clock();
      int posi, j, tries_count;
      bool found;
      for (j = 0; j < 9; j++)
          if (state[j] == 0) {
             posi = j + 1;
              break;
          }
    temperature = N_PUZZLE_OG_TEMP;
    tries_count = N_PUZZLE_ATTEMPTS;
    while (!solved(state)) {
         found = false;
          for (j = 0; j < 4; j++)
             if (n_digit(state, posi, j)) {
                  found = true;
                  switch (j) 
                  {
                      case UP:
                          swap_these(state[posi - 1], state[posi - 4]), posi -= 3;
                          break;

                      case DOWN:
                          swap_these(state[posi - 1], state[posi + 2]), posi += 3;
                          break;

                      case LEFT:
                          swap_these(state[posi - 1], state[posi - 2]), posi--;
                          break;

                      case RIGHT:
                          swap_these(state[posi - 1], state[posi]), posi++;
                          break;

                 }
                 break;
            }
          if (--tries_count == 0)
              tries_count = N_PUZZLE_ATTEMPTS, temperature *= COOL_DOWN;
         

          if (!found || temperature < STOP_TEPM) {
              Failure_count_ndigits++;
              return;
          }
    }
    Problem_time_ndigits += (double)(clock() - start_time) / CLK_TCK;
}

void Solve_Simulated_Annealing() {
  FILE *fp = fopen("Test.txt", "r");
    int original_state[9];
     while (fscanf(fp, "%d %d %d %d %d %d %d %d %d", original_state, original_state + 1, original_state + 2, original_state + 3, original_state + 4, original_state + 5, original_state + 6, original_state + 7, original_state + 8) != EOF)
         One_case(original_state);
     fclose(fp);
 }

 void Show() {

    /*#ifndef ONLINE_JUDGE
    // for writing output from input text file
    freopen("output.txt", "w", stdout);
    #endif*/

    printf("N-puzzle Solved Using Simulated Annealing Approach\n");
    printf("Average time taken to solve this: %lf\n", Problem_time_ndigits / (double)(TEST - Failure_count_ndigits));
    printf("Succes rate for solving this: %lf\n", 1 - double(Failure_count_ndigits) / TEST);
}

 int main() {
     Problem_time_ndigits = 0;
     Failure_count_ndigits = 0;
     Solve_Simulated_Annealing();
     Show();
   return 0;
}
