#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

enum type{ u_integer, u_double, u_string };

struct variable_desc
{
    variable_desc(int row_number, type data_type) : decl_row(row_number), var_type(data_type) {}
    variable_desc(){} //kell a maphoz
    int decl_row;
    type var_type;
};

struct expression_desc
{
    int row;
    type expr_type;
    //TODO value here???
    expression_desc( int row_number, type data_type) : row(row_number), expr_type(data_type) {}
    expression_desc(expression_desc* other) : row(other->row), expr_type(other->expr_type) {}
    expression_desc(){}

    void set_row(int r)
    {
        row=r;
    }
    int get_row()
    {
        return this->row;
    }
};

struct command_desc
{
    int row;
    command_desc(int row_number) : row(row_number) {}
    command_desc(){}

    void set_row(int r)
    {
        row=r;
    }
    int get_row()
    {
        return this->row;
    }
};

struct command_list_desc
{
    std::vector<command_desc> command_list;
    command_list_desc(command_list_desc* other){
        int osize = other->command_list.size();
        command_list.resize(osize);
        for(int i=0;i<osize;i++)
        {
            command_list[i] = other->command_list[i];
        }
    }
    command_list_desc(){}

    void add(command_desc* cd)
    {
        command_list.push_back(*cd);
    }

    void add(command_list_desc* other)
    {
        for(int i=0;i<other->command_list.size();i++)
        {
            command_list.push_back(other->command_list[i]);
        }
        delete other;
    }
};

struct expr_binary : public expression_desc
{
    int row;
    type expr_type;
    expression_desc* l;
    expression_desc* r;
    expr_binary(int row_number, expression_desc* left, expression_desc* right) : l(left), r(right), row(row_number){}
    expr_binary(){}
};

struct expr_unary : public expression_desc
{
    int row;
    type expr_type;
    expression_desc* e;
    expr_unary(int row_number, expression_desc* ex) : e(ex), row(row_number) {}
    expr_unary(){}
};

struct expr_add : public expr_binary
{
    expr_add(int row_number, expression_desc* left, expression_desc* right){
        if (left->expr_type == right->expr_type)
        {
            expr_type = left->expr_type;
        }
        else
        {
            if (l->expr_type==u_string || r->expr_type==u_string)
            {
                expr_type = u_string;
            }
            else
            {
                expr_type = u_double;
            }
        }
    }
};

struct expr_dif : public expr_binary
{
    expr_dif(int row_number, expression_desc* left, expression_desc* right){
        if (left->expr_type == right->expr_type)
        {
            expr_type = left->expr_type;
        }
        else
        {
            if (left->expr_type==u_string || right->expr_type==u_string)
            {
                expr_type = u_string;
            }
            else
            {
                expr_type = u_double;
            }
        }
    }
};

struct expr_mul : public expr_binary
{
    expr_mul(int row_number, expression_desc* left, expression_desc* right){
        if (left->expr_type == right->expr_type)
        {
            expr_type = left->expr_type;
        }
        else
        {
            if (left->expr_type==u_string || right->expr_type==u_string)
            {
                expr_type = u_string;
            }
            else
            {
                expr_type = u_double;
            }
        }
    }
};

struct expr_div : public expr_binary
{
    expr_div(int row_number, expression_desc* left, expression_desc* right){
        if (left->expr_type == right->expr_type)
        {
            expr_type = left->expr_type;
        }
        else
        {
            if (left->expr_type==u_string || right->expr_type==u_string)
            {
                expr_type = u_string;
            }
            else
            {
                expr_type = u_double;
            }
        }
    }
};

struct expr_pow : public expr_binary
{
    expr_pow(int row_number, expression_desc* left, expression_desc* right){
        if (left->expr_type == right->expr_type)
        {
            expr_type = left->expr_type;
        }
        else
        {
            if (left->expr_type==u_string || right->expr_type==u_string)
            {
                expr_type = u_string;
            }
            else
            {
                expr_type = u_double;
            }
        }
    }
};

struct expr_or : public expr_binary
{
    expr_or(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_and : public expr_binary
{
    expr_and(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_eq : public expr_binary
{
    expr_eq(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_neq : public expr_binary
{
    expr_neq(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_leq : public expr_binary
{
    expr_leq(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_geq : public expr_binary
{
    expr_geq(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_lt : public expr_binary
{
    expr_lt(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_gt : public expr_binary
{
    expr_gt(int row_number, expression_desc* left, expression_desc* right){
        expr_type = u_integer;
    }
};

struct expr_mod : public expr_binary
{
    expr_mod(int row_number, expression_desc* left, expression_desc* right){
        if(left->expr_type==u_integer && right->expr_type==u_integer){
            expr_type = u_integer;
        }
        else{
            //error
        }
    }
};

struct expr_neg : public expr_unary
{
    expr_neg(int row_number, expression_desc* ex){
        expr_type = u_integer;
    }
};

struct expr_um : public expr_unary
{
    expr_um(int row_number, expression_desc* ex){
        expr_type = ex->expr_type;
    }
};

struct assign_desc
{
    std::string* var_name;
    expression_desc* value;
    assign_desc(std::string* var_name_, expression_desc* value_) : var_name(var_name_), value(value_) {}
};


struct for_3_desc : public command_desc
{
    assign_desc* start;
    expression_desc* loop_condition;
    expression_desc* iterate;
    command_list_desc* commands;
    for_3_desc(assign_desc* start_, expression_desc* condition_, expression_desc* iterate_, command_list_desc* commands_) :
     start(start_), loop_condition(condition_), iterate(iterate_), commands(commands_) {}
};

struct for_in_desc : public command_desc
{
    expression_desc* variable;
    expression_desc* loop_expr;
    command_list_desc* commands;
    for_in_desc(expression_desc* variable_, expression_desc* loop_expr_, command_list_desc* commands_) :
    variable(variable_), loop_expr(loop_expr_), commands(commands_) {}
};

struct if_desc : public command_desc
{
    expression_desc* condition;
    command_list_desc* commands_pos;
    command_list_desc* commands_neg;
    if_desc(expression_desc* condition_, command_list_desc* commands_pos_, command_list_desc* commands_neg_) : 
    condition(condition_), commands_pos(commands_pos_), commands_neg(commands_neg_) {}
};

struct while_desc : public command_desc
{
    expression_desc* loop_condition;
    command_list_desc* commands;
    while_desc(expression_desc* condition_, command_list_desc* commands_) : loop_condition(condition_), commands(commands_) {}
};

struct until_desc : public command_desc
{
    expression_desc* loop_condition;
    command_list_desc* commands;
    until_desc(expression_desc* condition_, command_list_desc* commands_) : loop_condition(condition_), commands(commands_) {}
};

struct case_desc : public command_desc
{
    expression_desc* case_expr;
    command_list_desc* case_parts;
    case_desc(expression_desc* case_expr_, command_list_desc* case_parts_) :
    case_expr(case_expr_), case_parts(case_parts_) {}
};

#endif
