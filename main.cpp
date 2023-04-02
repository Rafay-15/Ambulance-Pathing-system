#include <iostream>
#include <stack>
#include <utility>
#define inf 9999

 /*In a triage system, patients are often assigned to different categories based on the color of the tags used to identify them.
 Red tags are used to indicate the most serious or critical cases, while yellow tags are used for less urgent cases,
 and green tags are used for the least urgent cases. Black tags are used to indicate that a patient has died or is expected to die.
 These tags help hospital staff prioritize the treatment of patients
 and ensure that the most critically ill patients receive care as quickly as possible.*/

using namespace std;
#define  V 12
void menu();
int main();
void CreateAmbulanceRequest();
void viewRequests();
void updateRequest(int);
void dijsktra(int*, int*, bool*, int* ,int);
int getNearest(bool*, int*);



//int Total =0;
int costStation[V][V]= {
        {inf,  11,  inf,  10,  21,  inf,inf,inf, inf, 3,  inf,inf},
        {11,   inf, 15,   18,  3,   4,  inf,inf, inf, inf,inf,inf},
        {inf,  15,  inf,  inf, 7,   6,  inf,inf, inf, inf,inf,13},
        {10,   18,  inf,  inf, 7,   inf,5,  12,  inf, 2,  inf,inf},
        {21,   3,   7,    7,   inf, 2,  7,  8,   inf, inf,inf,inf},
        {inf,  4,   6,    inf, 2,   inf,inf,9,   9,   inf,inf,6},
        {inf,  inf, inf,  5,   7,   inf,inf,5,   inf, inf,1,  inf},
        {inf,  inf, inf,  12,  8,   9,  5,  inf, 4,   inf,6,  inf},
        {inf,  inf, inf,  inf, inf, 9,  inf,4,   inf, inf,3,  12},
        {3,    inf, inf,  2,   inf, inf,inf,inf, inf, inf,inf,inf},
        {inf, inf,  inf, inf, inf, inf,1,  6,   3,   inf,inf,inf},
        {inf, inf,  13,  inf, inf, 6,  inf,inf, 12,  inf,inf,inf},

};
int srcStation;
int distanceStation[V]={inf} ;
bool visitedStation[V] = {false};
int parentStation[V];

int costHospital[V][V]= {
        {inf,  11,  inf,  10,  21  ,inf, inf, inf, inf, 7,   inf, 14},
        {11,   inf, 15,   18,  3,   4,   inf, inf, inf, 9,   inf, inf},
        {inf,  15,  inf,  inf, 7,   6,   inf, inf, inf, 19,  inf, 13},
        {10,   18,  inf,  inf, 7,   inf, 5,   12,  inf, inf, inf, 3},
        {21,   3,   7,    7,   inf, 2,   7,   8,   inf, inf, inf, inf},
        {inf,  4,   6,    inf, 2,   inf, inf, 9,   9,   inf, 13,  inf},
        {inf,  inf, inf,  5,   7,   inf, inf, 5,   inf, inf, 12,  4},
        {inf,  inf, inf,  12,  8,   9,   5,   inf, 4,   inf, 8,   inf},
        {inf,  inf, inf,  inf, inf, 9,   inf, 4,   inf, inf, 6,   inf},
        {7,    9,   19,   inf, inf, inf, inf, inf, inf, inf, inf, inf},
        {inf, inf, inf,  inf, inf, 13,  12,  8,   6,   inf, inf, inf},
        {14,  inf, inf,  3,   inf, inf, 4,   inf, inf, inf, inf, inf},
};
int srcHospital;
int distanceHospital[V]={inf} ;
bool visitedHospital[V] = {false};
int parentHospital[V];

string BlocksStation [V] = {"A Block", "B block", "C Block","D Block", "E block", "F Block",
                    "G Block", "H block", "I Block","Station 1", "Station 2", "Station3"}  ;

string BlocksHospital [V] = {"A Block", "B block", "C Block","D Block", "E block", "F Block",
                             "G Block", "H block", "I Block","Benazir Hospital", "Holy Family Hospital", "Shifa Hospital"}  ;

