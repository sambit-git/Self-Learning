#include<iostream>

class Node
{
    private:
        int data;
        Node * next;
    public:
        Node(int data) : data(data), next(NULL) {}

        int getData()
        {
            return data;
        }

        void setData(int data)
        {
            this->data = data;
        }

        Node* getNext()
        {
            return next;
        }
        
        void setNext(Node* next)
        {
            this->next = next;
        }
};

class LinkedList
{
    private:
        Node* head;
        int size;
        Node* tail;

        // These methods are recursive which need an initial value to start
        // So, these will be overloaded with default value in public section
        // with no arguments
        void printReverse(Node* tmp)
        {
            if(tmp != NULL){
                
                printReverse(tmp->getNext());

                if(tmp != head)
                    std::cout<<tmp->getData()<<"-> ";
                else
                    std::cout<<tmp->getData()<<std::endl;
            }
        }

        void headNode(int data)
        {
            head = new Node(data);
            size = 1;
            tail = head;
        }

    public:
        LinkedList(): head(nullptr), size(0), tail(head) {}
        
        LinkedList(int data): head(new Node(data)), size(1), tail(head) {}

         ~LinkedList() {
        // Destructor to free the memory for the linked list nodes
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->getNext();
            delete temp;
        }
        if (current == tail) {
            tail = nullptr;
        }

    }

        Node* getHead(){
            return head;
        }

        Node* getTail(){
            return tail;
        }

        int getSize(){
            return size;
        }

        void append(int data)
        {
            if(size == 0)
                headNode(data);
            else if(size > 0){
                Node* n = new Node(data);
                tail->setNext(n);
                size ++;
                tail = tail->getNext();
            }else{
                std::cout<<std::endl<<"Invalid Scenario. Size can't be negative"<<std::endl;
            }
        }

        void prepend(int data)
        {
            if(size == 0)
                headNode(data);
            else if(size > 0){
                Node* n = new Node(data);
                n->setNext(head);
                size ++;
                head = n;
            }else{
                std::cout<<std::endl<<"Invalid Scenario. Size can't be negative"<<std::endl;
            }
        }

        void insert(int data, int pos){
            if( pos < 0 || pos > size){
                std::cout<<std::endl;
                std::cout<<"Cannot insert node ";
                std::cout<<"beyond LinkedList range [0, "<<size<<"]"<<std::endl;
                return;
            }
            else if ( pos == 0 )
                prepend( data );
            else{
                Node* n = new Node(data);
                Node *tmp = head;
                for( int i = 0; i < pos-1; i++ )
                    tmp = tmp->getNext();
                
                n->setNext( tmp->getNext() );
                tmp->setNext( n );
                size ++;
            }
        }

        int search(int target)
        {
            Node* tmp = head;
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
            Node *prev = nullptr, *cur = head, *next;
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
            Node *pos=head, *minPtr;
            for(int i=0; i<size; i++){
                Node *tmpNode = pos;
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

        int popFirst()
        {
            int data = head->getData();
            Node *tmp = head->getNext();
            delete head;
            head = tmp;
            // delete tmp;
            size--;
            return data;
        }
        
        int popLast()
        {
            Node*tmp = head;
            while(tmp->getNext() != tail)
                tmp = tmp->getNext();
            int data = tail->getData();
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

        friend std::ostream& operator<<(std::ostream& os, const LinkedList& ll)
        {
            Node *tmp = ll.head;
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