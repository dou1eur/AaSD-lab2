#include <iostream>

using namespace std;

template<typename T>
struct Node{
    T data;
    Node<T>* prev;
    Node<T>* next;
    Node(const T& d){
        data=d;
        prev=next=nullptr;
    }
};

template<typename T>

class DLList{
    private:
        Node<T>*  _head;
        Node<T>*  _tail;
        size_t _size;
    public:
        //Constructors
        DLList(){
            _head=_tail=nullptr;
            _size=0;
        }
        DLList(const DLList<T>& other){
            _head=_tail=nullptr;
            _size=other._size;
            Node<T>* new_head=other._head;
            while(new_head){
                push_tail(new_head->data);
                new_head=new_head->next;
            }
        }
        DLList(size_t count, const T& min, const T& max){
            srand(time(0));
            _head=_tail=nullptr;
            _size=count;
            for(size_t i=0;i<_size;++i){
                T value=rand() % (max-min+1)+min;
                push_tail(value);
            }
        }
        ~DLList(){
            while(_head){
                auto tmp=_head;
                _head=_head->next;
                delete tmp;
            }
            _head=_tail=nullptr;
            _size=0;
        }

        //Getting class fields
        Node<T>* get_head() const{
            return _head;
        }
        Node<T>* get_tail() const{
            if(_head==nullptr){
                return nullptr;
            }
            Node<T>* tmp=_head;
            while(tmp->next!=nullptr){
                tmp=tmp->next;
            }
            return tmp;
        }
        size_t get_size() const{
            return _size;
        }
        Node<T>* get_data(size_t idx){
            Node<T>* tmp=_head;
            size_t index=0;
            while(index!=idx){
                if(tmp==nullptr){
                    return nullptr;
                }
                tmp=tmp->next;
                ++index;
            }
            return tmp;
        }


        //Operators, insert and remove value by idx
        DLList<T> operator=(const DLList<T>& other){
            if(this!= &other){
                clear();
                Node<T>* tmp=other._head;
                while(tmp!=nullptr){
                    push_tail(tmp->data);
                    tmp=tmp->next;
                }
            }
            //_size=other._size;
            return *this;
        }
        T& operator[](int idx){
            return get_data(idx)->data;
        }
        const T& operator[](int idx) const{
            return get_data(idx)->data;
        }

        Node<T>* insert(int idx,const T& value){
            Node<T>* right=get_data(idx);
            if(right==nullptr){
                ++_size;
                return push_tail(value);
            }
            Node<T>* left=right->prev;
            if(left==nullptr){
                ++_size;
                return push_head(value);
            }
            Node<T>* new_value=new Node<T>(value);
            new_value->prev=left;
            new_value->next=right;
            left->next=new_value;
            right->prev=new_value;
            ++_size;
            return new_value;
        }
        void remove(int idx){
            Node<T>* value=get_data(idx);
            if(value==nullptr){
                return;
            }
            if(value->prev==nullptr){
                return pop_head();
            }
            if(value->next==nullptr){
                return pop_tail();
            }
            Node<T>* right=value->next;
            Node<T>* left=value->prev;
            right->prev=left;
            left->next=right;
            delete value;
        }

        void clear(){
            Node<T>* head=_head;
            while(head){
                Node<T>* tmp=head;
                head=head->next;
                delete tmp;
            }
            _head=_tail=nullptr;
            _size=0;
        }

        //Head and tail insert
        Node<T>* push_tail(const T& value){
            Node<T>* tmp=new Node<T>(value);
            if(_tail==nullptr){
                _head=_tail=tmp;
            }
            else {
                tmp->prev=_tail;
                _tail->next=tmp;
                _tail=tmp;
            }
            ++_size;
            return tmp;
        }
        Node<T>* push_tail(const DLList<T>& other){
            Node<T>* tmp=other._head;
            while(tmp!=nullptr){
                push_tail(tmp->data);
                tmp=tmp->next;
            }
            return tmp;
        }
        Node<T>* push_head(const T& value){
            Node<T>* tmp=new Node<T>(value);
            tmp->next=_head;
            if(_head!=nullptr){
                _head->prev=tmp;
            }
            if(_tail==nullptr){
                _tail=_head=tmp;
            }
            _head=tmp;
            ++_size;
            return tmp;
        }