void init(int parent[],int distance[], int src)
{
    for (int i = 0; i <= V; i++){
        parent[i] = i;
        distance[i] = inf;
    }
    distance[src] = 0;
}

int getNearest( bool visited[],  int distance[]){                     // returns the nearest unvisited vertex with the least distance
    int minValue = inf; // initially all the nodes have 999 distance
    int minValueNode = 0;
    for (int i = 0; i <= V; i++)
    {
        if (!visited[i] && distance[i] < minValue)
        {
            minValue = distance[i];
            minValueNode = i;
        }
    }
//    cout<<"Min value Nodes: "<<minValueNode<<endl;
    return minValueNode;
}

void dijsktra( int cost [][V], int distance[],bool visited[], int parent[], int src)
{
    init(parent, distance, src);
    for (int i = 0; i <= V; i++)
    {
        int nearestUnvisitedVertex = getNearest(visited, distance);
        visited[nearestUnvisitedVertex] = true;

        // update the distances
        for (int adj = 0; adj < V; adj++){
            if (cost[nearestUnvisitedVertex][adj] != inf &&
                distance[adj] > distance[nearestUnvisitedVertex] + cost[nearestUnvisitedVertex][adj])
            {
                distance[adj] = distance[nearestUnvisitedVertex] + cost[nearestUnvisitedVertex][adj];
//                cout<< "Distancees"<<distance[adj];
                parent[adj] = nearestUnvisitedVertex; // take index of parent as key and its value will be the parent vertex
            }
        }

//        cout<<"DISTANCE FOR LOOP: ";
//        for(int x=0; x<12; x++){
//            cout<<distance[x]<<" ";
//        }
    }
}

void display(int distance[], int src, int parent[])
{
    stack<int> st;

    cout << "Node:\t\t\tCost:\t\t\tPath: ";
    cout << endl;
    // for (int i = 7; i <= 7; i++){
    int i = 10;
//    st.push(i);
    cout << i << "\t\t\t" << distance[i] << "\t\t\t"
         << " ";
    cout << i;
    int parnode = parent[i];
    while (parnode != src)
    {
        st.push(parnode);
        // cout << "<--" << parnode << " ";

        parnode = parent[parnode];
    }
    st.push(src);

    // cout << "<--" << source_vertex;
    cout << endl;
    while(!st.empty()){
        int x =st.top();
        st.pop();
        cout<<x<<"-->";
    }
    cout << i;
    cout << endl;
}


struct Patient{

    string name;
    int callID;
    int location;
    int priority;
    int distancefromStation;
    int distancetoHospital;
    double time;
    int StationID;
    int HospitalID;
    string Hospital;
    string Station;
    Patient* next{};

    Patient(string n, int location, int priority,string station,int stationID ,int distancefromStation,string hospital, int hospitalID,  int distancetoHospital, int callID)
            : name(std::move(n)), location(location), priority(priority), distancefromStation(distancefromStation),
              distancetoHospital(distancetoHospital), time(0), next(nullptr), callID(callID), StationID(stationID), Station(std::move(station)), Hospital(std::move(hospital)), HospitalID(hospitalID)  {}
};

class PatientQueue{
public:
    Patient* head = nullptr;
    bool isEmpty() {
        return (head == nullptr);
    }
public:
    void dequeue() {
        if (!isEmpty()) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        } else {
            std::cout << "No Emergency Calls Enqueued!!" << std::endl;
        }
        int timeSum=0;
        for(Patient* p= head; p!=nullptr; p=p->next){
            timeSum = timeSum + p->distancefromStation*60/65;
        }

    }
public:
    string peek() {
        if (!isEmpty()) {
            return head->name + "\tNearest Ambulance: " + to_string(head->distancefromStation) + "Km" + "\nNearest Hospital: "+
                    to_string(head->distancetoHospital)+"Km" + "\t Ambulance ETA: " + to_string(head->time)+ "min";
        } else {
            std::cout << "No Emergency Calls Enqued!!" << std::endl;
            return "";
        }
    }




