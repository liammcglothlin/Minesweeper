#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
struct Tile{
    string texture;
    int x;
    int y;
    int board_column;
    int board_row;
    int num = 0;
    string value;

    bool clicked = false;

    bool flagged = false;



};


struct Board{
    vector <Tile> list_tiles;

    void init_tiles(string columns, string rows){
        int x = 0;
        int y = 0;
        int temp_col = 0;
        int temp_row = 0;
        for (int i = 0; i < stoi(columns) * stoi(rows); i++){
            Tile current_tile;

            if(x >= stoi(columns) *32){
                y+= 32;
                x= 0;
                temp_row+= 1;
                temp_col = 0;
                current_tile.x = x;
                current_tile.y = y;
                current_tile.board_row = temp_row;
                current_tile.board_column = temp_col;
                current_tile.texture = "files/images/tile_hidden.png";
                list_tiles.push_back(current_tile);
                x+= 32;
                temp_col+= 1;
                continue;
            }

            current_tile.x = x;
            current_tile.y = y;
            current_tile.board_row = temp_row;
            current_tile.board_column = temp_col;
            current_tile.texture = "files/images/tile_hidden.png";
            list_tiles.push_back(current_tile);
            x+= 32;
            temp_col+= 1;

        }


    }

    void display_paused(sf::RenderWindow &game_window){
        for (int i = 0; i < list_tiles.size(); i++) {
            sf::Sprite tile;
            sf::Texture texture;
            texture.loadFromFile("files/images/tile_revealed.png");
            tile.setTexture(texture);
            tile.setPosition(list_tiles.at(i).x, list_tiles.at(i).y);
            game_window.draw(tile);
        }




    }

    void display(sf::RenderWindow &game_window) {

        for (int i = 0; i < list_tiles.size(); i++) {
            sf::Sprite tile;
            sf::Texture texture;
            texture.loadFromFile(list_tiles.at(i).texture);
            tile.setTexture(texture);
            tile.setPosition(list_tiles.at(i).x, list_tiles.at(i).y);
            game_window.draw(tile);


            if (!list_tiles.at(i).flagged){
                if (list_tiles.at(i).clicked) {
                    sf::Sprite num;
                    sf::Texture num_texture;
                    num_texture.loadFromFile(list_tiles.at(i).value);
                    num.setTexture(num_texture);
                    num.setPosition(list_tiles.at(i).x, list_tiles.at(i).y);
                    game_window.draw(num);
                }
            }else{
                sf::Sprite flag;
                sf::Texture flag_texture;
                flag_texture.loadFromFile("files/images/flag.png");
                flag.setTexture(flag_texture);
                flag.setPosition(list_tiles.at(i).x, list_tiles.at(i).y);
                game_window.draw(flag);
            }



        }
    }

    bool is_mine_clicked(int column, int row){
        for (int i = 0; i < list_tiles.size(); i++) {
            if (list_tiles.at(i).board_row == row && list_tiles.at(i).board_column == column) {
                if(list_tiles.at(i).num == 9){
                    return true;
                }else{
                    return false;
                }
            }
        }
        return false;
    }

    bool is_tile_flagged(int column, int row){
        for (int i = 0; i < list_tiles.size(); i++) {
            if (list_tiles.at(i).board_row == row && list_tiles.at(i).board_column == column) {
                if(list_tiles.at(i).flagged){
                    return true;
                }else{
                    return false;
                }
            }
        }
        return false;
    }

    void mine_clicked(sf::RenderWindow &game_window) {


        for (int i = 0; i < list_tiles.size(); i++) {
            if (list_tiles.at(i).num == 9) {
                list_tiles.at(i).flagged = false;
                sf::Sprite mine;
                sf::Texture texture;
                texture.loadFromFile("files/images/mine.png");
                mine.setTexture(texture);
                mine.setPosition(list_tiles.at(i).x, list_tiles.at(i).y);
                list_tiles.at(i).texture = "files/images/tile_revealed.png";
                game_window.draw(mine);

            }


        }
    }


