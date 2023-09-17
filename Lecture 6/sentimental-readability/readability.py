import cs50



def main():
    my_text = cs50.get_string("Text: ")

    sentences = get_sentences(my_text)

    chars = get_char(my_text)

    words = len(my_text.split())

    L = chars / words * 100

    S = sentences / words * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)


    if index > 15:
        print("Grade 16+")
    elif index < 2:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def get_sentences(txt):
    return txt.count(".") + txt.count("?") + txt.count("!")


def get_char(txt):

    characters = 0

    for char in txt:
        if char.isalpha():
            characters += 1

    return characters

if __name__ == "__main__":
    main()