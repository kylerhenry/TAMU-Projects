#ifndef _COMMANDS_H_
#define _COMMANDS_H_


	#include "utils.h"

	bool is_Builtin(char** command_args);
	vector<string> split(char* str, char* tokens);
	char** getargs(string command);

	//list of built-in commands that need to run in current context
	vector<string> builtin_cmds{ "cd", "exit" };

	//specifier if the shell should terminate
	bool stop = false;

	bool is_Builtin(char** command_args) {
		for (int i = 0; i < builtin_cmds.size(); i++) {
			char* test = command_args[0];
			int j = 0;
			while (test != NULL) {
				//cout << test << endl;
				if (string(test) == builtin_cmds.at(i)) {
					//cout << "Detected built in command " << test << endl;
					//perform built-in command
					if (string(test) == builtin_cmds.at(0)) {
						//cout << "Changing directory to:" << command_args[1] << endl;
						chdir(command_args[1]);
					}
					else if (string(test) == builtin_cmds.at(1)) {
						stop = true;
					}
					return true;
				}
				j += 1;
				test = command_args[j];
			}
		}
		return false;
	}

	vector<string> split(char* str, char* tokens) {
		vector<string> results;
		char* pch = strtok(str, tokens);

		while (pch != NULL) {
			//check for escape chars
			results.push_back(string(pch));
			pch = strtok(NULL, tokens);
		}
		return results;
	}

	char** getargs(string command) {
		vector<string> args = split((char*)command.c_str(), " ");
		char** ptr = new char*[args.size() + 1];
		for (int i = 0; i < args.size(); i++) {
			ptr[i] = new char[256];
			strcpy(ptr[i], args[i].c_str());
		}
		ptr[args.size()] = 0;
		return ptr;
	}

#endif;