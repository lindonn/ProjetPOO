#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>

#include "Pharmacie.hpp"

using namespace std;

Pharmacie::Pharmacie(string s){
	
	//vérification que le fichier est valide
	ifstream input(s.c_str());
	if(input.good()) //vérifie que le fichier est valide
		parsePharma(input);
	else
		throw runtime_error("file not good");
		//retourne une exception
}

void Pharmacie::parsePharma(ifstream& in){
		string s;
		while(in.good()){ // tant que le fichier n'est pas vide
			s = '\0';
			getline(in,s,'\n');//récupère la ligne jusqu'à \n
			parseMed(s);
		}
}

void Pharmacie::parseMed(string s){
	 size_t z = s.find(':');
	 size_t t = 0;
	 string nam = s.substr(0, z-1); // nom du médicament (de la position 0 dans le string à z-1, vu qu'il y a un espace avant ':')
	 vector<string> effects;  // liste d'effets secondaires
	 int i = z+2; // position du premier caractère après les ':'
	 while(i < s.length()){ // boucle jusqu'à la fin de la ligne
		t = s.find(',', i);
		if( t >= s.length()){ // pas de vigule trouvée, on en est donc au dernier effet secondaire
			effects.push_back(s.substr(i,s.length()-1-i));
			break;
		}
		else{ // il y a plusieurs effets secondaires à traiter encore
			effects.push_back(s.substr(i, t-i));
			i = t+2;	// on fait avancer i de la taille de la chaine + l'espace et la virgule
		}
	 }
	
	meds.insert(pair<string, vector<string> >(nam, effects)); //insertion de la paire représentant le médicament dans la map
}