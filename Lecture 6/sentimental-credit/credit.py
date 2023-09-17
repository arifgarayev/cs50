import cs50
import sys

def get_digits_sum(num):
    length = len(str(num))
    sum = 0
    for digit in str(num):
        sum += int(digit)

    return sum

def checSum(number):
    counter = 0
    for i in range(len(str(number)) - 2, -1, -2):

        if len(str(int(str(number)[i]) * 2)) > 1:
            sum = get_digits_sum(int(str(number)[i]) * 2)
            counter += sum + int(str(number)[i + 1])
        else:
            counter += (int(str(number)[i]) * 2) + int(str(number)[i + 1])


    if len(str(number)) % 2 != 0:
        counter += int(str(number)[0])

    return counter % 10 == 0

def main():

    credit_card_number = cs50.get_int("Number: ")

    if len(str(credit_card_number)) < 13 or len(str(credit_card_number)) > 16:
        print("INVALID")
        sys.exit(1)

    if checSum(credit_card_number):
        if str(credit_card_number)[0] == '4':
            print("VISA")
            sys.exit(0)
        elif str(credit_card_number)[:2] in ("51", "52", "53", "54", "55"):
            print("MASTERCARD")
            sys.exit(0)
        elif str(credit_card_number)[:2] in ("34", "37"):
            print("AMEX")
            sys.exit(0)
        else:
            print("INVALID")
            sys.exit(1)
    else:
        print("INVALID")
        sys.exit(1)

if __name__ == "__main__":
    main()