#include "YouTubeAlgo.hpp"
//  FOR DEBUGGING function  //
void searchalgo::dispInOrd(keywordsbst *n){
	//prints BST Nodes (In Order)
	if(n->l != nullptr){
		dispInOrd(n->l);
	}
	cout << "========= KEYWORD NODE ============" << endl;
	cout << n->keyword << endl;
	printll(n->head);
	if(n->r != nullptr){
		dispInOrd(n->r);
	}
};
void searchalgo::printll(videoll *n){
	videoll *traverse = n;
	cout << "========= LINKED LIST VIDEOS ============" << endl;
	while(traverse != NULL){
			cout << "- " << traverse->title << endl;
			cout << "  -By: " << traverse->creator << endl;
			cout << "  -DOP: " << traverse->date << endl;
			cout << "  -Like ratio: " << traverse->likeratio << endl;
			cout << "  -Duration: " << traverse->duration << endl;
			cout << "  -Total views on this video: " << traverse->views << endl;
			cout << "  -Video ID: https://www.youtube.com/watch?v=" << traverse->ID << endl;
			cout << endl;
			traverse = traverse->next;
	}
};
//  Non-Member HELPER FUNCTIONS  //
string convertlowercases(string keyword){
		int length = keyword.length();
		string lowercase = "";
		char c;
		for(int i = 0; i < length; i++)
		{
				if(isupper(keyword[i]))
				{
						c = tolower(keyword[i]);
						lowercase = lowercase + c;
				}
				else
				{
					lowercase = lowercase + keyword[i];
				}
		}
		return lowercase;
};
keywordsbst* findnoderecur(keywordsbst *rootPtr , string keyword){
    keywordsbst* thekeyword = rootPtr;
		if(thekeyword != NULL){
			if(thekeyword->keyword == keyword){
				return thekeyword;
			}
			else if(thekeyword->keyword > keyword){
				return findnoderecur(thekeyword->l, keyword);
			}
			else{
				return findnoderecur(thekeyword->r, keyword);
			}
		}
		else{
			return nullptr;
		}
};
keywordsbst* findnode(keywordsbst *rootPtr, string keyword){
    keywordsbst *ptr = findnoderecur(rootPtr,keyword);
    return ptr;
};
int* traverseKeyword(keywordsbst* root, int* count){
	if (root ==NULL){
		return count;
	}
	traverseKeyword(root->r,count);
	std::cout << root->keyword << '\n';
	(*count)++;
	traverseKeyword(root->l,count);
	return count;
};
int hashreturn(std::string s){
	return (s.length()+s[0]+s[s.length()])%57;
};
//Hash creator
bool alph(std::string a, std::string b ){
	std::string word[2] = {a,b};
	//std::cout << a<<" vs. "<< b << '\n';
	bool small = (a.length()>b.length());
	for (int i =0;i<word[small].length();i++){
		if (a[i] == b[i]){
			continue;
		}
		//std::cout <<word[(a[i]>b[i])] <<" comes first" << '\n';
		return (a[i]>b[i]);
	}
	//std::cout <<word[small] <<" comes first" << '\n';
	return small;
};
// Determines which title appears first alphabetically
void clearscreen(){
	for (int i = 0;i<100;i++){
		std::cout << "" << '\n';
	}
};
//Clears screen of text
bool priorityFirst(vid* a, vid* b){
	if (a->count == b->count){
		return (a->recScore > b->recScore);
	}
	return (a->count> b->count);
};
// Decides which video is prioritized in queue
void dealoctree(keywordsbst* root){
	if (root==NULL){
		return;
	}
	dealoctree(root->l);
	dealoctree(root->r);
	videoll* check = root->head;
	while(check!=NULL){
		std::cout << "Deleting video: " <<check->title << '\n';
		root->head = check->next;
		delete check;
		check = root->head;
	}
	std::cout << "Deleting Keyword: "<<root->keyword << '\n';
	delete root;
};
// Post-order Traversal of BST for deallocation of data-struct
//  Ben's //
bool searchalgo::findmatching(keywordsbst *n, string keyword){
	//cout << n->keyword << endl;
	if(n->l != nullptr){
		findmatching(n->l, keyword);
	}
	if(n->keyword == keyword){
		//cout << "found" << endl;
		match = true;
  }
	if(n->r != nullptr){
		findmatching(n->r, keyword);
	}
  return match;
};
int searchalgo::totalvideokeywords(string videotitle){
	int videotitlewords = 0;
	string storingkeyword = videotitle;
	int length = storingkeyword.length();
	for(int i = 0; i < length; i++){
			if(storingkeyword[i] == ' '){
					videotitlewords++;
			}
	}
	videotitlewords++;
	return videotitlewords;
};
videokeywords* searchalgo::getkeywords(string videotitle, int videotitlewords){
		string storingkeyword = videotitle;
		stringstream s(storingkeyword);
		int i = 0;
		keyword = new videokeywords[videotitlewords];
		while(i < videotitlewords){
			getline(s,storingkeyword,' ');
			bool stopcheck = isStopWord(storingkeyword);
			if(!stopcheck){
				keyword[i].key = storingkeyword;
			}
			i++;
		}
		/*
		for(int i = 0; i < videotitlewords; i++){
				cout << keyword[i].key << endl;
		}
		*/
		return keyword;
};
struct videoll* addvideo(videoll *theHead, string thecreator, string thedop, string thetitle, float ratio, int theduration, int theviews, string theID){
	//Creator|Subscriptions|DOP|Title|Likes|Dislikes|Duration|Views|SubCount|ID
	videoll* insertintoll = new videoll(thecreator, thedop, thetitle, ratio, theduration, theviews, theID);
	//if LL is empty
	if(theHead == NULL){
		theHead = insertintoll;
	    	return theHead;
	}
	//if LL is not empty
	else if(theHead != NULL){
		if(insertintoll->title < insertintoll->title){
      		insertintoll->next = theHead;
	      	return insertintoll;
	   	}
	  	else if(theHead->next == NULL){
	        theHead->next = insertintoll;
	        insertintoll->next = NULL;
	        return theHead;
	    	}
	    	else{
	        	videoll* current = theHead;
	        	videoll* prev;
	        	videoll* traverse = theHead->next;
	        	bool placement = false;
	        	while(traverse != NULL && placement == false){
	            	if(insertintoll->title > current->title){
	                	prev = current;
	                	current = current->next;
	                	traverse = traverse->next;
	            	}
	            	else{
	                	placement = true;
	            	}
	        	}
	        	insertintoll->next = current->next;
	        	current->next = insertintoll;
	    	}
	}
	return theHead;
};
void searchalgo::addkeyword(string keyword){
  	keywordsbst *prev = nullptr;
	keywordsbst *temp = root;
	keywordsbst *newkeyword = new keywordsbst;
	newkeyword->keyword = keyword;
	while(temp != nullptr){
		//set previous to temp to keep track of last node
		prev = temp;
		//check which way to look for empty spot
		if(newkeyword->keyword < temp->keyword){
			temp = temp->l;
		}
		else{
			// if greater than or equal to
			temp = temp->r;
		}
	}
	if(prev == nullptr){
		root = newkeyword;
	}
	else if(newkeyword->keyword < prev->keyword){
		prev->l = newkeyword;
		newkeyword->parent = prev;
	}
	else{
		prev->r = newkeyword;
		newkeyword->parent = prev;
	}
};
string wordhelper(string keyword){
		string word = "";
		if(keyword[0] == ' ')
		{
			int length = keyword.length();
			bool removefrontspace = false;
			for(int i=0;i<length;i++)
			{
					if(i != 0)
					{
							word = word + keyword[i];
					}
			}
			return word;
		}
		else
		{
			return keyword;
		}
};
searchalgo::searchalgo(string filename){
	for (int i = 0;i<57;i++){
		VideoHash[i] = NULL;
	}
 	// 1. SET PRIVATE MEMBER DEFAULTS  //
  	root = NULL;
  	videocount = 0;
	videowatched = 0;
  	keywordcount = 0;
	match = false;
	getstopwords("ignoreWords.txt");
  	// 2. READ IN THE FILE  //
  	ifstream data;
  	data.open(filename);
	//int getlinecounter = 0;
  	//Data: Keywords|Creator|DOP|Title|Likes|Dislikes|Duration|Views|ID
  	string datainput, thekeywords, thecreator, thedop, thetitle, thelikes, thedislikes, theduration, theviews, theID;
  	string tempkeywords[100];
	bool matchfound;
	bool setroot = false;
 	if(data.is_open()){
	//while there is data to read
	 	while(getline(data,datainput)){
			int i = 0;
			int j = 1;
	          stringstream s(datainput);
	          //2.1 KEYWORDS FOR BST
//int p;
//std::cin >> p;
//std::cout << datainput << '\n';
	          getline(s,datainput,'"');
//std::cout << datainput << '\n';
//std::cin >> p;
			getline(s,datainput,'"');
//std::cout << datainput << '\n';
//std::cin >> p;
	          thekeywords = datainput;
			//cout << thekeywords << endl;
			stringstream k(thekeywords);
			while(i < j){
				getline(k,thekeywords,',');
				if(thekeywords[0] == ' '){
					thekeywords = wordhelper(thekeywords);
				}
				//cout << thekeywords << endl;
				if(thekeywords != ""){
					thekeywords = convertlowercases(thekeywords);
					bool stopcheck = isStopWord(thekeywords);
					if(!stopcheck){
						tempkeywords[i] = thekeywords;
						//set the root if root is NULL
						if(setroot == false){
							addkeyword(thekeywords);
							setroot = true;
				          }
						else{
							matchfound = findmatching(root, thekeywords);
							//IF a match is not found, add it to the LL
							if(!matchfound){
								if(thekeywords != ""){
									addkeyword(thekeywords);
									//Split keywords into component
								}
							}
						}
						thekeywords = "";
						match = false;		//Sets match used in findmatching() to false for next word
						j++;
					}
				}
				i++;
			}
	          //2.2 DATA FOR LL
	          getline(s,datainput,',');
			getline(s,datainput,',');
	          thecreator = datainput;
	          	getline(s,datainput,',');
	          thedop = datainput;
				getline(s,datainput,',');
	          thetitle = datainput;
	          	getline(s,datainput,',');
	          thelikes = datainput;
				getline(s,datainput,',');
	          thedislikes = datainput;
			//std::cout << thelikes<<","<<thedislikes << '\n';
			float ratio = ((stof(thelikes) / (stof(thelikes) + stof(thedislikes))) * 100);
	          	getline(s,datainput,',');
	          theduration = datainput;
				getline(s,datainput,',');
	          theviews = datainput;
				getline(s,datainput);
	          theID = datainput.substr(0,datainput.find(",")-1);
			//2.3 INSERT FOR LL
			for(int i = 0; i < j; i++){
				//if the word is not an empty string
				if(tempkeywords[i] != ""){
					keywordsbst *nodeptr = findnode(root, tempkeywords[i]);					//find the bstNode equal to the keyword
					//below, the function adds the information to the ll and returns the head ptr of the ll at that node
					nodeptr->head = addvideo(nodeptr->head, thecreator, thedop, thetitle, ratio, stoi(theduration), stoi(theviews), theID);
				}
				tempkeywords[i] = "";			//sets tempkeyword to empty string since it is no longer needed
			}
					//getlinecounter++;
					//cout << getlinecounter << endl;
  		}
	}
	data.close();
	//dispInOrd(root);		//DEBUG ONLY: Shows the BST and LL of Each Node
};
// Will's  //
void searchalgo::getstopwords(std::string filename){
	for (int i = 0;i<26;i++){
		stopWordHash[i] = NULL;
	}
	std::ifstream f;
	f.open(filename);
	std::string s;
	while (getline(f,s)){
		int index = ((s[0]>=97)*s[0]+(s[0]<97)*(s[0]+32))-97;
		//std::cout<<"Inserting Stop word: '"<<s <<"' in hash #"<<index<<std::endl;
		ignoreWord* iW = new ignoreWord;
		iW->word = s;
		iW->next = stopWordHash[index];
		stopWordHash[index] = iW;
	}
};
bool searchalgo::isStopWord(std::string s){
	for (int i = 0;i<s.length();i++){
		s[i] = ((s[i]>=97)*s[i]+(s[i]<97)*(s[i]+32));
	}
	int index = ((s[0]>=97)*s[0]+(s[0]<97)*(s[0]+32))-97;
	//std::cout<<s<<": searching in "<<index<<" hash"<<std::endl;
	ignoreWord* head= stopWordHash[index];
	if (head == NULL){
		return false;
	}
	bool found = false;
	while (head!= NULL) {
		//std::cout<<s<<std::endl;
		if (head->word == s){
			found = true;
			break;
		}
		head = head->next;
	}
	return found;
};
keywordsbst* searchalgo::getKeyWordPoint(std::string keyword){
	//std::cout << "finding keyword "<<keyword << '\n';
	keywordsbst* check = root;
	while (check != NULL) {
		if (check->keyword == keyword){
			return check;
		}
		if (alph(keyword, check->keyword)){
			check = check->r;
			continue;
		}
		check = check->l;
		continue;
	}
	return NULL;
};
void searchalgo::printmenu(){
	clearscreen();
	vid* check = queue;
	std::cout << "[[List of recommended videos]]" << '\n';
	int c = 0;
	while ((check!=NULL)&& (vidrecco>c)){
		std::cout << "" << '\n';
		std::cout << c+1<<". "<<check->title << " By "<<check->refNode->creator<<" ["<< check->recScore<<"]"<<" ["<< check->count<<"]"<< '\n';
		std::cout << "https://www.youtube.com/watch?v="<<check->refNode->ID << '\n';
		check = check->n;
		c++;
	}
	std::cout << " _______________________________" << '\n';
	std::cout << "| 1. Watch                      |" << '\n';
	std::cout << "| 2. Read Detail                |" << '\n';
	std::cout << "| 3. Change # of recommendation |" << '\n';
	std::cout << "| 4. Quit                       |" << '\n';
};
void searchalgo::printVideoDetail(vid* check){
	std::cout << "_____________________________________________________________" << '\n';
	std::cout << check->title << " By "<<check->refNode->creator<< '\n';
	std::cout << ">Recommendation stats" << '\n';
	std::cout << ">> Number of Keyword match: "<< check->count << '\n';
	std::cout << ">> Recommendation Score   : "<< check->recScore << '\n';
	std::cout << "Video stats" << '\n';
	std::cout << ">>Date Published          :"<< check->refNode->date << '\n';
	std::cout << ">> View count             :"<< check->refNode->views<< '\n';
	std::cout << ">> Like ratio             :"<< check->refNode->likeratio << '\n';
	std::cout << ">> Duration               :"<< check->refNode->duration << '\n';
	std::cout << "_____________________________________________________________" << '\n';
};
videoll* searchalgo::getsuggestions(std::vector<std::string> v){
	std::cout << "getting suggestions" << '\n';
	for (int i = 0;i<57;i++){
		//std::cout << i << '\n';
		VideoHash[i] = NULL;
	}
	int numOfVid = 0;
	//std::cout << v.size() << '\n';
	for (int i = 0; i<v.size();i++){
		std::cout << "Getting keywordbst pointer for "<<v[i] << '\n';
		keywordsbst* keynode =  getKeyWordPoint(v[i]);
		if (keynode == 0){
			std::cout << "Keyword doesn't exist in library" << '\n';
			continue;
		}
		std::cout << "Found keyword address in "<<keynode << '\n';
		videoll* check = keynode->head;
		while (check != NULL){
			int index = hashreturn(check->title);
			vid* llcheck = VideoHash[index];
			vid* found = NULL;
			while (llcheck !=NULL) {
				if (llcheck->title == check->title){
					std::cout << "		found!" << '\n';
					found = llcheck;
					break;
				}
				llcheck = llcheck->n;
			}
			if (found!= NULL){
				(found->count)++;
			}
			else{
				vid* newvid = new vid;
				newvid->title = check->title;
				newvid->count = 1;
				newvid-> recScore = check->likeratio* log(check->views);
				newvid->n = VideoHash[index];
				VideoHash[index] = newvid;
				newvid -> refNode = check;
				std::cout << "Adding video to node" << '\n';
				std::cout << "     > "<<newvid->title <<": recScore of "<<newvid->recScore<< '\n';
				numOfVid++;
			}
			check = check->next;
		}

	}
	int n = 0;
	vid* tempQueue[numOfVid];
	for (int i = 0;i<57;i++){
		if (VideoHash[i]==NULL){
			continue;
		}
		//std::cout << "     In hash no."<<i << '\n';
		vid* point = VideoHash[i];
		while (point!=NULL) {
			tempQueue[n] = point;
			std::cout << point->title << '\n';
			n++;
			point = point->n;
		}
	}
	clearscreen();
std::cout << "Reordering queue" << '\n';

int p;
	for (int i = 0; i < numOfVid;i++){
		int rank = 1;
		vid* l = queue;
		while (l!=NULL) {
			std::cout <<"["<<rank<<"]:"<< l->title<<" "<<l->recScore << '\n';
			rank++;
			l = l->n;
		}
		//std::cin >> p;
		vid* point = tempQueue[i];
		std::cout << point->title << '\n';
		std::cout << "		"<<point->count << '\n';
		std::cout << "		"<<point->recScore << '\n';
		point->par = NULL;
		point->n = NULL;
		if (queue == NULL){
			queue = point;
			continue;
		}
		vid* check = queue;

		while (priorityFirst(check,point)) {
			if (check->n == NULL){
				break;
			}
			check = check->n;
		}

		if (check->n == NULL&&(priorityFirst(check,point))){
			check->n = point;
			std::cout << "check->n = point" << '\n';
			point->par = check;
			std::cout << "point->par = check" << '\n';
			continue;
		}

		point->par = check->par;
		std::cout << "point->par = check->par" << '\n';
		if (check->par != NULL){
			check->par->n = point;
			std::cout << "check->par->n = point" << '\n';
		}
		else {
			queue = point;
			std::cout << "Made into new head" << '\n';
		}
		check->par = point;
		std::cout << "check->par = point" << '\n';
		point->n = check;
		std::cout << "point->n = check" << '\n';
	}
	vid* check = queue;
	clearscreen();
	std::cout << "Suggestion Queue" << '\n';
	while (check!=NULL){
		printVideoDetail(check);
		check = check->n;
	}
	printmenu();
	return root->head;
};
void searchalgo::printallinfo() {
	vid* check = queue;
	int c = 1;
	while (check!=NULL&& (vidrecco>c)){
		printVideoDetail(check);
		check = check->n;
		c++;
	}
};
int main(int argc, char const *argv[]) {
	searchalgo sA = searchalgo(argv[2]);
	int n = 0;
	//traverseKeyword(sA.getRoot(),&n);
	//sA.setNumofRec(stoi(argv[1]));
	std::cout << "Reading all keywords" << '\n';
	std::vector<std::string> v;
	std::string key;
	for (int i = 0;i<stoi(argv[1]);i++){
		clearscreen();
		std::cout << "Enter a keyword, you must enter "<<stoi(argv[1])-i<<" more" << '\n';
		std::cout << ">";
		getline(cin,key);
		bool isStop = sA.isStopWord(key);
		//std::cout << argv[i]<<" is stop word? "<< isStop << '\n';
		if (!isStop){
			v.push_back(key);
		}
	}
	sA.getsuggestions(v);
	int o = 0;
	std::string s;
	while (true) {
		sA.printmenu();
		cin >>o;
		switch (o) {
			case 1:
				std::cout << "Watch which video?" << '\n';
				do {
					std::cin >> o;
				} while(sA.getrecconum()<o);
				s = sA.watchVidFromQueue(o);
				std::cout << "You have viewed the video '"<<s<<"'" << '\n';
				std::cin >> o;
			break;
			case 2:
				std::cout << "Read which video detail? Enter 0 to print all information" << '\n';
				do {
					std::cin >> o;
				} while(sA.getrecconum()<o);
				if (o==0){
					sA.printallinfo();
				}
				sA.readDetailFromQueue(o);
				std::cin >> o;
			break;
			case 3:
				std::cout << "Show how many recommendation?" << '\n';
				do {
					std::cin >> o;
				} while(o<=0);
				sA.setNumofRec(o);
				std::cout << "The number of recommendation set to "<<o << '\n';
				std::cin >> o;
			break;
			case 4:
				return 0 ;
			break;
		}
	}
	sA.printmenu();
	//~sA;
	return 0;
};
