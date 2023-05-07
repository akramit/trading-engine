#include<iostream>
#include<vector>
#include<string>
#include<sstream>


using namespace std;

class order{

    public: 
    string id;
    int price;
    int qty;
    string type;

    order(string i,int q, string t){
        id=i;
        qty=q;
        type=t;
    }
    order(string i,int p, int q, string t){
        id=i;
        price=p;
        qty=q;
        type=t;
    }
};

bool compareAsc(order a, order b){
    return a.qty < b.qty;
}
bool compareDesc(order a, order b){
    return a.qty > b.qty;
}

/*
* Executes Limit Order and add the unfullfilled order to buy/sell Book.
* Returns Total Value Traded
*/
int executeLimitOrder(order od, vector<order>& buyBook, vector<order>& sellBook){
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
                    break;
                }
            }
        }
        // Add the rest order to the Buy Book
        if(od.qty > 0){
            buyBook.push_back(od);
            sort(buyBook.begin(),buyBook.end(),compareDesc);
        }
        
        // Remove orders from Sell Book wity qty 0
        for(int i=0;i<sellBook.size();){
            if(sellBook[i].qty==0){
                sellBook.erase(sellBook.begin()+i);
            }
            else{
                i++;
            }
        }   
    }
    else if(od.type=="S"){
        for(int i=0;i<buyBook.size();i++){
            if(od.price <= buyBook[i].price){
                if(od.qty >= buyBook[i].qty){
                    totalValue+=buyBook[i].price*min(od.qty,buyBook[i].qty);
                    od.qty-=buyBook[i].qty;
                    buyBook[i].qty=0;
                }
                else{
                    totalValue+=buyBook[i].price*min(od.qty,buyBook[i].qty);
                    buyBook[i].qty-=od.qty;
                    od.qty=0;
                    break;
                }
            }
        }
        // Add the rest order to the Sell Book
        if(od.qty >0){
            sellBook.push_back(od);
            sort(sellBook.begin(),sellBook.end(),compareAsc);
        }
        
        // Remove orders from Buy Book wity qty 0
        for(int i=0;i<buyBook.size();){
            if(buyBook[i].qty==0){
                buyBook.erase(buyBook.begin()+i);
            }
            else{
                i++;
            }
        }
    }
    return totalValue;
}

/*
* Executes Marke Order and reject the unfulfilled order.
* Returns Total Value Traded
*/
int executeMarketOrder(order od, vector<order>& buyBook, vector<order>& sellBook){
    int totalValue=0;
    if(od.type=="B"){
        for(int i=0;i<sellBook.size();i++){
            if(od.qty >= sellBook[i].qty){
                totalValue+= sellBook[i].price*min(od.qty,sellBook[i].qty);
                od.qty-=sellBook[i].qty;
                sellBook[i].qty=0;
            }
            else{
                totalValue+= sellBook[i].price*min(od.qty,sellBook[i].qty);
                sellBook[i].qty-=od.qty;
                od.qty=0;
                break;
            }
        }
        // Remove orders from Sell Book wity qty 0
        for(int i=0;i<sellBook.size();){
            if(sellBook[i].qty==0){
                sellBook.erase(sellBook.begin()+i);
            }
            else{
                i++;
            }
        }
    }
    else if(od.type=="S"){
        for(int i=0;i<buyBook.size();i++){
            if(od.qty >= buyBook[i].qty){
                totalValue+=buyBook[i].price*min(od.qty,buyBook[i].qty);
                od.qty-=buyBook[i].qty;
                buyBook[i].qty=0;
            }
            else{
                totalValue+=buyBook[i].price*min(od.qty,buyBook[i].qty);
                buyBook[i].qty-=od.qty;
                od.qty=0;
                break;
            }
        }
        // Remove orders from Buy Book wity qty 0
        for(int i=0;i<buyBook.size();){
            if(buyBook[i].qty==0){
                buyBook.erase(buyBook.begin()+i);
            }
            else{
                i++;
            }
        }
    }
    return totalValue;
}

int main(){

    vector<order> buyBook;
    vector<order> sellBook;

    do{
        string in;
        getline(cin,in);
        vector<string> input;
        stringstream ss(in);
        string temp;
        while(ss >> temp){
            input.push_back(temp);
        }

        if(input[0]=="SUB"){
            if(input[1]=="LO"){ //SUB LO B 100 20 id2
                order od(input[5],stoi(input[4]),stoi(input[3]),input[2]);
                cout<<executeLimitOrder(od,buyBook,sellBook)<<endl;
            }
            else if(input[1]=="MO"){ //SUB MO B 100 id2
                order od(input[4],stoi(input[3]),input[2]);
                cout<<executeMarketOrder(od,buyBook,sellBook)<<endl;
            }
        }
        else if(input[0]=="CXL"){
            cout<<"To Do"<<endl;
        }
        else if(input[0]=="END"){
            cout<<"End of Program"<<endl;
            break;
        }
    }while(1);

    return 0;    
}