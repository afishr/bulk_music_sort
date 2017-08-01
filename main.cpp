#include <iostream>
#include <cstring>
#include <climits>
#include <dirent.h>
#include <windows.h>

using namespace std;

string songs[700];
int i = 0;

static int find_directory(const char*);
string get_artist(string);
string get_OS();


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	string command, last_artist = "", current_artist = "";
	string create_command = "mkdir", move_command;
	
	if (argc > 1)
	{
		find_directory(argv[1]);
		SetCurrentDirectory(argv[1]);
	}
	else
		find_directory ("./");
	
	 // <- it's for dev
	
	if (get_OS() == "Windows")
		move_command = "move";
	else
		move_command = "mv";
	
	
	for (int j = 0; j < i; j++)
	{
		current_artist = get_artist(songs[j]);
		if (current_artist != last_artist)
		{
			cout << songs[j] << endl;
			last_artist = current_artist;
			command = create_command + " \"" + current_artist + "\"";
			system(command.c_str());
			command = move_command + " \"" + songs[j] + "\" \"" + current_artist + "\\" + songs[j] + "\"";
			system(command.c_str());
		}
		else
		{
			cout << songs[j] << endl;
			command = move_command + " \"" + songs[j] + "\" \"" + current_artist + "\\" + songs[j] + "\"";
			system(command.c_str());
		}
	}
	
	cout << "Done";
	
	cin.sync();
	cin.get();
	return 0;
}

static int find_directory(const char *dirname)
{
	DIR *dir;
	char buffer[PATH_MAX + 2];
	char *p = buffer;
	const char *src;
	char *end = &buffer[PATH_MAX];
	int ok;
	
	/* Copy directory name to buffer */
	/*src = dirname;
	while (p < end  &&  *src != '\0') {
		*p++ = *src++;
	}
	*p = '\0';*/
	/* Open directory stream */
	dir = opendir (dirname);
	if (dir != NULL) {
		struct dirent *ent;
		
		/* Print all files and directories within the directory */
		while ((ent = readdir (dir)) != NULL) {
			char *q = p;
			//char c;
			
			/* Get final character of directory name */
			/*if (buffer < q) {
				c = q[-1];
			} else {
				c = ':';
			}
			
			*//* Append directory separator if not already there *//*
			if (c != ':'  &&  c != '/'  &&  c != '\\') {
				*q++ = '/';
			}*/
			
			/* Append file name */
			src = ent->d_name;
			while (q < end && *src != '\0') { //(*(src) != ' ' || *(src+1) != '-')
				*q++ = *src++;
			}
			*q = '\0';
			
			/* Decide what to do with the directory entry */
			switch (ent->d_type) {
				case DT_LNK:
				case DT_REG:
					/* Output file name with directory */
					songs[i] = buffer;
					i++;
					break;
				
				case DT_DIR:
					/* Scan sub-directory recursively */
					if (strcmp (ent->d_name, ".") != 0
					    &&  strcmp (ent->d_name, "..") != 0) {
						find_directory (buffer);
					}
					break;
				
				default:
					/* Ignore device entries */
					/*NOP*/;
			}
		}
		
		closedir (dir);
		ok = 1;
		
	} else {
		/* Could not open directory */
		printf ("Cannot open directory %s\n", dirname);
		ok = 0;
	}
	
	return ok;
}

string get_artist(string file)
{
	string artist;
	int k = 0;
	
	
	while (k < file.length() && (file[k] != ' ' || file[k+1] != '-'))
	{
		artist += file[k];
		k++;
	}
	
	return artist;
}

string get_OS()
{
#ifdef _WIN32
	return "Windows";
#elif _WIN64
	return "Windows";
#else
	return "Unix";
#endif
}