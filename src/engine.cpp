#include<bits/stdc++.h>

using namespace std;

class order{
    int price;
    int qty;
    string type;
};

int executeLO(order od, vector<order>& buyBook, vector<order>& sellBook){
    int totalValue=0;
    if(od.type=="B"){
        for(int i=0;i<sellBook.size();i++){
            if(od.price >= sellBook[i].price){
                if(od.qty >= sellBook[i].qty){
                    totalValue+=sellBook[i].price*min(od.qty,sellBook[i].qty);
                    od.qty-=sellBook[i].qty;
                    sellBook[i].qty=0;
                }
                else{
                    totalValue+=sellBook[i].price*min(od.qty,sellBook[i].qty);
                    sellBook[i].qty-=od.qty;
                    od.qty=0;
                }
            }
        }
        //Add the rest order to the Book
        if(od.qty >0)
            buyBook.add(od);
        return totalValue;
    }
    else if(od.type=="S"){

    }
}
int executeMO(order od, vector<int>& buyBook, vector<int>& sellBook){
    int totalValue;
    if(od.type=="B"){

    }
    else if(od.type=="S"){

    }
}

int main(){
    return 0;    
}