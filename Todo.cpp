//
//  Todo.cpp
//  Project2
//
//  Created by Mustafa Soby on 11/5/20.
//

#include "Todo.hpp"

int globalID=0;

//Four constructors using initializer list
Todo::Todo(){
    id=++globalID;
    title="Title";
    description="Description";
    setType("shopping");
    priority=1;
    setStatus("unstarted");
    setCreateDate();
    dueDate.day=0;
    dueDate.month=0;
    dueDate.year=0;
    setLastModified();
}
Todo::Todo(std::string inTitle, std::string inDesc, std::string inType):title(inTitle),description(inDesc){
    //User Defined
    setType(inType);
    
    //Default stuff
    id=globalID++;
    priority=1;
    setStatus("unstarted");
    setCreateDate();
    setLastModified();
};

Todo::Todo(std::string inTitle, std::string inType, int inPriority):title(inTitle),priority(inPriority){
    //User Defined
    setType(inType);
    
    //Default Stuff
    id=globalID++;
    priority=1;
    setStatus("unstarted");
    setCreateDate();
    setLastModified();
};

Todo::Todo(std::string inTitle, int inPriority, int month, int day, int year):title(inTitle),priority(inPriority){
    setDueDate(month,day,year);
    
    //Default Stuff
    id=globalID++;
    priority=1;
    description="Description";
    setType("shopping");
    setStatus("unstarted");
    setCreateDate();
    setLastModified();
};

//Setters for all attributes
void Todo::setId(int inId){
    id=inId;
}
void Todo::setTitle(std::string inTitle){
    title=inTitle;
}
void Todo::setDescription(std::string inDesc){
    description=inDesc;
}

void Todo::setType(std::string inType){
    if(inType=="shopping"){
        type=shopping;
    }
    else if(inType=="house"){
        type=house;
    }else if(inType=="work"){
        type=work;
    }
    else{
        std::cout<<"Not a valid Type"<<std::endl;
        assert(false);
    }
}

void Todo::setPriority(int inPriority){
    assert(inPriority>=1||inPriority<=5);
    priority=inPriority;
}

void Todo::setStatus(std::string inStatus){
    if(inStatus=="unstarted"){
        status=unstarted;
    }
    else if(inStatus=="done"){
        status=done;
    }else if(inStatus=="inProgress"){
        status=inProgress;
    }else if(inStatus=="hold"){
        status=hold;
    }
    else{
        std::cout<<"Not a valid Type"<<std::endl;
        assert(false);
    }
}

void Todo::setCreateDate(){
    time_t tt;
    time( &tt );
    tm TM = *localtime( &tt );
    createDate.month=TM.tm_mon+1;
    createDate.day=TM.tm_mday;
    createDate.year=TM.tm_year+1900;
}

void Todo::setCreateDate2(int month, int day, int year){
    createDate.month=month;
    createDate.day=day;
    createDate.year=year;
}

void Todo::setDueDate(int month, int day, int year){
    dueDate.month=month;
    dueDate.day=day;
    dueDate.year=year;
}
void Todo::setLastModified(){
    time_t tt;
    time( &tt );
    tm TM = *localtime( &tt );
    lastModified.month=TM.tm_mon+1;
    lastModified.day=TM.tm_mday;
    lastModified.year=TM.tm_year+1900;
}

void Todo::setLastModified2(int month, int day, int year){
    lastModified.month=month;
    lastModified.day=day;
    lastModified.year=year;
}

//Getters for all attributes
int Todo::getId(){
    return id;
}
std::string Todo::getTitle(){
    return title;
}
std::string Todo::getDescription(){
    return description;
}
Type Todo::getType(){
    return type;
}
int Todo::getPriority(){
    return priority;
}
Status Todo::getStatus(){
    return status;
}
Date Todo::getCreateDate(){
    return createDate;
}
Date Todo::getDueDate(){
    return dueDate;
}
Date Todo::getLastModified(){
    return lastModified;
}

