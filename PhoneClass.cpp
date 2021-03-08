#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Phone{
	
	private:
		
		string company;
		string model;
		string bat_cap;
		string ram;
		string os;
		string price;
		string weight;
		string screen_size;
		string camera_res;
		string audio_jack;
		int noOfRev;
		float aspect_score[7];
		
	public:
		
		Phone(){
			
			memset(aspect_score,0,sizeof(float));
		}
			
		void set_data(ifstream &infile){
			
			infile>>company;
			infile>>model;
			infile>>bat_cap;
			infile>>ram;
			infile>>os;
			infile>>price;
			infile>>weight;
			infile>>screen_size;
			infile>>camera_res;
			infile>>audio_jack;
		}
		
		void inc_rev()	{
			
			noOfRev++;
		}
		
		void set_score(int index,float score)	{
			
			aspect_score[index]+=score;
		}
		
		float* get_score()	{
			
			return aspect_score;
		}
		
		void Display(){
			
			cout<<"Phone Data: \n";
			cout<<company;
			cout<<" "<<model;
			cout<<" Battery capacity:"<<bat_cap;
			cout<<" Ram: "<<ram;
			cout<<" Operating System:"<<os;
			cout<<" Price:"<<price;
			cout<<" Wight:"<<weight;
			cout<<" Screen size:"<<screen_size;
			cout<<" Camera Resolution:"<<camera_res;
			cout<<" Audio jack:";
			if(audio_jack=="yes")
				cout<<"Yes";
			else
				cout<<"No";
				
			cout<<"\n";
		}
		
		void Display_score(){
			
			float sum = 0;
			for (int i = 0; i < 7; i++)
				sum += aspect_score[i];
			
			cout<<"\nCamera: "<<aspect_score[0] << "\n";
			cout<<"Perfomance: "<<aspect_score[1] << "\n";
			cout<<"Display: "<<aspect_score[2] << "\n";
			cout<<"Cost: "<<aspect_score[3] << "\n";
			cout<<"Battery: "<<aspect_score[4] << "\n";
			cout<<"Others: "<<aspect_score[5] << "\n";
			cout<<"Overall: "<<aspect_score[6] << "\n";
			cout<<"Review Sentences: "<< noOfRev << "\n";
			cout<<"Average Score: "<< (sum / noOfRev) * 10 << "\n";
		}
};

