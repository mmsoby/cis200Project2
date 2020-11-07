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
    cout<<"1. Add a task to the List"<<endl;
    cout<<"2. Edit a task from the list"<<endl;
    cout<<"3. Delete"<<endl;
    cout<<"4. Print"<<endl;
    cout<<"5. Sort"<<endl;
    cout<<"6. Merge"<<endl;
    cout<<"7. Clone"<<endl;
    cout<<"8. Make it 2D"<<endl;
    cout<<"9. Make it 3D"<<endl;
    cout<<"10. Input from a .csv"<<endl;
    
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
            
        case 10:
        {
            list1.readFile();
        }
    }
}
