//
//  TodoList.cpp
//  Project2
//
//  Created by Mustafa Soby on 11/5/20.
//

#include "TodoList.hpp"

//Global Variables
int TodoListId=1;

TodoList::TodoList(){    //Create linked list
    head=new list;
    head->next=nullptr;
}

TodoList::TodoList(const TodoList &orig){
    this->head=new list;
    
    list *ptrOld=orig.head;
    list *ptrNew=this->head;
    list *temp=new list;
    
    while(ptrOld!=nullptr){
        ptrNew->item=ptrOld->item;
        ptrNew->next=new list;
        
        temp=ptrNew;
        ptrOld=ptrOld->next;
        ptrNew=ptrNew->next;
    }
    temp->next=nullptr;
}

void TodoList::addItem(){
    list * tail=head;
    bool tailNotFound=true;
    
    while(tailNotFound){
        if(tail->next!=nullptr){
            tail=tail->next;
        }
        else{
            tailNotFound=false;
        }
    }
    
    tail->next=new list;
    tail->next->next=nullptr;
    tail->item.fillMe();
}


void TodoList::readFile(){
    inFile.open("TodoListSaveFile.csv");
    
    if(!inFile.is_open())
    {
        std::cout<<"COULD NOT OPEN INPUT FILE: \""<<"TodoListSaveFile.csv"<<"\""<<std::endl;
        assert(false);
    }
    
    //Delete First Line because it contains the Attribute names row
    std::string trash;
    getline(inFile, trash, '\n');
    
    std::string idIn;
    std::string titleIn;
    std::string descriptionIn;
    
    std::string typeIn;
    std::string priorityIn;
    std::string statusIn;
    
    std::string createDateIn;
    std::string dueDateIn;
    std::string lastModifiedIn;
    
    
    list * tail=head;
    bool tailNotFound=true;
    
    while(tailNotFound){
        if(tail->next!=nullptr){
            tail=tail->next;
        }
        else{
            tailNotFound=false;
        }
    }
    
    while(!inFile.eof()){
        //Extract input
        std::getline(inFile,idIn,',');
        std::getline(inFile,titleIn,',');
        std::getline(inFile,descriptionIn,',');
        
        std::getline(inFile,typeIn,',');
        std::getline(inFile,priorityIn,',');
        std::getline(inFile,statusIn,',');
        
        std::getline(inFile,createDateIn,',');
        std::getline(inFile,dueDateIn,',');
        std::getline(inFile,lastModifiedIn,'\n');
        
        
        
        tail->item.setId(stoi(idIn));
        tail->item.setTitle(titleIn);
        tail->item.setDescription(descriptionIn);
        
        tail->item.setType(typeIn);
        tail->item.setPriority(stoi(priorityIn));
        tail->item.setStatus(statusIn);
        
        std::istringstream createDateStream(createDateIn);
        std::istringstream dueDateStream(dueDateIn);
        std::istringstream lastModifiedStream(lastModifiedIn);
        
        
        std::string month;
        std::string day;
        std::string year;
        
        //Create Date
        std::getline(createDateStream, month, ' ');
        std::getline(createDateStream, day, ' ');
        std::getline(createDateStream, year, ' ');
        tail->item.setCreateDate2(stoi(month), stoi(day), stoi(year));
        
        //Due Date
        std::getline(dueDateStream, month, ' ');
        std::getline(dueDateStream, day, ' ');
        std::getline(dueDateStream, year, ' ');
        tail->item.setDueDate(stoi(month), stoi(day), stoi(year));
        
        //Last Modified Date
        std::getline(lastModifiedStream, month, ' ');
        std::getline(lastModifiedStream, day, ' ');
        std::getline(lastModifiedStream, year, ' ');
        tail->item.setLastModified2(stoi(month), stoi(day), stoi(year));
        
        
        //Prepare next item
        tail->next=new list;
        tail->next->next=nullptr;
        tail=tail->next;
    }
    
    //Set list end to nullptr
    //tail->next=nullptr;
    
    inFile.close();
}


void TodoList::printFile(){
    outFile.open("TodoListSaveFile.csv");
    
    if(!outFile.is_open())
    {
        std::cout<<"COULD NOT OPEN OUTPUT FILE: \""<<"TodoListSaveFile.csv"<<"\"";
        assert(false);
    }
    
    //Print headers for each column
    outFile<<"ID,Title,Description,Type,Priority,Status,Create Date,Due Date,Last Modified";
    
    list *ptr=head;
    
    while(ptr!=nullptr){
        if(ptr->next!=nullptr){
            outFile<<std::endl;
            outFile<<ptr->item;
        }
        ptr=ptr->next;
    }
    
    outFile.close();
}


void TodoList::printAll(){
    list * ptr=head;
    std::cout<<std::endl;
    while(ptr->next!=nullptr){
        std::cout<<"ID: "<<ptr->item.getId()<<std::endl;
        std::cout<<"Title: "<<ptr->item.getTitle()<<std::endl;
        std::cout<<"Description: "<<ptr->item.getDescription()<<std::endl;
        std::cout<<"Type: "<<ptr->item.getTypeAsString()<<std::endl;
        std::cout<<"Priority: "<<ptr->item.getPriority()<<std::endl;
        std::cout<<"Status: "<<ptr->item.getStatusAsString()<<std::endl;
        std::cout<<"Create Date: "<<ptr->item.getCreateDateAsString()<<std::endl;
        std::cout<<"Due Date: "<<ptr->item.getDueDateAsString()<<std::endl;
        std::cout<<"Last Modified: "<<ptr->item.getLastModifiedAsString()<<std::endl;
        std::cout<<std::endl;
        ptr=ptr->next;
    }
}

