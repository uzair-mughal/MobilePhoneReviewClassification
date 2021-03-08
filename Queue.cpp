#include<iostream>
#include"SinglyLinkedList.cpp"
using namespace std;

template <class T>
class Queue{
	
	private:
		
		List <T> *Q;
//		bool stat;
	
	public:
		
		Queue();
		~Queue();
		EnQueue(T);
		T DeQueue();
		T Process();
		bool isEmpty();
		bool isStat();
		void Display();
};

template<class T>
Queue<T>::Queue(){
	
	Q=new List<T>();
//	stat = true;
}

template<class T>
Queue<T>::~Queue(){
	
	if(Q!=0)
		delete Q;
}

template<class T>
bool Queue<T>::isEmpty()	{
	
	if(Q->getHead())	{
		
		return false;
	}
	return true;
}

//template<class T>
//bool Queue<T>::isStat()	{
//	
//	if(stat)	{
//		
//		return true;
//	}
//	return false;
//}

template<class T>
Queue<T>::EnQueue(T d){
	
	Q->insert_at_end(d);
}

template<class T>
T Queue<T>::DeQueue(){
	
	if(!isEmpty()){
		
		T temp;
		temp=Q->remove_at_front();
		return temp;
	}
}

template<class T>
T Queue<T>::Process(){
	
	T temp;	
	temp=Q->value_at_front();
	return temp;
}

template<class T>
void Queue<T>::Display(){
	
	Q->Display();
}