    void tile_clicked(int column, int row , int columns, int rows) {
        for (int i = 0; i < list_tiles.size(); i++) {
            if (list_tiles.at(i).board_row == row && list_tiles.at(i).board_column == column) {
                if(!list_tiles.at(i).flagged) {
                    list_tiles.at(i).clicked = true;
                    if (list_tiles.at(i).num == 9) {
                        list_tiles.at(i).value = "files/images/mine.png";
                    } else {
                        if (list_tiles.at(i).num == 1) {
                            list_tiles.at(i).value = "files/images/number_1.png";
                        } else if (list_tiles.at(i).num == 2) {
                            list_tiles.at(i).value = "files/images/number_2.png";
                        } else if (list_tiles.at(i).num == 3) {
                            list_tiles.at(i).value = "files/images/number_3.png";
                        } else if (list_tiles.at(i).num == 4) {
                            list_tiles.at(i).value = "files/images/number_4.png";
                        } else if (list_tiles.at(i).num == 5) {
                            list_tiles.at(i).value = "files/images/number_5.png";
                        } else if (list_tiles.at(i).num == 6) {
                            list_tiles.at(i).value = "files/images/number_6.png";
                        } else if (list_tiles.at(i).num == 7) {
                            list_tiles.at(i).value = "files/images/number_7.png";
                        } else if (list_tiles.at(i).num == 8) {
                            list_tiles.at(i).value = "files/images/number_8.png";
                        } else {
                            empty_clicked(i, columns, rows);
                        }
                    }

                }

            }


        }
    }



    void init_mines(int num_mines){
        srand((unsigned) time(NULL));
        for(int i = 0; i < num_mines; i++) {
            int random = (rand() % list_tiles.size());
            if(list_tiles.at(random).num == 9){
                i--;
                continue;
            } else {
                list_tiles.at(random).num = 9;
            }


        }

        for(int i = 0; i < list_tiles.size(); i ++){

            if(list_tiles.at(i).num == 9){
                cout <<"Column: " <<list_tiles.at(i).board_column << " Row: " << list_tiles.at(i).board_row << endl;
            }
        }




    }


    void debug_clicked(sf::RenderWindow &game_window){

        sf::Sprite mine;
        sf::Texture texture;
        texture.loadFromFile("files/images/mine.png");
        mine.setTexture(texture);
        for(int i = 0; i < list_tiles.size() ; i ++){
            if(list_tiles.at(i).num == 9){
                mine.setPosition(list_tiles.at(i).x, list_tiles.at(i).y);
                game_window.draw(mine);
            }
        }
    }


    void set_nums(int columns , int rows){
        for(int i = 0; i < list_tiles.size(); i ++){
            if(list_tiles.at(i).num == 9){
                continue;
            }
            int count;
            for(int j = 0; j < list_tiles.size(); j++){
                //Top left
                if(list_tiles.at(i).board_column > 0 && list_tiles.at(i).board_row > 0 && list_tiles.at(j).board_column == list_tiles.at(i).board_column -1  && list_tiles.at(j).board_row == list_tiles.at(i).board_row -1 ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }
                //top
                if(list_tiles.at(i).board_row > 0 && list_tiles.at(j).board_column == list_tiles.at(i).board_column  && list_tiles.at(j).board_row == list_tiles.at(i).board_row -1 ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }
                //top right
                if(list_tiles.at(i).board_column < columns && list_tiles.at(i).board_row > 0 && list_tiles.at(j).board_column == list_tiles.at(i).board_column + 1  && list_tiles.at(j).board_row == list_tiles.at(i).board_row -1 ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }

                //left
                if(list_tiles.at(i).board_column > 0 && list_tiles.at(j).board_column == list_tiles.at(i).board_column -1  && list_tiles.at(j).board_row == list_tiles.at(i).board_row ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }

                //right
                if(list_tiles.at(i).board_column < columns  && list_tiles.at(j).board_column == list_tiles.at(i).board_column +1  && list_tiles.at(j).board_row == list_tiles.at(i).board_row ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }
                //Bottom left
                if(list_tiles.at(i).board_column > 0 && list_tiles.at(i).board_row < rows  && list_tiles.at(j).board_column == list_tiles.at(i).board_column -1  && list_tiles.at(j).board_row == list_tiles.at(i).board_row + 1 ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }

                //bottom
                if(list_tiles.at(i).board_row < rows  && list_tiles.at(j).board_column == list_tiles.at(i).board_column  && list_tiles.at(j).board_row == list_tiles.at(i).board_row + 1 ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }

                //bottom right
                if(list_tiles.at(i).board_column < columns && list_tiles.at(i).board_row < rows && list_tiles.at(j).board_column == list_tiles.at(i).board_column +1 && list_tiles.at(j).board_row == list_tiles.at(i).board_row + 1 ){
                    if(list_tiles.at(j).num == 9) {
                        count++;
                    }
                }

            }
            list_tiles.at(i).num = count;
            count = 0;
        }
    }


