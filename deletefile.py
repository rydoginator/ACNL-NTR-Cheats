#!/usr/bin/env Python

import sys
import ftplib
import datetime
from ftplib import FTP

# Usage:
# 	sendfile.py "filename" "ftppath" "host" "ip"

def printf(string):
	print(datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S') + " : " + string);

if __name__ == '__main__':
	print("");
	printf("FTP File Deleter\n")
	try:
		filename = sys.argv[1]
		path = sys.argv[2]
		host = sys.argv[3]
		port = sys.argv[4]

		ftp = FTP()
		printf("Connecting to " + host + ":" + port);
		ftp.connect(host, port);
		printf("Connected");

		printf("Moving to: ftp:/" + path);
		ftp.cwd(path);
		printf("Deleting file...");
		ftp.delete(filename);
		printf("Done")


		ftp.quit();
		printf("Disconnected");

	except IOError as e:
		printf("/!\ An error occured. /!\ ");

