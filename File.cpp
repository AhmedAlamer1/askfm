#include <iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include <ctype.h>
#include<vector>
#define endl "\n"
typedef long long ll;
using namespace std;

struct question {
    string q;
    int to_id, from_id;
};

struct User  {
    string name, username, pass, email;
};

class Data_base {

public:
    map<int, question>Q;
    map<int, bool>is_answerd;
    map<int, string>Answers;
    map<string, string>Username_Pass_mp;
    map<string, int>username_Id_mp;
    map<int, User>Users_mp;
    
    void download_Users_username(){
        fstream Myfile;
        Myfile.open("UserNames.txt", ios::in);
        if (Myfile.is_open())
        {
            string line ;
            while (getline(Myfile, line))
            {
                stringstream x(line);
                string s1,s2;
                getline(x, s1, ' ');
                getline(x, s2, ' ');
                Username_Pass_mp[s1] = s2;
            }
            Myfile.close();
        }
    }
    void download_Users_id(){
        fstream Myfile;
        Myfile.open("UserId.txt", ios::in);
        if (Myfile.is_open())
        {
            string line ;
            while (getline(Myfile, line))
            {
                stringstream x(line);
                string s1, s2;
                getline(x, s1, ' ');
                getline(x, s2, ' ');
                username_Id_mp[s1] = stoi(s2);
            }
            Myfile.close();
        }
    }   
    void download_Users(){
        fstream Myfile;
        Myfile.open("Users.txt", ios::in);
        if (Myfile.is_open())
        {
            string line = "";
            while (getline(Myfile, line))
            {
                stringstream x(line);
                string s1, s2;
                getline(x, s1, ' ');
                int id = stoi(s1);
                getline(x, s2, ' ');
                Users_mp[id].username = s2;
                getline(x, s2, ' ');
                Users_mp[id].pass = s2;
                getline(x, s2, ' ');
                Users_mp[id].email = s2;
                getline(x, s2, ' ');
                Users_mp[id].name = s2;
            }
            Myfile.close();
        }
    }
    void upload_User(User u)
    {
        fstream Myfile;
        int id = Users_mp.size() + 1;
        Users_mp[id] = u;
        Myfile.open("Users.txt", ios::app);
        if (Myfile.is_open())
        {
            Myfile <<id<<' '<< u.username << ' ' << u.pass << ' ' << u.name << ' ' << u.email << endl;
            Myfile.close();
        }
        Myfile.open("UserId.txt", ios::app);
        if (Myfile.is_open())
        {
            Myfile << u.username << ' ' << id << endl;
            Myfile.close();
        }
        Myfile.open("UserNames.txt", ios::app);
        if (Myfile.is_open())
        {
            Myfile << u.username << ' ' << u.pass << endl;
            Myfile.close();
        }
    }

    void download_Questions(){
        fstream Myfile;
        Myfile.open("Question.txt", ios::in);
        if (Myfile.is_open())
        {
            string line,s;
            int id;
            while (getline(Myfile, line))
            {
                stringstream x(line);
                getline(x, s, ' ');
                id = stoi(s);
                getline(x, s, ' ');
                Q[id].from_id = stoi(s);
                getline(x, s, ' ');
                Q[id].to_id = stoi(s);
                getline(x, s, '\n');
                Q[id].q = s;
                
            }
            Myfile.close();
        }
    }
    void download_Answers() {
        fstream Myfile;
        Myfile.open("Answers.txt", ios::in);
        if (Myfile.is_open())
        {
            string line, s;
            int id;
            while (getline(Myfile, line))
            {
                stringstream x(line);
                getline(x, s, ' ');
                id = stoi(s);
                getline(x, s, '\n');
                Answers[id] = s;
                is_answerd[id] = 1;
            }
            Myfile.close();
        }
    }
    void upload_Questions(question q,int Q_id){ 
        fstream Myfile;
        is_answerd[Q_id] = 0;
        Myfile.open("Question.txt", ios::app);
        if (Myfile.is_open())
        {
            Myfile << Q_id << ' ' << q.from_id << ' ' << q.to_id << ' ' << q.q << endl;
            Myfile.close();
        }
    }
    void upload_Answer(string Answer, int Q_id) {
        fstream Myfile;
        Myfile.open("Answers.txt", ios::app);
        if (Myfile.is_open())
        {
            Myfile << Q_id << ' ' << Answer << endl;
            Myfile.close();
        }
    }

