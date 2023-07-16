#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

using namespace std;

class Planet{
    public:
        string Planet_name;
        double Position_x;
        double Position_y;
        double Position_z;

        Planet(string name, double x, double y, double z) {
            this->Planet_name = name;
            this->Position_x = x;
            this->Position_y = y;
            this->Position_z = z;
        }

        void setName(string name){
            Planet_name = name;
        }

        void setX(double x){
            Position_x = x;
        }

        void setY(double y){
            Position_y = y;
        }

        void setZ(double z){
            Position_z = z;
        }

        string getName() {
            return Planet_name;
        }

        double getX(){
            return Position_x;
        }

        double getY(){
            return Position_y;
        }

        double getZ(){
            return Position_z;
        }

        void getCoordinates() {
            cout << "Coordinates of planet " << Planet_name << ": (" << Position_x << ", " << Position_y << ", " << Position_z << ")" << endl;
        }
};

class moon : public Planet{

    public:
        int atmosphere;
        int waterlevel;
        void create_moon(int atmosphere, int waterlevel){
            this->atmosphere = atmosphere;
            this->waterlevel = waterlevel;
        }
        int getatmosphere(){
            return atmosphere;
        }
        int getwaterlevel(){
            return waterlevel;
        }
};

class mars : public Planet{
    public:
        int inhabitants;
        int waterlevel;
        void create_mars(int inhabitants, int waterlevel){
            this->inhabitants = inhabitants;
            this->waterlevel = waterlevel;
        }
        int getinhabitants(){
            return inhabitants;
        }
        int getwaterlevel(){
            return waterlevel;
        }
};

class earth : public Planet{
    public:
        int landlevel;
        int waterlevel;
        void create_earth(int landlevel, int waterlevel){
            this->landlevel = landlevel;
            this->waterlevel = waterlevel;
        }
        int getlandlevel(){
            return landlevel;
        }
        int getwaterlevel(){
            return waterlevel;
        }
};

class Traveller{
    protected:
        int trav_id;
    
    public:
        string name;
        vector <int> list_of_tckts;
        string inp_id; 
        static int count_id;

        string getName(){
            return name;
        }

        int get_trav_ID(){
            return trav_id;
        }
        
        string get_inp_id(){
            return inp_id;
        }

        void update_id(int new_id){
            this->inp_id = new_id;
        }

        void get_ticket(int id, string name);
};

int Traveller::count_id = 0;

class Passenger : public Traveller{
    int validity;

    public:
        Passenger(string name, string self_id){
            this->name = name;
            this->inp_id = self_id;
            count_id++;
        }  
        void setID(){
            trav_id = count_id;
        }  
};

class Astronaut : public Traveller{
    private :
        int Exp;

    public:

        void push_Astronaut(Astronaut* astronaut);

        Astronaut(string name, string self_id, int exp){
            this->name = name;
            this->Exp = exp;
            this->inp_id = self_id;
            count_id++;
            push_Astronaut(this);
        }    
        void setID(){
            trav_id = count_id;
        }
};

vector <Astronaut*> list_of_astronauts;

void Astronaut::push_Astronaut(Astronaut* astronaut){
    list_of_astronauts.push_back(astronaut);
}

class Commander : public Traveller{
    private:
        int Authority;

    public:
        friend class SpaceTravel;
        int Experience;
        int License_ID;

        void push_Commander(Commander* commander);

        Commander(string name, string self_id, int exp){
                this->name = name;
                this->Experience = exp;
                this->inp_id = self_id;
                count_id++;
                push_Commander(this);
        }    

        void setID(){
            trav_id = count_id;
        }
};

vector <Commander*> list_of_commanders;

void Commander::push_Commander(Commander* commander){
    list_of_commanders.push_back(commander);
}

class Ticket{
    int price;

    public:
        Traveller* traveller;
        Planet* Source;
        Planet* Dest;
        int id;
        int day;
        int month;
        int year;
        int validity;
        static int ticket_id;
        bool Return_ticket;
        bool is_valid;

        void push_ticket(Ticket* ticket);

        Ticket(Planet* Source, Planet* Dest, int day, int month, int year, bool Return_ticket, Traveller* traveller){
            this->traveller = traveller;
            this->Source = Source;
            this->Dest = Dest;
            this->day = day;
            this->month = month;
            this->year = year;
            this->Return_ticket = Return_ticket;
            ticket_id++;
            this->id = ticket_id;
            validity = 10;
            is_valid = true;
            push_ticket(this);
        }

        int setvalidity(int val){
            validity = val;
        }

