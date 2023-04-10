//#include "solve_expr.h"
void print(stdvector<std::pair<polynome,int>> arr){
    for(int i=0;i<6;++i){
        if (arr[i].second==0) {std::cout<<"INCORRECT EXPRESSION\n";return;}
    }
    for(int i=0;i<6;++i){
        if (arr[i].second==2) {std::cout<<"SET NOT ALL VARS\n";return;}
    }
    std::cout<<"hash_table_open_adr:\n";
    if (!arr[0].second) std::cout<<"no result(\n";
    else std::cout<<arr[0].first<<"\n";
    
    
    std::cout<<"tree_avl:\n";
    if (!arr[1].second) std::cout<<"no result(\n";
    else std::cout<<arr[1].first<<"\n";
    
    
    std::cout<<"ordered_table:\n";
    if (!arr[2].second) std::cout<<"no result(\n";
    else std::cout<<arr[2].first<<"\n";
    
    
    std::cout<<"hash_table_list:\n";
    if (!arr[3].second) std::cout<<"no result(\n";
    else std::cout<<arr[3].first<<"\n";
    
    
    std::cout<<"red-black tree:\n";
    if (!arr[4].second) std::cout<<"no result(\n";
    else std::cout<<arr[4].first<<"\n";
    
    std::cout<<"unordered_table:\n";
    if (!arr[5].second) std::cout<<"no result(\n";
    else std::cout<<arr[5].first<<"\n";
}
void insert( my_unordered_map<polynome>&var_hash, HashTable<polynome>&var_hash_list,Tree<std::string,polynome>&var_tree,TreeT<std::string, polynome>&var_tree_rb,Table<std::string,polynome>&var_table,TableT<std::string, polynome>&var_table_unord, std::string var){
    //my_unordered_map<polynome>tmp_var;
    if (!var.size()) return;
    polynome pol;
    std::cout<<var<<" = ";
    std::cin.ignore();
    std::string str;getline(std::cin,str);
    str+=' ';
    std::size_t pos = str.find(' ');
    State prev;
    bool neg=0;
    while (pos < str.size()){
        auto tmp_str=str.substr(0, pos);
        if (tmp_str!="-" && tmp_str!="+" && tmp_str!=" "){
            if(!checkmonome(tmp_str)){
                return;
            }
            monome mon(tmp_str);
            if (neg){
                mon=mon*-1;
                neg=0;
            }
            pol.insert(mon);
        }else{
            if (tmp_str=="-") neg=1;
        }
        str = str.substr(pos + 1);
        pos = str.find(' ');
    }
    var_hash[var]=pol;
    var_tree[var]=pol;
    var_table[var]=pol;
    var_hash_list[var]=pol;
    var_tree_rb[var]=pol;
    var_table_unord[var]=pol;
}
void erase(my_unordered_map<polynome>&var_hash, HashTable<polynome>& var_hash_list,Tree<std::string,polynome>& var_tree,TreeT<std::string, polynome>& var_tree_rb,Table<std::string,polynome>& var_table,TableT<std::string, polynome>& var_table_unord, std::string& var){
    var_hash.erase(var);
    var_tree.erase(var);
    var_table.erase(var);
    var_hash_list.erase(var);
    var_tree_rb.erase(var);
    var_table_unord.erase(var);
}
bool find(my_unordered_map<polynome>&var_hash, std::string var){
    return var_hash.find(var).second;
}
void menu( my_unordered_map<polynome>&var_hash,HashTable<polynome>&var_hash_list,Tree<std::string,polynome>&var_tree,TreeT<std::string, polynome>&var_tree_rb,Table<std::string,polynome>&var_table,TableT<std::string, polynome>&var_table_unord){
    int ch;
    std::cout<<"OPTIONS\n1 insert polynome\n2 erase polynome\n3 find polynome\n4 solve expression\n";
    do{
        std::cin>>ch;
    }while(ch<1 || ch>4);
    if (ch==1){
        int num;
        std::cout<<"number of variables = ";std::cin>>num;
        for(int i=0;i<num;++i){
            std::string var;
            std::cout<<i+1<<": ";
            do{
                std::cin>>var;
                
            }while(!check_var(var));
            insert(var_hash, var_hash_list, var_tree,var_tree_rb,var_table,var_table_unord,var);
        }
    }else if (ch==2){
        int num;
        std::cout<<"number of variables = ";std::cin>>num;
        for(int i=0;i<num;++i){
            std::string var;
            std::cout<<i+1<<": ";
            do{
                std::cin>>var;
                
            }while(!check_var(var));
            erase(var_hash, var_hash_list, var_tree,var_tree_rb,var_table,var_table_unord,var);
        }
    }else if (ch==3){
        std::string var;
        do{
            std::cin>>var;
            
        }while(!check_var(var));
        std::cout<<"variable is"<<(find(var_hash,var)?"in container":"is not in continer")<<"\n";
    }else{
        stdvector<polynome>test;
        std::cout<<"enter the expression:\n";
        std::string res;
        std::cin.ignore();
        getline(std::cin, res);
        stdvector<std::pair<polynome,int>>ans;
        my_unordered_map<polynome> a22;
        ans.push_back(solve<my_unordered_map<polynome>>(res,var_hash,test));
        ans.push_back(solve<HashTable<polynome>>(res,var_hash_list,test));
        ans.push_back(solve(res,var_tree,test));
        ans.push_back(solve(res,var_tree_rb,test));
        ans.push_back(solve(res,var_table,test));
        ans.push_back(solve(res,var_table_unord,test));
        print(ans);
    }
}

/*cout<<"enter the expression:\n";
 getline(cin, res);
 auto tmp=solve(res,a);
 if (!tmp.get_size()) cout<<"INCORRECT EXPRESSION\n";
 else print(tmp);
 string ans="1";
 //cin.ignore();*/