public:
    void enqueue(Patient* patient) {
        Patient* curr = patient;
        if (isEmpty() || patient->priority > head->priority) {
            curr->next = head; //In case new patient has higher Priority than what
            head = curr;
        } else {
            Patient* p = head;
            while (p->next != nullptr && p->next->priority > curr->priority) {
                p = p->next;
            }
            curr->next = p->next;
            p->next = curr;
        }
        double timeSum=0;
        for(Patient* p= head; p!=nullptr; p=p->next){
            timeSum = timeSum + p->distancefromStation*60/65;
            p->time = timeSum;
        }
    }
};

PatientQueue q;

void updateTime(Patient* head){
    double timeSum=0;
    for(Patient* p= head; p!=nullptr; p=p->next){
        timeSum = timeSum + p->distancefromStation*60/30;
        p->time = timeSum;
    }
};

void selectionSort(Patient* head) {
    // Iterate through the list
    for (Patient* i = head; i->next != nullptr; i = i->next) {
        // Find the minimum element in the unsorted part of the list
        Patient* max = i;
        for (Patient* j = i->next; j != nullptr; j = j->next) {
            if (j->priority > max->priority) {
                max = j;
            }
        }
        // Swap the minimum element with the first element in the unsorted part of the list
//        std::swap(i->data, max->data);
        swap(i->priority,max->priority );
        swap(i->time, max->time);
        swap(i->distancetoHospital, max->distancetoHospital);
        swap(i->distancefromStation, max->distancefromStation);
        swap(i->location, max->location);
        swap(i->callID, max->callID);
        swap(i->name, max->name);
        swap(i->StationID, max->StationID);
        swap(i->HospitalID, max->HospitalID);
        swap(i->Station, max->Station);
        swap(i->Hospital, max->Hospital);

    }

}

void CreateAmbulanceRequest(){
    int callerID, location, priority;
    string name;
    cout<< "****************************************    Create Ambulance Request    ****************************************"<<endl;
    cout<<"\n\nEnter Caller ID number: \n";
    cin>> callerID;
    cout<<"\nCaller Name: \n";
    cin>> name;
    cout<<"Select Patients Location!:\n"
          "1.   A block\n"
          "2.   B block\n"
          "3.   C block\n"
          "4.   D block\n"
          "5.   E block\n"
          "6.   F block\n"
          "7.   G block\n"
          "8.   H block\n"
          "9.   I block\n";
    cin>>location;
    location = location-1;
    while(location>8 || location<0){
        cout<< "Sorry! This is an experimental Service only Available in *Selected* Areas!\n\n";
        cout<<"Select Patients Location!:\n"
              "1.   A block\n"
              "2.   B block\n"
              "3.   C block\n"
              "4.   D block\n"
              "5.   E block\n"
              "6.   F block\n"
              "7.   G block\n"
              "8.   H block\n"
              "9.   I block\n";
        cin>>location;
        location = location-1;
    }

    cout<< "Enter Case Severity:\n"
           "0.   BLACK Tag (Dead Body)\n"
           "1.   GREEN Tag (Minor Injury, Stable Case)\n"
           "2.   YELLOW Tag (Stable Case)\n"
           "3.   RED Tag (Severe Case, Requires IMMEDIATE Assistance!)\n";
    cin>>priority;
    dijsktra(costStation, distanceStation,  visitedStation, parentStation, location);
    dijsktra(costHospital, distanceHospital,  visitedHospital, parentHospital, location);
    int stationIndex;
    if(distanceStation[9] <= distanceStation[10] && distanceStation[9]<= distanceStation[11] ){
        stationIndex= 9;
    }
    else if(distanceStation[10] <= distanceStation[9] && distanceStation[10]<= distanceStation[11] ){
        stationIndex =10;
    }
    else{
        stationIndex = 11;
    }
//    int time = ;


        //Finding The Closest Hospital
    int hospitalIndex;
    if(distanceHospital[9] <= distanceHospital[10] && distanceHospital[9]<= distanceHospital[11] ){
        hospitalIndex= 9;
    }
    else if(distanceHospital[10] <= distanceHospital[9] && distanceHospital[10]<= distanceHospital[11] ){
        hospitalIndex =10;
    }
    else {
        hospitalIndex = 11;
    }
    auto* curr = new Patient(name, location, priority,BlocksStation[stationIndex],stationIndex ,
                             distanceStation[stationIndex],BlocksHospital[hospitalIndex],
                             hospitalIndex ,distanceHospital[hospitalIndex], callerID );
    q.enqueue(curr);
    updateTime(q.head);
    cout<< "Ambulance ETA: "<< curr->time;

    menu();
}

