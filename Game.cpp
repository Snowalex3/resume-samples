/*
   File:    Game.cpp
   Author:  Snowlin Alex
   Section: 12
   E-mail:  salex2@umbc.edu
   Description:
       Project 2 - Game.cpp File
*/

#include "Game.h"
#include "Material.h"
#include <fstream>
#include <iostream>
#include <string>

//Constants (additional constants allowed)
//const string PROJ2_DATA = "proj2_data.txt"; //File constant
//const int PROJ2_SIZE = 62;

//No additional variables or functions allowed


  // Name: Game() Default Constructor
  // Desc - Builds a new game by:
  // 1. Loads all materials and their recipes into m_materials
  // 2. Asks user for their Ship's name (store in m_myShip as m_myName)
  // 3. Copies all materials from m_materials into the Ship's material array
  // Preconditions - None
  // Postconditions - m_materials is populated

Game::Game() { //Default Constructor
  GameTitle();
  LoadMaterials();
  string name;
  cout << "What is the name of your ship?" << endl;
  cin >> name;
  m_myShip.SetName(name);
}

  // Name: LoadMaterials
  // Desc - Loads each material into m_materials from file
  // Preconditions - Requires file with valid material data
  // Postconditions - m_material is populated with material structs
void Game::LoadMaterials() {
  string name, type, material1, material2;
  const char DELIMITER = ',';
  ifstream infile(PROJ2_DATA);
  Material  m_materials[PROJ2_SIZE];
  int count = 0;
  int quantity = 0;

  // Reads file
  if(infile.is_open()) {
    while( count < PROJ2_SIZE ) {
      getline(infile, name, DELIMITER);
      getline(infile, type, DELIMITER);
      getline(infile, material1, DELIMITER);
      getline(infile, material2);

      // creates array of materials using file data
      m_materials[count] = Material(name, type, material1, material2, quantity);
      m_myShip.AddMaterial(m_materials[count]);  // adds materials to the ship
      count++;
    }
    cout << count << " materials loaded." << endl;

  }else {
    cout << "FILE FAILED TO OPEN" << endl;
  }
  infile.close();

}

  // Name: StartGame()
  // Desc - Manages the game itself including win conditions continually
  //         calling the main menu
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5
void Game::StartGame() {
  int x = MainMenu();
  // Upgrades rank based on current rank
  while (m_myShip.GetRank() != 'S' and x != 5) {

    if( x== 1)
      DisplayMaterials();

    else if(x == 2)
      SearchMaterials();

    else if(x == 3)
      CombineMaterials();

    else if(x == 4)
      CalcScore();

     x = MainMenu();
  }
  cout << "Thanks for playing No Man's Alchemy" << endl;
}

  // Name: DisplayMyMaterials()
  // Desc - Displays the Ship's materials (Uses GetMaterial)
  // Preconditions - Player's Ship has materials
  // Postconditions - Displays a numbered list of materials
void Game::DisplayMaterials() {
  for(int i=0; i< m_myShip.GetNumMaterials(); i++) {
    cout << i+1 << ". " << m_myShip.GetMaterial(i).m_name << " " << m_myShip.GetMaterial(i).m_quantity << endl;
  }


}

  // Name: MainMenu()
  // Desc - Displays and manages menu. Also checks win condition (Ship reaches S rank).
  // Preconditions - Player has a Ship
  // Postconditions - Returns number including exit
int Game::MainMenu() {
  int ask = 0;
  cout << "What would you like to do?" << endl
       << "1. Display your Ship's Materials" << endl
       << "2. Search for Raw Materials" << endl
       << "3. Attempt to Merge Materials" << endl
       << "4. See Score" << endl
       << "5. Quit" << endl;
  cin >> ask;
  bool valid = true;
  if ( ask < 1 ) {
    valid = false; }
  if ( ask > 5 ) {
    valid = false; }

  while ( valid == false ) {
    cout << "That was not a vaild responce! Choose from the following: " << endl;
     cout << "What would you like to do?" << endl
       << "1. Display your Ship's Materials" << endl
       << "2. Search for Raw Materials" << endl
       << "3. Attempt to Merge Materials" << endl
       << "4. See Score" << endl
       << "5. Quit" << endl;
     cin >> ask;
     valid = true;
     if ( ask < 1 ) {
       valid = false; }
     if ( ask > 5 ) {
       valid = false; }
  }
  return ask;
}


  // Name: SearchMaterials()
  // Desc - Attempts to search for raw materials (must be type "raw")
  // Preconditions - Raw materials loaded
  // Postconditions - Increases quantity in Ship's possession of materials
