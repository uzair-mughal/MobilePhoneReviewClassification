#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cmath>
#include<bits/stdc++.h>

#include "SinglyLinkedList.cpp"
#include "Stack.cpp"
#include "Queue.cpp"
#include "PhoneClass.cpp"

using namespace std;


//GLOBAL DATA STRUCTURES - START

Queue<string> Phone_ReviewsQ[5];
Queue<string> SentencesQ;
Queue<string> posSentQ;
Queue<string> negSentQ;
Stack<string> Tokenised_WordsQ;
List<unsigned long long> **Hashed_Words;

Phone phone_obj[5];

//GLOBAL DATA STRUCTURES - END


//GLOBAL VARIABLES - START

int num_files=10;
int num_models=5;
float aspect_score[7];
string model_names[5] = {"Samsung_S10+","Huawei_P30-Pro","OPPO_Find-X","Vivo_V17-Pro","Apple_iPhone_11"};
string file_names[10]={"stopwords","poswords","negwords","camera","performance","display","cost","battery","others","overall"};
int file_size[10];
string alpha = " abcdefghijklmnopqrstuvwxyz+-*";

//GLOABAL VARIABLES - END


//UTILITY FUNCTIONS - START

//Returns the value of int in string
int get_num(string str, int n)	{
	
	int end, i = 0, num = 0;
	
	for(end = n - 1; end >= 0; end--)	{
	
		num += ((str[end] - 48) * pow(10, i));
		i++;
	}
	
	return num;
}

