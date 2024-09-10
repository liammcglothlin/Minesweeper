#include <iostream>
#include <SFML/Graphics.hpp>
#include "welcomewindow.h"
#include "gamewindow.h"
#include "stopwatch.h"
#include <fstream>
#include <vector>
#include <chrono>
#include <sstream>
#include <string>

using namespace std;


void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int main() {
    string columns;
    string rows;
    string mines;

    string path = "files/config.cfg";
    ifstream file;
    file.open(path);
    if(file.is_open()){
        cout<< "file opened" << endl;
    }
    else{
        cout<< "error" << endl;
    }

    getline(file, columns);
    getline(file, rows);
    getline(file, mines);

    cout << columns<< endl;
    cout << rows << endl;
    cout << mines<< endl;


    int mine_count = stoi(mines);

    sf::RenderWindow window(sf::VideoMode(stoi(columns)*32, (stoi(rows)*32)+100), "Minesweeper");
    bool open_gamewindow = false;



    sf::Font font;

    if (!font.loadFromFile("files/font.ttf"))
    {
        cout << "error" << endl;

    }
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(24);
    title.setString("WELCOME TO MINESWEEPER!");
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(title, (stoi(columns)*32)/2, ((stoi(rows)*32)+100)/2 - 150);


    sf::Text prompt;
    prompt.setFont(font);
    prompt.setCharacterSize(20);
    prompt.setString("Enter your name:");
    prompt.setStyle(sf::Text::Bold );
    setText(prompt, (stoi(columns)*32)/2, ((stoi(rows)*32)+100)/2 - 75);


    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(18);
    name.setStyle(sf::Text::Bold );
    setText(name, (stoi(columns)*32)/2, ((stoi(rows)*32)+100)/2 - 45);



    Welcomewindow welcomewindow;
    name.setString('|');

    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::TextEntered) {


                if (event.text.unicode < 0x80) // it's printable
                {

                    if (welcomewindow.word.size() > 10 && event.text.unicode != '\b') {
                        continue;
                    }

                    if (event.text.unicode == '\b') {
                        if (welcomewindow.word.size() == 1) {
                            continue;
                        }

                        welcomewindow.word.pop_back();
                        welcomewindow.word.pop_back();
                        welcomewindow.word.push_back('|');
                        name.setString(welcomewindow.display());
                        setText(name, 400, 255);
                        continue;
                    }

                    char keyString = (char) event.text.unicode;
                    if(!isalpha(keyString)){
                        continue;
                    }

                    if (welcomewindow.word.size() == 1) {
                        welcomewindow.word.at(welcomewindow.word.size() - 1) = toupper(keyString);
                    } else {
                        welcomewindow.word.at(welcomewindow.word.size() - 1) = tolower(keyString);
                    }
                    welcomewindow.word.push_back('|');
                    name.setString(welcomewindow.display());
                    setText(name, 400, 255);
                }
            }

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && welcomewindow.word.size() > 1){
            open_gamewindow = true;
            window.close();

        }

        window.clear(sf::Color::Blue);
        window.draw(title);
        window.draw(prompt);
        window.draw(name);
        window.display();
    }

    if(open_gamewindow){
        string temp_n = "";
        string temp_t = "";

        Stopwatch stopwatch;
        stopwatch.start();



        bool first_won = false;


        Board board;

        sf::RenderWindow game_window(sf::VideoMode(stoi(columns) *32, (stoi(rows) *32)+100), "Minesweeper");
        sf::Event event;

        sf::Texture smface_text;
        sf::Texture fface_text;
        sf::Texture wface_text;
        smface_text.loadFromFile("files/images/face_happy.png");
        fface_text.loadFromFile("files/images/face_lose.png");
        wface_text.loadFromFile("files/images/face_win.png");
        sf::Sprite face;
        face.setPosition(((stoi(columns)/2.0) *32)-32, (stoi(rows)+0.5) * 32 );

        sf::Texture debug_text;
        debug_text.loadFromFile("files/images/debug.png");
        sf::Sprite debug;
        debug.setTexture(debug_text);
        debug.setPosition((stoi(columns)*32)-304, (stoi(rows)+0.5) * 32 );

        sf::Texture pbutton_text;
        pbutton_text.loadFromFile("files/images/pause.png");
        sf::Sprite pbutton;
        pbutton.setTexture(pbutton_text);
        pbutton.setPosition((stoi(columns)*32)-240, (stoi(rows)+0.5) * 32 );

        sf::Texture leaderboard_text;
        leaderboard_text.loadFromFile("files/images/leaderboard.png");
        sf::Sprite leaderboard;
        leaderboard.setTexture(leaderboard_text);
        leaderboard.setPosition((stoi(columns)*32)-176, (stoi(rows)+0.5) * 32 );





        board.init_tiles(columns, rows);
        board.init_mines(stoi(mines));

        board.set_nums(stoi(columns)-1 , stoi(rows) -1);






        sf::Mouse mouse;

        bool debug_clicked = false;

        bool continue_game = true;
        bool paused = false;
        int time = 0;
        int time_temp = 0;
        int seconds = 0;
        int min = 0;
        auto start = std::chrono::high_resolution_clock::now();
        bool continue_time = true;
        bool game_won = false;
        bool open_leader = false;

        string path = "files/leaderboard.txt";
        vector<string> data;
        ifstream file;
        string read;
        file.open(path);
        while (getline(file, read)) {
            stringstream ss(read);
            while (getline(ss, read, ',')) {
                data.push_back(read);
            }
        }

        for(int i = 0; i < data.size(); i ++){
            cout << data.at(i) << endl;
        }

        while(game_window.isOpen()) {


                if(continue_time) {
                    auto now = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start);

                    if (duration.count() >= time_temp + 1) {
                        if(paused == false){
                            time++;
                        }
                        time_temp++;

                        seconds = time % 60;
                        min = time / 60;

                        cout << "Min:" << min << " Seconds:" << seconds << endl;



                    }
                }





            while (game_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    game_window.close();
                }


                if(event.type == sf::Event::MouseButtonPressed){
                    //right click
                    if (event.mouseButton.button == sf::Mouse::Right && continue_game && !game_won)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        int mousex = mouse.getPosition(game_window).x;
                        int mousey = mouse.getPosition(game_window).y;
                        cout << mousex << ',' << mousey << endl;
                        int mouse_col = mousex/32;
                        int mouse_row= mousey/32;
                        cout <<"Right clicked col " << mouse_col << endl;
                        cout << "Right clicked row " << mouse_row << endl;
                        if(mousey > stoi(rows) * 32){
                            continue;
                        }
                        for(int i = 0; i < board.list_tiles.size(); i ++){
                            if (board.list_tiles.at(i).board_row == mouse_row && board.list_tiles.at(i).board_column == mouse_col) {
                                if(!board.list_tiles.at(i).clicked){
                                    if(board.list_tiles.at(i).flagged){
                                        mine_count++;
                                    }
                                    else{
                                        mine_count--;
                                    }

                                    board.list_tiles.at(i).flagged = !board.list_tiles.at(i).flagged;

                                }

                            }
                        }

                        continue;
                    }

                    int mousex = mouse.getPosition(game_window).x;
                    int mousey = mouse.getPosition(game_window).y;
                    cout << mousex << ',' << mousey << endl;

                    int mouse_col = mousex/32;
                    int mouse_row= mousey/32;
                    //if below tiles
                    if(mousey > stoi(rows) * 32 ){
                        //debug
                        if(debug.getPosition().x <= mousex && debug.getPosition().x >= mousex -64 && debug.getPosition().y <= mousey && debug.getPosition().y >= mousey -64 && continue_game && paused == false && !game_won){
                            cout<< "debug clicked" << endl;
                            debug_clicked = !debug_clicked;
                        }

                        if(leaderboard.getPosition().x <= mousex && leaderboard.getPosition().x >= mousex -64 && leaderboard.getPosition().y <= mousey && leaderboard.getPosition().y >= mousey -64 ){
                            cout<< "Leaderboard clicked" << endl;
                                paused = true;
                                open_leader = true;


                        }

                        //face
                        if(face.getPosition().x <= mousex && face.getPosition().x >= mousex -64 && face.getPosition().y <= mousey && face.getPosition().y >= mousey -64 ){
                            cout<< "face clicked" << endl;
                           continue_game = true;
                           game_won = false;
                           for(int i = 0; i < board.list_tiles.size(); i++){
                               board.list_tiles.at(i).texture = "files/images/tile_hidden.png";
                               board.list_tiles.at(i).value = "";
                               board.list_tiles.at(i).clicked = false;
                               board.list_tiles.at(i).flagged = false;
                               board.list_tiles.at(i).num = 0;
                           }
                            board.init_mines(stoi(mines));
                            board.set_nums(stoi(columns)-1, stoi(rows)-1);
                            mine_count = stoi(mines);
                            time = 0;
                            time_temp = 0;
                            start = std::chrono::high_resolution_clock::now();
                            continue_time = true;
                        }
                        //pause/play
                        if(pbutton.getPosition().x <= mousex && pbutton.getPosition().x >= mousex -64 && pbutton.getPosition().y <= mousey && pbutton.getPosition().y >= mousey -64 && continue_game&& !game_won){
                            cout << "Pause/Play clicked" << endl;
                            paused = !paused;


                        }

                        continue;
                    }
                    cout << "column:" << mouse_col << endl;
                    cout << "row:" << mouse_row << endl;
                    if(continue_game && paused == false) {
                        board.tile_clicked(mouse_col, mouse_row, stoi(columns) - 1, stoi(rows) - 1);
                    }
                    if(board.is_mine_clicked(mouse_col, mouse_row) && !board.is_tile_flagged(mouse_col, mouse_row) && paused == false){
                        continue_game = false;
                        continue_time = false;
                    }


                }




            }
            int c = 0;
            for(int i = 0; i < board.list_tiles.size(); i ++){
                if(board.list_tiles.at(i).num != 9 && board.list_tiles.at(i).clicked == false){
                    c++;
                }
            }
            if(c==0){
                game_won = true;

                continue_time = false;
                debug_clicked = false;
                for(int i = 0; i < board.list_tiles.size(); i ++){
                    if(board.list_tiles.at(i).num == 9){
                        board.list_tiles.at(i).flagged = true;
                    }
                }


            }

            game_window.clear(sf::Color::White);
            board.display(game_window);board.display(game_window);
            if(debug_clicked ) {
                board.debug_clicked(game_window);
            }
            if(continue_game == false){
                board.mine_clicked(game_window);
                face.setTexture(fface_text);

            }else{
                face.setTexture(smface_text);
            }
            board.draw_counter( to_string(mine_count), rows, game_window);
            board.draw_time(columns, rows, min, seconds, game_window);
            if(paused){
                board.display_paused(game_window);

            }
            if(game_won){




                ofstream outfile("files/leaderboard.txt");
                if (!outfile) {
                    cerr << "Error: Unable to open file for writing!" << endl;
                    return 1;
                }


                face.setTexture(wface_text);

                string win_name = welcomewindow.display();

                win_name.pop_back();
                win_name = " " + win_name + "*";



                string win_time = to_string(min / 10) + to_string(min % 10) + ":" + to_string(seconds / 10) +
                                      to_string(seconds % 10);

                bool new_winner = false;
                if(win_name != temp_n || win_time != temp_t){
                    new_winner = true;
                }

                temp_t = win_time;
                temp_n = win_name;

                if(new_winner){
                    for(int i = 1; i < data.size(); i += 2){
                        string word = data.at(i);
                        if(word.back() == '*'){
                            word = word.substr(0, word.length()-1);
                        }
                        data.at(i) = word;

                    }


                }


                string temp_first = data.at(0);
                int first_seconds = (stoi(temp_first.substr(0, 1)) * 600) + (stoi(temp_first.substr(1, 1)) * 60) +
                                        (stoi(temp_first.substr(3, 1)) * 10) + stoi(temp_first.substr(4, 1));
                cout << "time: " << time << ", first_seconds: " << first_seconds << endl;

                string temp_sec = data.at(2);
                int sec_seconds = (stoi(temp_sec.substr(0, 1)) * 600) + (stoi(temp_sec.substr(1, 1)) * 60) +
                                      (stoi(temp_sec.substr(3, 1)) * 10) + stoi(temp_sec.substr(4, 1));
                cout << "time: " << time << ", sec_seconds: " << sec_seconds << endl;

                string temp_third = data.at(4);
                int third_seconds = (stoi(temp_third.substr(0, 1)) * 600) + (stoi(temp_third.substr(1, 1)) * 60) +
                                  (stoi(temp_third.substr(3, 1)) * 10) + stoi(temp_third.substr(4, 1));
                cout << "time: " << time << ", third_seconds: " << third_seconds << endl;

                string temp_fourth = data.at(6);
                int fourth_seconds = (stoi(temp_fourth.substr(0, 1)) * 600) + (stoi(temp_fourth.substr(1, 1)) * 60) +
                                    (stoi(temp_fourth.substr(3, 1)) * 10) + stoi(temp_fourth.substr(4, 1));
                cout << "time: " << time << ", fourth_seconds: " << fourth_seconds << endl;

                string temp_fith = data.at(8);
                int fith_seconds = (stoi(temp_fith.substr(0, 1)) * 600) + (stoi(temp_fith.substr(1, 1)) * 60) +
                                     (stoi(temp_fith.substr(3, 1)) * 10) + stoi(temp_fith.substr(4, 1));
                cout << "time: " << time << ", fith_seconds: " << fith_seconds << endl;

                vector<string> temp;
                for(int i = 0; i < data.size(); i ++){
                    temp.push_back(data.at(i));
                }

                if (new_winner && time < first_seconds) {


                    data.at(2) = temp.at(0);
                    data.at(3) = temp.at(1);
                    data.at(4) = temp.at(2);
                    data.at(5) = temp.at(3);
                    data.at(6) = temp.at(4);
                    data.at(7) = temp.at(5);
                    data.at(8) = temp.at(6);
                    data.at(9) = temp.at(7);

                    data.at(0) = win_time;
                    data.at(1) = win_name;

                } else if (new_winner && time < sec_seconds) {


                    data.at(4) = temp.at(2);
                    data.at(5) = temp.at(3);
                    data.at(6) = temp.at(4);
                    data.at(7) = temp.at(5);
                    data.at(8) = temp.at(6);
                    data.at(9) = temp.at(7);


                    data.at(2) = win_time;
                    data.at(3) = win_name ;
                }else if (new_winner && time < third_seconds) {

                    data.at(6) = temp.at(4);
                    data.at(7) = temp.at(5);
                    data.at(8) = temp.at(6);
                    data.at(9) = temp.at(7);

                    data.at(4) = win_time;
                    data.at(5) = win_name ;
                } else if (new_winner && time < fourth_seconds) {


                    data.at(8) = temp.at(6);
                    data.at(9) = temp.at(7);
                    data.at(6) = win_time;
                    data.at(7) = win_name;
                } else if (new_winner &&  time < fith_seconds) {
                    data.at(8) = win_time;
                    data.at(9) = win_name;
                }

                for(int i = 0; i < data.size(); i += 2){
                    outfile << data.at(i) + "," + data.at(i+1) << endl;
                }










            }
            game_window.draw(face);
            game_window.draw(debug);
            game_window.draw(pbutton);
            game_window.draw(leaderboard);

            game_window.display();

            while(open_leader){
                int width = stoi(columns) * 16;
                int height = stoi(rows) * 16 + 50;

                sf::RenderWindow leader_window(sf::VideoMode(width, height), "Leaderboard");
                sf::CircleShape shape(100.f);
                shape.setFillColor(sf::Color::Red);

                string content = "1.\t";
                content = content + data.at(0) + "\t" + data.at(1) + "\n\n";
                content = content + "2.\t";
                content = content + data.at(2) + "\t" + data.at(3) + "\n\n";
                content = content + "3.\t";
                content = content + data.at(4) + "\t" + data.at(5) + "\n\n";
                content = content + "4.\t";
                content = content + data.at(6) + "\t" + data.at(7) + "\n\n";
                content = content + "5.\t";
                content = content + data.at(8) + "\t" + data.at(9) + "\n\n";


                sf::Text leader;
                leader.setFont(font);
                leader.setCharacterSize(20);
                leader.setString("LEADERBOARD");
                leader.setStyle(sf::Text::Bold | sf::Text::Underlined);
                setText(leader, width/2,(height/2) -120);


                sf::Text first;
                first.setFont(font);
                first.setCharacterSize(18);
                first.setString(content);
                first.setStyle(sf::Text::Bold );
                setText(first, width/2,(height/2) +20);





                while(leader_window.isOpen()) {
                    auto now = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start);

                    if (duration.count() >= time_temp + 1) {
                        time_temp++;
                        seconds = time % 60;
                        min = time / 60;
                        cout << "Min:" << min << " Seconds:" << seconds << endl;
                    }
                    sf::Event event1;
                    while(leader_window.pollEvent(event1)) {
                        if(event1.type == sf::Event::Closed) {
                            leader_window.close();
                            open_leader = false;
                            paused = false;
                        }
                    }



                    file.close();


                    leader_window.clear(sf::Color::Blue);
                    leader_window.draw(leader);
                    leader_window.draw(first);
                    leader_window.display();
                }
            }


        }


    }




    return 0;
}