    void empty_clicked(int i, int columns, int rows){
        list_tiles.at(i).value = "files/images/tile_revealed.png";
        list_tiles.at(i).clicked = true;



        //top
        if(list_tiles.at(i).board_row > 0 && list_tiles.at(i - columns - 1).num != 9 && list_tiles.at(i - columns - 1).clicked == false && list_tiles.at(i - columns - 1).flagged == false){
            if(list_tiles.at(i - columns - 1).num == 1){
                list_tiles.at(i - columns - 1).value = "files/images/number_1.png";
                list_tiles.at(i - columns - 1).clicked = true;
            }else if(list_tiles.at(i - columns - 1).num == 2){
                list_tiles.at(i - columns - 1).value = "files/images/number_2.png";
                list_tiles.at(i - columns - 1).clicked = true;
            } else if(list_tiles.at(i - columns - 1).num == 3){
                list_tiles.at(i - columns - 1).value = "files/images/number_3.png";
                list_tiles.at(i - columns - 1).clicked = true;
            } else if(list_tiles.at(i - columns - 1).num == 4){
                list_tiles.at(i - columns - 1).value = "files/images/number_4.png";
                list_tiles.at(i - columns - 1).clicked = true;
            } else if(list_tiles.at(i - columns - 1).num == 5){
                list_tiles.at(i - columns - 1).value = "files/images/number_5.png";
                list_tiles.at(i - columns - 1).clicked = true;
            } else if(list_tiles.at(i - columns - 1).num == 6){
                list_tiles.at(i - columns - 1).value = "files/images/number_6.png";
                list_tiles.at(i - columns - 1).clicked = true;
            } else if(list_tiles.at(i - columns - 1).num == 7) {
                list_tiles.at(i - columns - 1).value = "files/images/number_7.png";
                list_tiles.at(i - columns - 1).clicked = true;
            }else if(list_tiles.at(i - columns - 1).num == 8){
                list_tiles.at(i - columns - 1).value = "files/images/number_8.png";
                list_tiles.at(i - columns - 1).clicked = true;
            }else {
                empty_clicked(i - columns - 1, columns, rows);
            }
        }

        // left
        if(list_tiles.at(i).board_column > 0 && list_tiles.at(i - 1 ).num != 9 && list_tiles.at(i - 1).clicked == false && list_tiles.at(i - 1).flagged == false ){
            if(list_tiles.at(i  - 1).num == 1){
                list_tiles.at(i - 1).value = "files/images/number_1.png";
                list_tiles.at(i - 1).clicked = true;
            }else if(list_tiles.at(i- 1).num == 2){
                list_tiles.at(i- 1).value = "files/images/number_2.png";
                list_tiles.at(i - 1).clicked = true;
            } else if(list_tiles.at(i- 1).num == 3){
                list_tiles.at(i - 1).value = "files/images/number_3.png";
                list_tiles.at(i - 1).clicked = true;
            } else if(list_tiles.at(i- 1).num == 4){
                list_tiles.at(i- 1).value = "files/images/number_4.png";
                list_tiles.at(i- 1).clicked = true;
            } else if(list_tiles.at(i- 1).num == 5){
                list_tiles.at(i- 1).value = "files/images/number_5.png";
                list_tiles.at(i- 1).clicked = true;
            } else if(list_tiles.at(i - 1).num == 6){
                list_tiles.at(i- 1).value = "files/images/number_6.png";
                list_tiles.at(i- 1).clicked = true;
            } else if(list_tiles.at(i- 1).num == 7) {
                list_tiles.at(i- 1).value = "files/images/number_7.png";
                list_tiles.at(i- 1).clicked = true;
            }else if(list_tiles.at(i- 1).num == 8){
                list_tiles.at(i- 1).value = "files/images/number_8.png";
                list_tiles.at(i- 1).clicked = true;
            }else {
                empty_clicked(i - 1, columns, rows);
            }
        }
        // right
        if(list_tiles.at(i).board_column < columns && list_tiles.at(i + 1 ).num != 9 && list_tiles.at(i + 1).clicked == false && list_tiles.at(i + 1).flagged == false ){
            if(list_tiles.at(i  + 1).num == 1){
                list_tiles.at(i + 1).value = "files/images/number_1.png";
                list_tiles.at(i + 1).clicked = true;
            }else if(list_tiles.at(i+ 1).num == 2){
                list_tiles.at(i+ 1).value = "files/images/number_2.png";
                list_tiles.at(i + 1).clicked = true;
            } else if(list_tiles.at(i+ 1).num == 3){
                list_tiles.at(i + 1).value = "files/images/number_3.png";
                list_tiles.at(i + 1).clicked = true;
            } else if(list_tiles.at(i+ 1).num == 4){
                list_tiles.at(i+ 1).value = "files/images/number_4.png";
                list_tiles.at(i+ 1).clicked = true;
            } else if(list_tiles.at(i+ 1).num == 5){
                list_tiles.at(i+ 1).value = "files/images/number_5.png";
                list_tiles.at(i+ 1).clicked = true;
            } else if(list_tiles.at(i + 1).num == 6){
                list_tiles.at(i+ 1).value = "files/images/number_6.png";
                list_tiles.at(i+ 1).clicked = true;
            } else if(list_tiles.at(i+ 1).num == 7) {
                list_tiles.at(i+ 1).value = "files/images/number_7.png";
                list_tiles.at(i+ 1).clicked = true;
            }else if(list_tiles.at(i+ 1).num == 8){
                list_tiles.at(i+ 1).value = "files/images/number_8.png";
                list_tiles.at(i+ 1).clicked = true;
            }else {
                empty_clicked(i + 1, columns, rows);
            }
        }




        // bottom
        if(list_tiles.at(i).board_row < rows  && list_tiles.at(i + columns + 1  ).num != 9 && list_tiles.at(i + columns + 1).clicked == false && list_tiles.at(i + columns + 1).flagged == false ){
            if(list_tiles.at(i + columns + 1).num == 1){
                list_tiles.at(i + columns + 1).value = "files/images/number_1.png";
                list_tiles.at(i + columns + 1).clicked = true;
            }else if(list_tiles.at(i + columns + 1).num == 2){
                list_tiles.at(i + columns + 1).value = "files/images/number_2.png";
                list_tiles.at(i + columns + 1).clicked = true;
            } else if(list_tiles.at(i + columns + 1).num == 3){
                list_tiles.at(i + columns + 1).value = "files/images/number_3.png";
                list_tiles.at(i + columns + 1).clicked = true;
            } else if(list_tiles.at(i + columns + 1).num == 4){
                list_tiles.at(i + columns + 1).value = "files/images/number_4.png";
                list_tiles.at(i + columns + 1).clicked = true;
            } else if(list_tiles.at(i + columns + 1).num == 5){
                list_tiles.at(i + columns + 1).value = "files/images/number_5.png";
                list_tiles.at(i + columns + 1).clicked = true;
            } else if(list_tiles.at(i + columns + 1).num == 6){
                list_tiles.at(i + columns + 1).value = "files/images/number_6.png";
                list_tiles.at(i + columns + 1).clicked = true;
            } else if(list_tiles.at(i + columns + 1).num == 7) {
                list_tiles.at(i + columns + 1).value = "files/images/number_7.png";
                list_tiles.at(i + columns + 1).clicked = true;
            }else if(list_tiles.at(i + columns + 1).num == 8){
                list_tiles.at(i + columns + 1).value = "files/images/number_8.png";
                list_tiles.at(i + columns + 1).clicked = true;
            }else {
                empty_clicked(i + columns + 1, columns, rows);
            }


        }


        //top right
        if(list_tiles.at(i).board_row > 0 && list_tiles.at(i).board_column < columns && list_tiles.at(i - columns).num != 9 && list_tiles.at(i - columns).clicked == false && list_tiles.at(i - columns).flagged == false){
            if(list_tiles.at(i - columns ).num == 1){
                list_tiles.at(i - columns).value = "files/images/number_1.png";
                list_tiles.at(i - columns).clicked = true;
            }else if(list_tiles.at(i - columns).num == 2){
                list_tiles.at(i - columns).value = "files/images/number_2.png";
                list_tiles.at(i - columns).clicked = true;
            } else if(list_tiles.at(i - columns).num == 3){
                list_tiles.at(i - columns).value = "files/images/number_3.png";
                list_tiles.at(i - columns).clicked = true;
            } else if(list_tiles.at(i - columns).num == 4){
                list_tiles.at(i - columns).value = "files/images/number_4.png";
                list_tiles.at(i - columns ).clicked = true;
            } else if(list_tiles.at(i - columns ).num == 5){
                list_tiles.at(i - columns ).value = "files/images/number_5.png";
                list_tiles.at(i - columns ).clicked = true;
            } else if(list_tiles.at(i - columns ).num == 6){
                list_tiles.at(i - columns ).value = "files/images/number_6.png";
                list_tiles.at(i - columns ).clicked = true;
            } else if(list_tiles.at(i - columns ).num == 7) {
                list_tiles.at(i - columns ).value = "files/images/number_7.png";
                list_tiles.at(i - columns ).clicked = true;
            }else if(list_tiles.at(i - columns ).num == 8){
                list_tiles.at(i - columns ).value = "files/images/number_8.png";
                list_tiles.at(i - columns ).clicked = true;
            }else {
                empty_clicked(i - columns , columns, rows);
            }
        }

        //top left
        if(list_tiles.at(i).board_row > 0 && list_tiles.at(i).board_column > 0 && list_tiles.at(i - columns-2).num != 9 && list_tiles.at(i - columns-2).clicked == false && list_tiles.at(i - columns-2).flagged == false){
            if(list_tiles.at(i - columns -2).num == 1){
                list_tiles.at(i - columns-2).value = "files/images/number_1.png";
                list_tiles.at(i - columns-2).clicked = true;
            }else if(list_tiles.at(i - columns-2).num == 2){
                list_tiles.at(i - columns-2).value = "files/images/number_2.png";
                list_tiles.at(i - columns-2).clicked = true;
            } else if(list_tiles.at(i - columns-2).num == 3){
                list_tiles.at(i - columns-2).value = "files/images/number_3.png";
                list_tiles.at(i - columns-2).clicked = true;
            } else if(list_tiles.at(i - columns-2).num == 4){
                list_tiles.at(i - columns-2).value = "files/images/number_4.png";
                list_tiles.at(i - columns-2 ).clicked = true;
            } else if(list_tiles.at(i - columns-2 ).num == 5){
                list_tiles.at(i - columns -2).value = "files/images/number_5.png";
                list_tiles.at(i - columns-2 ).clicked = true;
            } else if(list_tiles.at(i - columns-2 ).num == 6){
                list_tiles.at(i - columns-2 ).value = "files/images/number_6.png";
                list_tiles.at(i - columns-2 ).clicked = true;
            } else if(list_tiles.at(i - columns-2 ).num == 7) {
                list_tiles.at(i - columns-2 ).value = "files/images/number_7.png";
                list_tiles.at(i - columns-2 ).clicked = true;
            }else if(list_tiles.at(i - columns-2 ).num == 8){
                list_tiles.at(i - columns-2 ).value = "files/images/number_8.png";
                list_tiles.at(i - columns -2).clicked = true;
            }else {
                empty_clicked(i - columns -2, columns, rows);
            }
        }

        // bottom left
        if(list_tiles.at(i).board_row < rows  && list_tiles.at(i).board_column > 0 && list_tiles.at(i + columns  ).num != 9 && list_tiles.at(i + columns).clicked == false && list_tiles.at(i + columns ).flagged == false ){
            if(list_tiles.at(i + columns ).num == 1){
                list_tiles.at(i + columns).value = "files/images/number_1.png";
                list_tiles.at(i + columns ).clicked = true;
            }else if(list_tiles.at(i + columns).num == 2){
                list_tiles.at(i + columns).value = "files/images/number_2.png";
                list_tiles.at(i + columns ).clicked = true;
            } else if(list_tiles.at(i + columns).num == 3){
                list_tiles.at(i + columns).value = "files/images/number_3.png";
                list_tiles.at(i + columns ).clicked = true;
            } else if(list_tiles.at(i + columns ).num == 4){
                list_tiles.at(i + columns ).value = "files/images/number_4.png";
                list_tiles.at(i + columns ).clicked = true;
            } else if(list_tiles.at(i + columns ).num == 5){
                list_tiles.at(i + columns ).value = "files/images/number_5.png";
                list_tiles.at(i + columns ).clicked = true;
            } else if(list_tiles.at(i + columns ).num == 6){
                list_tiles.at(i + columns ).value = "files/images/number_6.png";
                list_tiles.at(i + columns ).clicked = true;
            } else if(list_tiles.at(i + columns ).num == 7) {
                list_tiles.at(i + columns ).value = "files/images/number_7.png";
                list_tiles.at(i + columns ).clicked = true;
            }else if(list_tiles.at(i + columns ).num == 8){
                list_tiles.at(i + columns ).value = "files/images/number_8.png";
                list_tiles.at(i + columns ).clicked = true;
            }else {
                empty_clicked(i + columns , columns, rows);
            }


        }

        // bottom right
        if(list_tiles.at(i).board_row < rows  && list_tiles.at(i).board_column < columns && list_tiles.at(i + columns+2  ).num != 9 && list_tiles.at(i + columns+2).clicked == false && list_tiles.at(i + columns+2 ).flagged == false ){
            if(list_tiles.at(i + columns+2 ).num == 1){
                list_tiles.at(i + columns+2).value = "files/images/number_1.png";
                list_tiles.at(i + columns+2 ).clicked = true;
            }else if(list_tiles.at(i + columns+2).num == 2){
                list_tiles.at(i + columns+2).value = "files/images/number_2.png";
                list_tiles.at(i + columns +2).clicked = true;
            } else if(list_tiles.at(i + columns+2).num == 3){
                list_tiles.at(i + columns+2).value = "files/images/number_3.png";
                list_tiles.at(i + columns +2).clicked = true;
            } else if(list_tiles.at(i + columns+2 ).num == 4){
                list_tiles.at(i + columns+2 ).value = "files/images/number_4.png";
                list_tiles.at(i + columns +2).clicked = true;
            } else if(list_tiles.at(i + columns +2).num == 5){
                list_tiles.at(i + columns+2 ).value = "files/images/number_5.png";
                list_tiles.at(i + columns+2 ).clicked = true;
            } else if(list_tiles.at(i + columns +2).num == 6){
                list_tiles.at(i + columns +2).value = "files/images/number_6.png";
                list_tiles.at(i + columns +2).clicked = true;
            } else if(list_tiles.at(i + columns+2 ).num == 7) {
                list_tiles.at(i + columns +2).value = "files/images/number_7.png";
                list_tiles.at(i + columns+2 ).clicked = true;
            }else if(list_tiles.at(i + columns +2).num == 8){
                list_tiles.at(i + columns+2 ).value = "files/images/number_8.png";
                list_tiles.at(i + columns+2 ).clicked = true;
            }else {
                empty_clicked(i + columns+2 , columns, rows);
            }


        }


    }