        void verify(){
            if (validity > 0 && validity <= 10)
                is_valid = true;
            else
                is_valid = false;
        }

        int setis_valid(bool valid){
            is_valid = valid;
        }
        
        Ticket* find_ticket(int tckid);

        void push_tck(Traveller* traveller, Ticket* ticket){
            (traveller->list_of_tckts).push_back(ticket_id);
        };

        void cancel_ticket(int ticket_id);

        void cancel_ticket(Ticket* ticket){
            delete this;
            cout<<"Your ticket has been deleted."<<endl;
        }

        void update_ticket(int ticket_id, Planet* Source, Planet* Dest, int day, int month, int year,bool Return_ticket, Traveller* traveller){
            Ticket* tck = find_ticket(ticket_id);
            tck->traveller = traveller;
            tck->Source = Source;
            tck->Dest = Dest;
            tck->day = day;
            tck->month = month;
            tck->year = year;
            tck->Return_ticket = Return_ticket;
        }

        void update_ticket(Ticket* ticket, Planet* Source, Planet* Dest, string Date,bool Return_ticket, Traveller* traveller){
            ticket->traveller = traveller;
            ticket->Source = Source;
            ticket->Dest = Dest;
            ticket->day = day;
            ticket->month = month;
            ticket->year = year;
            ticket->Return_ticket = Return_ticket;
        }

        int distance(Planet* Source, Planet* Dest){
            return sqrt(pow(Source->getX() - Dest->getX(), 2) + pow(Source->getY() - Dest->getY(), 2) + pow(Source->getZ() - Dest->getZ(), 2));
        }

        int tck_price(){
            tm date={
                0,
                0,
                0,
                day,
                month-1,
                year-1900,              
                0,
                0,
                0
            };
            time_t travel_time=mktime(&date);
            int K = distance(Source, Dest);
            auto present = chrono::system_clock::now();
            time_t now_c = chrono::system_clock::to_time_t(present);
            int time_until_travel = ceil(difftime( now_c,travel_time) / (60 * 60 * 24)) + 1;
            return K/time_until_travel;
        }

        void set_price(){
            price = tck_price()*(Return_ticket+1);
        }

        int get_price(){
            return price;
        }

        void print_ticket(){
            cout<<"Traveller Name: "<<this->traveller->name<<endl;
            cout<<"Ticket id: "<<this->id<<endl;
            cout<<"Source Planet: "<<this->Source->Planet_name<<endl;
            cout<<"Destination Planet: "<<this->Dest->Planet_name<<endl;
            cout<<"Date: "<<this->day<<"/"<<this->month<<"/"<<this->year<<endl;
            cout << "Return Ticket: " << (Return_ticket ? "Yes" : "No") << endl;
            cout << "Valid for: " << validity << " years" << endl;
            cout<<"Price: "<<this->get_price()<<endl;
        }
};

int Ticket::ticket_id = 0;

vector <Ticket*> list_of_tickets;

void Ticket::push_ticket(Ticket* ticket){
    list_of_tickets.push_back(ticket);
}

Ticket* Ticket::find_ticket(int tckid){
    for(auto i : list_of_tickets){
        if(i->ticket_id==tckid)
            return i;
    }
    return NULL;
}

void Ticket::cancel_ticket(int tckid){
    for(auto i = list_of_tickets.begin(); i!=list_of_tickets.end(); ++i){
        if((*i)->ticket_id==tckid){
            delete *i;
            list_of_tickets.erase(i);
            break; 
        }
    }      
    cout<<"Your ticket has been deleted."<<endl;
}

class SpaceTravel{  
    private:
        int id;
        Astronaut* Astronaut;
        Commander* Commander;
        vector <Traveller*> list_of_travellers;

    public:
        static int travel_id;

        SpaceTravel(){
            cout<<"Space Travel with id "<<get_ID()<<" created."<<endl<<endl;
            travel_id++;
        }
        void addTraveller(Traveller* traveller){
            list_of_travellers.push_back(traveller);
        }

        void listTravellers(){
            for(auto i : this->list_of_travellers){
                cout<<i->name<<endl;
            }
        }

        void setAstronaut(string ID){
            for(auto i: list_of_astronauts){
                if(i->inp_id==ID){
                    Astronaut = i;
                    cout << "Astronaut " << Astronaut->getName()<< " assigned to space travel " << get_ID() << endl;
                }
            }
        }

        void setCommander(string ID){
            for(auto i: list_of_commanders){
                if(i->inp_id==ID){
                    Commander = i;
                    cout << "Commander " << Commander->getName() << " assigned to space travel " << get_ID() << endl;
                }
            }
        }

