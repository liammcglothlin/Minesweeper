#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>

struct Welcomewindow{
    vector<char> word;


    Welcomewindow() {
        word.push_back('|');


    }

    string display(){




        string str(word.begin(), word.end());
        return str;



    }

    void setText(sf::Text &text, float x, float y){
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(x, y));
    }



};


