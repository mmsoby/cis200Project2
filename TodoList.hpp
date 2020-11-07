//
//  TodoList.hpp
//  Project2
//
//  Created by Mustafa Soby on 11/5/20.
//

#ifndef TodoList_hpp
#define TodoList_hpp

#include <stdio.h>
#include "Todo.hpp"
#include <fstream>
#include <sstream>

struct list{
    Todo item;
    list *next;
};

class TodoList{
private:
    list *head;
    std::ifstream inFile;
    std::ofstream outFile;
public:
    TodoList();
    TodoList(const TodoList &orig);
    void readFile();
    
    
    //Prints
    void printFile();
    void printAll();
    void printFilterPriority(int priorityIn);
    void printFilterType(std::string inputIn);
    void printFilterId(int idIn);
    
    //Deletes
    void deleteItem();
    void deleteByType();
    void deleteByStatus();
    
    void addItem();
};

#endif /* TodoList_hpp */