        Node<T>* push_head(const DLList<T>& other){
            Node<T>* tmp=other._tail;
            while(tmp!=nullptr){
                push_head(tmp->data);
                tmp=tmp->prev;
            }
            return tmp;
        }

        //delete
        void pop_head(){
            if(_head==nullptr){
                return;
            }
            Node<T>* new_head=_head->next;
            if(new_head!=nullptr){
                new_head->prev=nullptr;
            }
            else _tail=nullptr;
            delete _head;
            _head=new_head;
            --_size;
        }

        void pop_tail(){
            if(_tail == nullptr){
                return;
            }
            Node<T>* new_tail=_tail->prev;
            if(new_tail!=nullptr){
                new_tail->next=nullptr;
            }
            else _head=nullptr;
            delete _tail;
            _tail=new_tail;
            --_size;
        }

        void delete_node(T value){
            Node<T>* tmp=_head;
            while(tmp!=nullptr){
                if(tmp->data==value){
                    Node<T>* copy=tmp;
                    tmp=tmp->next;
                    if(copy->next!=nullptr){
                        copy->next->prev=copy->prev;
                    }
                    else _tail=copy->prev;
                    if(copy->prev!=nullptr){
                        copy->prev->next=copy->next;
                    }
                    else _head=copy->next;
                    delete copy;
                    --_size;
                }
                else tmp=tmp->next;
            }
        }

        friend ostream& operator<<(ostream& out,const DLList<T>& list){
            Node<T>* tmp=list.get_head();
            while(tmp!=nullptr){
                out<<tmp->data<<" ";
                tmp=tmp->next;
            }
            return out;
        }
};


int main(){
    DLList<int> l1;
    DLList<int> l2;
    l2.push_head(4);
    l2.push_head(7);
    l2.push_head(7);
    l2.push_head(0);
    cout<<"List l2: "<<l2<<endl;
    cout<<"Check push_head: "<<l2<<endl;
    cout<<"List l1 before copy: "<<l1<<endl;
    l1=l2;
    cout<<"Check l1(operator=) : "<<l1<<endl;
    DLList<double> l3;
    l3.push_tail(3.4);
    l3.push_tail(8.1);
    l3.push_tail(34.7);
    cout<<"List l3(check push_tail): "<<l3<<endl;
    cout<<"Check operator[] for l2[1]: "<<l2[1]<<endl;
    l2.insert(1,5);
    cout<<"Check insert by idx for l2: "<<l2<<endl;
    l3.insert(2,7.9);
    cout<<"Check insert by idx for l3: "<<l3<<endl;
    l2.remove(4);
    cout<<"Check remove by idx for l2: "<<l2<<endl;
    l3.remove(0);
    cout<<"Check remove for l3: "<<l3<<endl;
    DLList<int> l4;
    l4.push_tail(2);
    l4.push_tail(1);
    l4.push_tail(13);
    l4.push_tail(8);
    l4.push_tail(19);
    cout<<"List 4: "<<l4<<endl;
    l4.push_head(l2);
    cout<<"Check push_head(list) for l4: "<<l4<<endl;
    l4.push_tail(l1);
    cout<<"Check push_tail(list) for l4: "<<l4<<endl;
    l2.pop_head();
    cout<<"Check pop_head for l2: "<<l2<<endl;
    l3.pop_tail();
    cout<<"Check pop_tail for l3: "<<l3<<endl;
    l1.delete_node(4);
    cout<<"Check delete_node for l1: "<<l1<<endl;
};