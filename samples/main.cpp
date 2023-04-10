#include "solve_expr.h"
#include "menu.h"
using namespace std;
int main() {
    my_unordered_map<polynome>var_hash;
    HashTable<polynome>var_hash_list;

    Tree<std::string,polynome>var_tree;
    TreeT<std::string, polynome>var_tree_rb;

    Table<std::string,polynome>var_table;
    TableT<std::string, polynome>var_table_unord;
    stdvector<polynome>a;
    cout<<"terms of use:\n1 enter all operators and numbers separately by space (it can be more than 1)\n2 integers and decimals are supported\n3 addition, substraction, multiplication and division are supported\n4 Variables are supported\5 Variables must start with latin letter or with _\n6 Variables can consist latin letters, '_' and numbers\n8 polynomes can be wrote only as variables\n9 monomes' format: <coef>x<x power>y<y power>z<z power>\n";
    //solve("11", var_hash, a);
    while (true) {
        menu(var_hash,var_hash_list,var_tree, var_tree_rb, var_table, var_table_unord);
        std::string ans="22";
        while (ans!="y" && ans!="n") {
            cout<<"do you want to continue working with programm? (y/n) ";
            cin>>ans;
            //cin.ignore(INT_MAX);
        }
        if (ans=="n") break;
        cin.ignore();
    }
}

