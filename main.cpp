//
//  main.cpp
//  Project2
//
//  Created by Mustafa Soby on 11/4/20.
//

#include <iostream>
#include <stdlib.h>
#include "TodoList.hpp"

using namespace std;

TodoList list1;

int printMenu();
void handleSelection(int option);

int main() {
    int option=1;
    
    cout<<"This Application is used to create Todo Lists. A list has already been created for you, these are the options you have."<<endl<<endl;
    
    while(option!=0){
        option=printMenu();
        handleSelection(option);
    }
    
    return 0;
}

int printMenu(){
    int userInput;
    cout<<"Pick from these options:"<<endl;
    
    cout<<"0. Quit"<<endl;
    cout<<"1. Add"<<endl;
    cout<<"2. Edit"<<endl;
    cout<<"3. Delete"<<endl;
    cout<<"4. Print"<<endl;
    cout<<"5. Sort"<<endl;
    cout<<"6. Merge"<<endl;
    cout<<"7. Input from a .csv"<<endl;
    
    cin>>userInput;
    cout<<endl;
    return userInput;
}

void handleSelection(int option){
    switch(option){
        case 0:
            break;
        case 1:
            list1.addItem();
            break;
        case 2:
            list1.editItem();
            break;
        case 3:
            int deleteChoice;
            cout<<endl;
            cout<<"How do you want to delete?"<<endl;
            cout<<"1. Single item, by ID"<<endl;
            cout<<"2. Multiple Items, by type"<<endl;
            cout<<"3. Multiple Items, by status"<<endl;
            cin>>deleteChoice;
            
            switch(deleteChoice){
                case 1:
                    list1.deleteItem();
                    break;
                case 2:
                    list1.deleteByType();
                    break;
                case 3:
                    list1.deleteByStatus();
                    break;
            }
            
            break;
        case 4:
            int printChoice;
            cout<<endl;
            cout<<"How do you want to Print?"<<endl;
            cout<<"1. To console, one item"<<endl;
            cout<<"2. To console, all items"<<endl;
            cout<<"3. To console, all items, filtered by type"<<endl;
            cout<<"4. To console, all items, filtered by priority"<<endl;
            cout<<"5. To text file, all items"<<endl;
            cin>>printChoice;
            
            switch(printChoice){
                case 1:{
                    int inputID;
                    cout<<"What is the ID?"<<endl;
                    cin>>inputID;
                    list1.printFilterId(inputID);
                    break;
                    
                }
                case 2:{
                    list1.printAll();
                    break;}
                case 3:
                {
                    string inputType="";
                    cout<<"What is the type?"<<endl;
                    cin>>inputType;
                    list1.printFilterType(inputType);
                    break;
                }
                case 4:{
                    int inputPriority;
                    cout<<"What is the priority?"<<endl;
                    cin>>inputPriority;
                    list1.printFilterPriority(inputPriority);
                    break;
                }
                case 5:{
                    list1.printFile();
                    break;
                }
            }
            break;
            
        case 5:
        {
            int sortType;
            cout<<"How do you want to sort?"<<endl;
            cout<<"1. Priority"<<endl;
            cout<<"2. Due Date"<<endl;
            cout<<"3. Create Date"<<endl;
            cin>>sortType;
            
            switch(sortType){
                case 1:{
                    list1.sortPriority();
                }
                    break;
                case 2:{
                    list1.sortDueDate();
                }
                    break;
                case 3:{
                    list1.sortCreateDate();
                }
                    break;
            }
        }
            break;
        case 6:
        {
            //This option uses the copy constructor to copy the contents of list1(The main list used in the program) and put it into list2
            TodoList list2(list1);
            //Then list2 is copied to the end of list1 using the merge function.
            list1.merge(list2);
            //list2.printAll();
        }
            break;
        case 7:
        {
            list1.readFile();
        }
            break;
    }
}
