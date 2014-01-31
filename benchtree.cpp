#include "RST.hpp"
#include <chrono>
#include "BSTIterator.hpp"
#include "BST.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <stdio.h>  // printf
#include <math.h> // sqrt
#include <time.h> // clock

using namespace std;

/**
 * Application to measure time complexity for finding N elements in
 * set, RST, and BST. The input can be sorted or unsorted.
 */
int main (int argc, char* argv[])  {

  if (argc != 5)  {
    cout << "NEED TO ENTER 4 ELEMENTS, TRY AGAIN LATER" << endl;
    return -1;
  }
  srand(time(NULL));
  std::string treeType = argv[1];
  std::string sortType = argv[2];
  int maxSize = atoi(argv[3]);
  int runs = atoi(argv[4]);
  
  // printing the header for results
  cout<<"# "<<"Benchmarking average # of comparisons for successful find"<<endl;
  cout<<"# "<<"Data structure: "<<treeType<<endl;
  cout<<"# "<<"N is powers of 2, plus 1, from 1 to "<<maxSize<<endl;
  cout<<"# "<<"Averaging over "<<runs<<" for each N"<<endl;
  cout<<"#"<<endl;
  cout<<"\t# "<< "   \tmean "<<" \t\tstdev" << endl;

  // number of elements ranges from 1-N by powers of 2
  for(int N=1; N<maxSize; N = 2*N + 1)  {
  //  cout<<"starting adding " << N<< " elements"<<endl;
    int R = runs; // init number of trials 
    double totalTime = 0; // init average comparisons
    double totalSquaredTime = 0; // init square comparisons
    double seconds = 0; // init total comparisons
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point stop;
    //trials
    for(int j=0; j < R; j++)  {
    // create test fixture and start the count before adding
      std::vector<countint> v;
      v.clear();
      // inserting in a sorted order
      for(int i=1; i<N; ++i)  {
        v.push_back(i);
      }
      // randomizing vector if sortType is shuffled
      if(sortType.compare("shuffled")==0)  {
        std::random_shuffle(v.begin(), v.end());
      }
      if(sortType.compare("shuffled")!=0&&sortType.compare("sorted")!=0) {
        cout << "please enter valid sort type next time" << endl;
        return -1;
      }
      //insert the keys in the vector in the appropriate data structure
      std::vector<countint>::iterator vit = v.begin();
      std::vector<countint>::iterator ven = v.end();
      //checking which data structure to use
      if(treeType.compare("rst") == 0)  {
        RST<countint> s;
        for(vit=v.begin(); vit != ven; ++vit)  {
          s.insert(*vit);
        }
        // start timing
        start = chrono::high_resolution_clock::now();
        for(vit=v.begin(); vit != ven; ++vit)  {
          s.find(*vit);
        }
      }
      else if(treeType.compare("bst") == 0)  {
      // insert into bst 
        BST<countint> s;
        for(vit=v.begin(); vit != ven; ++vit)  {
          s.insert(*vit);
        }
        // start timing
        start = chrono::high_resolution_clock::now();
        for(vit=v.begin(); vit != ven; ++vit)  {
          s.find(*vit);
        }
      }
      else if(treeType.compare("set") == 0)  {
      // insert into bst 
        std::set<countint> s;
        for(vit=v.begin(); vit != ven; ++vit)  {
          s.insert(*vit);
        }
        // start timing
        start = chrono::high_resolution_clock::now();
        for(vit=v.begin(); vit != ven; ++vit)  {
          s.find(*vit);
        }
      }
      else  {
        cout<<"please enter a valid data structure next time"<<endl;
        return -1;
      }
      // stop the timer
      stop = chrono::high_resolution_clock::now();
      // get total time span
      chrono::duration<double> time_span;
      time_span = chrono::duration_cast<chrono::duration<double>>(stop-start);
      seconds = time_span.count();
      //cout<<"TOTAL TIME "<<seconds<<endl;
      totalTime += seconds;
      totalSquaredTime += seconds*seconds;
    } // end of trial/runs loop

    // calculate overall average
    double mean = totalTime/R;
    // calculate standard deviation
    double stanDev = sqrt(totalSquaredTime/R - mean*mean);
    //display the results
    //print the results: N, mean, standard deviation
    printf("%8d\t%10f\t%f\n", N, mean, stanDev);
  }

}
