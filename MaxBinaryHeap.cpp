#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;



struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data) 
{  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  node->data = data; 
  node->left = NULL; 
  node->right = NULL; 
  return(node); 
};

struct MaxHeap{
    struct node *root;;
    int nodecount;
    int arrayCounter;
    int arraySave[100];
    MaxHeap();
    void heapify(int count, node* cream){
        //count should initially be 0
        //case with only left child
        if(((count*2+1)<nodecount) && ((count*2+2)==nodecount)){
            if(cream->left->data>cream->data){
                int temp = cream->data;
                cream->data = cream->left->data;
                cream->left->data = temp;
                heapify(0, root);
            }
        }
        else if(((count*2+1)<nodecount) && ((count*2+2)<nodecount)){
            if(cream->left->data>cream->data || cream->right->data>cream->data){
                if(cream->left->data>cream->right->data){
                    int temp = cream->data;
                    cream->data = cream->left->data;
                    cream->left->data = temp;
                    heapify(0, root);
                }
                else if(cream->right->data>cream->left->data){
                    int temp = cream->data;
                    cream->data = cream->right->data;
                    cream->right->data = temp;
                    heapify(0, root);
                }
            }
            else{
                if((count*2+1)<nodecount){
                    heapify(count*2+1,cream->left);
                }
                if((count*2+2)<nodecount){
                    heapify(count*2+2,cream->right);
                }
            }
        }
    }
    void size(){
        cout << (nodecount) << endl;
    }
    void maxLookup(){
        cout << root->data << endl;
    }
    void extractMax(){
        deleteHeap(0, 0, nodecount, root);
    }
    void insert(int value, int count, node* cream){
        //initial count should always be 0
        if(count == nodecount){
            cream->data=value;
            //nodecount++;
            //heapify(0,root);
            return;
        }
        else if (count<nodecount){
            if(cream->left==NULL){
                cream->left = newNode(-1);
            }
            insert(value, (count*2)+1, cream->left);
            if(cream->right==NULL){
                cream->right = newNode(-1);
            }
            insert(value, (count*2)+2, cream->right);
        }
        return;
    }
    void fromArray(int* array, int size, node* cream){
        for(int i = 0; i < size; i++){
            insert(array[i], 0, cream);
            nodecount++;
            //heapify(0,root);
        }
        heapify(0,root);

    }
    void toArray(int count, int size, int print, node* cream){
        if ((count == arrayCounter) && (arrayCounter == size-1)){
            if(print == 1){
                cout << cream->data << "\n";
            }
            if(print == 0){
                arraySave[arrayCounter] = cream->data;
            }
            //arrayCounter ++;
        }
        else if (count == arrayCounter){
            if(print == 1){
                cout << cream->data << " ";
            }
            if(print == 0){
                arraySave[arrayCounter] = cream->data;
            }
            arrayCounter++;
            toArray(0, size, print, root);
        }
        if (count < arrayCounter){
            if(cream->left!=NULL){
                toArray((count*2+1), size, print, cream->left);
            }
            if(cream->right!=NULL){
                toArray((count*2+2), size, print, cream->right);
            }
        }
        if ((count == arrayCounter) && (arrayCounter == size-1)){
            arrayCounter = 0;
        }
    }
    void insertHeap(int value, int count, int size, node *cream){
        //initial count always 0
        if(nodecount!=0){
            toArray(count,size,0,cream);
            int tempArray[nodecount+1];
            for(int i = 0; i < nodecount;i++){
                tempArray[i] = arraySave[i];
            }
            tempArray[nodecount]=value;
            root = newNode(-1);
            nodecount = 0;
            fromArray(tempArray, sizeof(tempArray)/sizeof(tempArray[0]), root);
        }
        else if(nodecount==0){
            int temp[]={value};
            fromArray(temp,1,cream);
        }
    }
    void deleteHeap(int position, int count, int size, node *cream){
        toArray(count,size,0,cream);
        int temp = arraySave[position];
        arraySave[position] = arraySave[size-1];
        arraySave[size-1] = temp;
        int tempArray[size-1];
        for(int i = 0; i < size-1;i++){
            tempArray[i] = arraySave[i];
        }
        root = newNode(-1);
        nodecount = 0;
        fromArray(tempArray, sizeof(tempArray)/sizeof(tempArray[0]), root);
        
    }
};

MaxHeap :: MaxHeap(){
    root = newNode(-1);
    nodecount = 0;
    arrayCounter = 0;
    for (int i = 0; i < 100; i++){
        arraySave[i] = 0;
    }
}

int main(){
    MaxHeap CreamPie;
    
    CreamPie.size();
    CreamPie.insertHeap(5,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.maxLookup();
    //CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.insertHeap(18,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.maxLookup();
    //CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.insertHeap(3,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.maxLookup();
    CreamPie.insertHeap(12,0,CreamPie.nodecount,CreamPie.root);
    //CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.insertHeap(19,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.maxLookup();
    CreamPie.extractMax();
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.maxLookup();
    CreamPie.insertHeap(25,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.insertHeap(6,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.insertHeap(1,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.size();
    CreamPie.extractMax();
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.extractMax();
    CreamPie.extractMax();
    CreamPie.size();
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.deleteHeap(1,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.deleteHeap(1,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.deleteHeap(0,0,CreamPie.nodecount,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.size();
    //CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.maxLookup();

    //CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);

    /*int inputArray[] = {10,12,3,2,1};
    CreamPie.fromArray(inputArray, sizeof(inputArray)/sizeof(inputArray[0]), CreamPie.root);
    //CreamPie.heapify(0,CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.insertHeap(4, 0, CreamPie.nodecount, CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.size();
    CreamPie.deleteHeap(2, 0, CreamPie.nodecount, CreamPie.root);
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.size();
    CreamPie.extractMax();
    CreamPie.toArray(0, CreamPie.nodecount, 1, CreamPie.root);
    CreamPie.size();
    CreamPie.maxLookup();*/
    return 0;
}