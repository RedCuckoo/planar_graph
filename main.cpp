#include <iostream>
#include "graph.h"
#include "planar.h"
using namespace std;

int main()
{
    graph_clear();
    cout<<"Enter how many vertexes do you have => ";int s;cin>>s;
    graph test (s);
    //graph test1 (8);

   // test =* test.sumOrDif(test1,1);

   // test.out();

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
    cout<<endl;

    graph *n = planar::check(test);
    test.sumOrDif(*n,0);
    return 0;
}
