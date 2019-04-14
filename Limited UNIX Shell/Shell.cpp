/*Written by Kyle Henry
TAMU ECEN
02/2019
Implements a subset of the Bash commands in a terminal in UNIX
*/

#include "utils.h"
#include "commands.h"

int main() {
	cout << "===============MY SHELL===============" << endl;
	cout << "Created by Kyle Henry TAMU 2019 for CSCE 313" << endl;
	cout << "Please note that this implementation uses ANSI color codes. https://en.wikipedia.org/wiki/ANSI_escape_code" << endl;
	cout << "======================================" << endl;
	while (true) {
		cout << stop << endl;
		//print the working directory
		char workingDir[256];
		char userName[256];
		getcwd(workingDir, 256);
		getlogin_r(userName, 256);
		cout << RED << userName << ":" << CYAN << workingDir << RESET << "$ ";

		//get user input
		char command [256];
		cin.getline(command, 256);
		//get pipes
		vector<string> pipes = split(command, "|");
		
		//saving standard input and output
		int stdinSave = dup (0);
		int stdoutSave = dup (1);
		for (int i = 0; i < pipes.size(); i++) {
			//cout << pipes.at(i) << endl
			char** args = getargs(pipes[i]);
			if (is_Builtin(args)) {
				break;
			}
			int fd[2];
			pipe(fd);
			int pid = fork();
			if (pid == 0) {
				//children
				if (i < pipes.size() - 1)
					dup2(fd[1], 1);
				close(fd[1]);

				
				execvp(args[0], args);
			}
			else {
				//parent
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
				wait(0);
			}
			
		}
		//restore stdin and out to previous values
		dup2(stdinSave, 0);
		dup2(stdoutSave, 1);
		if (stop)
			return 0;
	}
	//user exits
	return 0;
}