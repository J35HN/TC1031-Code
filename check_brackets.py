# python3

from collections import namedtuple

from timeit import timeit

class bracket:
    def __init__(self,item, position):
        self.item = item
        self.position = position + 1

    def getItem(self):
        return self.item

    def getPosition(self):
        return self.position


#Bracket = namedtuple("Bracket", ["char", "position"])---------------------

def are_matching(left, right):
    return (left + right) in ["()", "[]", "{}"]

def find_mismatch(text):
    opening_brackets_stack = []
    deploySucces = False
    position = 0
    for i, next in enumerate(text):
        position= i + 1

        if next in "([{":
            # Process opening bracket, write your code here
            # print(next)
            # print(i)
            opening_brackets_stack.append(bracket(next,i))
            pass
        
        if next in ")]}":
            if opening_brackets_stack != []:
                top = opening_brackets_stack.pop()
                
                if top.getItem() == "{" and next == "}":
                    deploySucces = True
                elif top.getItem() == "[" and next == "]":
                    deploySucces = True
                elif top.getItem() == "(" and next == ")":
                    deploySucces = True
                else:
                    return i+1
            else:
                deploySucces = False
                return i+1
            # Process closing bracket, write your code here
            # print(next)
            # print(i)
            pass

    if opening_brackets_stack!=[]:
        deploySucces = False
        return opening_brackets_stack[0].getPosition()

    if deploySucces == True:
        return "Success"

def main():
    text = input()
    mismatch = find_mismatch(text)
    print(str(mismatch))
    # Printing answer, write your code here


if __name__ == "__main__":
   main()