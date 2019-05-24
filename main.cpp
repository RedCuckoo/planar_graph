#include <iostream>
#include "graph.h"
#include "planar.h"
using namespace std;

int main()
{
    graph_clear();
    cout<<"Enter how many vertexes do you have => ";int s;cin>>s;
    graph test (s);
//    graph test1 (2);
//
//    test.out();
//    std::cout<<"\n*******\n";
//    test1.out();
//    std::cout<<"\n*******\n";
//   test =* test.dif(test1);
//
//
//
//    test.out();

    std::cout<<"\n*******\n";
   // int* temp = new int [3];
    //if (test.cycled(&temp,s)){
     //   std::cout<<s<<'\n';
   //     for (int i = 0; i < s; i++){
   //        cout<<temp[i]<<" ";
  //      }
  //  }
//    else{
//        std::cout<<"NOT CYCLED";
//    }
   // cout<<endl;

    std::cout<< planar::check(test);
    return 0;
}