void viewRequests(){
    cout<< "\t\t****************************************    Ambulance Requests Enqueued    ****************************************"<<endl;

    Patient* head = q.head;
    while (head != nullptr){
        cout<< head->name + "\tNearest Ambulance: " + to_string(head->distancefromStation) + "Km" + "\nNearest Hospital: "+ head->Hospital +" is "+
               to_string(head->distancetoHospital)+"Km Away" + "\t Ambulance ETA: " + to_string(head->time)+ "min\n" << endl;
        head= head->next;
    }
    menu();
}

void updateRequest() {
    int callerID;
    cout<<"Enter the ID to update: ";
    cin>>callerID;
    Patient *pointer = q.head;
    int p;
    while (pointer->callID != callerID) {
        pointer = pointer->next;
    }
    cout << pointer->name + "\tNearest Ambulance: " + to_string(pointer->distancefromStation) + "Km" +
            "\nNearest Hospital: " +
            to_string(pointer->distancetoHospital) + "Km" + "\t Ambulance ETA: " + to_string(pointer->time) + "min" << endl;
    cout << "Enter Case Severity:\n"
            "0.   BLACK Tag (Dead Body)\n"
            "1.   GREEN Tag (Minor Injury, Stable Case)\n"
            "2.   YELLOW Tag (Stable Case)\n"
            "3.   RED Tag (Severe Case, Requires IMMEDIATE Assistance!)\n"
            "4.   Cancel Update!";
    cin >> p;
    while (p > 4 || p < 0) {
        cout << "Invaid Request!:\n\n"
                "Enter Case Severity:\n"
                "0.   BLACK Tag (Dead Body)\n"
                "1.   GREEN Tag (Minor Injury, Stable Case)\n"
                "2.   YELLOW Tag (Stable Case)\n"
                "3.   RED Tag (Severe Case, Requires IMMEDIATE Assistance!)\n"
                "4.   Cancel Update!";
        cin>>p;
    }
    if (p != 4) {
        pointer->priority = p;
    } else {
        menu();
    }

    selectionSort(q.head);
    updateTime(q.head);

    menu();
}

void menu(){
    int choice;
    cout<< "\t\t********************    City Medical Response System    ********************\n";
    cout<< "    1. Create Ambulance Request\n"
           "    2. View Ambulance Requests Queued\n"
           "    3. Update Ambulance Request Priority\n"
           "    4. Delete Ambulance Request\n";
    cin>> choice;
    switch (choice) {
        case 1:{
            cout<<endl;
            CreateAmbulanceRequest();
        }
        case 2:{
            cout<< endl;
            viewRequests();
        }
        case 3: {
            updateRequest();
        }
        default:{}
    }

}
int main() {
    menu();
    dijsktra(costStation, distanceStation,  visitedStation, parentStation, 7);
    dijsktra(costHospital, distanceHospital,  visitedHospital, parentHospital, 7);

    cout<< "DISP distSTATION ARR: "<<endl;
    for (int i = 0; i < V; i++) {
        cout<<distanceStation[i]<< "\t";
    }
    cout<< "DISP disthospital ARR: "<<endl;
    for (int i = 0; i < V; i++) {
        cout<<distanceHospital[i]<< "\t";
    }

    return 0;
}
