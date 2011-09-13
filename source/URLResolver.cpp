//
//  urlresolver.cpp
//  resolves url by command-line argument: <baseurl> <relativeurl>
//  Author: Nathan Standiford <ns@byu.edu>
//

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

const int SLASH = 47;
const int DOT   = 46;
const int POUND = 35;
const int QMARK = static_cast<int>('?');
const char NUL = '\0';


char * removeRoot(char * url) {
  const int SCHEME_LENGTH = 7;
  url = url + SCHEME_LENGTH;
  while (static_cast<int>(*url) != SLASH)
    ++url;
  *url = NUL;
  ++url;
  return url;
}
  
void parent(char * url) {
  char * path;
  path = url + static_cast<int>(strlen(url));
  while ((static_cast<int> (*(path - 1)) != NUL) 
         && static_cast<int> (*path) != SLASH)
    --path;
  *path = NUL;
}


char * resolve(char * url, char * relUrl) {  
 if (static_cast<int> (*relUrl) == DOT) {
    ++relUrl;
    if (static_cast<int> (*relUrl) == DOT) {
      parent(url);
      relUrl += 2;
    } else if (static_cast<int> (*relUrl) == SLASH) {
      ++relUrl;
    } else { 
      --relUrl;
    }
  }

  if (static_cast<int> (*relUrl) == DOT) {
    return resolve(url, relUrl);
  } else {
    return relUrl;
  }
}
void removeD(char * path) {
if(static_cast<int>(*path) == QMARK) {
    *path = NUL;
 }
 if(static_cast<int>(*path) == POUND) {
    *path = NUL;
 }
 if (*path != NUL) {
   path++;
   removeD(path);
 }
}

void removeDocument(char * url) {
  char * path;
 
  path = url;
  removeD(path);

  parent(url);
}

char * resolveUrl(char * url, char * relUrl) {
  removeDocument(url);
  relUrl = resolve(url, relUrl);  
  return relUrl;
} 

int main(int argc, char ** argv) {
  if (argc != 3) {
    cout << "Illegal operation!"
	 << endl;
    exit(1);
  }
  char * url;
  char * relUrl;

  url = *(argv + 1);

  relUrl = *(argv + 2);

  char * root;
  root = url;

  url = removeRoot(url);
  if(static_cast<int> (*relUrl) == SLASH) {
    cout << root
	 << relUrl
	 << endl;
  } else {
    relUrl = resolveUrl(url,relUrl);
    cout << root
	 << '/'
	 << url
	 << '/'
	 << relUrl
	 << endl;
  }
  return 1;
}
