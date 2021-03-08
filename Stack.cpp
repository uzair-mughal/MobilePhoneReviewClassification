#include<iostream>
#include "SinglyLinkedList.cpp"
using namespace std;

template<class T>
class Stack{
	
	List <T> *stk;
	int top;
	
	public:
		
		Stack();
		Stack(int);
		~Stack();
		bool isFull();
		bool isEmpty();
		void Display();
		void push(T d);
		T pop();
		void Multi_push(Stack &);
		Stack * Multi_pop(int);
		int get_top();
};

template<class T>
Stack<T>::Stack(){
	
	stk=new List<T>();
	top=-1;
}

template<class T>
Stack<T>::Stack(int size){
	
	stk=new List<T>();
	stk->set_size(size);
	top=-1;
}

template<class T>
Stack<T>::~Stack(){
	
	if(!isEmpty()){
		
		delete stk;
	}
}

template<class T>
bool Stack<T>::isEmpty(){
	
	if(top==-1)
		return true;
	else
		return false;
}

//template<class T>
//bool Stack<T>::isFull(){
//	
//	if(top==stk->getSize()-1)
//		return true;
//	else
//		return false;
//}

template<class T>
void Stack<T>::Display(){
	
	if(!isEmpty()){
		
		stk->Display();
	}
	else{
		
		cout<<"Stack is Empty."<<endl;
	}
}

template<class T>
void Stack<T>::push(T d)	{
	
//	if(!isFull()){
//		
		top++;
		stk->insert_at_front(d);
//	}
//	else{
//		
//		cout<<"Stack is Full."<<endl;
//	}
}

template<class T>
T Stack<T>::pop(){
	
	if(!isEmpty()){
		
		T temp=stk->remove_at_front();
		top--;
		return temp;
	}
	else{
		
		cout<<"Stack is Empty."<<endl;
	}
}

template<class T>
int Stack<T>::get_top(){
	
	return top;
}

template<class T>
void Stack<T>::Multi_push(Stack<T> &rhs){
	
	if(!isFull()){
		
		Stack <int> t(rhs.get_top()+1);
		
		while(!rhs.isEmpty())
			t.push(rhs.pop());
		
		while(!t.isEmpty())
			this->push(t.pop());
	}
	else{
		
		cout<<"Stack is Full."<<endl;
	}
}

template<class T>
Stack<T> * Stack<T>::Multi_pop(int s){
	
	Stack <int> *t=new Stack<T>(s);
	
	for(int i=0;i<s;i++)
		t->push(this->pop());
	
	return t;
}
