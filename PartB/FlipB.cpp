#include <iostream>
#include <string>

using namespace std;

class Card
{
    public: 

        // card value
        string value;

        // card suit. either a club, diamond, heart, or spade
        string suit;

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
    public:
         // object of Node class points to first card in deck
        Node* head;

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

            // if empty, new node becomes the head
            if (!head) 
            {
                head = newNode;
            }

            else 
            {
                Node* lastNode = head;

                while (lastNode->next)
                {
                    lastNode = lastNode -> next;
                }

                lastNode -> next = newNode;
            }

        }
       
};

void playFlip()
{
    // create Deck object
    Deck deck;

    // shuffle the deck three times
    deck.shuffle();
    deck.shuffle();
    deck.shuffle();

    int score = 0;

    string n;

    bool gameState = true;

    int z = 24; 

    while (gameState==true)
    {
        // print out the 24 top shuffled cards of the deck
        cout << "Your top 24 cards: " << endl; 
        Node* current = deck.head; 
        for (int i = 0; i < z && current != nullptr; i++) 
        {   
            cout << current->data << endl; 
            current = current->next; 
        } 

        cout << endl;

        // print out the remaining cards of the deck
        cout << "Remaining cards in deck: " << endl; 
        while (current != nullptr) 
        { 
            cout << current->data << endl; 
            current = current->next; 
        }
        
        cout << "Enter Y to continue playing and N to stop. "<< endl;
        cin >> n;

        if (n=="N" or n=="n")
        {
            cout << "Your final score is: " << score << endl;
            exit(1);
        }

        else if(n=="Y" or n=="y") 
        {
                // create new Card object
                Card cardFlipped = deck.deal();

                cout << "The card you have flipped is: " << cardFlipped << endl;

                // if the card flipped has a value of 7, divide the score by 2
                if (cardFlipped.value == "7")
                {
                    score = score/2;
                }

                // if the card flipped has a value of Ace, add 10 to the score
                else if (cardFlipped.value == "Ace")
                {
                    score += 10;
                }
                
                // if the card flipped has a value of King or Queen or Jack, add 5 to the score
                else if (cardFlipped.value == "King" || cardFlipped.value =="Queen" || cardFlipped.value =="Jack")
                {
                    score += 5;
                }

                // if the card flipped has a value of 8, 9, or, 10, add nothing to the score
                else if (cardFlipped.value == "8" || cardFlipped.value == "9" || cardFlipped.value == "10")
                {
                    score += 0;
                }

                // if the card flipped has a value of 2-6, reset the user score to 0
                else if (cardFlipped.value == "2" || cardFlipped.value == "3" || cardFlipped.value == "4" || cardFlipped.value == "5" || cardFlipped.value == "6")
                {
                    score = 0;
                }

                // if the card flipped has a suit of Hearts, add 1 to the score
                if (cardFlipped.suit == "Hearts")
                {
                    score += 1;
                }
    
                
            cout << "Your score is: " << score << endl;

            // add the card flipped to the bottom of the deck
            deck.replace(cardFlipped);

            z--;

        }

        if (z == 0)
        {
            cout << "You have flipped the last card." << endl;
            break;
        }

    }

    cout << "The game has ended! Thank you for playing!" << endl;
}


int main() 
{ 
    playFlip();
    return 0;

}