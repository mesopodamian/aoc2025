file = open("input.txt", "r")

result = 0

# Part One

for line in file:
    firstMax = 0
    firstMaxIndex = 0
    lineStripped = line.strip()
    for i, char in enumerate(lineStripped[:-1]): # from line start until second to last char ( 234234234234278 => [23423423423427] 8 )
        digit = int(char)
        if (digit > firstMax):
            firstMax = digit
            firstMaxIndex = i
            
    secondMax = int(lineStripped[len(lineStripped)-1]) # from max digit until last char ( 234234234234278 => 2342342342342 [78] )
    for char in lineStripped[firstMaxIndex+1:]:
        digit = int(char)
        if (digit > secondMax):
            secondMax = digit
    
    result += int(str(firstMax) + str(secondMax))

print("What is the total output joltage?", result)

file.close()