    void draw_counter(string mines, string rows, sf::RenderWindow &game_window) {

        //zero
        int temp_dig = stoi(mines);

        string temp = mines;
        if (stoi(mines) >= 0) {
            for (int i = 0; i < mines.length(); i++) {
                char a = temp.at(0);
                string s(1, a);
                int j = stoi(s);



                sf::Texture zero_text;
                zero_text.loadFromFile("files/images/digits.png", sf::IntRect(0 + (21 * j), 0, 21, 32));
                sf::Sprite zero;
                zero.setTexture(zero_text);
                zero.setPosition(33 + (21 * i), (32 * (stoi(rows) + 0.5) + 16));
                temp = temp.substr(1, temp.length());
                game_window.draw(zero);
            }


        } else {

            for (int i = 1; i < mines.length(); i++) {
                char a = temp.at(1);
                string s(1, a);
                int j = stoi(s);


                sf::Texture neg_text;
                neg_text.loadFromFile("files/images/digits.png", sf::IntRect(0 + (21 * 10), 0, 21, 32));
                sf::Sprite neg;
                neg.setTexture(neg_text);
                neg.setPosition(12, (32 * (stoi(rows) + 0.5) + 16));
                game_window.draw(neg);

                sf::Texture zero_text;
                zero_text.loadFromFile("files/images/digits.png", sf::IntRect(0 + (21 * j), 0, 21, 32));
                sf::Sprite zero;
                zero.setTexture(zero_text);
                zero.setPosition(33 + (21 * (i-1)), (32 * (stoi(rows) + 0.5) + 16));
                temp = temp.substr(1, temp.length());
                game_window.draw(zero);
            }
        }
    }

