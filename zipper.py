import sys
import shutil
import datetime

EUR_TID     = "0004000000086400"
USA_TID     = "0004000000086300"
JAP_TID        = "0004000000086200"
FILE        = "ACNL-NTR-Cheats.plg"

def printf(string):
    print(datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S') + " : " + string);

printf("Copying files into each folder");
shutil.copy2(FILE, "plugin/" + EUR_TID + "/" + FILE)
shutil.copy2(FILE, "plugin/" + USA_TID + "/" + FILE)
shutil.copy2(FILE, "plugin/" + JAP_TID + "/" + FILE)
shutil.make_archive("ACNL-NTR-Cheats", 'zip', ".\plugin");
printf("Done!");
