
#ifndef solve_expr_h
#define solve_expr_h
#include "state.h"
#include "queue.h"
#include "stack.h"
#include "expression_check.h"
#include "tree.h"
#include "table.h"
#include "hash_table.h"
#include "HashTable.h"
#include "TreeT.h"
#include "TableT.h"
//#include "menu.h"
template <class arr> inline std::pair<polynome,int> solve(std::string str, arr& container, stdvector<polynome>& test){
    std::pair <polynome,int>res;
    std::pair<polynome,int>err_expr;
    std::pair<polynome,int>err_var;
    err_expr.first=polynome();
    err_expr.second=0;
    err_var.first=polynome();
    err_var.second=2;
    TDynamicQueue<State>inf;
    TDynamicQueue<State>post;

    /*my_unordered_map<polynome>tmp_var;

    my_unordered_map<polynome>var_hash;
    HashTable<polynome>var_hash_list;

    Tree<std::string,polynome>var_tree;
    TreeT<std::string, polynome>var_tree_rb;

    Table<std::string,polynome>var_table;
    TableT<std::string, polynome>var_table_unord;*/
    if (!check_str(str,inf,container)) return err_expr;
    if (test.get_size()){
        int i=-1;
        auto it=container.begin();
        for(;it!=container.end();++it){
            if ((*it).first.size()){ i++;
                (*it).second=test[i];}
        }
    }else{
        for(auto el: container){
            if (el.first.size() && !el.second.size()) return err_var;
        }
    }
    if (!check_infix(inf,post)){
        return err_expr;
    }
    //std::cout<<var_tree["a"]<<"\n";
    TDynamicQueue<State>cop(post);
    if (!check_post(post,res,container)) return err_expr;
    return res;
}
#endif /* solve_expr_h */
