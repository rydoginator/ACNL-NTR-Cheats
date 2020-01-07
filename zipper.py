import sys
import shutil
import os
import datetime
JAP_TID_LOW = 86200
D_ASCII = 68
FILE        = "ACNL-NTR-Cheats.3gx"
def printf(string):
    print(datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S') + " : " + string)
if not os.path.exists("plugin"):
    for i in range(0, 3):
        os.makedirs("plugin/luma/plugins/" + "00040000000" + str(JAP_TID_LOW + (i * 100)))
        os.makedirs("plugin/luma/plugins/" + "0004000000198" + chr(D_ASCII + i) + "00")
printf("Copying files into each folder")
for i in range(0, 3):
    shutil.copy2(FILE, "plugin/luma/plugins/" + "00040000000" + str(JAP_TID_LOW + (i * 100)) + "/" + FILE)
    shutil.copy2(FILE, "plugin/luma/plugins/" + "0004000000198" + chr(D_ASCII + i) + "00" + "/" + FILE)
shutil.make_archive("ACNL-NTR-Cheats", 'zip', r".\\plugin")
printf("Done!")
