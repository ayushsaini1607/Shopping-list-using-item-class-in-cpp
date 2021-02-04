#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<string.h>
#include<process.h>

#define MAX_ITEMS 40

using namespace std;

class Items{
    char iCode[5];              //4 character item code
    char iName[30];             //item name      
    float iPrice;               //item price
    int qty;           //quantity of that item
    float amt;                  //amt=quantity * price
    static float billValue;     //sum of amount of all items added
    static int count;           //keeps the count of the items added
    void calculateAmount();     //to calculate amt=qty*price for each item
    bool validatePrice();
    bool checkCodeLength();
    bool validateQty();
    public:
      Items()
       {
         strcpy(iCode,"\0");
         strcpy(iName,"\0");
         iPrice=0;
         qty=0;
       }
      static int ret_count()
        {
          return count;      //returns the number of items in the cart now
        }
      static float ret_BillValue()
      {
         return billValue;      //returns the current billValue
      }
      char* ret_iCode()
        {
          return iCode;         //returns the item code so that we can search for item to remove
        }
      void getItem();                //to input the details of item from user
      void displayItems();            //to display the detail of item
      void removeItem();               //to remove an item i.e. reduce the count by 1 and reduce bill value
      ~Items(){}
};

int Items::count;                    //initialsing statements for static variables of class Items
float Items::billValue;

bool Items::checkCodeLength()
{
    int len=strlen(iCode);
    if(len!=4)
      {
          cout<<"\nInvalid ItemCode!\nEnter again: ";
          return false;
      }
    for(int i=0;i<len;i++)
      {
          if(iCode[i]<48 || iCode[i]>57)             //ascii value for digits
            {
                cout<<"\nInvalid Item Code!\nEnter again: ";
                return false;
            }
      }
    return true;
}


bool Items::validatePrice()
{
   return iPrice<0 ? false : true;
}

bool Items::validateQty()
{
  return qty<0 ? false :true;
}

void Items::calculateAmount()
{
    amt = iPrice * qty;
    billValue+=amt;       //add amount to bill value
}

void Items::displayItems()
{
    //cout<<"\n"<<setw(8)<<"ItemCode"<<setw(20)<<"ItemName"<<setw(15)<<"ItemPrice"<<setw(10)<<"Quantity"<<setw(20)<<"Amount";
    cout<<"\n"<<setw(8)<<iCode<<setw(20)<<iName<<setw(15)<<iPrice<<setw(10)<<qty<<setw(20)<<amt;
}

void Items::getItem()
{
    cout<<"Enter Item Code: ";
    fflush(stdin);
    gets(iCode);
    while(!checkCodeLength())
     {
       fflush(stdin);
       gets(iCode);
     }
    cout<<"\nEnter Item Name: ";
    fflush(stdin);
    gets(iName);
    cout<<"\nEnter Item Price : ";
    cin>>iPrice;
    while(!validatePrice())
     {
        cout<<"\nInvalid Price! Enter again : ";
        cin>>iPrice;
     }
    cout<<"\nEnter quantity: ";
    cin>>qty;
    while(!validateQty())
     {
       cout<<"\nInvalid Quantity!";
       cin>>qty;
     }
    count++;                     //item added so increment count
    calculateAmount();           //to calculate amount based on quantity and price and update bill value
}

void Items::removeItem()
{
   //value swap takes place in the main
   count--;                   //reduce count on deletion of item
   billValue-=amt;            //reduce the amount of that item from bill value on deletion of that item
} 

int main()
{
    Items I[MAX_ITEMS];
    int i=0;             //i is the index value for array of Items object
    int j=0;             //j is used to traverse through the object array as and when required
    unsigned int opt;                 //counter for switch case
    while(true)                          //until the user chooses to exit
    {
      cout<<"\n****Main Menu****";
      cout<<"\n1.Enter item";
      cout<<"\n2.Display all items";
      cout<<"\n3.Remove item";
      cout<<"\n4.Display bill";
      cout<<"\n5.Exit";
      cout<<"\n\nEnter your choice : ";
      cin>>opt;
      switch(opt)
        {
            case 1: 
                  if(I[i].ret_count()==MAX_ITEMS)             
                      cout<<"\nLimit of items exceeded";
                  else
                   {
                     I[i].getItem();
                     i++;
                   }
                  break;
            
            case 2:
                if(I[i].ret_count()!=0)
                 {
                  cout<<"\nDisplaying all items...";
                  cout<<"\n"<<setw(8)<<"ItemCode"<<setw(20)<<"ItemName"<<setw(15)<<"ItemPrice"<<setw(10)<<"Quantity"<<setw(20)<<"Amount\n";
                  for(j=0;j<I[i].ret_count();j++)     //from 0 to the no of items in the cart
                     I[j].displayItems(); 
                 }
                 else
                 {
                   cout<<"\nEmpty cart!";
                 }
                 
                  break;
            
            case 3: 
                char ic[5];
                cout<<"\nEnter item code of the item you want to delete : ";
                fflush(stdin);
                gets(ic);
                for(j=0;j<I[i].ret_count();j++)
                  if(strcmp(I[j].ret_iCode(),ic)==0)
                      break;                          //item found at position j
                if(j==I[i].ret_count())               //if j equals the no of items added
                  cout<<"\nItem not found!";
                else
                {
                   I[j].removeItem();                //reduce count and the amount from billValue for the item to be removed
                   for(;j<I[i].ret_count();j++)       //from the position of item to be deleted till the new value of count
                      {
                        I[j]=I[j+1];                    //left shift each item
                      }
                    i--;                          
                }
                break;
            
            case 4:
                  cout<<"\n"<<setw(40)<<"Bill";
                  cout<<"\n"<<setw(8)<<"ItemCode"<<setw(20)<<"ItemName"<<setw(15)<<"ItemPrice"<<setw(10)<<"Quantity"<<setw(20)<<"Amount\n";
                  for(j=0;j<I[i].ret_count();j++)
                    I[j].displayItems();
                  cout<<"\nTotal Items : "<<I[i].ret_count();
                  cout<<"\nTotal Bill Value : "<<I[i].ret_BillValue();
                  break;
            
            case 5:
                 exit(0);

            default:
                 cout<<"\nInvalid choice!";          
        }   
    }
   return 0;
}