//Check if char is number or not
inline bool cmp_with_num(char c)	{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

//File exists or not
inline bool fExists(string name)	{
	ifstream f(name.c_str());
	return f.good();
}

// Searches for letter and returns index
int get_alpha_val(char let)	{
	
	for(int i = 0; i < alpha.length(); i++)	{
		if (alpha[i] == let)
			return i;
	}
	return 0;
}

//UTILITY FUNCTIONS - END


//HASHING FUNCTIONS - START

//Convert string into hashed value
unsigned long long hashWord(string word)	{
	
	unsigned long long total = 0;
	int i;
	
	for(i = 0; i < word.length(); i++){
		
		total = total*17 + get_alpha_val(word[i]); //changed hash function
	}
	return total;
}

//Part of generate_hash_files
void hash_file(string fname)	{
	
	string temp = fname;
	string line;
	
	fname.append(".txt");
	ifstream in(fname.c_str());
	
	temp.append("_h.txt");
	ofstream out(temp.c_str());
	
	if (in == 0 || out == 0)
		return;
		
	// First line is number of words in the file
	getline(in, line);
	out << line << "\n";
	
	while(getline(in, line))
		out << hashWord(line) << "\n";
		
	in.close();
	out.close();
}

//Hashing all positive, negative, stopwords and aspects
void generate_hash_files(int n)	{
	
	while(n--)	{
		
		string temp = file_names[n];
		temp.append("_h.txt");
		
		if (!fExists(temp.c_str()))
			hash_file(file_names[n]);
	}
}

//Store all hashed words in array of SLL
void fetch_hashed_files()	{
	
	// Loop for each file to further hash the words
	for(int i = 0; i < num_files ; i++)	{
		
		int n=0; // debug
		unsigned long long val;
		
		string fileName = file_names[i];
		fileName.append("_h.txt");
		ifstream in(fileName.c_str());
		
		in >> val;
 		
		//for storing number of words in a file 
		file_size[i]=val;
 		
		int size = val;
		Hashed_Words[i] = new List<unsigned long long>[size];
		
		while(in >> val){
			
			Hashed_Words[i][val%size].insert_at_end(val);
			n++;
		}
//		for(int j=0;j<size;j++){
//			
//			cout<<"List "<<j<<": ";
//			Hashed_Words[i][j].Display();
//		}
		in.close();
	}
}

//Verifying if token is exists in hashed SLL
bool verify_token(string token,int file_id)	{
	
	// if question mark then check word after removing '?'
	if (token[token.length() - 1] == '?')
		token.erase(token.length() - 1, token.length() - 1);
	
	int index;

	unsigned long long value = hashWord(token);
	index = value % file_size[file_id];
	
	// debug
//	cout << "Token: " << token << "\n";
//	cout << "Num: " << num << "\n";
//	cout << "Value: " << value << "\n";
//	cout << "Index: " << index << "\n";
	// debug - END
	
	return (Hashed_Words[file_id][index].find_hashed_key(value));
}

//HASING FUNCTIONS - END

template <class T>
void read(Queue<T> *que, string fname)	{
	
	string line;
	ifstream file(fname.c_str());
	
	if (file == 0)
		return;
	
	while(getline(file, line))
		que->EnQueue(line);
}

// Stores phone data from file to objects
void fetch_mobile_data(){
	
	string filename;
	ifstream infile;
	
	for(int i=0;i<num_models;i++){
	
		filename=model_names[i];
		filename.append(".txt");
		infile.open(filename.c_str());
		
		phone_obj[i].set_data(infile);
		infile.close();
	}
	
	//for debug
	for(int i=0;i<num_models;i++)
		phone_obj[i].Display();
		
}

// Removes some symbols from an individual word
string remove_symbols(string word, string deli = ".! ")	{
	
	int i,s;
	string temp;
	
	for(i = 0; i < word.length(); i++)	{
		
		s=deli.length();
		
		while(s--)	{
			
			if (word[i] == deli[s])	{
				
				temp += word.substr(0, i);
				word.erase(0, i+1);
				i = -1;
			}
		}
	}
	
	temp += word.substr(0, i);
		
	return temp;
}

//Breaks sentences into words and removes stop words
void tokenize(Stack<string> *words, string sent)	{
	
	string token;
	int i = 0, j = 0, num;
	
	while((i = sent.find(" ")) <= sent.length()-1 && i >= 0)	{
		
		token = sent.substr(0, i);
		token = remove_symbols(token);
		
		if(token != "" && !verify_token(token,0))
			words->push(token);
			
		sent.erase(0, i + 1);
	}
	
	token = remove_symbols(sent.substr(0, sent.length()));
	if(token != "" && !verify_token(token,0))
		words->push(token);
	else if (token[token.length() - 1] == '?')
		words->push("?");
		
}

// Score aspects as being positive or negative
int score(Stack<string> *words, int idx)	{
	
	int aspects_in_sent[7];
	int pos=0;
	int neg=0;
	int check;
	int ret = 0;
	int noOfRev = 0;
	
	for(int j=0;j<7;j++)
		aspects_in_sent[j]=0;
	
	while (!words->isEmpty()){
		
		string word=words->pop();
		
		check=0;
			
		if(word[word.length()-1]== '?'){
			
			break;
		}
		else{
			
			for(int i=1;i<10;i++){
				
				if(i>=3 && verify_token(word,i)){
								
					aspects_in_sent[i-3]=1;
					
					if (noOfRev == -1 || noOfRev == 0)
						noOfRev += 2;
				}
				
				else if(verify_token(word,1)){
					
					pos=1;
				}
				
				else if(verify_token(word,2)){
					
					neg=1;
				}
				
				if(pos==1 || neg==1){
					
					if(pos==1){
						
						for(int j=0;j<7;j++){
							
							if(aspects_in_sent[j]==1){
								
								phone_obj[idx].set_score(j,1);
								aspects_in_sent[j]=0;
								ret++;
								if (noOfRev == 0 || noOfRev == 2)
									noOfRev--;
								check=1;
								pos=0;
							}
						}
					}
					
					if(neg==1){
						
						for(int j=0;j<7;j++){
							
							if(aspects_in_sent[j]==1){
								
								phone_obj[idx].set_score(j,-1);
								aspects_in_sent[j]=0;
								ret--;
								if (noOfRev == 0 || noOfRev == 2)
									noOfRev--;
								check=1;
								neg=0;
							}
						}
					}
				}
				if(check==1)
					break;
			}
		}
	}
	
	if (noOfRev == 1)
		phone_obj[idx].inc_rev();
		
//	phone_obj[idx].Display_score();
	return ret;
}

template <class T>
int sent_seg(Queue<T> *sentQ, string sent)	{
	
	// debug
//		cout << "\nBefore Sentence Segmentation String: \n";	
//		cout << sent;
//		cout << "\n";
		
	// debug - end
	
	string deli = ".!?";
	int i = 0, size = 0, k, j;
			
	for(j = i; j < sent.length(); j++){
		
		k = 0;
		
		while(k < 3){
			
			if (sent[j] == deli[k++]){
				
				while(sent[++j]==deli[0] || sent[j]==deli[1] || sent[j]==deli[2]); //for recursive(.... , ...? , !!!!)
				
				if (j != 0 && j != sent.length() && (!cmp_with_num(sent[j-2]) && !cmp_with_num(sent[j])))	{
					
					sentQ->EnQueue(sent.substr(i, j - i));
					i = j;	
					size++;			
				
				}
			}
		}
	}
	
	if(j >= sent.length()){
		
		sentQ->EnQueue(sent.substr(i, j - i));
		size++;
	}
	return size;
}

template <class T>
void initiate(Queue<T> *que, int idx)	{

	if(!que->isEmpty()){
		
		string str = que->DeQueue();
		int len = get_num(str, str.length());
		int numSent, index = 0;
		
		// Eliminate name of smartphone
		que->DeQueue();
		
		// Start workings on each review
		while(!que->isEmpty())	{
			
			//Number of sentences
			numSent = sent_seg(&SentencesQ, que->DeQueue());
			
			//debug
//			cout<<"\n";
//			SentencesQ.Display();
			
			index = 0;
			
			// Operation for each sentence
			while(!SentencesQ.isEmpty())	{	// edit: use !SentencesQ.isEmpty()
				
				string tempStr = SentencesQ.DeQueue();
				tokenize(&Tokenised_WordsQ, tempStr);
				
//				cout << "Last element of stack: " << Tokenised_WordsQ.pop() << "\n";
				
//				cout<<"\nAfter Tokenizing! and Removing Stop words: \n";
//				Tokenised_WordsQ.Display();
				
				int check = score(&Tokenised_WordsQ, idx);
				
				if (check > 0)
					posSentQ.EnQueue(tempStr);
				else if (check < 0)
					negSentQ.EnQueue(tempStr);
				
				while(!Tokenised_WordsQ.isEmpty())
					Tokenised_WordsQ.pop();
					
				index++;
			}
		}
	}
}

void startProg(void){
	
	//This Functions generates the hashed files for stop words , possitive words and negative words
	generate_hash_files(10);//3 means three files to be generated
	
	// Array of stop words, positive words and negative words
	Hashed_Words = new List<unsigned long long>*[num_files];
	
	//This Functions stores the hashed files to a 2D LinkedList.
	fetch_hashed_files();
	
	//This functions loads data of phones to objects
	fetch_mobile_data();
	
	int i = 0;
	
	while(i < 5)	{	// 5 for now
		
		// First Phase: Get reviews
		string fname = "reviews";
		fname.append(1, (char)(i+49));
		fname.append(".txt");
		
		// debug
//		fname = "egRev.txt";
		// debug - end
		
		read(&Phone_ReviewsQ[i], fname);
		initiate(&Phone_ReviewsQ[i], i);
		
		cout << "\n" << model_names[i] << "\n";
		cout << "\nPositive Reviews\n";
		
		int count=1;
		while(!posSentQ.isEmpty())
			cout <<count++<<"-"<< posSentQ.DeQueue() << "\n";
		
		cout << "\nNegative Reviews\n";
		
		count=1;
		while(!negSentQ.isEmpty())
			cout <<count++<<"-"<< negSentQ.DeQueue() << "\n";
		
		phone_obj[i].Display_score();
		
		i++;
	}
}

int main() {
	
	// debug
	remove("negwords_h.txt");//for hash funtion check
	remove("poswords_h.txt");
	remove("stopwords_h.txt");
	remove("camera_h.txt");
	remove("performance_h.txt");
	remove("display_h.txt");
	remove("cost_h.txt");
	remove("battery_h.txt");
	remove("others_h.txt");
	remove("overall_h.txt");
	// debug -END
	
	
	startProg();		
	return 0;
}

