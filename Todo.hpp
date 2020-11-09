//
//  Todo.hpp
//  Project2
//
//  Created by Mustafa Soby on 11/5/20.
//

#ifndef Todo_hpp
#define Todo_hpp

#include <stdio.h>
#include <string>
#include <cassert>
#include <ctime>
#include <iostream>

//Special Structures/Enums
struct Date{
    int month;
    int day;
    int year;
};
enum Type{shopping, house, work};
enum Status{unstarted, done, inProgress, hold};

class Todo{
private:
    int id;
    std::string title;
    std::string description;
    Type type;
    int priority;
    Status status;
    Date createDate;
    Date dueDate;
    Date lastModified;
    
    
public:
    //Four Constructors
    Todo();
    Todo(std::string inTitle, std::string inDesc, std::string inType);
    Todo(std::string inTitle, std::string inType, int inPriority);
    Todo(std::string inTitle, int inPriority, int month, int day, int year);
    
    //Setters for all attributes
    void setId(int inId);
    void setTitle(std::string inTitle);
    void setDescription(std::string inDesc);
    void setType(std::string inType);
    void setPriority(int inPriority);
    void setStatus(std::string inStatus);
    void setCreateDate();
    void setDueDate(int month, int day, int year);
    void setLastModified();
    
    void setCreateDate2(int month, int day, int year);
    void setLastModified2(int month, int day, int year);
    
    
    
    //Getters for all attributes
    int getId();
    std::string getTitle();
    std::string getDescription();
    Type getType();
    int getPriority();
    Status getStatus();
    Date getCreateDate();
    Date getDueDate();
    Date getLastModified();
    
    //Helpers
    void fillMe();
    std::string getTypeAsString();
    std::string getStatusAsString();
    std::string getCreateDateAsString();
    std::string getDueDateAsString();
    std::string getLastModifiedAsString();
    void decrementGlobalID();
    bool dueLessThan(Todo &td2);
    bool createLessThan(Todo &td2);
    
    
    //Overloaded Operators
    void operator=(const Todo &right);

};

std::ostream & operator<<(std::ostream& os, Todo x);

#endif /* Todo_hpp */
