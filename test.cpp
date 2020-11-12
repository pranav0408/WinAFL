/*
   WinAFL - A simple test binary that crashes on certain inputs:
     - 'test1' with a normal write access violation at NULL
     - 'test2' with a /GS stack cookie violation
   -------------------------------------------------------------

   Written and maintained by Ivan Fratric <ifratric@google.com>

   Copyright 2016 Google Inc. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

__declspec(noinline) int test_target(char* input_file_path, char* argv_0)
{
	string content;

	try{
		ifstream infile(input_file_path);
		ofstream outfile;
		outfile.open("customtest\\Input\\MalformAPDU.txt", ios_base::app);

		while (getline(infile, content)){
			outfile << content << "\n";
		}

		outfile.close();
		infile.close();
		return 0;
	}
	catch (exception e){
		cout << "Exception: " << e.what();
		return 0;
	}
}

int main(int argc, char** argv)
{
	printf("[+] %s() offset: 0x%x\n",__FUNCTION__,(char*)(*&test_target) - (char*)GetModuleHandleW(NULL));
    if(argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        
    }
    test_target(argv[1], argv[0]);
}
