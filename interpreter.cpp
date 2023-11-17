#include <iostream>
#include <unordered_map>
#include <string>
#include <any>
#include "TokenType.h"
#include "Token.h"
#include <ctype.h>
#include <map>
using namespace std;


class interpreter: public ExprVisitor<any> StmtVisitor<void>{
    private:
        any visitLiteralExpr(shared_ptr<Expr> expr) override{
            return expr->value;
        }
        any visitUnaryExpr(shared_ptr<Unary> expr) override {
            any right = evaluate(expr->right);

            switch (expr->oper.type) {
                 case BANG:
                    return !isTruthy(right);
                case MINUS:
                    return -any_cast<double>(right);
    }
     
        void visitExpressionStmt(Stmt.Expression stmt) override {
            any stmt = evaluate(stmt->expression);
            
  }
        void checkNumberOperand(Token oper, any operand) {
            if (operand.type() ==  typeid(double)) return;
            throw runtime_error("Operand must be a number.");
    }
        void checkNumberOperands(Token oper,any left, any right) {
            if (left.type() == typeid(double) && right.type() == typeid(double)) return;
    
            throw runtime_error("Operands must be numbers.");
  }
        void execute(Stmt stmt) {
            stmt->accept(*this);
  }
        void visitPrintStmt(Stmt.Print stmt) override{
            any value = evaluate(stmt->expression);
            cout << (stringify(value)) <<;
            
  }
        any visitBinaryExpr(shared_ptr<Binary> expr) override {
            any left = evaluate(expr->left);
            any right = evaluate(expr->right); 

            switch (expr.operator.type) {
                case BANG_EQUAL: return !isEqual(left, right);
                case EQUAL_EQUAL: return isEqual(left, right);
                case GREATER:
                    checkNumberOperands(expr->oper, left, right);
                    return cast_any<double>(left) > cast_any<double>(right);
                case GREATER_EQUAL:
                    checkNumberOperands(expr->oper, left, right);
                    return cast_any<double>(left) >= cast_any<double>(right);
                case LESS:
                    checkNumberOperands(expr->oper, left, right);
                    return cast_any<double>(left) < cast_any<double>(right);
                case LESS_EQUAL:
                    checkNumberOperands(expr->oper, left, right);
                    return cast_any<double>(left) <= cast_any<double>(right);
                case MINUS:
                    checkNumberOperands(expr->oper, left, right);
                    return any_cast<double>(left) - any_cast<double>(right);
                case PLUS:
                    if (left.type() == typeid(double) && right.type() == typeid(double)) {
                        return any_cast<double>(left)+ any_cast<double>(right);
                } 
                    if (left.type() == typeid(string) && right.type() == typeid(string)) {
                        return any_cast<string>(left) + any_cast<string>(right);
                }
                    //break;
                    throw runtime_error("Operands must be two numbers or two strings.");
                case SLASH:
                    checkNumberOperands(expr->oper, left, right);
                    return any_cast<double>(left) / any_cast<double>(right);
                case STAR:
                    checkNumberOperands(expr->oper, left, right);
                    return any_cast<double>(left) * any_cast<double>(right);
            }

    // Unreachable.
                return NULL;
        }
        bool isTruthy(any object) {
            if (object.type() == typeid(NULL)) return false;
            if (object.type() typeid(bool)) return any_cast<bool> object;
            return true;
        }
        bool isEqual(any a, any b) {
            if (a.type() == typeid(NULL) && b.type() == typeid(NULL)) return true;
            if (a.type() == typeid(NULL)) return false;

            return a.equals(b);
        }
        string stringify(any object) {
            if (object.type() == typeid(NULL)) return "nil";

            if (object.type() == typeid(double)) {
                string text = object.to_string();
            if (text.ends_with(".0")) {
                text = text.substr(0, text.length() - 2);
        }
        return text;
    }

    return object.to_string();
  }

        return NULL;
        }
        any evaluate(shared_ptr<Expr> expr) {
            return expr->accept(*this);
        }

        
    public:
        void interpret(shared_ptr<Expr> expression) { 
            try {
                any value = evaluate(expression);
                cout << stringify(value) <<endl;
            }   catch (runtime_error error) {
                runtime_error("error");
    }
  }

}; 