    void delet_question_from_Qfile(int Q_id) {
        fstream Myfile;
        Myfile.open("Question.txt", ios::in);
        fstream temp_file("temp_file.txt", ios::out);
        string line,s;
        int id;
        while (getline(Myfile, line)) {
            stringstream x(line);
            getline(x, s, ' ');
            id = stoi(s);
            if (id != Q_id) {
                temp_file << line << endl;
            }
        }

        Myfile.close();
        temp_file.close();

        remove("Question.txt");
        rename("temp_file.txt", "Question.txt");
    }
    void delet_question_from_Afile(int Q_id) {
        fstream Myfile;
        Myfile.open("Answers.txt", ios::in);
        fstream temp_file("temp_file.txt", ios::out);
        string line, s;
        int id;
        while (getline(Myfile, line)) {
            stringstream x(line);
            getline(x, s, ' ');
            id = stoi(s);
            if (id != Q_id) {
                temp_file << line << endl;
            }
        }

        Myfile.close();
        temp_file.close();

        remove("Answers.txt");
        rename("temp_file.txt", "Answers.txt");
    }
};

bool validat_username(string username)
{
    if (username.size() < 6 || username.size() > 30)
        return false;
    if (!isalpha(username[0]))
        return false;
    for (char c : username) {
        if (!isalnum(c) && c != '_') {
            return false;
        }
    }
    return true;
}
bool validate_password(string password) {
    if (password.size() < 8) 
        return false;
    bool upper=0, lower=0, digit=0,special=0;
    for (char c : password)
    {
        if (isupper(c))upper = 1;
        if (islower(c))lower = 1;
        if (isdigit(c))digit = 1;
        if (ispunct(c))special = 1;
    }
    if (upper && lower && digit && special)return true;
    return false;
}

class User_Operation:public Data_base {
public:

    bool Login(string username,string pass){
        if (Username_Pass_mp.find(username)!=Username_Pass_mp.end()){
            if (Username_Pass_mp[username] == pass){
                return true;
            }
        }
        return false;
    }
    bool SignUp()
    {
        User user;
        cout << "Enter user name : ";
        cin >> user.username;
        if (!validat_username(user.username)||(Username_Pass_mp.find(user.username) != Username_Pass_mp.end()))
        {
            cout << "Invalid user name " << endl
                 << "Try again.." << endl;
            return false;
        }
        cout << "Enter password: ";
        cin >> user.pass;
        if (!validate_password(user.pass))
        {
            cout << "Invalid Password" << endl
                 << "Try again.." << endl;
            return false;
        }
        cout << "Enter email: ";
        cin >> user.email;
        cout << "Enter name: ";
        cin >> user.name;
        upload_User(user);
        return true;
    }

