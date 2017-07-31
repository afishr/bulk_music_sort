#include <iostream>
#include <cstring>
#include <climits>
#include <dirent.h>

using namespace std;

static int find_directory(const char*);

int main()
{
	setlocale(LC_ALL, "Russian");
	find_directory ("E:\\Music\\##\\");
	
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
		
		int i = 0;
		
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
					printf ("%s\n", buffer);
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
			i++;
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