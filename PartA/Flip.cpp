#include <iostream>
#include <string>

using namespace std;

class Card
{
    private: 
        // card value
        string value;

        // card suit. either a club, diamond, heart, or spade
        string suit;

    public: 
        // constructor
        Card(string val, string st) : value(val), suit(st) {}

        // copy constructor 
        Card(const Card& other) : value(other.value), suit(other.suit) {}

        // a function to set and update the value of the card
        void setValue(string val) 
        {
            value = val;
        }

        // a function to set and update the suit of the card
        void setSuit(string st)
        {
            suit = st;
        }

        // a function to get the value of the card
        string getValue() const
        {
            return value;
        }

        // a function to get the suit of the card
        string getSuit() const
        {
            return suit;
        }

        // overloaded << operator that prints the card objects with the value followed by the suit 
        friend ostream& operator <<(ostream& os, const Card& card) 
        {
            os << card.value << " of " << card.suit;
            return os;
        }

        // overloaded assignment operator whose argument is a const reference to another Card object
        Card& operator=(const Card& other)
        {
            // check that the object is not itself
            if (this != &other) 
            {
                // copy the value from other object to the current object (this)
                value = other.value;

                // copy the suit from other object to the current object (this)
                suit = other.suit;
            }

            return *this;
        }

};

// node class for linked list
class Node
{
    public:
        Card data;
        Node* next;
        
        // constructor for Node
        Node(Card c): data(c), next(nullptr) {}
};

class Deck
{
    private:
        // object of Node class points to first card in deck
        Node* head;

    public:
        Deck(): head(nullptr)
        {
            // initiate the options for the suits of the cards
            string card_suits[] = {"Clubs","Diamonds","Hearts","Spades"};
            
            // initiate the options for the values of the cards as strings
            //string card_values[] ={"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
            string card_values[] ={"King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2", "Ace"};

            // create the deck for the player
            for (const string& suit : card_suits) 
            {
                for (const string& value : card_values) 
                {
                    Card card(value, suit);
                    Node* newNode = new Node(card);
                    newNode->next = head;
                    head = newNode;
                }
            }
        }


        //destructor for memory allocated to node head to be freed up
        ~Deck()
        {
            while (head)
            {
                Node* t = head;
                head = head-> next;
                delete t;
            }
        }
        
        void shuffle()
        {
            srand(time(nullptr)); // defines random number generator
            // for loop runs through entire deck using pointers
            for (Node* current = head; current != nullptr; current = current->next)
            {
                // generates random index out of 52 cards
                int genRand = rand()%52;
                // sets temporary node to first object in deck
                Node* t = head;
                // for loop to point to the node at the randomized index
                for (int i = 0; i < genRand; i++)
                {
                    t = t->next;
                }

                // swaps the two cards in the deck
                swap(current->data, t->data);
            }
        }

        // overloaded << operator which prints out the cards in deck
        friend ostream& operator<<(ostream& out, const Deck& deck) 
        {
            for (Node* current = deck.head; current != nullptr; current = current->next) 
            {
                out << current->data << endl;
            }
            return out;
        }

        Card deal()
        {
            // checks if the deck is empty, prints an error message and exits if so
            if(!head)
            {
                cout << "Deck is empty." << endl;
                exit(1);
            }

            // points to the top card in the deck
            Node* topOfDeck = head;

            // moves the pointer to the next card in the deck
            head = head -> next;

            // saves the card data to a card object 'topCard'
            Card topCard = topOfDeck ->data;

            // deallocates node that points to top card in the deck
            delete topOfDeck;

            // returns the top card in the deck
            return topCard;

        }

        //function passed object of type card
        void replace(const Card& c)
        {
            // new node that contains the card passed through the argument of the function
            Node* newNode = new Node(c);

            // sets next pointer to the current head
            newNode -> next = head;

            // updates the head pointer to point to node with card object
            head = newNode;

        }
       
};

int main() 
{
    //creates deck object    
    Deck card_deck;
    //prints deck before shuffle
    cout<<"Before Shuffle Values: "<<endl;
    cout<<card_deck<<endl;
    //prints deck after shuffle
    card_deck.shuffle();
    cout<<"After Shuffle Values: "<<endl;
    cout<<card_deck<<endl;
}