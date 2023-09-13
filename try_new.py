import time
import re
curr_time=time.strftime("%H:%M:%S", time.localtime())
while curr_time.startswith("09")==False or curr_time.startswith("22")==False:
    curr_time = time.strftime("%H:%M:%S", time.localtime())
    with open("webpage.html") as f:
        data = f.readlines()
    # print(data)
    updation = []
    pattern = r"<h4>Last Updated at:"
    for i in data:
        if re.search(pattern, i) is not None:
            updation.append(f"{pattern}  {curr_time} </h4>\n")
        else:
            updation.append(i)
    with open("webpage.html", "w") as f:
        data = f.writelines(updation)
    refresh_time=30*60
    time.sleep(refresh_time)
