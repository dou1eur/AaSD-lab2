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
            _size=other.get_size();
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
                T value=rand()%(max-min+1)+min;
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
                while(tmp){
                    push_tail(tmp->data);
                    tmp=tmp->next;
                }
            }
            _size=other._size;
            return *this;
        }
        T& operator[](int idx){
            return get_data(idx)->data;
        }
        const T& operator[](int idx) const{
            return get_data(idx)->data;
        }

        Node<T>* insert(int idx,const T& value){
            Node<T>* next=get_data(idx);
            if(next==nullptr){
                ++_size;
                return push_tail(value);
            }
            Node<T>* prev=next->prev;
            if(prev==nullptr){
                ++_size;
                return push_head(value);
            }
            Node<T>* new_value=new Node<T>(value);
            new_value->prev=prev;
            new_value->next=next;
            prev->next=new_value;
            next->prev=new_value;
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
            Node<T> right=value->next;
            Node<T> left=value->prev;
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
            if(!_head){
                _head=tmp;
            }
            else {
                Node<T>* cur=_head;
                while(cur->next!=nullptr){
                    cur=cur->next;
                    cur->next=tmp;
                    tmp->prev=cur;
                }
            }
            _tail=tmp;
            return tmp;
        }
        Node<T>* push_tail(const DLList<T>& other){
            Node<T>* tmp=other._head;
            while(tmp!=nullptr){
                T d=tmp->data;
                push_tail(d);
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
            for (Node<T>* l=list.get_head();l!=nullptr;l=l->next){
                out<<"List: "<<l->data<<endl;
            }
            return out;
        }
};

template<typename T>
void print(DLList<T> list){
    cout<<"List: "<<endl;
    for (Node<T>* l=list.get_head();l!=nullptr;l=l->next){
        cout<<l->data<<endl;
    }
}


int main(){
    DLList<int> l1;
    DLList<int> l2;
    l2.push_head(4);
    l2.push_head(7);
    l2.push_head(7);
    l2.push_head(0);
    cout<<"Check push_head: "<<l2<<endl;
    //print(l2);
    cout<<l1;
    cout<<"Check operator= : "<<(l1=l2)<<endl;
    //print(l2);
};