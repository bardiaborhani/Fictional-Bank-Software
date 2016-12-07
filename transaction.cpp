#include <transaction.h>

using namespace std;

/*


Pre-condition:
Post-condition:
*/
Transaction::Transaction(){ // Default no args constructor

}

/*


Pre-condition:
Post-condition:
*/
Transaction::~Transaction(){ // Destructor

}

/*


Pre-condition:
Post-condition:
*/
bool Transaction::setData(ifstream& inFile){ // Sets the transactin data from reading a filestream
  inFile >> >> >>;
}

/*


Pre-condition:
Post-condition:
*/
string Transaction::getDescription(void) const{ // Returns a string of transaction description
  return description;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getAmount(void) const{ // Returns an int with transaction amount
  return amount;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getFirstClient(void) const{ // Returns firstClient
    return firstClient;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getSecondClient(void) const{ // Returns secondClient
      return  secondClient;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getFirstClientID(void) const{ // Returns firstClientID
      return firstAccountID;
}

/*


Pre-condition:
Post-condition:
*/
int Transaction::getSecondClientID(void) const{ // Returns secondClientID
      return secondAccountID;
}

/*


Pre-condition:
Post-condition:
*/
void Transaction::deposit(){
      
}

/*


Pre-condition:
Post-condition:
*/
bool Transaction::withdraw(){
      
}

/*


Pre-condition:
Post-condition:
*/
bool Transaction::move(){
      
}

/*


Pre-condition:
Post-condition:
*/
string Transaction::history(){
      
}

