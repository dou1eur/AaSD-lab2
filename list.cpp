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
            size_t size=0;
            while(size!=idx){
                if(tmp==nullptr){
                    return nullptr;
                }
                tmp=tmp->next;
                ++size;
            }
            return tmp;
        }


        DLList<t> operator=(const DLList<T>& other){
            if(this!=other){
                clear();
                Node<T>* tmp=other._head;
                while(tmp){
                    push_tail(tmp->data);
                    tmp=tmp->next;
                }
                _size=other._size;
                return *this;
            }
        }
        T& operator[](int idx){
            return get_data(idx)->data;
        }
        const T& operator[](int idx) const{
            return get_data(idx)->data;
        }

        Node<T>* insert(int index,const T& value){

        }
        void remove(int index);

        Node<T>* push_tail(const T& value){
            Node<T>* tmp=other._head;
            if(tmp!=nullptr){
                push_tail(tmp->data);
                tmp=tmp->prev;
            }
            return tmp;
        }
        Node<T>* push_tail(const DLList<T>& other);
        Node<T>* push_head(const T& value){
            Node<T>* tmp=other._tail;
            if(tmp!=nullptr){
                push_head(tmp->data);
                tmp=tmp->prev;
            }
            return tmp;
        }
        Node<T>* push_head(const DLList<T>& other);

        void pop_head();
        void pop_tail();
        void delete_node(T value);
};
