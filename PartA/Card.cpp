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
