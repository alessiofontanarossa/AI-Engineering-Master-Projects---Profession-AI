////////////////////////////// README SECTION //////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Questa sezione e' riservata alla documentazione del codice, ed e' scritta (qui) per il Coach. In uno use-case reale, potrebbe contenere il manuale d'uso del software per l'utente finale (che sarebbe scritto in un file txt esterno, ad esempio).

// ------------------------------------------- Per il Coach: -------------------------------------------

// Il codice e' stato pensato e scritto interamente da me, senza copiare o adattare codice da fonti esterne. Ho seguito le best practices di programmazione in C++(14), inserendo commenti esplicativi.
// Inoltre il codice e' stato pensato per essere facilmente estendibile in futuro aggiungendo nuove funzionalita'. Quest'ultimo aspetto e' necessario per un software reale che richiede aggiornamenti nel tempo.
// A tale scopo, ho usato classi per rappresentare i concetti principali (Client, Interaction, DataBase) e metodi per incapsulare le funzionalita' associate a ciascuna classe. Rispetto alle linee guida del progetto,
// ho aggiunto alcune funzionalita' (minori) extra, cercando di immedesimarmi nel bisogno dell'utente finale. Per esempio, ho immaginato che un agente possa volere eliminare i meetings una volta completati, per tenere
// il database piu' ordinato. Oppure, ho pensato che un agente possa volere cercare un cliente non solo per nome e cognome, ma anche per altri attributi come indirizzo o email, per facilitare la ricerca in caso di omonimia,
// o di errori. Per esempio, se un agente ha digitato male il nome o cognome di un cliente, potrebbe comunque trovarlo cercando l'indirizzo email o la data di nascita durante il colloquio con il cliente stesso. La lettura e
// scrittura del file avviene su un csv che ha un formato prestabilito (si veda il csv allegato in zip come esempio, oppure la parte di scrittura su file alla fine del main).

// ------------------------------------------- Manuale d'uso del software: -------------------------------------------

// Questo programma e' un database per un'agenzia di assicurazioni, che permette di gestire i clienti (incluse le informazioni personali come nome, cognome, indirizzo, email, telefono, data di nascita e da quando e' cliente)
// e le loro interazioni (incontri e contratti). Ad ogni cliente e' associato in modo automatico un ID univoco, per faciltarne la gestione. Questo ID viene aggiornato automaticamente in caso di aggiunta o rimozione di un cliente,
// e serve per gestire l'eventualita' di omonimia tra clienti (stesso nome e cognome). Inoltre velocizza molte funzionalita', perche' puo' essere usato come indice per accedere direttamente al cliente desiderato senza dover immettere
// tutte le sue informazioni personali (che potrebbero non essere univoche).

// L'utente ha diverse opzioni per gestire il database, tra cui:

// 1. Visualizzare il numero totale di clienti.
// 2. Aggiungere un nuovo cliente al database.
// 3. Visualizzare le informazioni di tutti i clienti o degli ultimi N clienti.
// 4. Modificare le informazioni di un cliente specifico.
// 5. Rimuovere un cliente dal database.
// 6. Cercare le informazioni di un cliente specifico in base a vari attributi.
// 7. Gestire le interazioni (incontri e contratti) di un cliente specifico.

// Le opzioni di utilizzo vengono mostrate ad ogni interazione con il programma, cosicche' l'utente non debba memorizzarle. Inoltre, dal menu' principale, e' semore possibile premere 'help' o 'manual' per 
// mostrare il manuale d'uso. Il programma guida l'utente nelle varie operazioni, richiedendo le informazioni necessarie passo 
// dopo passo. Ad ogni passo, viene effettuato un accurato controllo di validita' dell'input, per evitare errori e garantire un'esperienza utente fluida e sicura. Nota Bene: tutti gli input devono essere digitati lower-case,
// e non devono contenere nessuna virgola ',' o punto e virgola ';'.

// All'apertura del programma, viene tentato il caricamento di un database salvato in precedenza. Se il file non viene trovato, ne viene creato uno. All'uscita, ottenuta attraverso il comando 'quit', il database viene salvato automaticamente. Nota Bene: l'utente puo' 
// chiudere il programma **in qualsiasi momento** digitando 'quit'. In questo modo, anche se l'utente si trova nel mezzo di un'operazione (ad esempio, l'aggiunta di un nuovo cliente), il programma termina in modo sicuro,
// salvando il database prima di uscire.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

