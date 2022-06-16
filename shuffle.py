from typing import List, Tuple

def split(deck: List[int]) -> Tuple[List[int], List[int]]:
    length = len(deck)
    odd = length & 1
    first_half = deck[:length // 2 + odd]
    second_half = deck[length // 2 + odd:]
    return first_half, second_half

def shuffle(deck: List[int]) -> List[int]:
    halves = split(deck)
    new_deck = []
    for i in range(len(deck)):
        new_deck.append(halves[i & 1][i // 2])

    return new_deck

def deck(size: int) -> List[int]:
    return list(range(size))


for i in range(2, 53):
    mydeck = deck(i)
    newdeck = shuffle(mydeck)
    count = 1
    while newdeck != mydeck:
        newdeck = shuffle(newdeck)
        count += 1
    print("{} cards: {} shuffles".format(i, count))
