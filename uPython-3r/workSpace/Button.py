import time 
 
while True:
   if polsador():
     print("The button is pressed.")
   else:
     print("The button is not pressed.")
   time.sleep(1)


