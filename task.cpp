#include "list.cpp"

using namespace std;

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
    cout<<"Check delete_node [4] for l1: "<<l1<<endl;
    DLList<int> l5(5,3,15);
    cout<<"Check counstructor with random numbers l5: "<<l5<<endl;
    DLList<string> pathList;
    pathList.push_tail("C:/Users/Yana/Documents");
    pathList.push_tail("Multithreading");
    pathList.push_tail("text");
    pathList.push_tail("TCK.txt");
    bool path=concatenation(pathList);
}