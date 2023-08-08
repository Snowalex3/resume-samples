/*
   File:    Ship.cpp
   Author:  Snowlin Alex
   Section: 12
   E-mail:  salex2@umbc.edu
   Description:
       Project 2 - Ship.cpp File
*/

#include "Ship.h"
#include "Material.h"

using namespace std;

//Constants (allowed to add more as needed)

// class - allowed to add HELPER functions only

  // Name: Ship() - Default Constructor
  // Desc: Used to build a new Player Ship
  // Preconditions - Requires default values
  // Postconditions - Creates a new Player Ship
Ship::Ship() {
  m_shipName = "Snowy";
  m_shipRank= 'D';
  m_numMaterials = 0;
  m_myMaterials;
}

  // Name: Ship(name) - Overloaded constructor
  // Desc - Used to build a new Player Ship
  // Preconditions - Requires name
  // Postconditions - Creates a new Player Ship
Ship::Ship(string name) {
  m_shipName = name;
  m_shipRank= 'D';
  m_numMaterials = 0;
  m_myMaterials;
}


  // Name: GetName()
  // Desc - Getter for the Player Ship's name
  // Preconditions - Player Ship exists
  // Postconditions - Returns the name of the Player Ship
string Ship::GetName() {
  return m_shipName;
}

  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Player Ship
  // Preconditions - Player Ship exists
  // Postconditions - Sets name of Player Ship
void Ship::SetName(string name) {
  m_shipName = name;
}

  // Name: CheckMaterial(Material)
  // Desc - Checks to see if the Ship has a material
  // Preconditions - Ship already has materials
  // Postconditions - Returns index of material if the Ship has it else -1
int Ship::CheckMaterial(Material material) {
  for(int i=0; i<m_numMaterials; i++) {

    // itertaies through list cheacking if name is same returns index if it is
    if(m_myMaterials[i].m_name == material.m_name)
      return i;
  }
  return -1;
}

// Name: CheckRecipeMaterial1(Material material)
// Desc - Checks to find the first recipe materials index
// Preconditions - The recipe is valid
// Postconditions - Returns index of material 1
int Ship::CheckRecipeMaterial1( Material material) {
  for(int i=0; i<m_numMaterials; i++) {

    if ( m_myMaterials[i].m_name == material.m_material1) {
      return i;
    }
  }
  return -1;
}

// Name: CheckRecipeMaterial1(Material material)
// Desc - Checks to find the first recipe materials index
// Preconditions - The recipe is valid
// Postconditions - Returns index of material 1
int Ship::CheckRecipeMaterial2( Material material) {
  for(int i=0; i<m_numMaterials; i++) {

    if (m_myMaterials[i].m_name == material.m_material2 ) {
      return i;
    }
  }
  return -1;
}

  // Name: AddMaterial(string)
  // Desc - Inserts a material into the Ship's list of materials
  // Preconditions - Ship exists
  // Postconditions - Add a material to the Ship's m_myMaterials with a quantity of 0
void Ship::AddMaterial(Material material) {
  m_myMaterials[ m_numMaterials ] =  material;
  m_numMaterials++;
}

  // Name: IncrementQuantity(Material)
  // Desc - Adds quantity to list of materials the Ship knows
  // Preconditions - Ship exists
  // Postconditions - Increases quantity of material for the Ship
void Ship::IncrementQuantity(Material mat) {
  // finds index of material in list
  int x = CheckMaterial(mat);

  // before - testing
  //cout << m_myMaterials[x].m_name << " " << m_myMaterials[x].m_type << " " << m_myMaterials[x].m_quantity << endl;
  m_myMaterials[x].m_quantity++;
  // after - testing
  //cout << m_myMaterials[x].m_name << " " << m_myMaterials[x].m_type << " " << m_myMaterials[x].m_quantity << endl;
}

  // Name: DecrementQuantity(Material)
  // Desc - Reduces quantity from the Ship's inventory with true, if no quantity false
  // Preconditions - A Ship exists
  // Postconditions - Reduces quantity of material for the Ship
bool Ship::DecrementQuantity(Material material) {
  int x = CheckMaterial(material);
  if ( x == -1 ) {
    return false;
  }
  if ( material.m_quantity == 0) {
    return false;
  }
  material.m_quantity--;
  return true;
}

  // Name: CheckQuantity(Material)
  // Desc - Checks to see if quantity of two merge materials are available
  // Preconditions - Ship exists with materials
  // Postconditions - Returns true if both are available (including two of same material)
bool Ship::CheckQuantity(Material material, Material stuff) {
  int a = CheckMaterial(material);
  int b = CheckMaterial(stuff);


  int numA;
  int numB;

  numA = m_myMaterials[a].m_quantity;
  numB = m_myMaterials[b].m_quantity;

  if(a == b) {
    numA = m_myMaterials[a].m_quantity;
    numA = m_myMaterials[a].m_quantity;

    if ( numA > 1)
      return true;
  }


  if ( numA > 0  && numB > 0 ) {
    return true; }

  return false;
}

  // Name: GetMaterial(int)
  // Desc - Checks to see if the Ship has any materials
  // Preconditions - The Ship already has materials
  // Postconditions - Returns material at specific index
Material Ship::GetMaterial(int num) {
  return m_myMaterials[num];
}

  // Name: IncRank()
  // Desc - Increments the rank of the ship to the next rank.
  // Preconditions - Ship exists and has a rank
  // Postconditions - m_shipRank will move to the next character
void Ship::IncRank() {
  if ( m_shipRank == 'D') {
    m_shipRank = 'C';
    return;
  }

  if ( m_shipRank == 'C') {
    m_shipRank = 'B';
    return;
  }

  if ( m_shipRank == 'B') {
    m_shipRank = 'A';
    return;
  }

  if ( m_shipRank == 'A') {
    m_shipRank = 'S';
    return;
  }
}

  // Name: GetRank()
  // Desc - Checks to see what the current ship's rank is
  // Preconditions - The ship exists
  // Postconditions - Returns the character indicating the rank of the ship
char Ship::GetRank() {
  return m_shipRank;
}

// Name: GetNumMaterials()
// Desc - Checks to see what the current ship's current num of know materials is
// Preconditions - The ship exists
// Postconditions - Returns the number of materials know to the ship
int Ship::GetNumMaterials() {
  return m_numMaterials;
}

  /*
private:
  string m_shipName; //Name of the Ship
  char m_shipRank; // Rank of the Ship, can be (D, C, B, A, or S)
  int m_numMaterials; //Current number of items in m_myMaterials known to the Player Ship  Material m_myMaterials[PROJ2_SIZE] = {}; //List of materials known to this Ship
};
  */
