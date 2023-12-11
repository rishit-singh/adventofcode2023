import os
import sys


def GetGameSet(setString: str) -> dict[str, int]:
    if (len(setString) < 1):
        return None
    
    rgb: dict[str, int] = {
                "red": 0,
                "green": 0,
                "blue": 0
            }

    for string in setString[setString.find(":") + 1:len(setString)].split(';'):
        for color in string.split(","):
            split: list[str] = color.strip().split(' ')
            
            rgb[split[1]] = rgb[split[1]] + int(split[0])

    return rgb 
           


def IsPossible(gameSet: dict[str, int], max: dict[str, int]):
    return (gameSet["red"] <= max["red"] and gameSet["green"] <= max["green"] and gameSet["blue"] <= max["blue"])  

def LoadDataset(file: str) -> list[str]:
    with open(file, 'r') as fp:
        return [GetGameSet(s) for s in fp.read().split("\n")]

sum: int = 0

index: int = 1

dataset = LoadDataset(sys.argv[1])

dataset.remove(None)

for s in dataset:

    if (IsPossible(s, {"red": 12, "green": 13, "blue": 14})):
        sum += index

    index += 1

print(f"sum: {sum}")
