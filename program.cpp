#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <ctime>

using namespace std;


struct Value{
    
    long int *list;
    
};

class MergeSort{
    
public:
    void mergeSort(Value *, int , int );
    
private:
    void merge(Value *, int , int , int );  
    
};

class BubbleSort{
    
public:
    void bubbleSort( Value* , int );
    
};


void MergeSort::merge(Value *val, int low, int mid, int high){
    
    int len1 = (mid - low) + 1;
    int len2 = (high - mid);
    
    Value leftArr;
    leftArr.list = new long int[len1 + 1];
    Value rightArr;
    rightArr.list= new long int[len2 + 1];
    
    for (int i = 0; i < len1; i++){
        
        leftArr.list[i] = val->list[(low + i)];
        
    }
    
    for (int j = 0; j < len1; j++){
        
        rightArr.list[j] = val->list[(mid + j) + 1];
        
    }
    
    leftArr.list[len1]=(INT_MAX);
    rightArr.list[len2]=(INT_MAX);
    int i(0), j(0);
    
    for (int k = low; k <= high; k++){
        
        if (leftArr.list[i] <= rightArr.list[j]){
            
            val->list[k] = leftArr.list[i];
            i++;
            
        }
        else{
            
            val->list[k] = rightArr.list[j];
            j++;
            
        }
        
    }

}
 
void MergeSort::mergeSort(Value *val, int low, int high){
    
    if (low < high){
        
        int mid = (low + high) / 2;
        mergeSort(val, low, mid);
        mergeSort(val, mid + 1, high);
        merge(val, low, mid, high);
        
    }
    
}


void BubbleSort::bubbleSort( Value* val, int length ){
    
    int i = length;
    bool sorted = false;
    
    while(i>1 && !sorted){
        sorted = true;
        
        for( int j = 1 ; j < i ; j++){
            
            if( val->list[j] < val->list[j-1] ) {
                
                int k = val->list[j];
                val->list[j] = val->list[j-1];
                val->list[j-1] = k;
                
                sorted = false;
                
            }
            
        }
        
        i--;   
        
    }
    
}


void readFile( Value* val, string pFileName, int length ){  
    
    ifstream file( pFileName );
    if ( file.is_open() ) {
        for(int i = 0; i<length; i++){

            file >> val->list[ i ];
            
           // cout << val->list[ i ] << endl;
        }
        file.close();
        
    }
    
}

void writeToFile(Value *val, int length){
    
    ofstream writeFile("output.txt");
    
    for( int i = 0; i < length; i++){
        writeFile << val->list[i] << endl;
    }
    
    writeFile.close();
    
}



int main(int argv, char *argc[])
{
    
    string mode = string(argc[1]);
    long length = stoi(argc[2]);
    string fileName = argc[3];
        
    Value values;
    values.list = new long int[length];
    readFile(&values, fileName, length);


    clock_t t;



    if(mode == "m"){

        MergeSort ms;
        t = clock();
        ms.mergeSort(&values, 0, length-1);
        t = clock() - t;
        printf("Running time is %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
        writeToFile(&values, length);
        
    }
    else if(mode == "b"){
        
        BubbleSort bs;
        t = clock();
        bs.bubbleSort( &values, length ); 
        t = clock() - t;
        printf("Running time is %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
        writeToFile(&values, length);
        
    }
              
    return 0;    
    
}
