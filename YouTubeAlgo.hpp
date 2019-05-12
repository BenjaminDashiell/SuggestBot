#ifndef YOUTUBEALGO_HPP
#define YOUTUBEALGO_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

struct videoll{
    string creator;
    string date;
    string title;
    float likeratio;
    int duration;
    int views;
    string ID;
    struct videoll *next;

    videoll(){} // default constructor

    // Parametrized constructor
    videoll(string c, string d, string t, float r, int w, int v, string i) : creator(c),
      date(d), title(t), likeratio(r), duration(w), views(v), ID(i), next(NULL) {}
};
struct vid{
	std::string title = "";
	std::string keywordlist = "";
	int count = 0;
	vid* n = NULL;
	vid* par = NULL;
	float recScore = 0;
	videoll* refNode = NULL;
};
struct keywordsbst
{
    string keyword; //node keyword
    keywordsbst *parent = NULL;
    keywordsbst *l = NULL;
    keywordsbst *r = NULL;
    videoll* head = NULL; //points to head of the list
};

struct ignoreWord{
    std::string word = "";
    ignoreWord* next = NULL;
};

struct videokeywords
{
    string key;
};

class searchalgo
{
	public:
	//BEN
	searchalgo(std::string filename);   //constructor, reads data from file
	/*~searchalgo();    //deconstructor  */
	void addkeyword(string keyword);
	int totalvideokeywords(string videotitle); // calculates size of video keywords array
	videokeywords* getkeywords(string videotitle, int videotitlewords);
	//WILLIAM
	videoll *getsuggestions(vector <std::string> keywordTab); // Goes through the bst and finds best suggestions
	//Helpers
	videoll* getVideoPointer(std::string title); // Returns the pointer of a videoll through title
	keywordsbst* getKeyWordPoint(std::string keyword); // Returns pointer of a keyword node
	bool findmatching(keywordsbst *n, string keyword); //Checks if keyword is already in the tree
	void getstopwords(std::string filename);  //constructs hashtable of stop words
	bool isStopWord(std::string word); // Checks if the word is a stop work
	std::string watchVidFromQueue(int i){
		std::string s;
		vid* check = queue;
		if (i == 1){
			s = queue->title;
			queue = queue->n;
			return s;
		}
		while (i>1) {
			check = check->n;
			i--;
		}
		s = check->title;
		if (i == vidrecco){
			check->par->n = NULL;
			return s;
		}
		check->par->n = check->n;
		return s;
	}
	void printVideoDetail(vid* check);
	void readDetailFromQueue(int i){
		vid* check = queue;
		while (i>1) {
			check = check->n;
			i--;
		}
		printVideoDetail(check);
	}
	void printallinfo();
	int getrecconum(){
		return vidrecco;
	}
	keywordsbst* getRoot(){
	return root;
	}
	void printmenu();
	//DEBUG ONLY

	void dispInOrd(keywordsbst *n); //prints BST, calls to printll at each node
	void printll(videoll *n);
	void setNumofRec(int n){
		vidrecco = n;
	}
	private:
	vid* queue = NULL;
	int vidrecco = 10;
	int videocount; // Total number of video in archive
	int videowatched; // Number of videos seen by user
	videokeywords* keyword; //pointer to the array of video keywords
	vector <videoll> watchedvideo; //Vector of the videos seen by user in the session
	int keywordcount; // Number of Keywords
	keywordsbst *root;    //bst root
	bool match;
	vid* VideoHash[57];
	ignoreWord* stopWordHash[26];
};
#endif
