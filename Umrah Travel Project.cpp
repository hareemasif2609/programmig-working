#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<iomanip>
#include<ctime>
#include<sstream>
#include<cctype>

using namespace std;

int main(){
    // Console setup
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Package storage
    string packageNames[50];
    int packageDays[50];
    double packageAmounts[50];
    string packageTypes[50];
    string packageIncludes[50];
    int packageCount = 0;
    
    // Booking storage
    string bookingIds[200];
    string bookingUserIds[200];
    string bookingUserNames[200];
    string bookingPackageNames[200];
    string bookingDates[200];
    string bookingPaymentStatus[200];
    string bookingBankNames[200];
    string bookingAccountNumbers[200];
    bool bookingCancelled[200];
    int bookingCount = 0;
    
    // User storage
    string userUsernames[100];
    string userPasswords[100];
    string userFullNames[100];
    string userPhones[100];
    string userEmails[100];
    string userCnic[100];
    int userCount = 0;
    
    // Admin accounts
    string adminUsernames[3] = {"admin", "manager", "staff"};
    string adminPasswords[3] = {"admin123", "manager@456", "staff#789"};
    string adminDisplayNames[3] = {"Super Admin", "Tour Manager", "Staff Member"};
    
    // Login session
    string loggedInUser = "";
    string loggedInName = "";
    bool isAdminLoggedIn = false;
    bool isUserLoggedIn = false;
    
    // Load data from files
    ifstream packageFile("packages.txt");
    if(packageFile.is_open()){
        packageFile >> packageCount;
        packageFile.ignore();
        for(int i = 0; i < packageCount; i++){
            getline(packageFile, packageNames[i]);
            packageFile >> packageDays[i];
            packageFile >> packageAmounts[i];
            packageFile.ignore();
            getline(packageFile, packageTypes[i]);
            getline(packageFile, packageIncludes[i]);
        }
        packageFile.close();
    }
    
    ifstream bookingFile("bookings.txt");
    if(bookingFile.is_open()){
        bookingFile >> bookingCount;
        bookingFile.ignore();
        for(int i = 0; i < bookingCount; i++){
            getline(bookingFile, bookingIds[i]);
            getline(bookingFile, bookingUserIds[i]);
            getline(bookingFile, bookingUserNames[i]);
            getline(bookingFile, bookingPackageNames[i]);
            getline(bookingFile, bookingDates[i]);
            getline(bookingFile, bookingPaymentStatus[i]);
            getline(bookingFile, bookingBankNames[i]);
            getline(bookingFile, bookingAccountNumbers[i]);
            bookingFile >> bookingCancelled[i];
            bookingFile.ignore();
        }
        bookingFile.close();
    }
    
    ifstream userFile("users.txt");
    if(userFile.is_open()){
        userFile >> userCount;
        userFile.ignore();
        for(int i = 0; i < userCount; i++){
            getline(userFile, userUsernames[i]);
            getline(userFile, userPasswords[i]);
            getline(userFile, userFullNames[i]);
            getline(userFile, userPhones[i]);
            getline(userFile, userEmails[i]);
            getline(userFile, userCnic[i]);
        }
        userFile.close();
    }
    
    // Initialize default packages if none exist
    if(packageCount == 0){
        packageNames[0] = "Silver Package";
        packageDays[0] = 14;
        packageAmounts[0] = 150000;
        packageTypes[0] = "Economy";
        packageIncludes[0] = "Flight + Hotel (3-Star) + Transport";
        
        packageNames[1] = "Gold Package";
        packageDays[1] = 21;
        packageAmounts[1] = 250000;
        packageTypes[1] = "Standard";
        packageIncludes[1] = "Flight + Hotel (4-Star) + Transport + Ziyarat";
        
        packageNames[2] = "Diamond Package";
        packageDays[2] = 30;
        packageAmounts[2] = 400000;
        packageTypes[2] = "Premium";
        packageIncludes[2] = "Flight + Hotel (5-Star) + Transport + Ziyarat + Meals";
        
        packageCount = 3;
        
        ofstream savePackage("packages.txt");
        savePackage << packageCount << "\n";
        for(int i = 0; i < packageCount; i++){
            savePackage << packageNames[i] << "\n";
            savePackage << packageDays[i] << "\n";
            savePackage << packageAmounts[i] << "\n";
            savePackage << packageTypes[i] << "\n";
            savePackage << packageIncludes[i] << "\n";
        }
        savePackage.close();
    }
    
    int mainChoice;
    
    do {
        // Clear screen and display header
        system("cls");
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n  ";
        for(int i=0;i<78;i++) cout << char(205);
        cout << "\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "  " << char(186) << "                                                                              " << char(186) << "\n";
        SetConsoleTextAttribute(hConsole, 14);
        cout << "  " << char(186);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "              ** UMRAH PACKAGE BOOKING MANAGEMENT SYSTEM **                  ";
        SetConsoleTextAttribute(hConsole, 14);
        cout << char(186) << "\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "  " << char(186) << "                     AL-HARAMAIN TOURS & TRAVELS                              " << char(186) << "\n";
        cout << "  " << char(186) << "                                                                              " << char(186) << "\n";
        SetConsoleTextAttribute(hConsole, 14);
        cout << "  ";
        for(int i=0;i<78;i++) cout << char(205);
        cout << "\n";
        SetConsoleTextAttribute(hConsole, 7);
        
        cout << "\n\n";
        cout << "          " << char(201);
        for(int i=0;i<42;i++) cout << char(205);
        cout << char(187) << "\n";
        cout << "          " << char(186) << "           MAIN MENU                        " << char(186) << "\n";
        cout << "          " << char(204);
        for(int i=0;i<42;i++) cout << char(205);
        cout << char(185) << "\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "          " << char(186) << "   [1]  Admin Login                        " << char(186) << "\n";
        cout << "          " << char(186) << "   [2]  User Login                         " << char(186) << "\n";
        cout << "          " << char(186) << "   [3]  New User Registration              " << char(186) << "\n";
        SetConsoleTextAttribute(hConsole, 12);
        cout << "          " << char(186) << "   [0]  Exit System                        " << char(186) << "\n";
        SetConsoleTextAttribute(hConsole, 14);
        cout << "          " << char(200);
        for(int i=0;i<42;i++) cout << char(205);
        cout << char(188) << "\n\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "          Enter Your Choice : ";
        SetConsoleTextAttribute(hConsole, 7);
        cin >> mainChoice;
        
        if(mainChoice == 1){
            // Admin Login
            system("cls");
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\n  " << char(201);
            for(int i=0;i<55;i++) cout << char(205);
            cout << char(187) << "\n";
            cout << "  " << char(186) << "              ADMIN LOGIN PORTAL                         " << char(186) << "\n";
            cout << "  " << char(204);
            for(int i=0;i<55;i++) cout << char(205);
            cout << char(185) << "\n";
            SetConsoleTextAttribute(hConsole, 13);
            cout << "  " << char(186) << "   Predefined Admins: admin | manager | staff           " << char(186) << "\n";
            SetConsoleTextAttribute(hConsole, 14);
            cout << "  " << char(200);
            for(int i=0;i<55;i++) cout << char(205);
            cout << char(188) << "\n\n";
            
            string uname, pass;
            SetConsoleTextAttribute(hConsole, 11);
            cout << "  Enter Admin Username : ";
            SetConsoleTextAttribute(hConsole, 7);
            cin >> uname;
            SetConsoleTextAttribute(hConsole, 11);
            cout << "  Enter Admin Password : ";
            SetConsoleTextAttribute(hConsole, 7);
            pass = "";
            char ch;
            while((ch = getch()) != 13){
                if(ch == 8){
                    if(!pass.empty()){
                        pass.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    pass += ch;
                    cout << "*";
                }
            }
            cout << "\n";
            
            bool adminFound = false;
            for(int i = 0; i < 3; i++){
                if(adminUsernames[i] == uname && adminPasswords[i] == pass){
                    adminFound = true;
                    isAdminLoggedIn = true;
                    loggedInName = adminDisplayNames[i];
                    break;
                }
            }
            
            if(adminFound){
                SetConsoleTextAttribute(hConsole, 10);
                cout << "\n  Login Successful! Welcome, " << loggedInName << "\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n  Press any key to continue...";
                getch();
                
                // Admin Menu
                int adminChoice;
                do {
                    system("cls");
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "\n  " << char(201);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(187) << "\n";
                    cout << "  " << char(186) << "               ADMIN CONTROL PANEL                  " << char(186) << "\n";
                    cout << "  " << char(204);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(185) << "\n";
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  " << char(186) << "   [1]  Add Package                              " << char(186) << "\n";
                    cout << "  " << char(186) << "   [2]  View All Packages                        " << char(186) << "\n";
                    cout << "  " << char(186) << "   [3]  Packages Summary Report                  " << char(186) << "\n";
                    cout << "  " << char(186) << "   [4]  Update Package                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [5]  Delete Package                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [6]  Search Package                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [7]  View Bookings                            " << char(186) << "\n";
                    cout << "  " << char(186) << "   [8]  Cancel Booking                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [9]  Customer List                            " << char(186) << "\n";
                    cout << "  " << char(186) << "   [10] Customer Details                         " << char(186) << "\n";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "  " << char(186) << "   [0]  Logout                                   " << char(186) << "\n";
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "  " << char(200);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(188) << "\n";
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "\n  Enter Your Choice : ";
                    SetConsoleTextAttribute(hConsole, 7);
                    cin >> adminChoice;
                    
                    if(adminChoice == 1){
                        // Add Package
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "              ADD NEW UMRAH PACKAGE                         " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n";
                        SetConsoleTextAttribute(hConsole, 7);
                        
                        if(packageCount >= 50){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  Package storage full!\n";
                            SetConsoleTextAttribute(hConsole, 7);
                        } else {
                            string pname, ptype, pincludes;
                            int pdays;
                            double pamount;
                            
                            cin.ignore();
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  Enter Package Name     : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            getline(cin, pname);
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Number of Days   : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin >> pdays;
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Package Amount   : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin >> pamount;
                            
                            cin.ignore();
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Package Type     : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            getline(cin, ptype);
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Inclusions       : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            getline(cin, pincludes);
                            
                            packageNames[packageCount] = pname;
                            packageDays[packageCount] = pdays;
                            packageAmounts[packageCount] = pamount;
                            packageTypes[packageCount] = ptype;
                            packageIncludes[packageCount] = pincludes;
                            packageCount++;
                            
                            // Save to file
                            ofstream savePackage("packages.txt");
                            savePackage << packageCount << "\n";
                            for(int i = 0; i < packageCount; i++){
                                savePackage << packageNames[i] << "\n";
                                savePackage << packageDays[i] << "\n";
                                savePackage << packageAmounts[i] << "\n";
                                savePackage << packageTypes[i] << "\n";
                                savePackage << packageIncludes[i] << "\n";
                            }
                            savePackage.close();
                            
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << "\n  Package Added Successfully!\n";
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 2){
                        // View Packages
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<76;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                        ALL AVAILABLE UMRAH PACKAGES                            " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<76;i++) cout << char(205);
                        cout << char(188) << "\n";
                        
                        if(packageCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No packages available.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  " << left << setw(5) << "No." << setw(22) << "Package Name" << setw(8) << "Days" << setw(16) << "Amount (PKR)" << setw(15) << "Type" << "Inclusions\n";
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  ";
                            for(int i=0;i<76;i++) cout << char(196);
                            cout << "\n";
                            SetConsoleTextAttribute(hConsole, 7);
                            
                            for(int i = 0; i < packageCount; i++){
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  " << left << setw(5) << (i+1);
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << setw(22) << packageNames[i];
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << setw(8) << packageDays[i];
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << setw(16) << packageAmounts[i];
                                SetConsoleTextAttribute(hConsole, 13);
                                cout << setw(15) << packageTypes[i];
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << packageIncludes[i] << "\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 3){
                        // Packages Summary Report
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                 PACKAGES SUMMARY REPORT                    " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "  Total Packages Available : " << packageCount << "\n\n";
                        
                        double totalRevenue = 0;
                        for(int i = 0; i < bookingCount; i++){
                            if(!bookingCancelled[i] && bookingPaymentStatus[i] == "Paid"){
                                for(int j = 0; j < packageCount; j++){
                                    if(packageNames[j] == bookingPackageNames[i]){
                                        totalRevenue += packageAmounts[j];
                                        break;
                                    }
                                }
                            }
                        }
                        
                        SetConsoleTextAttribute(hConsole, 10);
                        cout << "  Total Revenue Collected  : PKR " << fixed << setprecision(2) << totalRevenue << "\n\n";
                        
                        for(int i = 0; i < packageCount; i++){
                            int bookingsCnt = 0;
                            for(int j = 0; j < bookingCount; j++){
                                if(bookingPackageNames[j] == packageNames[i] && !bookingCancelled[j])
                                    bookingsCnt++;
                            }
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  " << char(254) << " ";
                            SetConsoleTextAttribute(hConsole, 15);
                            cout << left << setw(25) << packageNames[i];
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "Bookings: " << bookingsCnt;
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << "   Revenue: PKR " << (bookingsCnt * packageAmounts[i]) << "\n";
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 4){
                        // Update Package
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               UPDATE UMRAH PACKAGE                         " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(packageCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No packages available to update.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Available Packages:\n";
                            for(int i = 0; i < packageCount; i++){
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  [" << (i+1) << "] ";
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << packageNames[i] << "\n";
                            }
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  Enter Package Name to Update : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin.ignore();
                            string searchName;
                            getline(cin, searchName);
                            
                            int idx = -1;
                            for(int i = 0; i < packageCount; i++){
                                if(packageNames[i] == searchName){
                                    idx = i;
                                    break;
                                }
                            }
                            
                            if(idx == -1){
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  Package not found!\n";
                            } else {
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "\n  Current Details:\n";
                                cout << "  Name    : " << packageNames[idx] << "\n";
                                cout << "  Days    : " << packageDays[idx] << "\n";
                                cout << "  Amount  : PKR " << packageAmounts[idx] << "\n\n";
                                
                                string newName;
                                int newDays;
                                double newAmount;
                                
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Enter New Package Name   : ";
                                SetConsoleTextAttribute(hConsole, 7);
                                getline(cin, newName);
                                
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Enter New Number of Days : ";
                                SetConsoleTextAttribute(hConsole, 7);
                                cin >> newDays;
                                
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Enter New Amount         : ";
                                SetConsoleTextAttribute(hConsole, 7);
                                cin >> newAmount;
                                
                                packageNames[idx] = newName;
                                packageDays[idx] = newDays;
                                packageAmounts[idx] = newAmount;
                                
                                // Save to file
                                ofstream savePackage("packages.txt");
                                savePackage << packageCount << "\n";
                                for(int i = 0; i < packageCount; i++){
                                    savePackage << packageNames[i] << "\n";
                                    savePackage << packageDays[i] << "\n";
                                    savePackage << packageAmounts[i] << "\n";
                                    savePackage << packageTypes[i] << "\n";
                                    savePackage << packageIncludes[i] << "\n";
                                }
                                savePackage.close();
                                
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "\n  Updated Successfully!\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 5){
                        // Delete Package
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               DELETE UMRAH PACKAGE                         " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(packageCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No packages available.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Available Packages:\n";
                            for(int i = 0; i < packageCount; i++){
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  [" << (i+1) << "] ";
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << packageNames[i] << "\n";
                            }
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  Enter Package Name to Delete : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin.ignore();
                            string delName;
                            getline(cin, delName);
                            
                            int idx = -1;
                            for(int i = 0; i < packageCount; i++){
                                if(packageNames[i] == delName){
                                    idx = i;
                                    break;
                                }
                            }
                            
                            if(idx == -1){
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  Package not found!\n";
                            } else {
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "\n  Package Found: " << packageNames[idx] << "\n\n";
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "  [1] Delete\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  [2] Cancel\n";
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << "\n  Enter Choice : ";
                                int choice;
                                cin >> choice;
                                
                                if(choice == 1){
                                    for(int i = idx; i < packageCount - 1; i++){
                                        packageNames[i] = packageNames[i+1];
                                        packageDays[i] = packageDays[i+1];
                                        packageAmounts[i] = packageAmounts[i+1];
                                        packageTypes[i] = packageTypes[i+1];
                                        packageIncludes[i] = packageIncludes[i+1];
                                    }
                                    packageCount--;
                                    
                                    // Save to file
                                    ofstream savePackage("packages.txt");
                                    savePackage << packageCount << "\n";
                                    for(int i = 0; i < packageCount; i++){
                                        savePackage << packageNames[i] << "\n";
                                        savePackage << packageDays[i] << "\n";
                                        savePackage << packageAmounts[i] << "\n";
                                        savePackage << packageTypes[i] << "\n";
                                        savePackage << packageIncludes[i] << "\n";
                                    }
                                    savePackage.close();
                                    
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "\n  Deleted Successfully!\n";
                                } else {
                                    SetConsoleTextAttribute(hConsole, 13);
                                    cout << "\n  Cancel Deletion\n";
                                }
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 6){
                        // Search Package
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               SEARCH UMRAH PACKAGE                         " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "  Enter Package Name : ";
                        SetConsoleTextAttribute(hConsole, 7);
                        cin.ignore();
                        string searchName;
                        getline(cin, searchName);
                        
                        int idx = -1;
                        for(int i = 0; i < packageCount; i++){
                            if(packageNames[i] == searchName){
                                idx = i;
                                break;
                            }
                        }
                        
                        if(idx == -1){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  Package not found!\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "\n  " << char(201);
                            for(int i=0;i<55;i++) cout << char(205);
                            cout << char(187) << "\n";
                            cout << "  " << char(186) << "               PACKAGE DETAILS                          " << char(186) << "\n";
                            cout << "  " << char(204);
                            for(int i=0;i<55;i++) cout << char(205);
                            cout << char(185) << "\n";
                            SetConsoleTextAttribute(hConsole, 15);
                            cout << "  " << char(186) << "  Package Name  : " << left << setw(38) << packageNames[idx] << char(186) << "\n";
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  " << char(186) << "  Duration      : " << left << setw(35) << (to_string(packageDays[idx]) + " Days") << char(186) << "\n";
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << "  " << char(186) << "  Amount        : PKR " << left << setw(34) << packageAmounts[idx] << char(186) << "\n";
                            SetConsoleTextAttribute(hConsole, 13);
                            cout << "  " << char(186) << "  Package Type  : " << left << setw(38) << packageTypes[idx] << char(186) << "\n";
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  " << char(186) << "  Inclusions    : " << left << setw(38) << packageIncludes[idx] << char(186) << "\n";
                            cout << "  " << char(200);
                            for(int i=0;i<55;i++) cout << char(205);
                            cout << char(188) << "\n";
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 7){
                        // View Bookings
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<76;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                         ALL BOOKINGS LIST                                      " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<76;i++) cout << char(205);
                        cout << char(188) << "\n";
                        
                        if(bookingCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No bookings found.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  " << left << setw(12) << "Booking ID" << setw(16) << "Customer" << setw(22) << "Package" << setw(13) << "Date" << setw(8) << "Payment" << "Status\n";
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  ";
                            for(int i=0;i<76;i++) cout << char(196);
                            cout << "\n";
                            
                            for(int i = 0; i < bookingCount; i++){
                                if(bookingCancelled[i]){
                                    SetConsoleTextAttribute(hConsole, 12);
                                    cout << "  " << left << setw(12) << bookingIds[i] << setw(16) << bookingUserNames[i]
                                         << setw(22) << bookingPackageNames[i] << setw(13) << bookingDates[i]
                                         << setw(8) << bookingPaymentStatus[i] << "Cancelled\n";
                                } else {
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "  " << left << setw(12) << bookingIds[i];
                                    SetConsoleTextAttribute(hConsole, 15);
                                    cout << setw(16) << bookingUserNames[i];
                                    SetConsoleTextAttribute(hConsole, 11);
                                    cout << setw(22) << bookingPackageNames[i];
                                    SetConsoleTextAttribute(hConsole, 14);
                                    cout << setw(13) << bookingDates[i];
                                    if(bookingPaymentStatus[i] == "Paid") SetConsoleTextAttribute(hConsole, 10);
                                    else SetConsoleTextAttribute(hConsole, 12);
                                    cout << setw(8) << bookingPaymentStatus[i];
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "Active\n";
                                }
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 8){
                        // Cancel Booking (Admin)
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               CANCEL A BOOKING                             " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(bookingCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No bookings available.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Booking ID to Cancel : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin.ignore();
                            string bid;
                            getline(cin, bid);
                            
                            int idx = -1;
                            for(int i = 0; i < bookingCount; i++){
                                if(bookingIds[i] == bid && !bookingCancelled[i]){
                                    idx = i;
                                    break;
                                }
                            }
                            
                            if(idx == -1){
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  Booking not found or already cancelled!\n";
                            } else {
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "\n  Booking Details:\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Customer : " << bookingUserNames[idx] << "\n";
                                cout << "  Package  : " << bookingPackageNames[idx] << "\n";
                                cout << "  Date     : " << bookingDates[idx] << "\n\n";
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "  [1] Cancel Booking\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  [2] Go Back\n";
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << "\n  Enter Choice : ";
                                int ch;
                                cin >> ch;
                                
                                if(ch == 1){
                                    bookingCancelled[idx] = true;
                                    
                                    // Save to file
                                    ofstream saveBooking("bookings.txt");
                                    saveBooking << bookingCount << "\n";
                                    for(int i = 0; i < bookingCount; i++){
                                        saveBooking << bookingIds[i] << "\n";
                                        saveBooking << bookingUserIds[i] << "\n";
                                        saveBooking << bookingUserNames[i] << "\n";
                                        saveBooking << bookingPackageNames[i] << "\n";
                                        saveBooking << bookingDates[i] << "\n";
                                        saveBooking << bookingPaymentStatus[i] << "\n";
                                        saveBooking << bookingBankNames[i] << "\n";
                                        saveBooking << bookingAccountNumbers[i] << "\n";
                                        saveBooking << bookingCancelled[i] << "\n";
                                    }
                                    saveBooking.close();
                                    
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "\n  Booking Cancelled Successfully!\n";
                                } else {
                                    SetConsoleTextAttribute(hConsole, 13);
                                    cout << "\n  Operation Cancelled.\n";
                                }
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 9){
                        // Customer List
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                    CUSTOMER LIST                            " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(bookingCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No customers found.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  " << left << setw(5) << "No." << setw(25) << "Customer Name" << setw(20) << "User ID" << "Bookings\n";
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  ";
                            for(int i=0;i<60;i++) cout << char(196);
                            cout << "\n";
                            
                            int serial = 1;
                            for(int i = 0; i < bookingCount; i++){
                                bool alreadyPrinted = false;
                                for(int j = 0; j < i; j++){
                                    if(bookingUserIds[j] == bookingUserIds[i]){
                                        alreadyPrinted = true;
                                        break;
                                    }
                                }
                                if(!alreadyPrinted){
                                    int bcount = 0;
                                    for(int j = 0; j < bookingCount; j++){
                                        if(bookingUserIds[j] == bookingUserIds[i] && !bookingCancelled[j]) bcount++;
                                    }
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "  " << left << setw(5) << serial++;
                                    SetConsoleTextAttribute(hConsole, 15);
                                    cout << setw(25) << bookingUserNames[i];
                                    SetConsoleTextAttribute(hConsole, 11);
                                    cout << setw(20) << bookingUserIds[i];
                                    SetConsoleTextAttribute(hConsole, 14);
                                    cout << bcount << "\n";
                                }
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(adminChoice == 10){
                        // Customer Details
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<72;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                       COMPLETE CUSTOMER DETAILS                                " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<72;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(userCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No customers registered.\n";
                        } else {
                            for(int i = 0; i < userCount; i++){
                                int bcount = 0;
                                for(int j = 0; j < bookingCount; j++){
                                    if(bookingUserIds[j] == userUsernames[i]) bcount++;
                                }
                                
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(201);
                                for(int k=0;k<68;k++) cout << char(205);
                                cout << char(187) << "\n";
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << "  " << char(186) << "  Customer #" << (i+1) << " : " << left << setw(56) << userFullNames[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(204);
                                for(int k=0;k<68;k++) cout << char(205);
                                cout << char(185) << "\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  " << char(186) << "  Username    : " << left << setw(53) << userUsernames[i] << char(186) << "\n";
                                cout << "  " << char(186) << "  Phone       : " << left << setw(53) << userPhones[i] << char(186) << "\n";
                                cout << "  " << char(186) << "  Email       : " << left << setw(53) << userEmails[i] << char(186) << "\n";
                                cout << "  " << char(186) << "  CNIC        : " << left << setw(53) << userCnic[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  " << char(186) << "  Bookings    : " << left << setw(53) << bcount << char(186) << "\n";
                                
                                for(int j = 0; j < bookingCount; j++){
                                    if(bookingUserIds[j] == userUsernames[i]){
                                        string status = bookingCancelled[j] ? "Cancelled" : "Active";
                                        cout << "  " << char(186) << "  [" << bookingIds[j] << "] " << bookingPackageNames[j] << " | " << bookingDates[j] << " | " << bookingPaymentStatus[j] << " | " << status;
                                        cout << string(68 - (bookingIds[j] + bookingPackageNames[j] + bookingDates[j] + bookingPaymentStatus[j] + status).length(), ' ') << char(186) << "\n";
                                    }
                                }
                                
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(200);
                                for(int k=0;k<68;k++) cout << char(205);
                                cout << char(188) << "\n\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    
                } while(adminChoice != 0);
                isAdminLoggedIn = false;
            } else {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n  Invalid username or password!\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n  Press any key to return to main menu...";
                getch();
            }
        }
        else if(mainChoice == 2){
            // User Login
            system("cls");
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\n  " << char(201);
            for(int i=0;i<50;i++) cout << char(205);
            cout << char(187) << "\n";
            cout << "  " << char(186) << "              USER LOGIN PORTAL                      " << char(186) << "\n";
            cout << "  " << char(200);
            for(int i=0;i<50;i++) cout << char(205);
            cout << char(188) << "\n\n";
            
            string uname, pass;
            SetConsoleTextAttribute(hConsole, 11);
            cout << "  Enter Username : ";
            SetConsoleTextAttribute(hConsole, 7);
            cin >> uname;
            SetConsoleTextAttribute(hConsole, 11);
            cout << "  Enter Password : ";
            SetConsoleTextAttribute(hConsole, 7);
            pass = "";
            char ch;
            while((ch = getch()) != 13){
                if(ch == 8){
                    if(!pass.empty()){
                        pass.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    pass += ch;
                    cout << "*";
                }
            }
            cout << "\n";
            
            bool userFound = false;
            for(int i = 0; i < userCount; i++){
                if(userUsernames[i] == uname && userPasswords[i] == pass){
                    userFound = true;
                    isUserLoggedIn = true;
                    loggedInUser = uname;
                    loggedInName = userFullNames[i];
                    break;
                }
            }
            
            if(userFound){
                SetConsoleTextAttribute(hConsole, 10);
                cout << "\n  Login Successful! Welcome, " << loggedInName << "\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n  Press any key to continue...";
                getch();
                
                // User Menu
                int userChoice;
                do {
                    system("cls");
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "\n  " << char(201);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(187) << "\n";
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "  " << char(186) << "   Welcome, " << left << setw(38) << loggedInName << char(186) << "\n";
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "  " << char(204);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(185) << "\n";
                    cout << "  " << char(186) << "               USER PANEL                           " << char(186) << "\n";
                    cout << "  " << char(204);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(185) << "\n";
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  " << char(186) << "   [1]  View Packages                            " << char(186) << "\n";
                    cout << "  " << char(186) << "   [2]  Book a Package                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [3]  Rate Package                             " << char(186) << "\n";
                    cout << "  " << char(186) << "   [4]  Payment System                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [5]  Cancel Booking                           " << char(186) << "\n";
                    cout << "  " << char(186) << "   [6]  View Booking Details                     " << char(186) << "\n";
                    cout << "  " << char(186) << "   [7]  Rate Package (Feedback)                  " << char(186) << "\n";
                    cout << "  " << char(186) << "   [8]  Check Payment Status                     " << char(186) << "\n";
                    cout << "  " << char(186) << "   [9]  Booking History                          " << char(186) << "\n";
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "  " << char(186) << "   [0]  Logout                                   " << char(186) << "\n";
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << "  " << char(200);
                    for(int i=0;i<50;i++) cout << char(205);
                    cout << char(188) << "\n";
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "\n  Enter Your Choice : ";
                    SetConsoleTextAttribute(hConsole, 7);
                    cin >> userChoice;
                    
                    if(userChoice == 1){
                        // View Packages
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<76;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                    AVAILABLE UMRAH PACKAGES                                    " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<76;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(packageCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No packages available at the moment.\n";
                        } else {
                            for(int i = 0; i < packageCount; i++){
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(201);
                                for(int k=0;k<60;k++) cout << char(205);
                                cout << char(187) << "\n";
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << "  " << char(186) << "  " << char(254) << " " << left << setw(57) << packageNames[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(204);
                                for(int k=0;k<60;k++) cout << char(205);
                                cout << char(185) << "\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  " << char(186) << "  Duration     : " << left << setw(44) << (to_string(packageDays[i]) + " Days") << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  " << char(186) << "  Amount       : PKR " << left << setw(40) << packageAmounts[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 13);
                                cout << "  " << char(186) << "  Type         : " << left << setw(44) << packageTypes[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << "  " << char(186) << "  Includes     : " << left << setw(44) << packageIncludes[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(200);
                                for(int k=0;k<60;k++) cout << char(205);
                                cout << char(188) << "\n\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 2){
                        // Book a Package
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                BOOK UMRAH PACKAGE                           " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        if(packageCount == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No packages available for booking.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Available Packages:\n";
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  ";
                            for(int i=0;i<55;i++) cout << char(196);
                            cout << "\n";
                            for(int i = 0; i < packageCount; i++){
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  [" << (i+1) << "] ";
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << left << setw(25) << packageNames[i];
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "PKR " << packageAmounts[i] << "   (" << packageDays[i] << " days)\n";
                            }
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  ";
                            for(int i=0;i<55;i++) cout << char(196);
                            cout << "\n\n";
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Package Name to Book : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin.ignore();
                            string pkgName;
                            getline(cin, pkgName);
                            
                            int pkgIdx = -1;
                            for(int i = 0; i < packageCount; i++){
                                if(packageNames[i] == pkgName){
                                    pkgIdx = i;
                                    break;
                                }
                            }
                            
                            if(pkgIdx == -1){
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  Package not found!\n";
                            } else {
                                // Get current date
                                time_t now = time(0);
                                tm* ltm = localtime(&now);
                                stringstream ss;
                                ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
                                   << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "/"
                                   << (1900 + ltm->tm_year);
                                string currentDate = ss.str();
                                
                                string bookingId = "BK" + to_string(bookingCount + 1001);
                                bookingIds[bookingCount] = bookingId;
                                bookingUserIds[bookingCount] = loggedInUser;
                                bookingUserNames[bookingCount] = loggedInName;
                                bookingPackageNames[bookingCount] = pkgName;
                                bookingDates[bookingCount] = currentDate;
                                bookingPaymentStatus[bookingCount] = "Unpaid";
                                bookingBankNames[bookingCount] = "";
                                bookingAccountNumbers[bookingCount] = "";
                                bookingCancelled[bookingCount] = false;
                                bookingCount++;
                                
                                // Save to file
                                ofstream saveBooking("bookings.txt");
                                saveBooking << bookingCount << "\n";
                                for(int i = 0; i < bookingCount; i++){
                                    saveBooking << bookingIds[i] << "\n";
                                    saveBooking << bookingUserIds[i] << "\n";
                                    saveBooking << bookingUserNames[i] << "\n";
                                    saveBooking << bookingPackageNames[i] << "\n";
                                    saveBooking << bookingDates[i] << "\n";
                                    saveBooking << bookingPaymentStatus[i] << "\n";
                                    saveBooking << bookingBankNames[i] << "\n";
                                    saveBooking << bookingAccountNumbers[i] << "\n";
                                    saveBooking << bookingCancelled[i] << "\n";
                                }
                                saveBooking.close();
                                
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "\n  Booking Confirmed!\n";
                                cout << "  Booking ID : " << bookingId << "\n";
                                cout << "  Package    : " << pkgName << "\n";
                                cout << "  Date       : " << currentDate << "\n";
                                cout << "  Payment    : Unpaid (Complete from Option 4)\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 3 || userChoice == 7){
                        // Rate Package
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               RATE YOUR PACKAGE                             " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        bool found = false;
                        for(int i = 0; i < bookingCount; i++){
                            if(bookingUserIds[i] == loggedInUser && !bookingCancelled[i]){
                                found = true;
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Your Package: " << bookingPackageNames[i] << "\n";
                                break;
                            }
                        }
                        
                        if(!found){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No active bookings to rate.\n";
                        } else {
                            int rating;
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  Rate the package (1-5 stars): ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin >> rating;
                            
                            if(rating >= 1 && rating <= 5){
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "\n  Thank you for your rating: ";
                                SetConsoleTextAttribute(hConsole, 14);
                                for(int i = 0; i < rating; i++) cout << char(1) << " ";
                                cout << "\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Your feedback has been recorded.\n";
                            } else {
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  Invalid rating! Please rate between 1-5.\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 4){
                        // Payment System
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                   PAYMENT SYSTEM                            " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        bool hasUnpaid = false;
                        int unpaidIndex = -1;
                        for(int i = 0; i < bookingCount; i++){
                            if(bookingUserIds[i] == loggedInUser && !bookingCancelled[i] && bookingPaymentStatus[i] == "Unpaid"){
                                hasUnpaid = true;
                                unpaidIndex = i;
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Pending Payment:\n";
                                cout << "  Booking ID : " << bookingIds[i] << "\n";
                                cout << "  Package    : " << bookingPackageNames[i] << "\n";
                                for(int j = 0; j < packageCount; j++){
                                    if(packageNames[j] == bookingPackageNames[i]){
                                        SetConsoleTextAttribute(hConsole, 10);
                                        cout << "  Amount     : PKR " << packageAmounts[j] << "\n";
                                        break;
                                    }
                                }
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << "\n";
                                break;
                            }
                        }
                        
                        if(!hasUnpaid){
                            SetConsoleTextAttribute(hConsole, 10);
                            cout << "\n  All your bookings are already paid or no active bookings found.\n";
                        } else {
                            string bankName, accNum;
                            cin.ignore();
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Bank Name       : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            getline(cin, bankName);
                            
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "  Enter Account Number  : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            getline(cin, accNum);
                            
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "\n  [1] Confirm Payment\n";
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "  [2] Cancel\n";
                            SetConsoleTextAttribute(hConsole, 7);
                            cout << "\n  Enter Choice : ";
                            int ch;
                            cin >> ch;
                            
                            if(ch == 1){
                                bookingPaymentStatus[unpaidIndex] = "Paid";
                                bookingBankNames[unpaidIndex] = bankName;
                                bookingAccountNumbers[unpaidIndex] = accNum;
                                
                                // Save to file
                                ofstream saveBooking("bookings.txt");
                                saveBooking << bookingCount << "\n";
                                for(int i = 0; i < bookingCount; i++){
                                    saveBooking << bookingIds[i] << "\n";
                                    saveBooking << bookingUserIds[i] << "\n";
                                    saveBooking << bookingUserNames[i] << "\n";
                                    saveBooking << bookingPackageNames[i] << "\n";
                                    saveBooking << bookingDates[i] << "\n";
                                    saveBooking << bookingPaymentStatus[i] << "\n";
                                    saveBooking << bookingBankNames[i] << "\n";
                                    saveBooking << bookingAccountNumbers[i] << "\n";
                                    saveBooking << bookingCancelled[i] << "\n";
                                }
                                saveBooking.close();
                                
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "\n  Payment Status = Paid\n";
                                cout << "  Bank Name      : " << bankName << "\n";
                                cout << "  Account No     : " << accNum << "\n";
                            } else {
                                SetConsoleTextAttribute(hConsole, 13);
                                cout << "\n  Payment Status = Unpaid\n";
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 5){
                        // Cancel Booking
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               CANCEL YOUR BOOKING                           " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<60;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        bool hasBooking = false;
                        for(int i = 0; i < bookingCount; i++){
                            if(bookingUserIds[i] == loggedInUser && !bookingCancelled[i]){
                                hasBooking = true;
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "  ID: " << bookingIds[i] << "  |  " << bookingPackageNames[i] << "  |  " << bookingDates[i] << "\n";
                            }
                        }
                        
                        if(!hasBooking){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No active bookings found.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "\n  Enter Booking ID to Cancel : ";
                            SetConsoleTextAttribute(hConsole, 7);
                            cin.ignore();
                            string bid;
                            getline(cin, bid);
                            
                            int idx = -1;
                            for(int i = 0; i < bookingCount; i++){
                                if(bookingIds[i] == bid && bookingUserIds[i] == loggedInUser && !bookingCancelled[i]){
                                    idx = i;
                                    break;
                                }
                            }
                            
                            if(idx == -1){
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  Booking not found!\n";
                            } else {
                                SetConsoleTextAttribute(hConsole, 12);
                                cout << "\n  [1] Confirm Cancellation\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  [2] Go Back\n";
                                SetConsoleTextAttribute(hConsole, 7);
                                cout << "\n  Enter Choice : ";
                                int ch;
                                cin >> ch;
                                
                                if(ch == 1){
                                    bookingCancelled[idx] = true;
                                    
                                    // Save to file
                                    ofstream saveBooking("bookings.txt");
                                    saveBooking << bookingCount << "\n";
                                    for(int i = 0; i < bookingCount; i++){
                                        saveBooking << bookingIds[i] << "\n";
                                        saveBooking << bookingUserIds[i] << "\n";
                                        saveBooking << bookingUserNames[i] << "\n";
                                        saveBooking << bookingPackageNames[i] << "\n";
                                        saveBooking << bookingDates[i] << "\n";
                                        saveBooking << bookingPaymentStatus[i] << "\n";
                                        saveBooking << bookingBankNames[i] << "\n";
                                        saveBooking << bookingAccountNumbers[i] << "\n";
                                        saveBooking << bookingCancelled[i] << "\n";
                                    }
                                    saveBooking.close();
                                    
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "\n  Booking Cancelled Successfully.\n";
                                } else {
                                    SetConsoleTextAttribute(hConsole, 13);
                                    cout << "\n  Operation Cancelled.\n";
                                }
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 6){
                        // View Booking Details
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<65;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                   YOUR BOOKING DETAILS                            " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<65;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        bool found = false;
                        for(int i = 0; i < bookingCount; i++){
                            if(bookingUserIds[i] == loggedInUser && !bookingCancelled[i]){
                                found = true;
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(201);
                                for(int k=0;k<60;k++) cout << char(205);
                                cout << char(187) << "\n";
                                SetConsoleTextAttribute(hConsole, 15);
                                cout << "  " << char(186) << "  Booking ID     : " << left << setw(42) << bookingIds[i] << char(186) << "\n";
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  " << char(186) << "  Package        : " << left << setw(42) << bookingPackageNames[i] << char(186) << "\n";
                                cout << "  " << char(186) << "  Booking Date   : " << left << setw(42) << bookingDates[i] << char(186) << "\n";
                                if(bookingPaymentStatus[i] == "Paid") SetConsoleTextAttribute(hConsole, 10);
                                else SetConsoleTextAttribute(hConsole, 12);
                                cout << "  " << char(186) << "  Payment Status : " << left << setw(42) << bookingPaymentStatus[i] << char(186) << "\n";
                                if(bookingPaymentStatus[i] == "Paid"){
                                    SetConsoleTextAttribute(hConsole, 13);
                                    cout << "  " << char(186) << "  Bank Name      : " << left << setw(42) << bookingBankNames[i] << char(186) << "\n";
                                    cout << "  " << char(186) << "  Account No     : " << left << setw(42) << bookingAccountNumbers[i] << char(186) << "\n";
                                }
                                for(int j = 0; j < packageCount; j++){
                                    if(packageNames[j] == bookingPackageNames[i]){
                                        SetConsoleTextAttribute(hConsole, 10);
                                        cout << "  " << char(186) << "  Duration       : " << left << setw(39) << (to_string(packageDays[j]) + " Days") << char(186) << "\n";
                                        cout << "  " << char(186) << "  Amount         : PKR " << left << setw(39) << packageAmounts[j] << char(186) << "\n";
                                        break;
                                    }
                                }
                                SetConsoleTextAttribute(hConsole, 14);
                                cout << "  " << char(200);
                                for(int k=0;k<60;k++) cout << char(205);
                                cout << char(188) << "\n\n";
                            }
                        }
                        
                        if(!found){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No active bookings found.\n";
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 8){
                        // Check Payment Status
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<55;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "               CHECK PAYMENT STATUS                      " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<55;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        bool found = false;
                        for(int i = 0; i < bookingCount; i++){
                            if(bookingUserIds[i] == loggedInUser && !bookingCancelled[i]){
                                found = true;
                                SetConsoleTextAttribute(hConsole, 11);
                                cout << "  Booking ID : " << bookingIds[i] << "\n";
                                cout << "  Package    : " << bookingPackageNames[i] << "\n";
                                if(bookingPaymentStatus[i] == "Paid"){
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "\n  Payment Status = Paid\n";
                                } else {
                                    SetConsoleTextAttribute(hConsole, 12);
                                    cout << "\n  Payment Status = Unpaid\n";
                                }
                                cout << "\n";
                            }
                        }
                        
                        if(!found){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No active bookings found.\n";
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    else if(userChoice == 9){
                        // Booking History
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 14);
                        cout << "\n  " << char(201);
                        for(int i=0;i<65;i++) cout << char(205);
                        cout << char(187) << "\n";
                        cout << "  " << char(186) << "                    BOOKING HISTORY                                " << char(186) << "\n";
                        cout << "  " << char(200);
                        for(int i=0;i<65;i++) cout << char(205);
                        cout << char(188) << "\n\n";
                        
                        int total = 0, active = 0, cancelled = 0;
                        for(int i = 0; i < bookingCount; i++){
                            if(bookingUserIds[i] == loggedInUser){
                                total++;
                                if(bookingCancelled[i]) cancelled++;
                                else active++;
                            }
                        }
                        
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "  Total Packages Booked : " << total << "\n";
                        cout << "  Active Bookings       : " << active << "\n";
                        cout << "  Cancelled Bookings    : " << cancelled << "\n\n";
                        
                        if(total == 0){
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "\n  No booking history found.\n";
                        } else {
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "  " << left << setw(12) << "Booking ID" << setw(25) << "Package Name" << setw(14) << "Booking Date" << setw(10) << "Payment" << "Status\n";
                            cout << "  ";
                            for(int i=0;i<65;i++) cout << char(196);
                            cout << "\n";
                            
                            for(int i = 0; i < bookingCount; i++){
                                if(bookingUserIds[i] == loggedInUser){
                                    if(bookingCancelled[i]) SetConsoleTextAttribute(hConsole, 12);
                                    else SetConsoleTextAttribute(hConsole, 10);
                                    cout << "  " << left << setw(12) << bookingIds[i]
                                         << setw(25) << bookingPackageNames[i]
                                         << setw(14) << bookingDates[i]
                                         << setw(10) << bookingPaymentStatus[i]
                                         << (bookingCancelled[i] ? "Cancelled" : "Active") << "\n";
                                }
                            }
                        }
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "\n  Press any key to return to main menu...";
                        SetConsoleTextAttribute(hConsole, 7);
                        getch();
                    }
                    
                } while(userChoice != 0);
                isUserLoggedIn = false;
            } else {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n  Invalid username or password!\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n  Press any key to return to main menu...";
                getch();
            }
        }
        else if(mainChoice == 3){
            // New User Registration
            system("cls");
            SetConsoleTextAttribute(hConsole, 14);
            cout << "\n  " << char(201);
            for(int i=0;i<60;i++) cout << char(205);
            cout << char(187) << "\n";
            cout << "  " << char(186) << "               NEW USER REGISTRATION                        " << char(186) << "\n";
            cout << "  " << char(204);
            for(int i=0;i<60;i++) cout << char(205);
            cout << char(185) << "\n";
            SetConsoleTextAttribute(hConsole, 13);
            cout << "  " << char(186) << "   All fields are required and validated.               " << char(186) << "\n";
            SetConsoleTextAttribute(hConsole, 14);
            cout << "  " << char(200);
            for(int i=0;i<60;i++) cout << char(205);
            cout << char(188) << "\n\n";
            
            if(userCount >= 100){
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\n  User registration limit reached!\n";
            } else {
                string uname, pass, fullname, phone, email, cnic;
                
                SetConsoleTextAttribute(hConsole, 11);
                cout << "  Enter Username       : ";
                SetConsoleTextAttribute(hConsole, 7);
                cin >> uname;
                
                SetConsoleTextAttribute(hConsole, 11);
                cout << "  Enter Password       : ";
                SetConsoleTextAttribute(hConsole, 7);
                pass = "";
                char ch;
                while((ch = getch()) != 13){
                    if(ch == 8){
                        if(!pass.empty()){
                            pass.pop_back();
                            cout << "\b \b";
                        }
                    } else {
                        pass += ch;
                        cout << "*";
                    }
                }
                cout << "\n";
                
                SetConsoleTextAttribute(hConsole, 11);
                cout << "  Confirm Password     : ";
                SetConsoleTextAttribute(hConsole, 7);
                string confirmPass = "";
                while((ch = getch()) != 13){
                    if(ch == 8){
                        if(!confirmPass.empty()){
                            confirmPass.pop_back();
                            cout << "\b \b";
                        }
                    } else {
                        confirmPass += ch;
                        cout << "*";
                    }
                }
                cout << "\n";
                
                if(pass != confirmPass){
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << "\n  Passwords do not match!\n";
                } else {
                    cin.ignore();
                    
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  Enter Full Name      : ";
                    SetConsoleTextAttribute(hConsole, 7);
                    getline(cin, fullname);
                    
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  Enter Phone Number   : ";
                    SetConsoleTextAttribute(hConsole, 7);
                    getline(cin, phone);
                    
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  Enter Email          : ";
                    SetConsoleTextAttribute(hConsole, 7);
                    getline(cin, email);
                    
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "  Enter CNIC           : ";
                    SetConsoleTextAttribute(hConsole, 7);
                    getline(cin, cnic);
                    
                    userUsernames[userCount] = uname;
                    userPasswords[userCount] = pass;
                    userFullNames[userCount] = fullname;
                    userPhones[userCount] = phone;
                    userEmails[userCount] = email;
                    userCnic[userCount] = cnic;
                    userCount++;
                    
                    // Save to file
                    ofstream saveUser("users.txt");
                    saveUser << userCount << "\n";
                    for(int i = 0; i < userCount; i++){
                        saveUser << userUsernames[i] << "\n";
                        saveUser << userPasswords[i] << "\n";
                        saveUser << userFullNames[i] << "\n";
                        saveUser << userPhones[i] << "\n";
                        saveUser << userEmails[i] << "\n";
                        saveUser << userCnic[i] << "\n";
                    }
                    saveUser.close();
                    
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "\n  Registration Successful!\n";
                    cout << "  You can now login with your credentials.\n";
                }
            }
            SetConsoleTextAttribute(hConsole, 11);
            cout << "\n  Press any key to return to main menu...";
            SetConsoleTextAttribute(hConsole, 7);
            getch();
        }
        
    } while(mainChoice != 0);
    
    // Exit message
    system("cls");
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n\n\n";
    cout << "          " << char(201);
    for(int i=0;i<47;i++) cout << char(205);
    cout << char(187) << "\n";
    cout << "          " << char(186) << "   Thank you for using our system!              " << char(186) << "\n";
    cout << "          " << char(186) << "   AL-HARAMAIN Tours & Travels                  " << char(186) << "\n";
    cout << "          " << char(186) << "   May Allah Accept Your Umrah. Ameen.          " << char(186) << "\n";
    cout << "          " << char(200);
    for(int i=0;i<47;i++) cout << char(205);
    cout << char(188) << "\n\n";
    SetConsoleTextAttribute(hConsole, 7);
    
    return 0;
}