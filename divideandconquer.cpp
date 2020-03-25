#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;

double dist(double* ar[],int i, int j){
	double d = sqrt(((ar[j][0]-ar[i][0])*(ar[j][0]-ar[i][0]))+((ar[j][1]-ar[i][1])*(ar[j][1]-ar[i][1])));

	return d;
}
double strCloest(double* str[], int s, double d){
	double min=d;
	for (int i=0;i<s;i++){
		for(int j=i+1;j<s && (str[j][0]-str[i][0])<min;j++){
			if(dist(str,i,j)<min){
				min = dist(str,i,j);

			}
		}
	}
	return min;
}

double min(double x, double y){
	if(x<=y){
		return x;
	}
	else{
		return y;
	}
}
bool srtY(double* x, double* y){
	return x[1]<y[1];
}
double divide(double* array[],int n){
	double d;
	double mind = 99999;
	if(n<=3){
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if(mind > dist(array,i,j)){
					mind = dist(array,i,j);
				}
			}
		}
		d=mind;
		return d;

	}
	int m=n/2;   
	double dl, dr;
	sort(array, array+n,srtY);
	double **left = new double*[n];
	double **right = new double*[n];
	int midx = array[m][0];
	int midy = array[m][1];
	int leftn = 0;
	int rightn = 0;
	for (int i = 0;i<m;i++){
		left[leftn]=array[i];
		leftn++;
	}
	for(int i=m;i<n;i++){
		right[rightn]=array[i];
		rightn++;
	}

	dl = divide(left, m);
	dr = divide(right, n-m); 
	d = min(dl,dr);

	double **strip = new double*[n];
	int sI=0;
	for (int i=0;i<n;i++){
		if(abs(array[i][1]-midy)<d){
			strip[sI] = array[i];
			sI++;
		}
	}
	double wow = min(d,strCloest(strip,sI,d));


	return wow;

}
int main(int argc, char* argv[]){
	clock_t start_time, end_time;
	double duration;   
	start_time = clock();

	int n=0;
	int x,y,new_i;
	double d;
	vector<int> arrx;
	vector<int> arry;
	if(argc!=2){
		cout<<"command must equal to 2"<<endl;
	}
	else{
		ifstream file_;
		if(!file_){
			cerr<<"open error!"<<endl;
			exit(1);
		}
		file_.open(argv[1],ios::in);
		while(file_>>x>>y){
			arrx.push_back(x);
			arry.push_back(y);
			n=n+1;
		}
		double **arr = new double*[n];
		for(int i=0;i<n;i++){
			arr[i] = new double[2];
		}
		for(int i=0;i<n;i++){
			arr[i][0]= arrx[i];
			arr[i][1]= arry[i];
		} 

		d = divide(arr,n);
		double **new_arr = new double*[n];
		new_i = 0;
		for(int i = 0; i < n;i ++){
			new_arr[i] = new double[2];
		}
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				if(dist(arr,i,j) == d){
					new_arr[new_i] = arr[i];
					new_arr[new_i+1] = arr[j];
					new_i+=2;
				}
			}
		}

		ofstream outfile_;
		outfile_.open("output_divideandconquer.txt");
		if(!outfile_.is_open()){
			cout << "Cannot open the out_file." << endl;
			return 1;
		}
		else{
			outfile_ << d << endl; 
			for(int i = 0; i < new_i; i++){
				outfile_ << "(" << new_arr[i][0] << ", " << new_arr[i][1] << "), (" << new_arr[i+1][0] << ", " << new_arr[i+1][1] <<")" << endl;
				i++;
			}
			outfile_.close();
		}


	}
	end_time=clock();
	duration = double(end_time - start_time)/CLOCKS_PER_SEC;
	cout<<"Run time: " <<duration<<" s"<<endl;
	return 0;
}  