    void draw_time(string columns, string rows, int min, int seconds, sf::RenderWindow &game_window){
        sf::Texture min1_text;
        min1_text.loadFromFile("files/images/digits.png", sf::IntRect(0 + (21 * (min/10)), 0, 21, 32));
        sf::Sprite min1;
        min1.setTexture(min1_text);
        min1.setPosition((stoi(columns)*32) -97, (32 * (stoi(rows) + 0.5) + 16));
        game_window.draw(min1);

        sf::Texture min2_text;
        min2_text.loadFromFile("files/images/digits.png", sf::IntRect(0 + (21 * (min%10)), 0, 21, 32));
        sf::Sprite min2;
        min2.setTexture(min2_text);
        min2.setPosition((stoi(columns)*32) -76, (32 * (stoi(rows) + 0.5) + 16));
        game_window.draw(min2);

        sf::Texture sec1_text;
        sec1_text.loadFromFile("files/images/digits.png", sf::IntRect(0+ (21* (seconds/10)), 0, 21, 32));
        sf::Sprite sec1;
        sec1.setTexture(sec1_text);
        sec1.setPosition((stoi(columns)*32) -54, (32 * (stoi(rows) + 0.5) + 16));
        game_window.draw(sec1);

        sf::Texture sec2_text;
        sec2_text.loadFromFile("files/images/digits.png", sf::IntRect(0+ (21* (seconds%10)), 0, 21, 32));
        sf::Sprite sec2;
        sec2.setTexture(sec2_text);
        sec2.setPosition((stoi(columns)*32) -33, (32 * (stoi(rows) + 0.5) + 16));
        game_window.draw(sec2);
    }

};