////////////////////////////// CLASS DEFINITIONS //////////////////////////////

class Interaction{
    public:
        vector<string> meetings, contracts;
        Interaction(){ // default constructor
            meetings = {};
            contracts = {};
        };
        Interaction(vector<string> _meetings, vector<string> _contracts){ // specific constructor
            meetings = _meetings;
            contracts = _contracts;
        };
        void add_meeting(string new_meeting){ // function to add a new meeting
            meetings.push_back(new_meeting);
        };
        void add_contract(string new_contract){ // function to add a new meeting
            contracts.push_back(new_contract);
        };
        void print_meetings(){ // function to print all meetings
            for(int i = 0; i < meetings.size(); i++){
                cout <<"Meeting " << i+1 <<" : " << meetings[i] << endl;
            };
        };
        void print_contracts(){ // function to print all contracts
            for(int i = 0; i < contracts.size(); i++){
                cout <<"Contract " << i+1 <<" : " << contracts[i] << endl;
            };
        };
        void clear_meetings(){ // function to clear the mettings list once done all meetings are completed
            meetings.clear();
        };
};

class Client{
    public:
        int effective_ID = -1; // defalut value is undefined
        string name, surname, address, email, phone, birth_date, client_from;
        Interaction interaction;

        Client(){ // default constructor
            name = "John";
            surname = "Doe";
            address = "unknown";
            email = "unknown@gmail.com";
            phone = "unknown";
            birth_date = "unknown";
            client_from = "unknown";
            interaction = Interaction();
        };
        Client(string _name, string _surname, string _address, string _email, 
               string _phone, string _birth_date, string _client_from, 
               Interaction _interaction = Interaction()){ // specific constructor
            name = _name;
            surname = _surname;
            address = _address;
            email = _email;
            phone = _phone;
            birth_date = _birth_date;
            client_from = _client_from;
            interaction = _interaction;
        };

        /////////////////////////////// INTERACTIONS ///////////////////////////////

        void add_meeting(string new_meeting){ // function to add a new meeting
            interaction.add_meeting(new_meeting);
        };
        void add_contract(string new_contract){ // function to add a new contract
            interaction.add_contract(new_contract);
        };
        void print_meetings(){ // function to print all meetings
            interaction.print_meetings();
        };
        void print_contracts(){ // function to print all contracts
            interaction.print_contracts();
        };
        void clear_meetings(){ // function to clear the mettings list once done all meetings are completed
            interaction.clear_meetings();
        };
};

class DataBase{
    public:
        int db_ID; // database identification number
        vector<Client*> clients;

        DataBase(){ // default constructor, if the insurance agency has no clients yets
            db_ID = -1; // -1 for an empty database
            clients = {};
        };
        DataBase(vector<Client*> _clients){ // specific constructor, if the insurance agency already has some clients
            clients = _clients;
            for(db_ID = 0; db_ID < clients.size(); db_ID++){     
                clients[db_ID]-> effective_ID = db_ID +1; // this modifies the effective:ID attribute of each client in the database
            };
        };

        ~DataBase(){
            for (Client* c : clients) {
                delete c;
            }
        };

        void how_many_clients(){ // function to check the number of clients in the database
            cout << endl;
            cout << "Number of clients: " << clients.size() << endl << endl;
        };

        /////////////////////////////// ADD CLIENTS ///////////////////////////////

        bool client_exists(Client* new_client){ // function to check if a client is already in the database using some of the client's useful/unique information
            for(int i = 0; i < clients.size(); i++){
                if(new_client -> name == clients[i] -> name &&
                    new_client -> surname == clients[i] -> surname &&
                   new_client -> address == clients[i] -> address &&
                   new_client -> birth_date == clients[i] -> birth_date &&
                   new_client -> client_from == clients[i] -> client_from){
                    return true;
                }
            }
            return false;
        };
        void add_client(Client* new_client){ // function to add a new client to the database, if not already present
            if (client_exists(new_client)){
                cout << endl;
                cout << "This user is already a client." << endl << endl;
            }else{
                clients.push_back(new_client);
                new_client -> effective_ID = clients.size();
                cout << endl;
                cout << "Client with ID " << clients.size() << " correctly added." << endl << endl;
            };
        };
        void add_client_from0(Client* new_client){ // function to add a new client to the database, if not already present, when opening the database
            if (client_exists(new_client)){
                return;
            }else{
                clients.push_back(new_client);
                new_client -> effective_ID = clients.size();
            };
        };

