#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

void check();

int main(){
    check();

    return 0;
}

void cli(){
    string command;
    cout << "Enter command: ";
    cin >> command;

    if (command == "help"){
        cout << "\nhelp - show this help" << endl;
        cout << "exit - exit from program" << endl;
        cout << "d2ip - show ip of server" << endl;
        cout << "d2port - show port of server" << endl;
        cout << "ip2d - show ip of client\n" << endl;

        cli();

    } else if (command == "exit"){
        cout << "Bye!" << endl;
        exit(0);

    } else if (command == "d2ip") {
        string domain;
        cout << "Enter domain: ";
        cin >> domain;

        cout << "IP: " << system(("nslookup " + domain).c_str()) << endl;
        cli();

    } else if (command == "ip2d") {
        string ip;
        cout << "Enter ip: ";
        cin >> ip;

        cout << "Domain: " << system(("nslookup " + ip).c_str()) << endl;
        cli();

    } else if (command == "ping") {
        string domain;
        cout << "Enter domain: ";
        cin >> domain;

        cout << "Ping: " << system(("ping " + domain).c_str()) << endl;
        cli();
    
    } else if (command == "d2port") {
        string domain;
        cout << "Enter domain: ";
        cin >> domain;

        // scan for open ports on domain

        cout << "Open ports: " << system(("sudo nmap -sS " + domain).c_str()) << endl;
        
        cli();
 
    } else {
        cout << "Unknown command" << endl;
        cli();
    
    }        
}

void success(){
    cout << "Successfull login!" << endl;
    // wait 0.5 seconds 
    this_thread::sleep_for(std::chrono::milliseconds(300));
    
    // check if operating system is windows or linux / unix
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Welcome to the 1cyOSINT!" << endl;

    cout << "Type help to see the list of commands" << endl;

    cli();

}


void login(){
    cout << "Please login to the system" << endl;
    // check if the file exists 
    ifstream file("login.txt");
    // check if username and password are correct 
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    if(file.is_open()){
        while(!file.eof()){
            string line;
            getline(file, line);
            if(line == username){
                getline(file, line);
                if(line == password){
                    success();
                    
                } else {
                    cout << "Wrong password!\nTry again\n" << endl;
                    login();
                }
            } else {
                cout << "Wrong username!\nTry again\n" << endl;
                login();
            }
        }
    }
    file.close();
}

void registration(){
    string username;
    string password;
    string password_confirm;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // ask to enter password again to verify 
    cout << "Enter your password again: ";
    cin >> password_confirm;

    // check if the password is the same
    if(password == password_confirm){
        cout << "Your username is: " << username << endl;
        cout << "Your password is: " << password << endl;
        ofstream file("login.txt", ios::app);
        if(file.is_open()){
            file << username << endl;
            file << password << endl;
        }
        file.close();
        success();
    }
    else{
        cout << "Passwords do not match!" << endl;
        // retry if passwords do not match
        cout << "retry" << endl;
        registration();
    }

}


// function to check for register or login
void check(){

    // check if file with name login.txt exists 
    // if it does, then call login function 

    ifstream file("login.txt");
    if(file.is_open()){
        login();
    }
    else{
        cout << "You are not registered!\nPlease fill out username and password" << endl;
        registration();
    }


}