    void ask_question(int current_id,int Last_Qid,vector<pair<string,string>>&From_me_questions){
        string username,q;
        int Q_id=++Last_Qid;
        cout << "Enter the username of the user that you want to ask : ";
        cin >> username;
        if (username_Id_mp.find(username)!=username_Id_mp.end()) {
            cout << "Enter The Question : ";
            cin.ignore();
            getline(cin, q);
            Q[Q_id].from_id = current_id;
            Q[Q_id].to_id = username_Id_mp[username];
            Q[Q_id].q = q;
            upload_Questions(Q[Q_id], Q_id);
            From_me_questions.push_back({ q, username});
            cout << "Your question has been sent to the user you requested \n\n";
        }
        else {
            cout << "Sorry, the username you entered does not match any of our users \n\n";
        }
    }
    void answer_question(int Q_id){
        if (is_answerd[Q_id]) {
            cout << "\nWarning: Already answered.Answer will be updated\n";
        }
        string Answer;
        cout << "Answer : ";
        cin.ignore();
        getline(cin, Answer);
        Answers[Q_id] = Answer;
        upload_Answer(Answer, Q_id);
        is_answerd[Q_id] = 1;
    }
    void delet_question(int Q_id, int Q_number, vector<pair<string, string>>& From_me_questions) {
        is_answerd[Q_id] = 0;
        Q.erase(Q_id);
        auto it = From_me_questions.begin() + Q_number-1;
        From_me_questions.erase(it);
        delet_question_from_Qfile(Q_id);
        delet_question_from_Afile(Q_id);
        cout << "\nYour question has been deleted successfully.\n\n";
    }
};

class Users_Manager:public User_Operation {
public:
    User Current_user;
    int current_user_id,Last_Questionid;
    vector<pair<string,string>>To_Me_Questions, From_Me_Questions;
    map<int, int>ToMe_Q_number_id, FromMe_Q_number_id;
    void setLast_Questionid() {
        if (!Q.empty()) {
            Last_Questionid = Q.rbegin()->first;
        }
        else
            Last_Questionid = 0;
    }

    void List_Users() {
        int cnt = 1;
        for (auto it:Users_mp) {
            cout << cnt << ". " <<it.second.username << endl;
            cnt++;
        }
        cout << endl;
    }
    void List_Questions() {
        if (Q.size() == 0) {
            cout << "No Questions\n";
        }
        int cnt = 1;
        for (auto it:Q) {
            cout << "Question " << cnt << ". From(" << Users_mp[it.second.from_id].username << ") _ To(" << Users_mp[it.second.to_id].username<<')' << endl
                 << "Question : " << it.second.q << "?\t" << "Answer : " << ((is_answerd[it.first])?Answers[it.first]:"Not answer yet ") << ".\n\n";
            cnt++;
        }
        cout << endl;
    }

    void Fill_ToFrom_Me_Questions()
    {
        To_Me_Questions.clear();
        From_Me_Questions.clear();
        //for (auto it : Q)cout << it.first << ' ' << it.second.to_id << ' ' << it.second.from_id << it.second.q;
        for (auto it : Q) {
            if (it.second.to_id == current_user_id) {
                To_Me_Questions.push_back({ it.second.q ,Users_mp[it.second.from_id].username});
                ToMe_Q_number_id[To_Me_Questions.size()] = it.first;
            }
            if (it.second.from_id == current_user_id) {
                From_Me_Questions.push_back({ it.second.q, Users_mp[it.second.to_id].username });
                FromMe_Q_number_id[From_Me_Questions.size()] = it.first;
            }
            
        }
    }

    void List_From_me_Question() {
        if (From_Me_Questions.size() == 0)
            cout << "No Questions" << endl;
        for (int i = 1;i <= From_Me_Questions.size();i++) {
            cout << "Question " << i << ". To (" << From_Me_Questions[i - 1].second << ") : " << From_Me_Questions[i - 1].first << " ?" << endl
                << "Answer :";
            if (is_answerd[FromMe_Q_number_id[i]]) {
                cout << Answers[FromMe_Q_number_id[i]] << " ." << "\n\n";
            }
            else
                cout << "Not Answerd yet ." << "\n\n" ;
            cout << "\n";
        }
    }
    void List_To_me_Question() {
        if (To_Me_Questions.size() == 0)
            cout << "No Questions"<<endl ;
        for (int i = 1;i <= To_Me_Questions.size();i++)
        {
            cout << "Question " << i << ". From (" << To_Me_Questions[i - 1].second << ") : " << To_Me_Questions[i - 1].first << " ?" << endl
                << "Answer : ";
            if (is_answerd[ToMe_Q_number_id[i]]) {
                cout << Answers[ToMe_Q_number_id[i]] << " ." << "\n\n";
            }
            else
                cout << "Not Answerd yet ." << "\n\n";
        }
        cout << "\n";
    }

};