void TodoList::printFilterPriority(int priorityIn){
    list * ptr=head;
    std::cout<<std::endl;
    while(ptr->next!=nullptr){
        if(ptr->item.getPriority()==priorityIn){
            std::cout<<"ID: "<<ptr->item.getId()<<std::endl;
            std::cout<<"Title: "<<ptr->item.getTitle()<<std::endl;
            std::cout<<"Description: "<<ptr->item.getDescription()<<std::endl;
            std::cout<<"Type: "<<ptr->item.getTypeAsString()<<std::endl;
            std::cout<<"Priority: "<<ptr->item.getPriority()<<std::endl;
            std::cout<<"Status: "<<ptr->item.getStatusAsString()<<std::endl;
            std::cout<<"Create Date: "<<ptr->item.getCreateDateAsString()<<std::endl;
            std::cout<<"Due Date: "<<ptr->item.getDueDateAsString()<<std::endl;
            std::cout<<"Last Modified: "<<ptr->item.getLastModifiedAsString()<<std::endl;
            std::cout<<std::endl;
        }
        ptr=ptr->next;
    }
}

void TodoList::printFilterType(std::string inputIn){
    list * ptr=head;
    std::cout<<std::endl;
    while(ptr->next!=nullptr){
        if(ptr->item.getTypeAsString()==inputIn){
            std::cout<<"ID: "<<ptr->item.getId()<<std::endl;
            std::cout<<"Title: "<<ptr->item.getTitle()<<std::endl;
            std::cout<<"Description: "<<ptr->item.getDescription()<<std::endl;
            std::cout<<"Type: "<<ptr->item.getTypeAsString()<<std::endl;
            std::cout<<"Priority: "<<ptr->item.getPriority()<<std::endl;
            std::cout<<"Status: "<<ptr->item.getStatusAsString()<<std::endl;
            std::cout<<"Create Date: "<<ptr->item.getCreateDateAsString()<<std::endl;
            std::cout<<"Due Date: "<<ptr->item.getDueDateAsString()<<std::endl;
            std::cout<<"Last Modified: "<<ptr->item.getLastModifiedAsString()<<std::endl;
            std::cout<<std::endl;
        }
        ptr=ptr->next;
    }
}

void TodoList::printFilterId(int idIn){
    list * ptr=head;
    std::cout<<std::endl;
    while(ptr->next!=nullptr){
        if(ptr->item.getId()==idIn){
            std::cout<<"ID: "<<ptr->item.getId()<<std::endl;
            std::cout<<"Title: "<<ptr->item.getTitle()<<std::endl;
            std::cout<<"Description: "<<ptr->item.getDescription()<<std::endl;
            std::cout<<"Type: "<<ptr->item.getTypeAsString()<<std::endl;
            std::cout<<"Priority: "<<ptr->item.getPriority()<<std::endl;
            std::cout<<"Status: "<<ptr->item.getStatusAsString()<<std::endl;
            std::cout<<"Create Date: "<<ptr->item.getCreateDateAsString()<<std::endl;
            std::cout<<"Due Date: "<<ptr->item.getDueDateAsString()<<std::endl;
            std::cout<<"Last Modified: "<<ptr->item.getLastModifiedAsString()<<std::endl;
            std::cout<<std::endl;
            break;
        }
        ptr=ptr->next;
    }
}


//Deletes
void TodoList::deleteItem(){
    int idIn;
    std::cout<<"Which item do you want to delete?(Enter its Id)"<<std::endl;
    std::cin>>idIn;
    
    list * ptr=head;
    list *prev=head;
    std::cout<<std::endl;
    
    //In case this is the only item in the list
    if(ptr->item.getId()==idIn){
        if(ptr->next!=nullptr){
            list * oldHead=head;
            head=head->next;
            delete oldHead;
        }
        
        Todo x;
        ptr->item=x;
        ptr->next=nullptr;
    }
    
    while(ptr->next!=nullptr){
        if(ptr->item.getId()==idIn){
            prev->next=ptr->next;
            delete ptr;
            break;
        }
        prev=ptr;
        ptr=ptr->next;
    }

}

void TodoList::deleteByType(){
    std::string typeIn;
    std::cout<<"Which type of item do you want to delete?"<<std::endl;
    std::cin>>typeIn;
    
    list * ptr=head;
    list *prev=head;
    std::cout<<std::endl;
    
    //In case this is the only item in the list
    if(ptr->item.getTypeAsString()==typeIn){
        if(ptr->next!=nullptr){
            list * oldHead=head;
            head=head->next;
            delete oldHead;
        }
        
        Todo x;
        ptr->item=x;
        ptr->next=nullptr;
    }
    
    while(ptr!=nullptr){
        if(ptr->item.getTypeAsString()==typeIn){
            prev->next=ptr->next;
            delete ptr;
            ptr=prev;
        }
        prev=ptr;
        ptr=ptr->next;
    }
}

void TodoList::deleteByStatus(){
    
}

