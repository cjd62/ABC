#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Checks each individual card if it is incorrectly formatted, returns true if it is;
bool badFormat(string s, vector<string>	&vec){
	if(s.length() == 0){
		return true;
	}
	bool result = false;

	int sSize = s.length();
	for(int i = 0; i < sSize; i+=2){
		if(s.at(i) == '1'){
			if(std:: find(vec.begin(), vec.end(), s.substr(i, 3)) == vec.end()){
				result = true;
				return result;
			}
			else{
				i++;
			}
		}
		else{
			if(std:: find(vec.begin(), vec.end(), s.substr(i, 2)) == vec.end()){
				result = true;
				return result;
			}
		}
	}
	return result;
}

//checks if the hand has the wrong number of cards, returns true if it does.
bool wrongNumCards(string s){
	bool result = false;

	int handLen = s.length();	//size of the hand

	//counts how many tens are in the hand
	int countTens = 0;
	for (int i = 0; i < handLen; i++){
		if(s.at(i) == '1'){
			countTens++;
		}
	}

	if(handLen != (26 + countTens)){
		result = true;
	}
	return result;
}
//checks if there are any duplicates in the hand, returns true if there are.
bool checkDuplicates(string s, vector<string> &vec){
	bool result = false;
	string possibleDuplicate;

	//checks if the card being checked is a 10 or not
	for (unsigned int i = 0; i < s.length(); i+=2){

		//if it is a 10 then increment i by 3 in order to skip the whole card
		if(s.at(i) == '1'){
			possibleDuplicate = s.substr(i,3);
			i++;
		}
		else{
			possibleDuplicate = s.substr(i,2);
		}
		//looks through the vector to see if the card is in there.
		if(std:: find(vec.begin(), vec.end(), possibleDuplicate) != vec.end()){

			//if card is in there then switch the card with the last element
			for(unsigned int j = 0; j < vec.size() - 1; j++){

				//swaps matching element with last element in vector for easy removal
				if(possibleDuplicate.compare(vec[j]) == 0){
					string temp = vec[vec.size()-1];
					vec[vec.size()-1] = vec[j];
					vec[j] = temp;
					vec.pop_back();
				}
			}
		}
		else{
			result = true;
			return result;
		}
	}
	return result;
}
//calculates the points in a hand
int calcPoints(string s){
	int countA = 0, countJ = 0, countK = 0, countQ = 0; //counters for each condition for points
	int countH = 0 , countS = 0, countD = 0, countC = 0, points = 0;

	//goes through each character in the string to see if they match a condition
	for(unsigned int i = 0; i < s.length(); i++){

		//cases to be true to increment corresponding counter
		switch(s.at(i)){
			case 'A' : countA++;
			break;

			case 'J' : countJ++;
			break;

			case 'Q' : countQ++;
			break;

			case 'K' : countK++;
			break;

			case 'H' : countH++;
			break;

			case 'S' : countS++;
			break;

			case 'D' : countD++;
			break;

			case 'C' : countC++;
			}
	}
	if(countA == 0){
		--points;
	}
	else if(countA == 4){
		++points;
	}
	if(countJ == 1){
		--points;
	}
	if(countQ == 1){
		--points;
	}
	if(countK == 1){
		--points;
	}
	if(countH > 4){
		points+= (countH - 4);
	}
	else if(countH == 0){
		points += 3;
	}
	else if(countH == 1){
		points += 2;
	}
	else if(countH == 2){
		points += 1;
	}
	if(countD > 4){
		points +=( countD-4);
	}
	else if(countD ==0){
		points += 3;
	}
	else if(countD == 1){
		points += 2;
	}
	else if(countD == 2){
		points += 1;
	}
	if(countC > 4){
		points += (countC - 4);
	}
	else if(countC ==0){
		points += 3;
	}
	else if(countC == 1){
		points += 2;
	}
	else if(countC == 2){
		points += 1;
	}

	if(countS > 4){
		points += (countS - 4);
	}
	else if(countS ==0){
		points += 3;
	}
	else if(countS == 1){
		points += 2;
	}
	else if(countS == 2){
		points += 1;
	}
	points = points + (countA * 4) + (countK * 3) +(countQ *2) + countJ;
	return points;
}

