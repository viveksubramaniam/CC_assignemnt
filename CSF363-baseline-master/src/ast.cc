#include "ast.hh"

#include <string>
#include <vector>

NodeBinOp::NodeBinOp(NodeBinOp::Op ope, Node *leftptr, Node *rightptr) {
    type = BIN_OP;
    op = ope;
    left = leftptr;
    right = rightptr;
}

std::string NodeBinOp::to_string() {
    std::string out = "(";
    switch(op) {
        case PLUS: out += '+'; break;
        case MINUS: out += '-'; break;
        case MULT: out += '*'; break;
        case DIV: out += '/'; break;
    }

    out += ' ' + left->to_string() + ' ' + right->to_string() + ')';
    for(int i=0;i<left->to_string().length();i++){
        if(!(left->to_string()[i]<='9' && left->to_string()[i]>='0')){
            return out;
        }
    }
    for(int i=0;i<right->to_string().length();i++){
        if(!(right->to_string()[i]<='9' && right->to_string()[i]>='0')){
            return out;
        }
    }
    std::string temp="";
    switch(op) {
        case PLUS: temp += std::to_string(stoi(left->to_string())+stoi(right->to_string())); break;
        case MINUS: temp += std::to_string(stoi(left->to_string())-stoi(right->to_string())); break;
        case MULT: temp += std::to_string(stoi(left->to_string())*stoi(right->to_string())); break;
        case DIV: temp += std::to_string(stoi(left->to_string())/stoi(right->to_string())); break;
    }
    return temp;
}

NodeInt::NodeInt(int val) {
    type = INT_LIT;
    value = val;
}

std::string NodeInt::to_string() {
    return std::to_string(value);
}

NodeStmts::NodeStmts() {
    type = STMTS;
    list = std::vector<Node*>();
}

void NodeStmts::push_back(Node *node) {
    list.push_back(node);
}

std::string NodeStmts::to_string() {
    std::string out = "(begin";
    for(auto i : list) {
        out += " " + i->to_string();
    }

    out += ')';

    return out;
}

NodeDeclInt::NodeDeclInt(std::string id, Node *expr) {
    type = ASSN;
    identifier = id;
    expression = expr;
}

NodeDeclShort::NodeDeclShort(std::string id, Node *expr) {
    type = ASSN;
    identifier = id;
    expression = expr;
}

NodeDeclLong::NodeDeclLong(std::string id, Node *expr) {
    type = ASSN;
    identifier = id;
    expression = expr;
}

std::string NodeDeclInt::to_string() {
    return "(let " + identifier + " : int = " + expression->to_string() + ")";
}

std::string NodeDeclShort::to_string() {
    return "(let " + identifier + " : short = " + expression->to_string() + ")";
}

std::string NodeDeclLong::to_string() {
    return "(let " + identifier + " : long = " + expression->to_string() + ")";
}

NodeDebug::NodeDebug(Node *expr) {
    type = DBG;
    expression = expr;
}

std::string NodeDebug::to_string() {
    return "(dbg " + expression->to_string() + ")";
}

NodeIdent::NodeIdent(std::string ident) {
    identifier = ident;
}
std::string NodeIdent::to_string() {
    return identifier;
}
