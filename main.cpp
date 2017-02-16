
/* 
 * File:   main.cpp
 * Author: Henry
 *
 * Created on 08 November 2014, 17:46
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream> 
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#define FALSE 0
#define TRUE !FALSE
using namespace std;
const char space= ' ';
float pi = M_PI;
class WorldDistances{

	public:  
		fstream thefile;

		vector<string> list;//for storing strings of cities and their corresponding coordindates 
		vector<float> lats;//for storing latitude coorindates as floats
		vector<float> lons;//for storing longitude coorindates as floats


		//Constructor that reads cities file and adds any previously added cities
		WorldDistances() {
			ifstream ifs("cities.txt");
			string line;

			while(getline(ifs, line)) {
				stringstream s(line);
				string word;
				string city;
				float lat;
				float lon;

				for (int i = 0; s >> word; i++) {
					if (i == 0) {
						city = word;
					}
					else if (i == 1) {
						lat = stof(word);
					}

					else if (i == 2) {
						lon = stof(word);
					}
					else {
						cout << "error with format of cities.txt file" << endl;
					}	 
				}
				addCity(city, lat, lon);
			}

		}

		void addCity(string city,float x,float y){
			lats.push_back(x);
			lons.push_back(y);
			ostringstream ss;   
			ss <<city<<space<<x<<space<<y<<endl;//contructs string of city and its coordinates to be stored in list vector
			string getcontent=ss.str();
			list.push_back(getcontent);

			thefile.open("cities.txt",ios::out);
			for(int i=0;i<list.size();i++){
				thefile<<list[i];
			} 

			thefile.close();

		}
		void clear(){

			list.clear();
			lats.clear();
			lons.clear();
			thefile.open("cities.txt",ios::out);
			thefile.close();

		}

		void display(){

			ifstream openfile ("cities.txt");

			for(int i=0;i<list.size();i++){
				cout<<i+1<<")"<<space<<list[i];

			}
			cout<<endl;

			openfile.close();

		}
		void replace(int city,string newCity,float lat,float lon){
			if(city>list.size() || city<1){
				cout<<"please enter a valid value for the city you want to modify"<<endl;
			}
			else{

				ostringstream ss;   
				ss <<newCity<<space<<lat<<space<<lon<<endl;
				string getcontent=ss.str();
				list[city-1]=getcontent;
				lats[city-1]=lat;
				lons[city-1]=lon;
				thefile.open("cities.txt",ios::out);
				for(int i=0;i<list.size();i++){
					thefile<<list[i];
				}
				thefile.close();
				cout<<"cities updated!!!";cout<<endl;
			}
		}
		float getDistance(int x,int y){
			if(x>list.size() || x<1 || y>list.size() || y<1){
				cout<<"both values entered must be valid"<<endl;
				return 0;
			}
			else{
				//fetch longitude and latitude coordinates from lats and lons vectors
				float lat1=(lats[x-1]);
				float lon1=(lons[x-1]);
				float lat2=(lats[y-1]);
				float lon2=(lons[y-1]);

				//convert coordinates to radians:
				lat1 = lat1*pi/180;
				lat2 = lat2*pi/180; 
				lon1 = lon1*pi/180; 
				lon2 = lon2*pi/180; 


				float a = (sin(lat1)) * (sin(lat2));
				float b = (cos(lat1) * cos(lat2));
				float c = cos(lon1-lon2);
				float d = a + (b*c);

				float e = acos(d); // inverse of cosine
				e = e * (180/pi); // converting back to degrees
				double linearDistance = (6371 * pi * e)/180; //calculating linear distance
				cout<<"the distance between the two cities in km is: "<<endl<<linearDistance<<endl;
				return linearDistance; 
			}
		}


		void deleteCity(int i){
			if(i>list.size() || i<1){
				cout<<"please enter a valid value for the city you want to delete"<<endl;
			}
			else{
				list.erase(list.begin()+i-1);
				lats.erase(lats.begin()+i-1);
				lons.erase(lons.begin()+i-1);
				thefile.open("cities.txt",ios::out);
				for(int i=0;i<list.size();i++){
					thefile<<list[i];
				}
				thefile.close();
			}
		}
};

int main(){
	int i =1;
	WorldDistances cities;
	string city;
	string newCity;
	float lat;
	float lon;
	int condition=TRUE;

	while(condition){
		//menu
		cout<<"press 1 to add a city \n"
			"press 2 to display cities \n"
			"press 3 to modify a city \n"
			"press 4 to delete a city \n"
			"press 5 to clear the list \n"
			"press 6 to get the distance between two cities \n"
			"press 7 to quit \n";cin>>i;

		switch(i)
		{case 1: 

			cout<< "enter city name: ";cin>>city;
			cout<< "enter a the latitude coordinate: ";cin>>lat;
			cout<< "enter a the longitude coordinate: ";cin>>lon;
			cout<<"\n";

			cities.addCity(city,lat,lon);


			break;
			case 2:
			cities.display();

			break;
			case 3:
			int city;

			float lat;
			float lon;
			cities.display();
			cout<<"enter a number for the city you want to replace: ";cin>>city;
			cout<<"enter new city name: ";cin>>newCity;
			cout<< "enter a the new latitude coordinate: ";cin>>lat;
			cout<< "enter a the new longitude coordinate: ";cin>>lon;
			cout<<"\n";

			cities.replace(city,newCity,lat,lon);


			break;
			case 4:
			int i;
			cities.display();
			cout<<"choose the number for the city you want to delete: ";cin>>i;
			cout<<endl;
			cities.deleteCity(i);

			break;
			case 5:
			cities.clear();

			break;
			case 6:
			int city1;
			int city2;
			cities.display();
			cout<<"enter a number for the first city: ";cin>>city1;
			cout<<"enter a number for the second city: ";cin>>city2;
			cout<<endl;
			cities.getDistance(city1,city2);

			break;
			case 7:
			condition=FALSE;
			break;
			default:

			cout<<"you entered an invalid value"<<endl;


			break;
		}

	}      



}
