#include <iostream>
#pragma once
using namespace std;

template <class T>
class List;

template<class T>
class Node{
	
	private:
		
		T data;
		Node <T> *nextPtr;
		friend class List<T>;
		
	public:
		
		Node():nextPtr(0){}
		
		Node(T d){
			
			this->data=d;
			nextPtr=0;
		}
		Node (T d,Node <T> *n){
			
			this->data=d;
			this->nextPtr=n;
		}
};

template<class T>
class List{
	
	private:
		
		Node<T> *Head;
		int size;
		
	public:
		
		List():Head(0),size(0){}
		void insert_at_front(const T &);
		void insert_at_end(const T &);
		T remove_at_front();
		void remove_at_end();
		bool find_hashed_key(unsigned long long);
		void Display()const;
		int getSize();
		void reverse();
		Node<T>* getHead();
};

template<class T>
void List<T>::insert_at_front(const T &value ){
	
	Node<T> *newPtr = new Node<T>(value);
	
	if(Head==0){
		
		Head=newPtr;
	}
	else{ 
	
		newPtr->nextPtr = Head;
		Head = newPtr;
	}
	size++;
}

template<class T>
void List<T>::insert_at_end(const T & value)	{
	
	Node<T> *newPtr = new Node<T>(value);
	Node<T> *currentPtr=this->Head;
	
	if(Head==0)	{
		
		Head=newPtr;
	}
	else{
		
		while(currentPtr->nextPtr!=0)	{
			
			
			currentPtr=currentPtr->nextPtr;
		}
		currentPtr->nextPtr=newPtr;
	}	
	size++;
}

template<class T>
T List<T>::remove_at_front(){
	
	if(Head==0 ){
		
		cout<<"Error: list is empty!\n";
	}
	else{
		
		T temp;
		Node<T> *currentPtr=Head;
		temp=currentPtr->data;
		Head=Head->nextPtr;
		delete currentPtr;
		size--;
		return temp;
	}
}

template<class T>
void List<T>::remove_at_end(){
	
	if(Head==0 ){
		
		cout<<"Error: list is empty!\n";
	}
	else{
		
		Node<T> *currentPtr=this->Head;
		Node<T> *tempPtr=this->Head;
		
		while(currentPtr->nextPtr!=0){
			
			tempPtr=currentPtr;
			currentPtr=currentPtr->nextPtr;
		}
		tempPtr->nextPtr=0;
		delete currentPtr;
		size--;
	}
}

template<class T>
bool List<T>::find_hashed_key(unsigned long long hash_key){ 
			
	if(Head==0)
		return false;
	else{

		Node<T> *currentPtr=Head;
		
		while(currentPtr!=0){
					
			if(currentPtr->data==hash_key)
				return true;
					
			currentPtr=currentPtr->nextPtr;
		}
	}		
}

template <class T>
void List<T>::reverse(){
	
	Node<T> *currentPtr=this->Head;
	Node<T> *prevPtr=0;
	Node<T> *nextPtr=0;
	
	while(currentPtr!=0){
		
		nextPtr=currentPtr->nextPtr;
		currentPtr->nextPtr=prevPtr;
		prevPtr=currentPtr;
		currentPtr=nextPtr;
	}
	Head=prevPtr;
}

template<class T>
void List<T>::Display() const{
	
	if(Head==0)
		cout <<"The list is empty\n\n";
	else	{
		
		Node<T> *currentPtr = Head;
		
		cout << "['";
		while(currentPtr!=0){
			
			if (currentPtr->nextPtr != 0)
				cout << currentPtr->data << "', '";
			else
				cout << currentPtr->data;
			currentPtr = currentPtr->nextPtr;
			
//			cout <<"["<<currentPtr->data<<"]";
//			currentPtr=currentPtr->nextPtr;
		}
		cout << "']";
	}
	
	cout <<"\n";
}

template<class T>
Node<T>* List<T>::getHead(){
	
	return Head;
}

template <class T>
List<T>::getSize(){
	
	return size;
}