        /////////////////////////////// VISUALIZE CLIENTS ///////////////////////////////

        void print_client_by_c(Client* client){ // function to print client information using the Client object
            cout << endl;
            cout << "Client ID: " << client->effective_ID<< endl;
            cout << "Name: " << client -> name << endl;
            cout << "Surname: " << client -> surname << endl;
            cout << "Address: " << client -> address << endl;
            cout << "Email: " << client -> email << endl;
            cout << "Phone: " << client -> phone << endl;
            cout << "Birth Date: " << client -> birth_date << endl;
            cout << "Client From: " << client -> client_from << endl << endl;
        };
        void print_all_clients(){ // function to print all clients information
            for(int i = 0; i < clients.size(); i++){
                print_client_by_c(clients[i]);
            };
        };
        void print_last(int n){ // function to print last n clients information
            if(n > clients.size()){
                cout << endl;
                cout << "There are only " << clients.size() << " clients in the database. " << endl << endl;
                return;
            };
            for(int i = clients.size()-n; i < clients.size(); i++){
                cout << endl;
                print_client_by_c(clients[i]);
            };
        };

        /////////////////////////////// MODIFY CLIENTS ///////////////////////////////

        bool validate_field(string field){ // function to validate the input field in the next functions
            vector<string> valid_fields = {"name", "surname", "address", "email", "phone", "birth_date", "client_from"};
            for(int i = 0; i < valid_fields.size(); i++){
                if(field == valid_fields[i]){
                    return true;
                };
            };
            return false;
        };

        void mod_client(int client_ID, string field, string new_info){ // function to modify a client's information, searching by effective_ID, because name and surname may be not unique
            bool is_valid_field = validate_field(field);
            if(is_valid_field == false){
                cout << endl;
                cout << "Field " << field << " not found." << endl << endl;
                return;
            };
            for(int db_index = 0; db_index < clients.size(); db_index ++){
                if(clients[db_index] -> effective_ID == client_ID){
                    if(field == "name"){
                        clients[db_index] -> name = new_info;
                    }else if(field == "surname"){
                        clients[db_index] -> surname = new_info;
                    }else if(field == "address"){
                        clients[db_index] -> address = new_info;
                    }else if(field == "email"){
                        clients[db_index] -> email = new_info;
                    }else if(field == "phone"){
                        clients[db_index] -> phone = new_info;
                    }else if(field == "birth_date"){
                        clients[db_index] -> birth_date = new_info;
                    }else if(field == "client_from"){
                        clients[db_index] -> client_from = new_info;
                    }
                    cout << endl;
                    cout << "Client with ID " << client_ID << " correctly modified." << endl << endl;
                    return;
                };
            };
        };
        
        /////////////////////////////// REMOVE CLIENTS ///////////////////////////////

         void remove_client(int client_ID){ // remove a client by effective_ID, because name and surname may be not unique
            for(int db_index = 0; db_index < clients.size(); db_index ++){
                if(clients[db_index]->effective_ID == client_ID){
                    delete clients[db_index];
                    clients.erase(clients.begin() + db_index);
                    cout << endl;
                    cout << "Client with ID " << client_ID << " correctly removed." << endl << endl;
                    for(int j = db_index; j < clients.size(); j++){ // update effective_IDs from the removed one, necessary to use all the for cycles
                        clients[j]->effective_ID = j + 1;
                    };
                    return;
                };
   
            };
        };
        
        /////////////////////////////// SEARCH CLIENTS BY NAME, SURNAME, AND MORE! ///////////////////////////////

        void print_client_by_string(string field, string attribute){ // function to search information about one (or more) clients by name, surname, and so on
            bool is_valid_field = validate_field(field);
            if(is_valid_field == false){
                cout << endl;
                cout << "Field " << field << " not found." << endl << endl;
                return;
            };

            bool found_match_at_least = false;
            for(int db_index = 0; db_index < clients.size(); db_index++){
                bool match = false;
                if(field == "name" && clients[db_index] -> name == attribute){match = true;}
                else if(field == "surname" && clients[db_index] -> surname == attribute){match = true;}
                else if(field == "address" && clients[db_index] -> address == attribute){match = true;}
                else if(field == "email" && clients[db_index] -> email == attribute){match = true;}
                else if(field == "phone" && clients[db_index] -> phone == attribute){match = true;}
                else if(field == "birth_date" && clients[db_index] -> birth_date == attribute){match = true;}
                else if(field == "client_from" && clients[db_index] -> client_from == attribute){match = true;}

                if(match){
                    print_client_by_c(clients[db_index]);
                    found_match_at_least = true;
                }
            };
            if(found_match_at_least == false){
                cout << endl;
                cout << "Client with ( " << field << " = " << attribute << " ) not found." << endl << endl;
            }
        };
        