int main(int argc, char **argv){

	//the characters needed to create the deck and number of suits and different types of cards
	string face = "A234567891JQK";
	string suit = "CHSD";
	int numSuit = suit.length();
	int numFace = face.length();

	//creates table of cards possible card
	vector<string> deck;
	for (int j = 0; j < numSuit; j++){
		for(int k = 0; k<numFace; k++){

			// if the card is a 10 it will make the card
			if(face.at(k) == '1'){
				string ten = "";
				ten+= face.at(k);
				ten+= '0';
				ten+= suit.at(j);
				deck.push_back(ten);
			}

			else{
				string card = "";
				card += face.at(k);
				card+= suit.at(j);
				deck.push_back(card);
			}
		}
	}

	vector<string>& deckRef = deck; //reference to the deck which will have elements removed
	vector<string> copyDeck(deck); //copy of the deck which will be used to check format

	string input;
	string hand1, hand2, hand3, hand4, possibleHand;

	//infinite loop to get input
	while(true){
		getline(cin,input);

		//allows program to terminate on end of file
		if(cin.eof()){
			break;
		}

		//check input of cards and calculate points
		else{
			//if a single dot(".") is entered as input, then that signifies the end of input
			//for that hand
			if(input.compare(".") == 0){

				//creates hand1
				if (hand1.length() == 0){
					hand1 = possibleHand.substr(0,possibleHand.length());
					possibleHand = "";
					//in the case of just a period being entered, it will not revisit hand 1
					//because the hand will still be empty
					if(hand1.length() == 0){
						hand1 = "visited";
					}

					//checks format of the hand
					bool hand1Format = badFormat(hand1,copyDeck);
					if(hand1Format){
						cout << "BAD FORMAT." << endl;
						continue;
					}

					//checks number of cards in the hand
					bool hand1Len = wrongNumCards(hand1);
					if(hand1Len){
						cout << "WRONG NUMBER OF CARDS" << endl;
						continue;
					}

					//checks if the hand has any duplicates
					bool hand1Duplicate = checkDuplicates(hand1, deckRef);
					if(hand1Duplicate){
						cout << "DUPLICATE CARD" << endl;
						continue;
					}

					//calculates the total points in the hand
					int total = calcPoints(hand1);
					cout << "HAND 1 TOTAL POINTS " << total << endl;
				}
				//same set of functions as hand1 for hand2, hand3, and hand4
				else if(hand2.length() == 0){
					hand2 = possibleHand.substr(0,possibleHand.length());
					possibleHand = "";
					if(hand2.length() == 0){
						hand2 = "visited";
					}

					bool hand2Format = badFormat(hand2,copyDeck);
					if(hand2Format){
						cout << "BAD FORMAT." << endl;
						continue;
					}

					bool hand2Len = wrongNumCards(hand2);
					if(hand2Len){
						cout << "WRONG NUMBER OF CARDS" << endl;
						continue;
					}

					bool hand2Duplicate = checkDuplicates(hand2, deckRef);
					if(hand2Duplicate){
						cout << "DUPLICATE CARDS" << endl;
						continue;
					}

					int total2 = calcPoints(hand2);

					cout << "HAND 2 TOTAL POINTS " << total2 << endl;
				}
				else if(hand3.length() == 0){
					hand3 = possibleHand.substr(0,possibleHand.length());
					possibleHand = "";

					if(hand3.length() == 0){
						hand3 = "visited";
					}

					bool hand3Format = badFormat(hand3,copyDeck);
					if(hand3Format){
						cout << "BAD FORMAT." << endl;
						continue;
					}

					bool hand3Len = wrongNumCards(hand3);
					if(hand3Len){
						cout << "WRONG NUMBER OF CARDS" << endl;
						continue;
					}

					bool hand3Duplicate = checkDuplicates(hand3, deckRef);
					if(hand3Duplicate){
						cout << "DUPLICATE CARDS" << endl;
						continue;
					}

					int total3 = calcPoints(hand3);

					cout << "HAND 3 TOTAL POINTS " << total3 << endl;
				}
				else if (hand4.length() == 0) {
					hand4 = possibleHand.substr(0,possibleHand.length());
					possibleHand = "";
					if(hand4.length() == 0){
						hand4 = "visited";
					}
					bool hand4Format = badFormat(hand4,copyDeck);
					if(hand4Format){
						cout << "BAD FORMAT." << endl;
						continue;
					}

					bool hand4Len = wrongNumCards(hand4);
					if(hand4Len){
						cout << "WRONG NUMBER OF CARDS" << endl;
						continue;
					}

					bool hand4Duplicate = checkDuplicates(hand4, deckRef);
					if(hand4Duplicate){
						cout << "DUPLICATE CARDS" << endl;
						continue;
					}


					int total4 = calcPoints(hand4);
					cout << "HAND 4 TOTAL POINTS " << total4 << endl;
				}
			}

			//if the input is not only a dot("."), then add it to the possibleHand
			else{

				//goes through each character in the input
				for(unsigned int i = 0; i < input.length(); i++){
					//checks the input for spaces, newlines, or commas and does not add it to
					//possible hand
					if (input[i] == ' ' || input[i] == '\n'
							|| input[i] == ','){
						continue;
					}

					//adds the input to the possible hand
					else if(input[i] != '.'){
						possibleHand += input[i];	//when "." encountered, add it to
						//the empty hand
					}
				}
			}
		}
	}
	return 0;
}