//Helpers
void Todo::fillMe(){
    std::string temp;
    int month, day, year;
    
    //To clear the previous inputs
    fflush(stdin);
    
    std::cout<<"Title?"<<std::endl;
    getline(std::cin, title);
    
    std::cout<<"Decription?"<<std::endl;
    getline(std::cin, description);
    
    std::cout<<"Type?"<<std::endl;
    std::cin>>temp;
    setType(temp);
    
    std::cout<<"Priority?"<<std::endl;
    std::cin>>priority;
    
    std::cout<<"Status?"<<std::endl;
    std::cin>>temp;
    setStatus(temp);
    
    setCreateDate();
    
    std::cout<<"Due Date?"<<std::endl;
    std::cout<<"Enter month, day, and year separated by a space:"<<std::endl;
    std::cin>>month>>day>>year;
    setDueDate(month, day, year);
    
    setLastModified();
}

std::string Todo::getTypeAsString(){
    if(type==shopping){
        return "shopping";
    }
    else if(type==house){
        return "house";
    }else if(type==work){
        return "work";
    }
    return "";
}

std::string Todo::getStatusAsString(){
    if(status==unstarted){
        return "unstarted";
    }
    else if(status==done){
        return "done";
    }
    else if(status==inProgress){
        return "inProgress";
    }
    else if(status==hold){
        return "hold";
    }
    return "";
}

std::string Todo::getCreateDateAsString(){
    std::string month=std::to_string(createDate.month);
    std::string day=std::to_string(createDate.day);
    std::string year=std::to_string(createDate.year);
    return month+" "+day+" "+year;
}

std::string Todo::getDueDateAsString(){
    std::string month=std::to_string(dueDate.month);
    std::string day=std::to_string(dueDate.day);
    std::string year=std::to_string(dueDate.year);
    return month+" "+day+" "+year;
}

std::string Todo::getLastModifiedAsString(){
    std::string month=std::to_string(lastModified.month);
    std::string day=std::to_string(lastModified.day);
    std::string year=std::to_string(lastModified.year);
    return month+" "+day+" "+year;
}

void Todo::decrementGlobalID(){
    globalID--;
}

//Overloaded Operators
void Todo::operator=(const Todo &right)
{
    setId(right.id);
    setTitle(right.title);
    setDescription(right.description);
    
    if(right.type==shopping){
        setType("shopping");
    }
    else if(right.type==house){
        setType("house");
    }else if(right.type==work){
        setType("work");
    }
    
    setPriority(right.priority);
    
    if(right.status==unstarted){
        setStatus("unstarted");
    }
    else if(right.status==done){
        setStatus("done");
    }
    else if(right.status==inProgress){
        setStatus("inProgress");
    }
    else if(right.status==hold){
        setStatus("hold");
    }
    
    this->createDate.day=right.createDate.day;
    this->createDate.year=right.createDate.year;
    this->createDate.month=right.createDate.month;
    
    setDueDate(right.createDate.month, right.createDate.day, right.createDate.year);
    
    this->dueDate.day=right.dueDate.day;
    this->dueDate.year=right.dueDate.year;
    this->dueDate.month=right.dueDate.month;
}




bool Todo::dueLessThan(Todo &td2){
    if(this->dueDate.year<td2.dueDate.year){
        return true;
    }
    if(this->dueDate.year>td2.dueDate.year){
        return false;
    }
    if(this->dueDate.month<td2.dueDate.month){
        return true;
    }
    if(this->dueDate.month>td2.dueDate.month){
        return false;
    }
    if(this->dueDate.day<td2.dueDate.day){
        return true;
    }
    if(this->dueDate.day>td2.dueDate.day){
        return false;
    }
    return false;
}

bool Todo::createLessThan(Todo &td2){
    if(this->createDate.year<td2.createDate.year){
        return true;
    }
    if(this->createDate.year>td2.createDate.year){
        return false;
    }
    if(this->createDate.month<td2.createDate.month){
        return true;
    }
    if(this->createDate.month>td2.createDate.month){
        return false;
    }
    if(this->createDate.day<td2.createDate.day){
        return true;
    }
    if(this->createDate.day>td2.createDate.day){
        return false;
    }
    return false;
}


std::ostream & operator<<(std::ostream& os, Todo x){
    os<<x.getId()<<","<<x.getTitle()<<","<<x.getDescription()<<","<<x.getTypeAsString()<<","<<x.getPriority()<<","<<x.getStatusAsString()<<","<<x.getCreateDateAsString()<<","<<x.getDueDateAsString()<<","<<x.getLastModifiedAsString();
    return os;
}
