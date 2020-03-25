#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]){
   int x, y;
   int n = 0;
   double dis = 0;
   double md=0;
   int minx1, miny1,minx2,miny2;
   vector<double> d;
   vector<int> arrx;
   vector<int> arry;
   if(argc!=2){
      cout<<"must be 2 cammand"<<endl;
   }
   else{
      ifstream file_;
      if(!file_){
         cerr<<"open error!"<<endl;
	 exit(1);
      }
      file_.open(argv[1],ios::in);
      while(file_>>x>>y){
         n=n+1;
	 arrx.push_back(x);
	 arry.push_back(y);
      }
     
      for(int i=0; i<n ; i++){
         for (int j = i+1; j<n; j++){
	    dis = sqrt((arrx[j]-arrx[i])*(arrx[j]-arrx[i])+(arry[j]-arry[i])*(arry[j]-arry[i]));	    
	    d.push_back(dis);
	 }
      }
      vector<double>::iterator Mdis = min_element(d.begin(),d.end());
      for(int i=0;i<n;i++){
         for(int j=i+1;j<n;j++){
	    md=sqrt((arrx[j]-arrx[i])*(arrx[j]-arrx[i])+(arry[j]-arry[i])*(arry[j]-arry[i]));
	    if(md==*Mdis){
	       minx1=arrx[i];
	       minx2=arrx[j];
	       miny1=arry[i];
               miny2=arry[j];
	    }
	 }
      }
      ofstream outfile("Brute_force_output.txt");
      if(!outfile){
         cerr<<"open error"<<endl;
	 exit(1);
      }
      outfile<<*Mdis<<"\n";
      outfile<<"("<<minx2<<", "<<miny2<<")"<<", "<<"("<<minx1<<", "<<miny1<<")"<<"\n";
      outfile.close();
   }

   return 0;
}