void Game::SearchMaterials() {
  int x = (rand() % (m_myShip.GetNumMaterials() +1));
  string type = m_myShip.GetMaterial(x).m_type;
  while(type != "raw") {
     x = (rand() % (m_myShip.GetNumMaterials() -1)) + 1;
     type = m_myShip.GetMaterial(x).m_type;
     //cout << m_myShip.GetMaterial(x).m_type << endl;
  }

  Material add = m_myShip.GetMaterial(x);

  m_myShip.IncrementQuantity(add);
  cout << m_myShip.GetMaterial(x).m_name << " Found!" << endl;
}

  // Name: CombineMaterials()
  // Desc - Attempts to combine known materials. If combined, quantity of material decreased
  // Preconditions - Ship is populated with materials
  // Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineMaterials() {
  int mat1;
  int mat2;
  cout << "Which materials would you like to merge? "
       << "To list known materials enter -1" << endl;
  cin >> mat1; /// validate input!!!!
  cout << "Which materials would you like to merge? "
       << "To list known materials enter -1" << endl;
  cin >> mat2;

  while(mat1 > m_myShip.GetNumMaterials() -1 or mat1 < 1) {
    cout << "Which materials would you like to merge? "
       << "To list known materials enter -1" << endl;
    cin >> mat1;
  }

  while(mat2 > m_myShip.GetNumMaterials() -1 or mat2 < 1) {
    cout << "Which materials would you like to merge? "
       << "To list known materials enter -1" << endl;
    cin >> mat2;
  }


  if(mat1 == -1 or mat2 == -1) {
    DisplayMaterials();
    return;
  }

  string mat1Name = m_myShip.GetMaterial(mat1-1).m_name;
  //cout << "1. " << mat1Name << endl;
  string mat2Name = m_myShip.GetMaterial(mat2-1).m_name;
  //cout << "2. " << mat2Name << endl;


  int recipe = SearchRecipes(mat1Name, mat2Name);

  if ( recipe == -1 ) {
    cout << "Nothing happened when you tried to combine "
         << mat1Name << " and " << mat2Name << endl;
    return;
  }

  RequestMaterial( recipe );
}

  // Name: RequestMaterial()
  // Desc - Requests material to use to merge
  // Preconditions - Ship has materials to try and merge
  // Postconditions - Returns integer of item selected by user
void Game::RequestMaterial(int &choice) {
  if ( m_myShip.GetMaterial(choice).m_type == "unique" ) {

    if ( m_myShip.GetMaterial(choice).m_quantity > 0 ) {
      cout << m_myShip.GetMaterial(choice).m_name
           << " is a unique material you can only create one at time!" << endl;
      return;
    }
  }

  Material material = m_myShip.GetMaterial(choice);

  int index1 = m_myShip.CheckRecipeMaterial1(material);
  int index2 = m_myShip.CheckRecipeMaterial2(material);

  bool valid = m_myShip.CheckQuantity( m_myShip.GetMaterial(index1), m_myShip.GetMaterial(index2) );


  if(valid == true) {
    cout << material.m_material1 << " combined with " << material.m_material2 << " to make " << material.m_name << endl;
    cout << "You have built "<< material.m_name << " for your ship." << endl;
    if(material.m_type == "unique") {
      m_myShip.IncRank();
    }

    m_myShip.DecrementQuantity(m_myShip.GetMaterial(index1));
    m_myShip.DecrementQuantity(m_myShip.GetMaterial(index2));
    m_myShip.IncrementQuantity(m_myShip.GetMaterial(choice));
  }
  else {
    cout << "You don't have enough materials" << endl;
  }

}

  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings (name of item)
  // Preconditions - m_materials is populated
  // Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string mat1, string mat2) {

  for(int i=0; i< m_myShip.GetNumMaterials(); i++) {

    if(m_myShip.GetMaterial(i).m_material1 == mat1) {
      if (m_myShip.GetMaterial(i).m_material2 == mat2 ) {
        return i; }
    }
    if(m_myShip.GetMaterial(i).m_material1 == mat2) {
      if (m_myShip.GetMaterial(i).m_material2 == mat1 ) {
        return i; }
    }

  }
  return -1;
}

  // Name: CalcScore()
  // Desc - Displays current score for Ship
  // Preconditions - Ship is populated with materials
  // Postconditions - Displays total
void Game::CalcScore() {
  cout << "***The Ship***" << endl
       << "The Great Ship " << m_myShip.GetName()
       << endl << "Ship Rank: " <<  m_myShip.GetRank() << endl;
}


  // Name: GameTitle()
  // Desc - Title for Game (Do not edit)
  // Preconditions - None
  // Postconditions - None
void GameTitle(){
    cout << "N   N OOO   M   M  AA  N   N '' SSS    AA  L   CCC H  H EEE M   M Y   Y" << endl;
    cout << "NN  N O O   MM MM A  A NN  N    S     A  A L   C   H  H E   MM MM  Y Y " << endl;
    cout << "N N N O O   M M M AAAA N N N    SSS   AAAA L   C   HHHH EEE M M M   Y  " << endl;
    cout << "N  NN O O   M   M A  A N  NN      S   A  A L   C   H  H E   M   M   Y  " << endl;
    cout << "N   N OOO   M   M A  A N   N    SSS   A  A LLL CCC H  H EEE M   M   Y  " << endl;
}
