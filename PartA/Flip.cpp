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
            string card_suits[] = {"clubs","diamonds","hearts","spades"};
            
            for (int value = 1; value <= 13; value++)
            {
                for(const auto& suit: card_suits)
                {
                    Card card(value,suit);
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
                //generates random index out of 52 cards
                int genRand = rand()%52;
                //sets temporary node to first object in deck
                Node* t = head;
                // for loop to point to the node at the randomized index
                for (int i = 0; i < genRand; i++)
                {
                    t = t->next;
                }

                //swaps the two cards in the deck
                swap(current->data, t->data);
            }
        }


        friend ostream& operator<<(ostream&out,Deck&A)
        {
            for(Node* current = A.head; current != nullptr; current = current->next) 
            {
                out << "Cards: " << current -> data << endl;
            }
            
            return out;
        }
};