        ///////////////////////////// INTERACTIONS ///////////////////////////////

        bool validate_interaction(string field){ // function to validate the interaction field in the next functions
            vector<string> valid_fields = {"meeting", "contract"};
            for(int i = 0; i < valid_fields.size(); i++){
                if(field == valid_fields[i]){
                    return true;
                };
            };
            return false;
        };

        void add_interaction_to_client(int client_ID, string field, string interaction){ // function to add an interaction given the client ID
            bool is_valid_field = validate_interaction(field);
            if(is_valid_field == false){
                cout << endl;
                cout << "The interaction " << field << " is not valid." << endl << endl;
                return;
            };
            for(int db_index = 0; db_index < clients.size(); db_index ++){
                if(clients[db_index] -> effective_ID == client_ID){
                    if(field == "meeting"){
                        clients[db_index] -> add_meeting(interaction);
                    }else if(field == "contract"){
                        clients[db_index] -> add_contract(interaction);
                    }
                    cout << endl;
                    cout << "Interaction (" << field << ") correctly added to client with ID " << client_ID << "." << endl << endl;
                    return;
                };
            };
        };

        void remove_mettings_from_client(int client_ID){ // function to remove all meetings from a client given the client ID
            for(int db_index = 0; db_index < clients.size(); db_index ++){
                if(clients[db_index] -> effective_ID == client_ID){
                    clients[db_index] -> clear_meetings();
                    cout << endl;
                    cout << "All meetings correctly removed from client with ID " << client_ID << "." << endl << endl;
                    return;
                };
            };
        };

        void print_interactions_of_clients(int client_ID){ // function to print all interactions of a client with a given ID
            for(int db_index = 0; db_index < clients.size(); db_index ++){
                if(clients[db_index] -> effective_ID == client_ID){
                    cout << endl;
                    cout << "#######################################################################################" << endl << endl;
                    cout << "------------------------ " << "Meetings of client " << clients[db_index] -> name << " " << clients[db_index] -> surname <<  " (ID " << client_ID << ") ------------------------ " << endl << endl;
                    clients[db_index] -> print_meetings();
                    cout << endl;
                    cout << "------------------------ " << "Contracts of client " << clients[db_index] -> name << " " << clients[db_index] -> surname <<  " (ID " << client_ID << ") ------------------------ " << endl << endl;
                    clients[db_index] -> print_contracts();
                    cout << endl;
                    cout << "#######################################################################################" << endl << endl;
                    return;
                };
            };
        };
};

////////////////////////////// FUNCTION DECLARATIONS //////////////////////////////

bool validate_menu_option(string option);
bool validate_number(string n_str);
void print_menu();
vector<string> split_line_comma(string line);
vector<string> split_line_semicolon(string line);
void print_goodbye_message();
void print_welcome_message();
void print_manual();

////////////////////////////// MAIN //////////////////////////////

