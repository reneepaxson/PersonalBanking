/*
 Renee Paxson
 9 May 2021
 CIS 1111 FINAL PROJECT
 This program loads user's bank information, deposits and withdraws money to a checking account,
 transfers money between checking and savings account, shows user data,
 and allows a password protected admin account to view all user data
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
#define SIZE 3 //defines standard size for all arrays

double amt = 0.0, checkBal = 0.0, savBal = 0.0; //starts account details at $0
double acctNum = (rand() % 1000000)+1;
int userSelect, success, menu;
string username, password;
string userArray[SIZE] ={"renpax","jglover","new"};//user base
double acctArray [SIZE][SIZE]={{acctNum, 0.0, 0.0},//account information, updates as program runs
                                {acctNum+1, 0.0, 0.0},
                                {acctNum+2, 0.0,0.0}};

//begin various necessary void functions
//main starts at 221
void deposit()//option 1: deposit money
{
    cout <<"How much are you depositing?: $";
    cin >> amt;
    while (amt <0)//validate the input and loop until positive
    {
        cout << "That is an invalid amount!\n";
        cout << "How much are you depositing?: $";
        cin >>amt;
    }
    checkBal+=amt; //add deposit amount to checking balance
    acctArray[userSelect-1][1]={checkBal};//update checking balance to account array
    cout << "$" << setprecision(2)<<fixed<<amt <<" has been deposited into your checking account.\n";
    cout << "Your checking account balance is: $" << setprecision(2)<<fixed<<acctArray[userSelect-1][1] << endl<< endl;
}

void withdraw()//option 2: withdraw money
{
    cout <<"How much do you wish to withdraw from your checking account?: $";
    cin >> amt;
    while (amt<0||amt>checkBal) //validate the input
    {
        if (amt <0)
        {
            cout << "That is an invalid amount!\n";
        }
        else if (amt >checkBal)
        {
            cout << "Insufficient funds!\n";
        }
        cout <<"How much do you wish to withdraw?: $";
        cin >> amt;
    } //loop until the input is within range
        
    checkBal-=amt;//subtract withdraw amount from checking
    acctArray[userSelect-1][1]={checkBal}; //update checking balance
    cout << "$" << setprecision(2)<<fixed<<amt << " has been withdrawn from your checking account.\n";
    cout << "Your checking account balance is: $" << setprecision(2)<< fixed<<acctArray[userSelect-1][1] << endl <<endl;
}
    
void transfer() //option 3: transfer money
{
    do//validate menu input
    {
        cout << "User chose transfer between accounts.\n";
        cout << "Please choose between the following actions:\n";
        cout << "\t1. Transfer from checking to savings\n";
        cout << "\t2. Transfer from savings to checking\n";
        cout << "Enter your choice: ";
        cin >> menu;
        if (menu == 1)//menu option 1
        {
            cout << "User chose to transfer from checking to savings.\n";
            cout << "How much do you want to transfer?: $";
            cin >> amt;
            while (amt > checkBal || amt <0) //validate the amt input
            {
                if (amt >checkBal)//verify amt is not more than available checking balance
                {
                    cout << "\nInsufficient funds for this transfer!\n";
                    cout << "You currently have $" <<setprecision(2)<<fixed<<acctArray[userSelect-1][1];
                    cout<< " available in your checking account.\n";
                }
                else if (amt <0)//verify amt is not neative
                {
                    cout << "That is an invalid amount!\n";
                }
                cout << "Please enter a valid transfer amount: $";
                cin >> amt;//prompts user to enter a valid number and loops again
            }
            
            checkBal -=amt;//subtract transfer amount from checking
            savBal += amt;//add transfer amount to savings
            acctArray[userSelect-1][1]={checkBal};//update checking balance
            acctArray[userSelect-1][2]={savBal};//update savings balance
            cout << "\n$" << setprecision(2)<<fixed<<amt << " has been transferred from your checking account";
            cout <<" to your savings account.\n";
            cout << "Your checking account balance is: $";
            cout << setprecision(2)<<fixed<< acctArray[userSelect-1][1]<< endl;
            cout << "Your savings account balance is: $";
            cout << setprecision(2)<<fixed<<acctArray[userSelect-1][2]<<endl << endl;
            break;//end loop
        }
        else if (menu == 2)//menu option 2
        {
            cout << "How much do you want to transfer from your savings account?: $";
            cin >> amt;
            while (amt > savBal||amt <0)//validate the amt input
            {
                if (amt >savBal)//verify amt is not more than available savings balane
                {
                    cout << "\nInsufficient funds for this transfer!\n";
                    cout << "You currently have $" << setprecision(2)<<fixed<<acctArray[userSelect-1][2];
                    cout<< " available in your savings account.\n";
                }
                else if (amt<0)//verify amt is not negative
                {
                    cout << "That is an invalid amount!\n";
                }
                cout << "Please enter a valid transfer amount: $";
                cin >>amt;//prompts user to enter a valid number and loops again
            }
            
            savBal -= amt;//subtract transfer amount from savings
            checkBal += amt;// add transfer amount to checking
            acctArray[userSelect-1][1]={checkBal};//update checking balance
            acctArray[userSelect-1][2]={savBal};//update savings balance
            cout << "\n$" << setprecision(2)<< fixed<< amt;
            cout << " has been transferred from your savings account to your checking account.\n";
            cout << "Your checking account balance is: $" <<setprecision(2)<<fixed<<acctArray[userSelect-1][1]<< endl;
            cout << "Your savings account balance is: $";
            cout << setprecision(2)<<fixed<<acctArray[userSelect-1][2] << endl << endl;
            break; //end loop
        }
        else if (menu!=1 || menu!=2)//catchall for invalid menu input
        {
            cout << "Invalid choice!\n\n";
        }
    }while(menu!=1 || menu!=2);//loops until menu input is valid
}

void admin()//admin menu
{
    do //begins admin menu loop
    {
        cout << "Please choose an admin action from the following menu:\n";
        cout << "\t1. View all user data\n";
        cout << "\t2. Log out and switch user\n";
        cout << "Enter your choice: ";
        cin >>menu;
        switch (menu)
        {
            case 1: //option 1: displays all user data
                cout << "All user data:\n\n";
                cout.width(15); cout << left << "Username";
                cout.width(10); cout << left << "Account #";
                cout.width(17); cout << right << "Checking";
                cout.width(14); cout << right << "Savings"<<endl;
                cout.width(15); cout << left << " ";
                cout.width(10); cout << left << " ";
                cout.width(16); cout << right << "Account";
                cout.width(15); cout << right << "Account" << endl;
                cout << "------------------------------------------------------------\n";
                for (int i=0;i<SIZE;i++)//loops until all user data has been displayed
                {
                    cout.width(15); cout << left <<userArray[i];
                    cout.width(10); cout << left <<setprecision(0)<<fixed<< acctArray[i][0];
                    cout.width(10); cout << right <<setprecision(2)<<fixed<< "$" << acctArray[i][1];
                    cout.width(10); cout << right <<setprecision(2)<<fixed<< "$" << acctArray[i][2] <<endl;
                }
                cout << "------------------------------------------------------------\n";
                break;
            case 2://option 2: returns to user login
                cout <<"\nLogging out...\n\n";
                break;
            default: //catchall for invalid menu input
                cout << "Invalid choice\n";
        }
    }while (menu !=2);//loops until user chooses option 2
}

void acctDetails() //option 4
{
    //sets up account data chart for individual users
    cout <<setw(15) << left << "Username";
    cout <<setw(10) << left << "Account #";
    cout <<setw(17)<< right << "Checking";
    cout <<setw(14)<< right << "Savings"<<endl;
    cout <<setw(15) << left << " ";
    cout <<setw(10) << left << " ";
    cout <<setw(16)<< right << "Account";
    cout <<setw(15)<< right << "Account" << endl;
    cout << "------------------------------------------------------------\n";
    cout<< setw(15)<< left <<userArray[userSelect-1];
    cout <<setw(10)<< left <<setprecision(0)<<fixed<< acctArray[userSelect-1][0];
    cout <<setw(10)<< right <<setprecision(2)<<fixed<< "$" << acctArray[userSelect-1][1];
    cout<<setw(10) << right <<setprecision(2)<<fixed<< "$" << acctArray[userSelect-1][2] <<endl;
    cout << "------------------------------------------------------------\n";
}
    
void loadUserData()//pulls selected user's account number, checking balance, and savings balance from the array
{                   //and sets it to the account varialbes for calculations
    acctNum = acctArray[userSelect-1][0];
    checkBal = acctArray[userSelect-1][1];
    savBal = acctArray[userSelect-1][2];
}
//end void functions


int main()//start of main!
{
    cout <<"Welcome to RPaX Credit Union!\n";
    do //loops login menu until user chooses to exit
    {
        cout << "Please select a user from our user base: \n";
        cout << "\t1. renpax\n\t2. jglover\n\t3. New User\n\t4. Admin\n\t5. Exit\n";
        cout <<"Select user: ";
        cin >> userSelect;
        
        if (userSelect == 1||userSelect ==2||userSelect==3)//standard user menu
        {
            if (userSelect == 1)//user 1: renpax
            {
                cout << "Welcome back renpax!\n";
                cout << "Loading user data....\n\n";
                loadUserData();//loads data for calculations
                
            }
            else if (userSelect == 2)//user 2: jglover
            {
                cout << "Welcome back jglover!\n";
                cout << "Loading user data....\n\n";
                loadUserData();//loads data for calculations
                
            }
            else if (userSelect == 3)//user 3: new user
            {
                cout << "Welcome new user!\nPlease enter username: ";
                cin >> username;
                cout << "Setting up new account for "<<username<<"...\n\n";
                userArray[2] = {username};//updates userArray with the new username
                loadUserData();//loads data for calculations
                
            }
            do//loops standard menu until user chooses to log out
            {
                cout << "Please chose an action from the following menu:\n";
                cout << "\t1. Deposit money\n";
                cout << "\t2. Withdraw money\n";
                cout << "\t3. Transfer money\n";
                cout << "\t4. Display account details\n";
                cout << "\t5. Log out and switch user\n";
                cout << "Enter your choice: ";
                cin >> menu;
                cout << endl;
                switch (menu)
                {
                    case 1://option 1: deposit money
                        deposit();
                        break;
                    case 2: //option 2: withdraw money
                        withdraw();
                        break;
                    case 3: //option 3: transfer money
                        transfer();
                        break;
                    case 4: //option 4: display account details
                        acctDetails();
                        break;
                    case 5://option 5: log out and switch user
                        cout << "Logging out...\n\n";
                        break;
                    default://catchall for invalid menu input
                        cout << "Invalid choice\n";
                        break;
                }
            }while (menu != 5);//ends menu loop and logs out
        }
        
        else if (userSelect == 4)//user 4: admin
        {
            cout << "Selected Admin" <<endl;
            do //begins password loop
            {
                cout << "Please enter password to gain access: ";
                cin>>password;
                if (password =="getaccess")
                {
                    cout << "Welcome Admin!\n\n";
                    success = 0;//allows loop to end
                    admin();//then loads admin menu
                    break;
                }
                else if (password !="getaccess")
                {
                    cout << "Incorrect password!\n";
                    success = 1;
                }
            }while (success==1);//loops until password is correct
        }
        else if (userSelect==5)//option 5: quit
        {
            cout << "Quitting program.\n";
            return 0;//quits program
        }
        else//any other option catchall
        {
            cout <<"User does not exist!\n\n";
            cout << "Please select from list of existing users or create a new profile.\n";
        }
    }while (userSelect!=5); //loops until user quits with option 5
}

