from typing import List, Tuple

def shuffle(deck: List[int]) -> list:
    length: int = len(deck)
    odd: int = length & 1
    first_half: List[int] = deck[:length // 2 + odd]
    second_half: List[int] = deck[length // 2 + odd:]
    halves: Tuple[List[int], List[int]] = first_half, second_half
    new_deck: List[int] = []
    for i in range(length):
        new_deck.append(halves[i & 1][i // 2])

    return new_deck

def deck(size: int) -> List[int]:
    return list(range(size))


for i in range(2, 53):
    mydeck: List[int] = deck(i)
    newdeck: List[int] = shuffle(mydeck)
    count: int = 1
    while newdeck != mydeck:
        newdeck = shuffle(newdeck)
        count += 1
    print("{} cards: {} shuffles".format(i, count))