int main(){
    //////// EXAMPLE OF CLASS CREATION ////////
    // Interaction inter({"meeting1", "meeting2"}, {"contract11"});
    // Client* c = new Client("name", "surn", "addr", "email", "phone", "birth", "client_from", inter);
    ///////////////////////////////////////////
    // Interaction inter1({"meeting1", "meeting2"}, {"contract11"});
    // Client* c1 = new Client("nome1", "sur1", "indi1", "email1", "phone1", "birth1", "client_from1", inter1);
    DataBase db;

    print_welcome_message();

    //////// OPENING THE CSV ////////

    string filename = "database.csv";
    ifstream fin(filename);
    if(fin.is_open()){
        cout << "Database opened successfully." << endl << endl;
    }else{
        cout << "Error opening the database. Creating a new database..." << endl << endl;
        ofstream outfile(filename);
        cout << "Database created correctly." << endl << endl;
    };

    //////// POPULATING THE DATABASE ////////

    string line;
    while(getline(fin, line)){
        if(line.empty()){
            continue;
        }
        vector<string> splitted_client_info = split_line_comma(line);
        if(splitted_client_info.size() < 7){
            continue;
        };
        vector<string> meetings = split_line_semicolon(splitted_client_info[7]);
        vector<string> contracts = split_line_semicolon(splitted_client_info[8]);
        Interaction inter({},{});
        for(int i = 0; i < meetings.size(); i++){
            inter.add_meeting(meetings[i]);
        };
        for(int i = 0; i < contracts.size(); i++){
            inter.add_contract(contracts[i]);
        };
        Client* c = new Client(splitted_client_info[0], splitted_client_info[1], splitted_client_info[2], splitted_client_info[3], splitted_client_info[4], splitted_client_info[5], splitted_client_info[6], inter);
        db.add_client_from0(c);
    };
    fin.close();
    cout << "Database loaded correctly with " << db.clients.size() << " clients loaded. All information are now available to the user." << endl << endl;

   //////// START EXECUTION OF SOFTWARE ////////

    bool execution = true;
    while(execution){
        print_menu();
        string user_input;
        getline(cin, user_input);
        if(validate_menu_option(user_input) == false){
            cout << endl;
            cout << "Option " << user_input << " not valid. Please try again." << endl << endl;
            continue;
        };
        if(user_input == "quit"){
            execution = false;
            print_goodbye_message();
        }

        else if (user_input == "help" || user_input == "manual"){ // View the user manual.
            print_manual();
        }
        
        else if(user_input == "1"){ // View the total number of clients.
            db.how_many_clients();
        }
        
        else if(user_input == "2"){ // Add a new client to the database.
            vector<string> client_attributes = {};
            vector<string> ask_attributes = {"Name: ", "Surname: ", "Address: ", "Email: ", "Phone: ", "Birth Date: ", "Client From: "};
            cout << endl;
            cout << "Enter the following information about the new client:" << endl << endl;
            
            for(int i = 0; i < ask_attributes.size(); i++){
                string user_input;
                cout << ask_attributes[i];
                getline(cin, user_input);
                if(user_input == "quit"){
                    execution = false;
                    print_goodbye_message();
                    break;
                }
                else{
                    client_attributes.push_back(user_input);
                };
            };

            if(execution == false){
                continue; 
            };

            Client* new_client = new Client(client_attributes[0], client_attributes[1], client_attributes[2], client_attributes[3], client_attributes[4], client_attributes[5], client_attributes[6]);
            db.add_client(new_client);
        }
        
        else if(user_input == "3.1"){ // Print all client's information.
            db.print_all_clients();
        }
        
        else if(user_input == "3.2"){ // Print last N client's information.
            cout << endl;
            string n_str;
            cout << "Enter the number of last clients to view: ";
            getline(cin, n_str);
            if(n_str == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            if(validate_number(n_str) == false){
                cout << endl;
                cout << "The input " << n_str << " is not a valid number. Please try again." << endl << endl;
                continue;
            };
            int n = stoi(n_str);
            db.print_last(n);
        }
        
        else if(user_input == "4"){ // Edit a client's information.
            cout << endl;
            string client_ID_str, field, new_info;
            cout << "Enter the client ID to modify: ";
            getline(cin, client_ID_str);
            if(client_ID_str == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            if(validate_number(client_ID_str) == false){
                cout << endl;
                cout << "The input " << client_ID_str << " is not a valid number. Please try again." << endl << endl;
                continue;
            };
            int client_ID = stoi(client_ID_str);
            if(client_ID < 1 || client_ID > db.clients.size()){
                cout << endl;
                cout << "Client with ID " << client_ID << " not found. Please try again." << endl << endl;
                continue;
            };
            cout << "Enter the field to modify (name, surname, address, email, phone, birth_date, client_from): ";
            getline(cin, field);
            if(field == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            cout << "Enter the new information: ";
            getline(cin, new_info);
            if(new_info == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            db.mod_client(client_ID, field, new_info);
        }
        
        else if(user_input == "5"){ // Remove a client from the database.
            cout << endl;
            string client_ID_str;
            cout << "Enter the client ID to remove: ";
            getline(cin, client_ID_str);
            if(client_ID_str == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            if(validate_number(client_ID_str) == false){
                cout << endl;
                cout << "The input " << client_ID_str << " is not a valid number. Please try again." << endl << endl;
                continue;
            };
            int client_ID = stoi(client_ID_str);
            if(client_ID < 1 || client_ID > db.clients.size()){
                cout << endl;
                cout << "Client with ID " << client_ID << " not found. Please try again." << endl << endl;
                continue;
            };
            db.remove_client(client_ID);
        }
        
        else if(user_input == "6"){ // Search the information of a specific client. 
            cout << endl;
            string field, attribute;
            cout << "Enter the field to search by (name, surname, address, email, phone, birth_date, client_from): ";
            getline(cin, field);
            if(field == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            cout << "Enter the attribute to search for: ";
            getline(cin, attribute);
            if(attribute == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            db.print_client_by_string(field, attribute);
        }
        
        else if(user_input == "7.1"){ // View meetings and contracts of a specific client.
            cout << endl;
            string client_ID_str;
            cout << "Enter the client ID to view interactions: ";
            getline(cin, client_ID_str);
            if(client_ID_str == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            if(validate_number(client_ID_str) == false){
                cout << endl;
                cout << "The input " << client_ID_str << " is not a valid number. Please try again." << endl << endl;
                continue;
            };   
            int client_ID = stoi(client_ID_str);
            if(client_ID < 1 || client_ID > db.clients.size()){
                cout << endl;
                cout << "Client with ID " << client_ID << " not found. Please try again." << endl << endl;
                continue;
            };
            db.print_interactions_of_clients(client_ID);
        }
        
        else if(user_input == "7.2"){ // Add a new interaction (meeting or contract) to a specific client.
            cout << endl;
            string client_ID_str, field, interaction;
            cout << "Enter the client ID to add an interaction: ";
            getline(cin, client_ID_str);
            if(client_ID_str == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            if(validate_number(client_ID_str) == false){
                cout << endl;
                cout << "The input " << client_ID_str << " is not a valid number. Please try again." << endl << endl;
                continue;
            };   
            int client_ID = stoi(client_ID_str);
            if(client_ID < 1 || client_ID > db.clients.size()){
                cout << endl;
                cout << "Client with ID " << client_ID << " not found. Please try again." << endl << endl;
                continue;
            };
            cout << "Enter the type of interaction to add ('meeting' or 'contract'): ";
            getline(cin, field);
            if(field == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            cout << "Enter the " << field << " details: ";
            getline(cin, interaction);
            if(interaction == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            db.add_interaction_to_client(client_ID, field, interaction);
        }
        
        else if(user_input == "7.3"){ // Remove all meetings from a specific client.
            cout << endl;
            string client_ID_str;
            cout << "Enter the client ID to remove all meetings: ";
            getline(cin, client_ID_str);
            if(client_ID_str == "quit"){
            execution = false;
            print_goodbye_message();
            break;}
            if(validate_number(client_ID_str) == false){
                cout << endl;
                cout << "The input " << client_ID_str << " is not a valid number. Please try again." << endl << endl;
                continue;
            };
            int client_ID = stoi(client_ID_str);
            if(client_ID < 1 || client_ID > db.clients.size()){
                cout << endl;
                cout << "Client with ID " << client_ID << " not found. Please try again." << endl << endl;
                continue;
            };
            db.remove_mettings_from_client(client_ID);
        };
    };

    //////// POPULATING THE CSV WITH NEW DATA ////////
    
    ofstream fout(filename);
    if(fout.is_open()){
        for(int i = 0; i < db.clients.size(); i++){ // writing from zero, because some client's information could have been change
            fout << db.clients[i] -> name << ',' << db.clients[i] -> surname << ',' << db.clients[i] -> address << ',' << db.clients[i] -> email << ',';
            fout << db.clients[i] -> phone << ',' << db.clients[i] -> birth_date << ',' << db.clients[i] -> client_from << ',';
            for(int j =0; j < (db.clients[i] -> interaction.meetings).size(); j++){
                fout << db.clients[i] -> interaction.meetings[j] << ';' ;
            };
            fout << ',';
            for(int j =0; j < (db.clients[i] -> interaction.contracts).size(); j++){
                fout << db.clients[i] -> interaction.contracts[j] << ';' ;
            };
            fout << ',';
            fout << endl << endl;;
        };
        cout << "Database saved correctly." << endl << endl;
    ;}else{
        cout << "Unable to save the Database." << endl << endl;
    };
    return 0;
}

////////////////////////////// DEBUGGING SECTION //////////////////////////////
// 1. funziona
// 2. funziona: - quit
//              - aggiunta cliente duplicato  
//              - aggiunta cliente nuovo    
// 3.1 funziona
// 3.2 funziona: - quit
//               - input non numerico
//               - n maggiore del numero di clienti 
//               - n valido
// 4 funziona: - quit 
//             - numero 0 o maggiore del numero di clienti
//             - ID non numerico
//             - ID numerico valido:
//                 - field non valido
//                 - field valido: 
//                     - nuova informazione
// 5 funziona: - quit
//             - ID non numerico
//             - ID numerico valido:
//                 - numero 0 o maggiore del numero di clienti
//                 - rimozione cliente
// 6 funziona: - quit
//             - field non valido
//             - field valido:
//                 - scelta dell'attribute
//                     - nessun match
//                     - uno o piu' match
// 7.1 funziona: - quit
//               - ID non numerico
//               - ID numerico valido:
//                   - numero 0 o maggiore del numero di clienti
//                   - stampa interazioni
// 7.2 funziona: - quit
//               - ID non numerico
//               - ID numerico valido:
//                   - numero 0 o maggiore del numero di clienti
//                   - field (meeting o contract) non valido
//                   - aggiunta interazione
// 7.3 funziona: - quit
//               - ID non numerico
//               - ID numerico valido:
//                   - numero 0 o maggiore del numero di clienti
//                   - rimozione meetings
////////////////////////////// END OF DEBUGGING SECTION ////////////////////////////

////////////////////////////// FUNCTION DEFINITIONS //////////////////////////////

bool validate_menu_option(string option){
    vector<string> valid_options = {"quit", "1", "2", "3.1", "3.2", "4", "5", "6", "7.1", "7.2", "7.3", "help", "manual"};
    for(int i = 0; i < valid_options.size(); i++){
        if(option == valid_options[i]){
            return true;
        };
    };
    return false;
};

bool validate_number(string n_str){
    try{
        stoi(n_str); 
        return true;
    }catch(invalid_argument&){
        return false;
    };
};

void print_menu(){
    cout << "Please select a number (or 'quit') from the menu below:" << endl;
    cout << endl;
    cout << " 'quit' : Exit and save the database." << endl;
    cout << " '1' : View the total number of clients." << endl;
    cout << " '2' : Add a new client to the database." << endl;
    cout << " '3.1' : Print all client's information." << endl;
    cout << " '3.2' : Print last N client's information." << endl;
    cout << " '4' : Edit a client's information." << endl;
    cout << " '5' : Remove a client from the database." << endl;
    cout << " '6' : Search the information of a specific client." << endl;
    cout << " '7.1' : View meetings and contracts of a specific client." << endl;
    cout << " '7.2' : Add a new interaction (meeting or contract) to a specific client." << endl;
    cout << " '7.3' : Remove all meetings from a specific client." << endl;  
    cout << " 'help' or 'manual': View the user manual." << endl << endl;
};

vector<string> split_line_comma(string line){
    vector<string> parsed_line;
    int auxiliary_pos = 0;

    for(int pos = 0; pos < line.size(); pos++){
        if(line[pos] == ','){
            parsed_line.push_back(line.substr(auxiliary_pos, pos - auxiliary_pos));
            auxiliary_pos = pos +1;
        };
    }
    return parsed_line;
};

vector<string> split_line_semicolon(string line){
    vector<string> parsed_line;
    int auxiliary_pos = 0;

    for(int pos = 0; pos < line.size(); pos++){
        if(line[pos] == ';'){
            parsed_line.push_back(line.substr(auxiliary_pos, pos - auxiliary_pos));
            auxiliary_pos = pos +1;
        };
    }
    return parsed_line;
};

void print_goodbye_message(){
    cout << endl;
    cout << "Thank you for using the Insurance Agency Client Database." << endl << endl;
};

void print_welcome_message(){
    cout << endl;
    cout << "Welcome to the Insurance Agency Client Database!" << endl;
    cout << "You can manage your clients and their interactions with this application, or quit the program by pressing 'quit' any time." << endl << endl;
};

void print_manual(){
    // Prints the user manual
    cout << endl;
    cout << "User Manual:" << endl;
    cout << "This application allows you to manage a database of clients for an insurance agency." << endl;
    cout << "You can add, modify, remove, and search for clients, as well as manage their interactions (meetings and contracts)." << endl;
    cout << "At any time, you can exit the program by typing 'quit', which will save the current state of the database." << endl << endl;   
};