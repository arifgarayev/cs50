import cs50

while True:
    n = cs50.get_int("Height: ")

    if n > 0 and n < 9:
        break

hash = "#"

for i in range(1, n + 1):

    for j in range(n - i):

        print(" ", end="")

    print(hash * i, end="")
    print("  ", end="")
    print(hash * i)






"""
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
  ######  ######
 #######  #######
########  ########

"""