        void updateAstronaut(string ID){
            for(auto i: list_of_astronauts){
                if(i->inp_id==ID){
                    Astronaut = i;
                    cout << "Now Astronaut " << Astronaut->getName() << " assigned to space travel " << id << endl;
                }
            }
        }

        void updateCommander(string ID){
            for(auto i: list_of_commanders){
                if(i->inp_id==ID){
                    Commander = i;
                    cout << "Now Commander " << Commander->getName() << " assigned to space travel " << id << endl;
                }
            }
        }
        int get_ID(){
            return id;
        }
        void set_ID(){
            id = travel_id;
        }
};

int SpaceTravel::travel_id = 0;

int main(){

    Planet*Earth = new Planet("Earth", 0, 0, 0);
    Planet*Moon = new Planet("Moon", 10, 20, 30);
    Planet* Mars = new Planet("Mars", -10, 5, -15);

    Astronaut* Astro1 = new Astronaut("Astro1", "Astro1_ID", 7);
    Astronaut* Astro2 = new Astronaut("Astro2", "Astro2_ID", 11);

    Commander* Comm1 = new Commander("Comm1", "Comm1_ID", 7);
    Commander* Comm2 = new Commander("Comm2", "Comm2_ID", 7);

    Passenger* Pass1 = new Passenger("Pass1", "Pass1_ID");
    Passenger* Pass2 = new Passenger("Pass2", "Pass2_ID");
    Passenger* Pass3 = new Passenger("Pass3", "Pass3_ID");
    Passenger* Pass4 = new Passenger("Pass4", "Pass4_ID");
    Passenger* Pass5 = new Passenger("Pass5", "Pass5_ID");
    Passenger* Pass6 = new Passenger("Pass6", "Pass6_ID");
    Passenger* Pass7 = new Passenger("Pass7", "Pass7_ID");
    Passenger* Pass8 = new Passenger("Pass8", "Pass8_ID");
    Passenger* Pass9 = new Passenger("Pass9", "Pass9_ID");
    Passenger* Pass10 = new Passenger("Pass10", "Pass10_ID");
    Passenger* Pass11 = new Passenger("Pass11", "Pass11_ID");

    Ticket* Aticket = new Ticket(Earth, Mars, 11, 11, 2023, 0, Astro1);
    Ticket* Cticket = new Ticket(Earth, Mars, 11, 11, 2023, 0, Comm1);
    Ticket* Pticket1 = new Ticket(Earth, Mars, 11, 11, 2023, 0, Pass7);
    Ticket* Pticket2 = new Ticket(Earth, Mars, 11, 11, 2023, 0, Pass11);


    int i,j,k,flag = 0;
    for (i = 0; i <= list_of_tickets.size(); i++){
        for (j = 0; j <= list_of_tickets.size(); j++){
            if (i == j)
                continue;
            for (k = 0; k <= list_of_tickets.size(); k++){
                if (j == k || i == k)
                    continue;
                if ((list_of_tickets[i]->Source)->Planet_name == (list_of_tickets[j]->Source)->Planet_name && (list_of_tickets[i]->Source)->Planet_name == (list_of_tickets[k]->Source)->Planet_name
                     && (list_of_tickets[i]->Dest)->Planet_name == (list_of_tickets[j]->Dest)->Planet_name && (list_of_tickets[i]->Dest)->Planet_name == (list_of_tickets[k]->Dest)->Planet_name 
                     && list_of_tickets[i]->day == list_of_tickets[j]->day && list_of_tickets[i]->day == list_of_tickets[k]->day&& list_of_tickets[i]->month == list_of_tickets[j]->month 
                     && list_of_tickets[i]->month == list_of_tickets[k]->month&& list_of_tickets[i]->year == list_of_tickets[j]->year && list_of_tickets[i]->year == list_of_tickets[k]->year){
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
            break;
    }

    if (flag){
        SpaceTravel* Travel1 = new SpaceTravel();
        
        Travel1->addTraveller(Astro1); 
        Travel1->addTraveller(Comm1);
        Travel1->addTraveller(Pass7);
        Travel1->addTraveller(Pass11);

        Travel1->setAstronaut("Astro1_ID");
        Travel1->setCommander("Comm1_ID");

        cout<<endl;

        Travel1->listTravellers();
        
        cout<<endl;
    }

    cout<<"Ticket of Passenger 7: "<<endl;
    Pticket1->print_ticket();
    cout<<endl;
    cout<<"Ticket of Passenger 11: "<<endl;
    Pticket2->print_ticket();
}