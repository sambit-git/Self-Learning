#include<iostream>

template <typename T>
class Node
{
    private:
        T data;
        Node<T> * next;
    public:
        Node(T data) : data(data), next(NULL) {}

        T getData()
        {
            return data;
        }

        void setData(T data)
        {
            this->data = data;
        }

        Node<T>* getNext()
        {
            return next;
        }
        
        void setNext(Node<T>* next)
        {
            this->next = next;
        }
};

template <typename T>
class LinkedList
{
    private:
        Node<T>* head;
        int size;
        Node<T>* tail;

        // These methods are recursive which need an initial value to start
        // So, these will be overloaded with default value in public section
        // with no arguments
        void printReverse(Node<T>* tmp)
        {
            if(tmp != NULL){
                
                printReverse(tmp->getNext());

                if(tmp != head)
                    std::cout<<tmp->getData()<<"-> ";
                else
                    std::cout<<tmp->getData()<<std::endl;
            }
        }

        void headNode(T data)
        {
            head = new Node(data);
            size = 1;
            tail = head;
        }

    public:
        LinkedList(): head(nullptr), size(0), tail(head) {}
        
        LinkedList(T data): head(new Node(data)), size(1), tail(head) {}

         ~LinkedList() {
        // Destructor to free the memory for the linked list nodes
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->getNext();
            delete temp;
        }
        if (current == tail) {
            tail = nullptr;
        }

    }

        Node<T>* getHead(){
            return head;
        }

        Node<T>* getTail(){
            return tail;
        }

        int getSize(){
            return size;
        }

        void append(T data)
        {
            if(size == 0)
                headNode(data);
            else if(size > 0){
                Node<T>* n = new Node(data);
                tail->setNext(n);
                size ++;
                tail = tail->getNext();
            }else{
                std::cout<<std::endl<<"Invalid Scenario. Size can't be negative"<<std::endl;
            }
        }

        void prepend(T data)
        {
            if(size == 0)
                headNode(data);
            else if(size > 0){
                Node<T>* n = new Node(data);
                n->setNext(head);
                size ++;
                head = n;
            }else{
                std::cout<<std::endl<<"Invalid Scenario. Size can't be negative"<<std::endl;
            }
        }

        void insert(T data, int pos){
            if( pos < 0 || pos > size){
                std::cout<<std::endl;
                std::cout<<"Cannot insert node ";
                std::cout<<"beyond LinkedList range [0, "<<size<<"]"<<std::endl;
                return;
            }
            else if ( pos == 0 )
                prepend( data );
            else{
                Node<T>* n = new Node(data);
                Node<T>* tmp = head;
                for( int i = 0; i < pos-1; i++ )
                    tmp = tmp->getNext();
                
                n->setNext( tmp->getNext() );
                tmp->setNext( n );
                size ++;
            }
        }

        int search(T target)
        {
            Node<T>* tmp = head;
            for ( int i=0; i<size; i++)
            {
                if(tmp->getData() == target)
                    return i;
                tmp = tmp->getNext();
            }
            return -1;
        }

        void printReverse()
        {
            printReverse(head);
        }

        void reverse(){
            Node<T> *prev = nullptr, *cur = head, *next;
            tail = head;
            while (cur != nullptr)
            {
                next = cur->getNext();
                cur->setNext(prev);
                prev = cur;
                cur = next;
            }
            head = prev;
        }

        void sort()
        {
            int min;
            Node<T> *pos=head, *minPtr;
            for(int i=0; i<size; i++){
                Node<T> *tmpNode = pos;
                minPtr = pos;
                min = INT32_MAX;
                while (tmpNode != NULL)
                {
                    if ( tmpNode->getData() < min)
                    {
                        min = tmpNode->getData();
                        minPtr = tmpNode;
                    }
                    tmpNode = tmpNode->getNext();
                }
                int tmpData = pos->getData();
                pos->setData(minPtr->getData());
                minPtr->setData(tmpData);
                pos = pos->getNext();
            }
            
        }

        T popFirst()
        {
            T data = head->getData();
            Node<T> *tmp = head->getNext();
            delete head;
            head = tmp;
            if(head == nullptr)
                tail = nullptr;
            // delete tmp;
            size--;
            return data;
        }
        
        T popLast()
        {
            Node<T>*tmp = head;
            while(tmp->getNext() != tail)
                tmp = tmp->getNext();
            T data = tail->getData();
            // delete tail;
            tail = tmp;
            tmp->setNext(NULL);
            // delete tmp;
            size--;
            return data;
        }
        // int remove(int element){}
        // int popAt(int index){}
        // void swap(int index1, int index2){}

        friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll)
        {
            Node<T> *tmp = ll.head;
            os<<std::endl;
            if ( tmp == NULL ){
                os<<"EMPTY -> LINKED -> LIST"<<std::endl;
                return os;
            }
            
            os<<"LinkedList[ "<<ll.size<<" ]: ";
            
            while(tmp != ll.tail){
                os<<tmp->getData()<<" -> ";
                tmp = tmp->getNext();
            }
            os<<tmp->getData()<<std::endl;
            os<<std::endl;
            
            return os;
        }
};