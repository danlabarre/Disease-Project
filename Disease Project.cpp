#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;


class Person{
        public:

        int n; //Infection status/Days left infected

        Person(){
                n = 0;
        };

        string status_string(){
                if (n==0)
                        return "susceptible";
                if (n==-1)
                        return"recovered";
                if (n<=-2)

                        return "inocculated";
                if (n>0)
                        return "sick with", n , "days to go";
        }

        void update(){ //Updates person's status to the next day
                n--;
        }

        void infect(int n){ //Infect this bih for n days
                this->n += n;
        }

        bool is_infected(){
                return (n>0);
        }

        int get_n(){
                return n;
        }

        bool is_stable(){ //Person was sick but is now recovered
                return (n==-2) ? true : false;
        }
};
class Population{
        public:

        std::vector<Person> pop;
        int numPeople;
        float probability_of_transfer;

        Population(int numPeople){
                this->numPeople = numPeople;
                int i;
                for(i = 0; i < numPeople; i++){
                    Person i;
                    pop.push_back(i);
                    }
              }

              void random_infection(){ //Infects a random person
                   //srand(time(NULL)); //This will truly randomize
                   int personToInfect = rand() % numPeople;
                   pop[personToInfect].infect(5);
              }

                void update(){
                        int i = 0, j = 0;
                        for(i = 0; i < sizeOfPop(); i++){
                                pop[i].update();
                        }
                        //cout << "The number of people is: " << this->numPeople << endl;
                        for(j = 1; j < this->numPeople - 1; j++){
                                int temp = j;
                                //cout << "Is " << j << " not less than " << this->numPeople - 1 << endl;
                                //cout << "We've found number of people: " << j << endl;
                                if((pop[temp--].is_infected() || pop[temp++].is_infected()) && pop[temp].is_infected()){
                                        pop[i].infect(5);
                                }
                                //cout << "Is " << j << " not less than " << this->numPeople - 1 << endl;
                                //cout << "We've found number of people: " << j << endl;
                                //cout << "Dod we get here??" << endl;
                        }
                }
                int sizeOfPop(){
                return numPeople;
                }
                int count_infected(){
                        int count = 0;
                        for(int i = 0; i < this->numPeople; i++){
                                if(pop[i].is_infected()){
                                        //cout << "Do we ever get here tho" << endl;
                                        count++;
                        }
                }
                return count;
        }
        void randomizeSickness(){
                for(int i = 0; i < this->numPeople; i++){
                        int sickChance = (float) rand()/(float)RAND_MAX;
                        if(sickChance >= probability_of_transfer){
                                pop[i].infect(5);
                        }
                }
        }
        void set_probability_of_transfer(float probability){
                this->probability_of_transfer = probability;
        }
        void spread(int numContacts){
                for(int i = 0; i < this->numPeople; i++){
                        for(int j = 0; j < numContacts; j++){
                                int randomPerson = rand() % this->numPeople;
                                if(pop[randomPerson].is_infected()){
                                        int sickChance = (float) rand()/(float)RAND_MAX;
                                        if(sickChance >= probability_of_transfer)
                                                pop[i].infect(5);
                                }
                        }
                }
        }
        void stepThrough(){
                int step = 0, i;
                while(count_infected() > 0){ //Counting the steps
                        step++;
                        cout << "In step " << step << " #sick: " << count_infected() << " : ";
                        for(i = 0; i < this->numPeople; i++){ //Each person's status
                                char curr;
                                int n = pop[i].get_n();
                                if(n == 0){
                                        curr = '?';
                                }
                                else if(n > 0){
                                        curr = '+';
                                }                                                                            else{ //n < 0
                                        curr = '-';
                                }
                                cout << curr << " ";
                        }
                        cout << endl;
                        update();
                        cout << "We've updated" << endl;
                }
                cout << "Disease ran its course by step " << step << endl;
        }
};

int main()
{
        cout << "******** PERSON ********" << endl;
        Person joe;
        int step = 0;
        srand(time(NULL)); //This will truly randomize
        while(step < 5) {
                step++;
                joe.update();
                float bad_luck = (float) rand()/(float)RAND_MAX; //Generate Random Number
                if(bad_luck > .95)
                        joe.infect(5); //Infect joe for 5 days
                        cout << "On day " << step << ",Joe is " << joe.status_string() << endl;
                        if(joe.is_stable())
                                break;
                        }
                        cout << "******* POPULATION *******" << endl;
                                int contagionpopNum;
                        cout << "Entering Contagion simulation.." << endl;
                        cout << "size of population?" << endl;
                        cin >> contagionpopNum;
                        Population contagionPop (contagionpopNum);
                        float infectProb;
                        cout << "Probability of infection: ";
                        cin >> infectProb;
                        int contagionUser;
                        cout << "Do you want random sickness? (Enter 1) or one sick person (else)" << endl;
                        cin >> contagionUser;
                        if(contagionUser == 1)
                                contagionPop.randomizeSickness();

                        else
                                contagionPop.random_infection();
                        contagionPop.stepThrough();

                        cout << "******* SPREADING *******" << endl;
                        int spreadingpopNum;
                        cout << "Entering Contagion simulation.. ";
                        cout << "size of population" << endl;
                        cin >> spreadingpopNum;
                        Population SpreadingPop(spreadingpopNum);
                        cout << "A person will come into contact with 3 infected people per day" << endl;
                        SpreadingPop.random_infection();
                        SpreadingPop.spread(3);
                        SpreadingPop.stepThrough();
                        return 0;
}