void Enter_system(Users_Manager &User){
    int option, Q_number;
    cout << "Enter Number in range 1 - 8 : ";
    cin >> option;
    cout << endl;
    if (option == 1){
            User.List_To_me_Question();
    }
    else if (option == 2){
            User.List_From_me_Question();
    }
    else if (option == 3) {
        User.List_Users();
        User.ask_question(User.current_user_id,User.Last_Questionid,User.From_Me_Questions);
    }
    else if (option == 4) {
        User.List_To_me_Question();
        if (!User.To_Me_Questions.size() == 0) {
            cout << "Enter The number of wanted Question : ";
            cin >> Q_number;
            if (Q_number > User.To_Me_Questions.size())
                cout << "Invaild number\n";
            User.answer_question(User.ToMe_Q_number_id[Q_number]);
            cout << "Question number " << Q_number << " has been answered successfully .\n\n";
        }
    }
    else if (option == 5) {
        User.List_From_me_Question();
        if (!User.From_Me_Questions.size() == 0) {
            cout << "Enter The number of wanted Question : ";
            cin >> Q_number;
            if (Q_number > User.From_Me_Questions.size())
                cout << "Invaild number\n";
            User.delet_question(User.FromMe_Q_number_id[Q_number], Q_number, User.From_Me_Questions);
        }
    }
    else if (option == 6) {
        User.List_Users();
    }
    else if (option == 7) {
        User.List_Questions();
    }
    else if (option == 8) {
        cout << "Loggedout Successfully!\n";
        return;
    }
    else {
        cout << "invalid number...Try again" << endl;
    }
    Enter_system(User);
}

void PrintMenu() {
    cout << "Menu: " << endl
        << "1. Print Questions To me " << endl
        << "2. Print Questions From me " << endl
        << "3. Ask Question " << endl
        << "4. Answer Question " << endl
        << "5. Delete Question " << endl
        << "6. List System Users" << endl
        << "7. Feed" << endl
        << "8. Logout \n\n";
}

void mainmenu(Users_Manager &service) {
    int option;
    Users_Manager user;
    cout << "Menu :" << endl
        << "1: Login" << endl
        << "2: Sign Up" << endl;
    cout << "Enter Number in range 1 - 2 : ";
    cin >> option;
    cout << endl;
    if (option == 1)
    {
        cout << "Enter username: ";
        cin >> user.Current_user.username;
        cout << "Enter password: ";
        cin >> user.Current_user.pass;
        if (service.Login(user.Current_user.username, user.Current_user.pass))
        {
            service.Current_user = user.Current_user;
            user = service;
            int id = user.username_Id_mp[user.Current_user.username];
            user.current_user_id = id;
            user.Current_user = service.Users_mp[id];
            user.Fill_ToFrom_Me_Questions();
            cout << "\nLogin Successfully!\n\n";
            PrintMenu();
            Enter_system(user);
            service = user;
        }
        else
            cout << "Wrong user name or password." << endl;
    }
    else if (option == 2)
    {
        if (service.SignUp())
        {
            user = service;
            user.download_Questions();
            cout << "Signed up Successfully!" << endl;
            PrintMenu();
            Enter_system(user);
            service = user;
        }
    }
    else
        cout << "invalid number...Try again" << endl;
    mainmenu(service);
}
Users_Manager Run_System() {
    Users_Manager Service;
    Service.download_Users();
    Service.download_Users_username();
    Service.download_Users_id();
    Service.download_Answers();
    Service.download_Questions();
    Service.setLast_Questionid();
    return Service;
}
int main()
{
    Users_Manager service=Run_System();
    mainmenu(service);
}
