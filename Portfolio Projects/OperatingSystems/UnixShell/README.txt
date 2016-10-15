Benjamin Cooper - BJC12b
Operating Systems - Assignment 1 - Tiny Shell

Design Overview: The project is designed functionally, calling either an Interactive, Help, or Script function based upon arguments from main. Main handles file opening and error checking so scipt(file) operates under the assumption that the file exists.

	Script parses through the file, creating a cstring "response" and then sending it to the process function for execution, as well as echo printing the response. Interactive operates similarly but waits for stdinput and takes in no argument for a file. Help prints the usage and returns.

	Process breaks down the command, first removing the newline, then parsing by ';' to break down each individual instruction. This is then parsed into another array based on whitespace, which proceeds to be fed into a forked process via execvp. Process then waits for all commands to be executed before returning a status "ret". ret is generally 1, unless Quit or EOF is read, which returns 0, indicating that processing should halt and the program should terminate.

Specifications: Blank space/no command semicolons are handled passively and generally discarded and ignored. Blank lines rebring up the prompt with no printed errors. Excessively long lines are greeted with a warning message and any characters exceeding the limit are discarded and then the rest are processed. Nonexistant commands are processed with an error message, the shell continues to run. Improper arguments prompt a usage message and terminatino. Nonexistant files prompt an error, along with usage message and termination.

Known Bugs or Problems: None.