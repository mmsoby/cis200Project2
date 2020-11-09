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
    list * prev=head;
    list * ptr=prev->next;
    
    while(true){
        if(ptr==nullptr){
            break;
        }
        prev=ptr;
        ptr=ptr->next;
    }
    
    if(prev==head && isEmpty(head)){
        head->item.fillMe();
    }
    else{
        prev->next=new list;
        prev->next->next=nullptr;
        prev->next->item.fillMe();
    }
}

bool TodoList::isEmpty(list * x){
    return x->item.getTitle()=="Title" && x->item.getDescription()=="Description" ;
}

void TodoList::editItem(){
    int idIn;
    std::cout<<"Which item do you want to edit?(Enter the ID)"<<std::endl;
    std::cin>>idIn;
    
    list * ptr=head;
    std::cout<<std::endl;
    while(ptr!=nullptr){
        if(ptr->item.getId()==idIn){
            break;
        }
        ptr=ptr->next;
    }
    
    //Ask what to change and do it
    std::string attributeToEdit, temp;
    int tempInt;
    std::cout<<"Which attribute do you want to edit?"<<std::endl;
    std::cin.ignore();
    getline(std::cin, attributeToEdit);
    
    if(attributeToEdit=="Title"){
        std::cout<<"Enter the Title you want it to become:"<<std::endl;
        getline(std::cin, temp);
        ptr->item.setTitle(temp);
    }else if(attributeToEdit=="Description"){
        std::cout<<"Enter the Description you want it to become:"<<std::endl;
        getline(std::cin, temp);
        ptr->item.setDescription(temp);
    }else if(attributeToEdit=="Priority"){
        std::cout<<"Enter the Priority you want it to become:"<<std::endl;
        std::cin>>tempInt;
        ptr->item.setPriority(tempInt);
    }else if(attributeToEdit=="Status"){
        std::cout<<"Enter the Status you want it to become:"<<std::endl;
        getline(std::cin, temp);
        ptr->item.setStatus(temp);
    }else if(attributeToEdit=="Due Date"){
        std::cout<<"Enter the Due Date you want it to become:(Separated by spaces)"<<std::endl;
        int month,day,year;
        std::cin>>month>>day>>year;
        ptr->item.setDueDate(month, day, year);
    }
    else{
        std::cout<<"Invalid attribute"<<std::endl;
    }
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
    
    
    list * prev=head;
    list * ptr=prev->next;
    
    while(true){
        if(ptr==nullptr){
            break;
        }
        prev=ptr;
        ptr=ptr->next;
    }
    
    list *tail=prev;
    
    if(prev==head && isEmpty(head)){
        tail=head;
    }
    else{
        prev->next=new list;
        prev->next->next=nullptr;
        tail=prev->next;
    }
    list * last=tail;
    
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
        last=tail;
        tail=tail->next;
        
    }
    
    //Set list end to nullptr
    last->next=nullptr;
    
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
        if(ptr!=nullptr){
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
    while(ptr!=nullptr){
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
    while(ptr!=nullptr){
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
    while(ptr!=nullptr){
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
    std::cout<<std::endl;
    
    list * ptr=head;
    list *prev=head;
    
    while(ptr!=nullptr){
        if(ptr->item.getId()==idIn){
            if(ptr==head){
                head=head->next;
                break;
            }
            prev->next=ptr->next;
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
    std::cout<<std::endl;
    
    list *ptr=head;
    list *prev=ptr;
    
    while(ptr!=nullptr){
        if(ptr->item.getTypeAsString()==typeIn){
            if(ptr==head){
                head=head->next;
                //delete ptr;
                ptr=head;
                continue;
            }
            else{
                prev->next=ptr->next;
                //delete ptr;
                ptr=prev;
            }
        }
        prev=ptr;
        ptr=ptr->next;
    }
    prev->next=nullptr;
    
}

void TodoList::deleteByStatus(){
    std::string statusIn;
    std::cout<<"Which status of item do you want to delete?"<<std::endl;
    std::cin>>statusIn;
    std::cout<<std::endl;
    
    list *ptr=head;
    list *prev=ptr;
    
    while(ptr!=nullptr){
        if(ptr->item.getStatusAsString()==statusIn){
            if(ptr==head){
                head=head->next;
                //delete ptr;
                ptr=head;
                continue;
            }
            else{
                prev->next=ptr->next;
                //delete ptr;
                ptr=prev;
            }
        }
        prev=ptr;
        ptr=ptr->next;
    }
    prev->next=nullptr;
    
}
//Sorts
void TodoList::sortPriority(){
    list *outer=head;
    list *inner=nullptr;
    list *minIndex=nullptr;
    
    while(outer!=nullptr){
        minIndex=outer;
        inner=outer->next;
        while(inner!=nullptr){
            if(inner->item.getPriority()<minIndex->item.getPriority()){
                minIndex=inner;
            }
            inner=inner->next;
        }
        Todo temp=outer->item;
        outer->item=minIndex->item;
        minIndex->item=temp;
        
        outer=outer->next;
    }
}

void TodoList::sortDueDate(){
    list *outer=head;
    list *inner=nullptr;
    list *minIndex=nullptr;
    
    while(outer!=nullptr){
        minIndex=outer;
        inner=outer->next;
        while(inner!=nullptr){
            if(inner->item.dueLessThan(minIndex->item)){
                minIndex=inner;
            }
            inner=inner->next;
        }
        Todo temp=outer->item;
        outer->item=minIndex->item;
        minIndex->item=temp;
        
        outer=outer->next;
    }
}

void TodoList::sortCreateDate(){
    list *outer=head;
    list *inner=nullptr;
    list *minIndex=nullptr;
    
    while(outer!=nullptr){
        minIndex=outer;
        inner=outer->next;
        while(inner!=nullptr){
            if(inner->item.createLessThan(minIndex->item)){
                minIndex=inner;
            }
            inner=inner->next;
        }
        Todo temp=outer->item;
        outer->item=minIndex->item;
        minIndex->item=temp;
        
        outer=outer->next;
    }
}


void TodoList::merge(TodoList &iGoAtTheEnd){
    list * prev=head;
    list * ptr=prev->next;
    
    while(true){
        if(ptr==nullptr){
            break;
        }
        prev=ptr;
        ptr=ptr->next;
    }
    
    list *tail=prev;
    
    if(prev==head && isEmpty(head)){
        tail=head;
    }
    else{
        prev->next=new list;
        prev->next->next=nullptr;
        tail=prev->next;
    }
    list * last=tail;
    
    list *ptrNew=iGoAtTheEnd.head;
    while(ptrNew!=nullptr){
        tail->item=ptrNew->item;
        tail->next=new list;
        last=tail;
        tail=tail->next;
        tail->next=nullptr;
        ptrNew=ptrNew->next;
    }
    
    last->next=nullptr;
    
    list *traverse=head;
    int i=0;
    while(traverse!=nullptr){
        traverse->item.setId(++i);
        traverse=traverse->next;
    }
}
